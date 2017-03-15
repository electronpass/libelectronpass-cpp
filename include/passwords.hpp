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
#include <vector>

/**
 * @file passwords.hpp
 * @author Žiga Patačko Koderman <ziga.patacko@protonmail.com>
 * @brief Contains methods for random password generation and password strength evaluation.
 */

namespace electronpass {
    namespace passwords {
        /// Set of digits to include in random password generation .
        const std::string digits_list = "0123456789";
        /// Set of lowercase characters to include in random password generation.
        const std::string letters_list = "abcdefghijklmnopqrstuvwxyz";
        /// Set of uppercase characters to include in random password generation.
        const std::string uppercase_letters_list = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        /// Set of special characters/symbols to include in random password generation.
        const std::string special_chars_list = "!\"#$%&'()*+,-./:;<=>?@[\\]^_{|}";

        /// Vector including some bad phrases to be included in password.
        static const std::vector<std::string> bad_phrases = {
                "123", "234", "345",
                "567", "678", "789",
                "890", "101", "asdf",
        };

        /**
         * @brief Generates random password.
         * @param len Desired length of password.
         * @param digits Number of digits to be included.
         * @param symbols Number of symbols to be included.
         * @param uppercase Number of uppercase letters to be included.
         * @details Characters are randomly selected to fulfill len, digits and symbols respectively.
         * @details Lowercase letters are added at the end to match len parameter.
         * @details Characters are selected and shuffled using mt19937 algorithm and C++ device_random seed.
         * @return String of desired length.
         */
        std::string generate_random_pass(int len, int digits, int symbols, int uppercase);

        /**
         * @brief Evaluates password strength.
         * @param password Password to be inspected.
         * @return Double between 0 and 1 representing strength (0 is terribly bad, 1 is good).
         */
        double password_strength(std::string password);
    }
}


#endif //ELECTRONPASS_RANDOM_H
