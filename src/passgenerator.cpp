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

#include "passgenerator.hpp"
#include <random>
#include <functional>
#include <iostream>

// Seeds and obtains random int between min and max using mt19937 algorithm.
int true_random_int(int min, int max) {
    std::mt19937 prng;
    std::mt19937::result_type seed = std::random_device{}();
    prng.seed(seed);
    auto randGen = std::bind(std::uniform_int_distribution<int>(min, max),
                             std::mt19937(seed));
    return randGen();
}

// Rewrites string without n-th char and returns it.
std::string rm_char(std::string a, int n) {
    std::string result = "";
    for (int i = 0; i < (int) a.size(); i++) {
        if (i != n) result += a[i];
    }
    return result;
}

// Takes random characters from initial dataset according to numbers provided and shuffles them.
// If sum of len, digits and symbols is bigger than len, they are filled to fulfill settings respectively.
std::string electronpass::passgenerator::generate_pass(int len, int digits, int symbols, int uppercase) {
    // take random characters from initial ones
    std::string dataset = "";
    for (int i = 0; i < digits && (int) dataset.size() < len; ++i) {
        dataset += digits_list[true_random_int(0, digits_list.size() - 1)];
    }
    for (int i = 0; i < symbols && (int) dataset.size() < len; ++i) {
        dataset += special_chars_list[true_random_int(0, special_chars_list.size() - 1)];
    }
    for (int i = 0; i < uppercase && (int) dataset.size() < len; ++i) {
        dataset += uppercase_letters_list[true_random_int(0, uppercase_letters_list.size() - 1)];
    }
    for (int i = 0; i < len - (int) dataset.size(); ++i) {
        dataset += letters_list[true_random_int(0, letters_list.size() - 1)];
    }

    // shuffle dataset
    std::string result = "";
    while ((int) result.size() < len) {
        if (dataset.size() > 1) {
            // select random char and move it into result
            int i = true_random_int(0, dataset.size() - 1);
            result += dataset[i];
            dataset = rm_char(dataset, i);
        } else {
            // handle last remaining char case
            result += dataset;
            break;
        }
    }
    return result;
}
