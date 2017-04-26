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

#ifndef ELECTRONPASS_CRYPTO_HPP
#define ELECTRONPASS_CRYPTO_HPP

#include <sodium.h>
#include <string>

/**
 * @file crypto.hpp
 * @author Matej Marinko <matejmarinko123@gmail.com>
 * @brief Defined encryption and decryption functions.
 */

namespace electronpass {
    //// All chars in Base64.
    static const std::string BASE64_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    // Salt used for generating encryption keys.
    static const unsigned char CRYPTO_SALT[crypto_pwhash_scryptsalsa208sha256_SALTBYTES] = {  // 32 bytes
        0xf4, 0x78, 0x2a, 0x93, 0x4c, 0x56, 0xb8, 0xd9,
        0xfb, 0x66, 0xca, 0xb6, 0x43, 0x31, 0xb8, 0xd9,
        0xb5, 0x78, 0x33, 0x96, 0xaa, 0xbf, 0xb8, 0x01,
        0xfb, 0x90, 0xca, 0x02, 0x4c, 0x31, 0xa6, 0x11
    };

    /// Class for cryptographics functions and helper functions.
    class Crypto {
      private:

        // Key for encryption
        unsigned char key[crypto_box_SEEDBYTES];  // 32 bytes
        // if key was generated from password, if libsodium init was successful
        bool sodium_success = false;

        // Generates key from sha256 hash of password.
        bool generate_key(const char *password, unsigned int pass_len);

      public:

        /**
         * @brief Constructor
         * @param password Password, from which encryption key will be generated.
         */
        Crypto(std::string password);

        /**
         * @brief Encrypts plain text.
         * We use ChaCha20-Poly1305 authenticated encryption algorithm, implemented in library libsodium.
         * @param plain_text String, which will be encrypted.
         * @param success If encryption was successful. See also check().
         * @return Encrypted plain text, already converted to Base64. If encrypton wasn't successful
         * returns empty string.
         */
        std::string encrypt(const std::string& plain_text, bool& success);

        /**
         * @brief Decrypts Base64 encoded cipher text.
         * We use ChaCha20-Poly1305 authenticated encryption algorithm, implemented in library libsodium.
         * @param cipher_text Base64 encoded string, which will be encrypted.
         * @param success True if message was decoded from cipher text, false otherwise.
         * @return Decrypted text if decrypting was successful. If not, empty string ("").
         */
        std::string decrypt(const std::string& cipher_text, bool& success);

        /**
         * @brief Checks if Crypto initialization was successful.
         * Initialization consist of:
         * - libsodium initialization (checks system random)
         * - generating key from password (sha256 salted hashing)
         * @returns true if everything was ok, otherwise false.
         */
        bool check();

        /**
         * @brief Function for encoding to Base64.
         * @param s String, which will be encoded in Base64.
         * @return Encoded string.
         */
        static std::string base64_encode(const std::string& s);

        /**
         * @brief Function for decoding from Base64.
         * @param s String, which will be decoded from Base64.
         * @return Decoded string.
         */
        static std::string base64_decode(const std::string& s);

        /**
         * @brief Generate UUID used for identifying items.
         * @return UUID
         */
        // TODO: tests
        static std::string generate_uuid();
    };
}


#endif // ELECTRONPASS_CRYPTO_HPP
