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

#include "crypto.hpp"
#include <string.h>
#include <string>
#include <cassert>
#include <iostream>


electronpass::Crypto::Crypto(std::string password) {
    bool part_success = false;
    if (sodium_init() != -1) part_success = true;

    unsigned int password_len = password.length();
    char *password_char = new char[password_len];

    strcpy(password_char, password.c_str());
    part_success &= generate_key(password_char, password_len);
    sodium_success = part_success;

    delete[] password_char;
}


bool electronpass::Crypto::generate_key(const char* password, unsigned int password_len) {
    if (crypto_pwhash_scryptsalsa208sha256(key, sizeof key, password, password_len, CRYPTO_SALT,
            crypto_pwhash_scryptsalsa208sha256_OPSLIMIT_INTERACTIVE,
            crypto_pwhash_scryptsalsa208sha256_MEMLIMIT_INTERACTIVE) != 0) {
        return false;
    }
    return true;
}

std::string electronpass::Crypto::encrypt(const std::string& plain_text, bool& success) {
    if (!check()) {
        success = false;
        return "";
    }
    const unsigned int message_len = plain_text.length();
    unsigned char *message = new unsigned char[message_len];

    // the idea is that we could save encoding / length / metadata ... in additional_data.
    const unsigned int additional_data_len = 0;
    const unsigned char *additional_data = {};

    strcpy(reinterpret_cast<char*>(message), plain_text.c_str());

    unsigned char *cipher_text = new unsigned char[message_len + crypto_aead_chacha20poly1305_ABYTES];
    unsigned long long cipher_text_len;

    success = (crypto_aead_chacha20poly1305_encrypt(cipher_text, &cipher_text_len, message, message_len,
        additional_data, additional_data_len, NULL, CRYPTO_NONCE, key) == 0);

    delete[] message;

    if (!success) {
        delete[] cipher_text;
        return "";
    }

    std::string cipher(cipher_text_len, '/');  // '/' is just a random char, which will be overwritten
    for (unsigned long long i; i < cipher_text_len; ++i) cipher[i] = cipher_text[i];
    delete[] cipher_text;

    cipher = base64_encode(cipher);

    return cipher;
}

std::string electronpass::Crypto::decrypt(const std::string& base64_cipher_text, bool& success) {
    std::string cipher_text = base64_decode(base64_cipher_text);

    const unsigned int cipher_text_len = cipher_text.length();
    unsigned char *cipher = new unsigned char[cipher_text_len];

    // ADDITIONAL_DATA
    unsigned int additional_data_len = 0;
    unsigned char *additional_data = {};  // need to allocate memory if we will use this

    strcpy(reinterpret_cast<char*>(cipher), cipher_text.c_str());
    cipher_text.clear();

    unsigned char *plain_text = new unsigned char[cipher_text_len];
    unsigned long long plain_text_len;

    int neki = crypto_aead_chacha20poly1305_decrypt(plain_text, &plain_text_len, NULL,
                                                    cipher, cipher_text_len, additional_data,
                                                    additional_data_len, CRYPTO_NONCE, key);
    std::cout << neki << std::endl;
    success = neki == 0;
    delete[] cipher;

    if (!success) {
        delete[] plain_text;
        return "";
    }

    std::string plain(plain_text_len, '/');
    for (unsigned long long i; i < plain_text_len; ++i) plain[i] = plain_text[i];
    delete[] plain_text;

    return plain;
}

bool electronpass::Crypto::check() {
    return sodium_success;
}
