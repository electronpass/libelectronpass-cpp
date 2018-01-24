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

/// Size of key used for AES 256 encryption.
#define KEY_SIZE CryptoPP::AES::MAX_KEYLENGTH
/// Size of block used for AES 256 encryption.
#define AES_BLOCKSIZE CryptoPP::AES::BLOCKSIZE

/**
 * @file crypto.hpp
 * @authors Matej Marinko <matejmarinko123@gmail.com>
 * @authors Vid Drobnič <vid.drobnic@gmail.com>
 * @brief Defined encryption and decryption functions.
 */

namespace electronpass {
    /// Salt used for AES key generation.
    static const std::string KEY_SALT = "wwT>y\\x06f\\x19=\\x19RZt\\x11hpoy\\x052 H?\\x1b\\x0eM.\\n\\x000~([\\x17^\\x03ER,\\x15K:\\x1b)\\x01\\x01`{g\\x10\\x0eX\\x1e\\x18\\x14\\x12\\x02G\\t+\\x1d|Wz";

    /// Class for cryptographic functions and helper functions.
    class Crypto {
    private:
        // Key for encryption
        CryptoPP::byte key[KEY_SIZE];
    public:

        /**
         * @brief Constructor
         * @param password Password, from which encryption key will be generated.
         */
        Crypto(const std::string &password);

        /**
         * @brief Encrypts plain text.
         * We use AES256 authenticated encryption algorithm, implemented in library crypto++.
         * @param plain_text String, which will be encrypted.
         * @return Encrypted plain text, already converted to Base64.
         */
        std::string encrypt(const std::string &plain_text) const;

        /**
         * @deprecated Encrypts plain text.
         * @param plain_text String, which will be encrypted.
         * @param success parameter, used only for backwards compatibility (can be omitted). Should be always true.
         * @return Encrypted plain text, already converted to Base64.
         */
        std::string encrypt(const std::string &plain_text, bool &success) const;

        /**
         * @brief Decrypts Base64 encoded cipher text.
         * We use AES256 authenticated encryption algorithm, implemented in library crypto++.
         * @param cipher_text Base64 encoded string, which will be deencrypted.
         * @param success True if message was decoded from cipher text, false otherwise.
         * @return Decrypted text if decrypting was successful. If not, empty string ("").
         */
        std::string decrypt(const std::string &cipher_text, bool &success) const;

        /**
         * @brief Generate random UUID used for identifying items.
         * @return UUID
         */
        static std::string generate_uuid();
    };
}


#endif // ELECTRONPASS_CRYPTO_HPP
