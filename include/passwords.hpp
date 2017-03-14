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

#ifndef SRC_PASSGENERATOR_HPP_
#define SRC_PASSGENERATOR_HPP_

#include <string>

namespace electronpass {
    namespace passwords {
        // Set of characters to include when generating passwords
        static const std::string digits_list = "0123456789";
        static const std::string letters_list = "abcdefghijklmnopqrstuvwxyz";
        static const std::string uppercase_letters_list = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        static const std::string special_chars_list = "!\"#$%&'()*+,-./:;<=>?@[\\]^_{|}";

        std::string generate_random_pass(int len, int digits, int symbols, int uppercase);
    }
}


#endif //ELECTRONPASS_RANDOM_H
