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

#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/err.h>

#include <string>

/**
 * @file crypto.hpp
 * @author Matej Marinko <matejmarinko123@gmail.com>
 * @brief Defined encryption and decryption functions.
 */

namespace electronpass {
    /** @brief All chars in Base64. */
    static const std::string BASE64_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    /// Class for cryptographics functions and helper functions.
    class Crypto {
      private:
        unsigned char aes_key[32], aes_iv[16];
        bool keys_generated = false;

        bool generate_keys(const unsigned char *password, int pass_len);

      public:

        /**
         * @brief Constructor. Creates AES keys from password.
         * Use Crypto.check_keys() before encryption.
         * @param password password string.
         */
        Crypto(std::string password);

        /**
         * @brief AES 256 cbc encryption implementation.
         * We use OpenSSL library fron encryption.
         *
         * Error codes:
         * - 0: success
         * - 1: check_keys() returned false
         * - 2: encrypt init failed
         * - 3: encrypt update failed
         * - 4: encrypt final failed
         *
         * Encrypted string is converted to Base64 and then returned.
         * @param plain_text Input string, which will be encrypted.
         * @param error Integer in where error will be stored.
         * @return encrypted plain_text.
         */
        std::string aes_encrypt(const std::string& plain_text, int& error);

        /**
         * @brief AES 256 cbc decryption implementation with.
         * We use OpenSSL library fron encryption.
         *
         * Error codes:
         * - 0: success
         * - 1: check_keys() returned false
         * - 2: encrypt init failed
         * - 3: encrypt update failed
         * - 4: encrypt final failed
         *
         * @param cipher_text Input string in Base64, which will be converted to unsigned char* and decrypted.
         * @param error Integer in where error will be stored.
         * @return decrypted cipher text.
         */
        std::string aes_decrypt(const std::string& cipher_text, int& error);

        /**
         * @brief Check if key generating was successful.
         * @return true if keys were generated and false otherwise.
         */
        bool check_keys();


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
    };
}


#endif // ELECTRONPASS_CRYPTO_HPP
