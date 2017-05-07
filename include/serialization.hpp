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

#ifndef ELECTRONPASS_SERIALIZATION_HPP
#define ELECTRONPASS_SERIALIZATION_HPP

#include <string>
#include <vector>

#include "json/json.h"
#include "json/json-forwards.h"
#include "wallet.hpp"
#include "crypto.hpp"

/**
 * @file serialization.hpp
 * @author Vid Drobnič <vid.drobnic@gmail.com>
 * @brief Defined serialization functions for serialization and deserialization of JSON data.
 */

namespace electronpass {
    /**
     * @brief Functions for serialization and deserialization of JSON data.
     */
    namespace serialization {
        /**
         * @brief Deserialize JSON data and create Wallet object from it.
         *
         * @param json JSON to deserialize.
         * @return Wallet object generated from JSON data.
         */
        electronpass::Wallet deserialize(const std::string& json);

        /**
         * @brief Serialize Wallet object to JSON data.
         *
         * @param wallet Wallet to serialize.
         * @return JSON string.
         */
        std::string serialize(const Wallet& wallet);

        /**
         * @brief Loads wallet object from disk data.
         *
         * Error codes:
         *
         * - 0: success
         * - 1: could not decrypt data
         * - 2: invalid json
         *
         * **Note:** for now version is ignored. Will change in the future.
         *
         * @param data Data stored on disk
         * @param crypto Crypto object used for encryption
         * @param error Error that has occurred
         * @return Wallet object
         */
        electronpass::Wallet load(const std::string &data, const Crypto &crypto, int &error);

        /**
         * @brief Converts wallet to json that can be saved on disk.
         * @param wallet Wallet to save
         * @param crypto Crypto object used for encryption
         * @param success Set to true if successful, otherwise false
         * @return JSON that can be saved to disk
         */
        std::string save(const Wallet &wallet, const Crypto &crypto, bool &success);
    }
}



#endif //ELECTRONPASS_SERIALIZATION_HPP
