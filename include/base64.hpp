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
 * @brief Functions for Base63 encoding and decoding.
 */

namespace electronpass {
    namespace crypto {

        /**
         * @brief Function for encoding to Base64.
         * @param bytes Input bytes, which will be converted to Base64 string.
         * @return Base64 string.
         */
        std::string base64_encode(const unsigned char* bytes);

        /**
         * @brief Function for decoding from Base64.
         * @param base64_string String, which will be decoded from Base64.
         * @param bytes Char buffer where decoded bytes, will be saved. Needs to be large enough.
         * @return Number of characters written in bytes buffer.
         */
        int base64_decode(const std::string& base64_string, unsigned char* bytes);

        /**
         * @brief Calculates informative length of decoded string in Base64.
         * Length will be for sure large enough, but can be larger than the actual decoded length.
         * @param length Length of string encoded in Base64.
         * @return Informative length of decoded string.
         */
        int base64_decoded_length(int length);
    }
}


#endif // ELECTRONPASS_BASE64_HPP
