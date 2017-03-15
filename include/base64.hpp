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

#ifndef ELECTRONPASS_BASE64_HPP
#define ELECTRONPASS_BASE64_HPP

#include <string>

/**
 * @file base64.hpp
 * @author Matej Marinko <matejmarinko123@gmail.com>
 * @brief Functions for Base64 encoding and decoding.
 */

namespace electronpass {
    namespace crypto {

        /** @brief All chars in Base64. */
        static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

        /**
         * @brief Function for encoding to Base64.
         * @param s String, which will be encoded in Base64.
         * @return Encoded string.
         */
        std::string base64_encode(const std::string& s);

        /**
         * @brief Function for decoding from Base64.
         * @param s String, which will be decoded from Base64.
         * @return Decoded string.
         */
        std::string base64_decode(const std::string& s);

    }
}


#endif // ELECTRONPASS_BASE64_HPP
