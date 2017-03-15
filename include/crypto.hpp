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

    /// @brief Namespace for cryptographics functions and helper functions.
    namespace crypto {

        /**
         * @brief AES 256 cbc encryption implementation.
         * We use OpenSSL library fron encryption.
         * Encrypted string is converted to Base64 and then returned.
         * @param plain_text Input string, which will be encrypted.
         * @param password Password from which will be generated aes key and initialization vector.
         * @return encrypted plain_text.
         */
        std::string aes_encrypt(const std::string& plain_text, const std::string& password);

        /**
         * @brief AES 256 cbc decryption implementation with.
         * We use OpenSSL library fron encryption.
         * @param cipher_text Input string in Base64, which will be converted to unsigned char* and decrypted.
         * @param password Password from which will be generated aes key and initialization vector.
         * @return decrypted cipher text.
         */
        std::string aes_decrypt(const std::string& cipher_text, const std::string& password);
    }
}


#endif // ELECTRONPASS_CRYPTO_HPP
