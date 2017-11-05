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

#include "cryptopp/aes.h"
#include "cryptopp/sha.h"
#include "cryptopp/iterhash.h"
#include "cryptopp/filters.h"
#include "cryptopp/osrng.h"
#include "cryptopp/base64.h"
#include "cryptopp/ccm.h"
#include <string>
#include <cassert>

#define KEY_SIZE CryptoPP::AES::MAX_KEYLENGTH
#define AES_BLOCKSIZE CryptoPP::AES::BLOCKSIZE

/**
 * @file crypto.hpp
 * @authors Matej Marinko <matejmarinko123@gmail.com>
 * @authors Vid Drobnič <vid.drobnic@gmail.com>
 * @brief Defined encryption and decryption functions.
 */

namespace electronpass {
    //// All chars in Base64.
    static const std::string BASE64_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    static const std::string KEY_SALT = "electronpass salt";  // TODO: set salt

    /// Class for cryptographics functions and helper functions.
    class Crypto {
      private:
        // Key for encryption
        byte key[KEY_SIZE];
      public:

        /**
         * @brief Constructor
         * @param password Password, from which encryption key will be generated.
         */
        Crypto(std::string password);

        /**
         * @brief Encrypts plain text.
         * We use AES256 authenticated encryption algorithm, implemented in library crypto++.
         * @param plain_text String, which will be encrypted.
         * @param success If encryption was successful. See also check().
         * @return Encrypted plain text, already converted to Base64. If encryption wasn't successful
         * returns empty string.
         */
        std::string encrypt(const std::string& plain_text, bool& success) const;

        /**
         * @brief Decrypts Base64 encoded cipher text.
         * We use AES256 authenticated encryption algorithm, implemented in library crypto++.
         * @param cipher_text Base64 encoded string, which will be deencrypted.
         * @param success True if message was decoded from cipher text, false otherwise.
         * @return Decrypted text if decrypting was successful. If not, empty string ("").
         */
        std::string decrypt(const std::string& cipher_text, bool& success) const;

        /**
         * @brief Generate UUID used for identifying items.
         * @return UUID
         */
        static std::string generate_uuid();
    };
}


#endif // ELECTRONPASS_CRYPTO_HPP
