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

electronpass::Crypto::Crypto(const std::string &password) {
    // Generate key from password using SHA256 hash.
    CryptoPP::SHA256 sha256;
    CryptoPP::StringSource string_source(password + KEY_SALT, true,
                                         new CryptoPP::HashFilter(sha256,
                                                                  new CryptoPP::ArraySink(key,
                                                                                          static_cast<size_t>(KEY_SIZE))));
}

std::string electronpass::Crypto::encrypt(const std::string &plain_text) const {
    // Generate random IV.
    CryptoPP::AutoSeededRandomPool random_pool;
    CryptoPP::byte iv[AES_BLOCKSIZE];
    random_pool.GenerateBlock(iv, sizeof(iv));

    CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encryption;
    encryption.SetKeyWithIV(key, static_cast<size_t >(KEY_SIZE), iv);

    // Allocate memory for cipher text
    unsigned long encrypted_size = (plain_text.size() / AES_BLOCKSIZE + 1) * AES_BLOCKSIZE;
    auto encrypted_bytes = new CryptoPP::byte[encrypted_size];  // Can't allocate on stack because of the standard

    // Put plain text into encryption algorithm.
    CryptoPP::StringSource source(plain_text, true,
                                  new CryptoPP::StreamTransformationFilter(encryption,
                                                                           new CryptoPP::ArraySink(encrypted_bytes,
                                                                                                   encrypted_size),
                                                                           CryptoPP::StreamTransformationFilter::PKCS_PADDING));
    // Generate signature (hash for authentication).
    CryptoPP::SHA256 sha256;

    CryptoPP::HashFilter hash_filter(sha256);
    hash_filter.Put(encrypted_bytes, encrypted_size);
    hash_filter.Put(key, static_cast<size_t >(KEY_SIZE));
    hash_filter.MessageEnd();

    CryptoPP::byte signature[CryptoPP::SHA256::DIGESTSIZE];
    hash_filter.Get(signature, static_cast<size_t >(CryptoPP::SHA256::DIGESTSIZE));

    // Convert encrypted_bytes to Base64, add signature and IV.
    CryptoPP::Base64Encoder encoder(nullptr, false);
    encoder.Put(encrypted_bytes, encrypted_size);
    encoder.Put(signature, static_cast<size_t >(CryptoPP::SHA256::DIGESTSIZE));
    encoder.Put(iv, static_cast<size_t >(AES_BLOCKSIZE));
    encoder.MessageEnd();

    unsigned long encrypted_message_size = encoder.MaxRetrievable();
    std::string encrypted_message;
    encrypted_message.resize(encrypted_message_size);
    encoder.Get((CryptoPP::byte *) encrypted_message.data(), encrypted_message_size);

    delete[] encrypted_bytes;

    return encrypted_message;
}

// Function used for backwards compatibility.
std::string electronpass::Crypto::encrypt(const std::string &plain_text, bool &success) const {
    success = true;
    return encrypt(plain_text);
}

std::string electronpass::Crypto::decrypt(const std::string &base64_cipher_text, bool &success) const {
    // Decode cipher_text from Base64.
    CryptoPP::Base64Decoder decoder;
    decoder.Put((CryptoPP::byte *) base64_cipher_text.data(), base64_cipher_text.size());
    decoder.MessageEnd();

    unsigned long message_byte_size = decoder.MaxRetrievable();
    auto message_bytes = new CryptoPP::byte[message_byte_size];
    decoder.Get(message_bytes, message_byte_size);

    // Calculate where starts signature and IV.
    unsigned long iv_beginning = message_byte_size - AES_BLOCKSIZE;
    unsigned long signature_beginning = iv_beginning - CryptoPP::SHA256::DIGESTSIZE;

    // Retrieve IV
    CryptoPP::byte iv[AES_BLOCKSIZE];
    for (unsigned long i = 0; i < AES_BLOCKSIZE; ++i) {
        iv[i] = message_bytes[i + iv_beginning];
    }

    // Retrieve signature
    CryptoPP::byte signature[CryptoPP::SHA256::DIGESTSIZE];
    for (unsigned long i = 0; i < CryptoPP::SHA256::DIGESTSIZE; ++i) {
        signature[i] = message_bytes[i + signature_beginning];
    }

    // Retrieve cipher text
    unsigned long encrypted_bytes_size = signature_beginning;
    auto encrypted_bytes = new CryptoPP::byte[encrypted_bytes_size];
    for (unsigned long i = 0; i < signature_beginning; ++i) encrypted_bytes[i] = message_bytes[i];

    delete[] message_bytes;

    // Generate signature
    CryptoPP::byte generated_signature[CryptoPP::SHA256::DIGESTSIZE];

    CryptoPP::SHA256 sha256;
    CryptoPP::HashFilter hash_filter(sha256);
    hash_filter.Put(encrypted_bytes, encrypted_bytes_size);
    hash_filter.Put(key, static_cast<size_t >(KEY_SIZE));
    hash_filter.MessageEnd();

    hash_filter.Get(generated_signature, static_cast<size_t >(CryptoPP::SHA256::DIGESTSIZE));

    // Check if signatures are equal.
    bool signatures_match = true;
    for (int i = 0; i < CryptoPP::SHA256::DIGESTSIZE; ++i) {
        if (signature[i] != generated_signature[i]) {
            signatures_match = false;
            break;
        }
    }

    // If signatures do not match -> key is incorrect
    if (!signatures_match) {
        delete[] encrypted_bytes;
        success = false;
        return "";
    }

    // Actual decryption.
    std::string decrypted_string;
    CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption decryption;
    decryption.SetKeyWithIV(key, static_cast<size_t >(KEY_SIZE), iv);

    CryptoPP::ArraySource decryption_source(encrypted_bytes, encrypted_bytes_size, true,
                                            new CryptoPP::StreamTransformationFilter(decryption,
                                                                                     new CryptoPP::StringSink(
                                                                                             decrypted_string),
                                                                                     CryptoPP::StreamTransformationFilter::PKCS_PADDING));

    delete[] encrypted_bytes;

    success = true;
    return decrypted_string;
}

std::string electronpass::Crypto::generate_uuid() {
    // Generates random UUID.
    const unsigned int uuid_size = 24; // Bytes
    unsigned char uuid[uuid_size];
    CryptoPP::AutoSeededRandomPool random_pool;
    random_pool.GenerateBlock(uuid, uuid_size);

    std::string uuid_string;
    CryptoPP::ArraySource encoder(uuid, uuid_size, true,
                                  new CryptoPP::Base64Encoder(new CryptoPP::StringSink(uuid_string), false));

    return uuid_string;
}
