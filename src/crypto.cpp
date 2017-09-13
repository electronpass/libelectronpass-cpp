/*
This file is part of libelectronpass.

Libelectronpass is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Libelectronpass is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with libelectronpass.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "electronpass/crypto.hpp"

electronpass::Crypto::Crypto(std::string password) {
    bool part_success = false;
    // Sodium init returns 0 if everything is ok and 1 if sodium was already initialized.
    if (sodium_init() != -1) part_success = true;

    unsigned int password_len = static_cast<unsigned int>(password.length());
    char *password_char = new char[password_len];

    for (unsigned int i = 0; i < password_len; ++i) password_char[i] = password[i];

    part_success &= generate_key(password_char, password_len);
    sodium_success = part_success;

    delete[] password_char;
}


bool electronpass::Crypto::generate_key(const char* password, unsigned int password_len) {
    // Generates 32 bytes key for encryption.
    // Salt is a constant, but we are generating a random nonce for every encrypton.
    return crypto_pwhash_scryptsalsa208sha256(key, sizeof key, password, password_len, CRYPTO_SALT,
                                              crypto_pwhash_scryptsalsa208sha256_OPSLIMIT_INTERACTIVE,
                                              crypto_pwhash_scryptsalsa208sha256_MEMLIMIT_INTERACTIVE) == 0;
}

std::string electronpass::Crypto::encrypt(const std::string& plain_text, bool& success) const {
    if (!check()) {
        success = false;
        return "";
    }
    // Convert std::string to unsigned char array.
    const unsigned int message_len = static_cast<const unsigned int>(plain_text.length());
    unsigned char *message = new unsigned char[message_len];

    // Copy string with for loop, just in case there is a '\0' char in plain_text.
    for (unsigned int i = 0; i < message_len; ++i) message[i] = static_cast<unsigned char>(plain_text[i]);

    // Allocate memory for encrypted message.
    // Additional ChaCha20 - Poly1305 bytes are needed for authentication.
    unsigned char *cipher_text = new unsigned char[message_len + crypto_aead_chacha20poly1305_ABYTES];
    unsigned long long cipher_text_len;

    // Generate random nonce. It will be added at the beginning of encrypted data.
    // (Same nonce should never be reused with same key, that's why we are generating a random one.)
    unsigned int nonce_size = crypto_aead_chacha20poly1305_NPUBBYTES;  // 8 bytes
    unsigned char *nonce = new unsigned char[nonce_size];
    randombytes_buf(nonce, sizeof nonce);

    // Actual encryption.
    success = (crypto_aead_chacha20poly1305_encrypt(cipher_text, &cipher_text_len,
                                                    message, message_len,
                                                    nullptr, 0, nullptr, nonce, key) == 0);

    delete[] message;

    if (!success) {
        // probably key was not generated or system random is not actual random.
        delete[] cipher_text;
        delete[] nonce;
        return "";
    }

    // '/' is just a random char, which will be overwritten
    // At the beginning of the string will be stored nonce and behind it encrypted message.
    std::string cipher(nonce_size + cipher_text_len, '/');

    for (unsigned int i = 0; i < nonce_size; ++i) cipher[i] = nonce[i];
    delete[] nonce;
    for (unsigned long long i = 0; i < cipher_text_len; ++i) cipher[i + nonce_size] = cipher_text[i];
    delete[] cipher_text;

    // encode everything in Base64 for better portability...
    cipher = base64_encode(cipher);

    return cipher;
}

std::string electronpass::Crypto::decrypt(const std::string& base64_cipher_text, bool& success) const {
    if (!check()) {
        success = false;
        return "";
    }
    // Convert from Base64.
    std::string cipher_text = base64_decode(base64_cipher_text);

    // Get nonce from beginning of cipher_text.
    unsigned int nonce_size = crypto_aead_chacha20poly1305_NPUBBYTES;  // 8 bytes
    unsigned char *nonce = new unsigned char[nonce_size];

    if (cipher_text.length() < nonce_size) {
        success = false;
        return "";
    }
    
    for (unsigned int i = 0; i < nonce_size; ++i) nonce[i] = static_cast<unsigned char>(cipher_text[i]);

    // Convert std::string to unsigned char array.
    // New length will be smaller, because we won't copy first nonce_size bytes (8 bytes).
    const unsigned int cipher_text_len = static_cast<const unsigned int>(cipher_text.length() - nonce_size);
    unsigned char *cipher = new unsigned char[cipher_text_len];

    for (unsigned int i = 0; i < cipher_text_len; ++i) cipher[i] = static_cast<unsigned char>(cipher_text[i + nonce_size]);
    // delete string here, because it might be quite large and we are later allocating additional memory.
    cipher_text.clear();

    // Allocate memory.
    unsigned char *plain_text = new unsigned char[cipher_text_len - crypto_aead_chacha20poly1305_ABYTES];
    unsigned long long plain_text_len;

    // Actual encryption.
    success = (crypto_aead_chacha20poly1305_decrypt(plain_text, &plain_text_len, nullptr,
                                                    cipher, cipher_text_len,
                                                    nullptr, 0, nonce, key) == 0);
    delete[] cipher;
    delete[] nonce;

    if (!success) {
        // Probably authentication had failed.
        // Also possible that key was not generated or that sodium was not initialized.
        delete[] plain_text;
        return "";
    }

    // '/' is just a random char, which will be overwritten
    // Need to copy in for loop because otherwise '\0' would terminate copying.
    std::string plain(plain_text_len, '/');

    for (unsigned long long i = 0; i < plain_text_len; ++i) plain[i] = plain_text[i];
    delete[] plain_text;

    return plain;
}

bool electronpass::Crypto::check() const {
    return sodium_success;
}

std::string electronpass::Crypto::generate_uuid() {
    assert(sodium_init() != -1);

    const unsigned int uuid_size = 24; // Bytes
    unsigned char uuid[uuid_size];
    randombytes_buf(uuid, uuid_size);

    std::string uuid_str(uuid_size, '/');
    for (unsigned long long i = 0; i < uuid_size; ++i) uuid_str[i] = uuid[i];
    uuid_str = Crypto::base64_encode(uuid_str);

    return uuid_str;
}
