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

#include "passwords.hpp"
#include <random>
#include <functional>
#include <iostream>
#include <algorithm>
#include <set>
#include <cassert>

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
    for (int i = 0; i < static_cast<int>(a.size()); i++) {
        if (i != n) result += a[i];
    }
    return result;
}

// counts number of occurrences of string b in string a
int number_of_occurrences(std::string a, std::string b) {
    int occurrences = 0;
    std::string::size_type start = 0;

    while ((start = a.find(b, start)) != std::string::npos) {
        ++occurrences;
        start += b.length();
    }
    return 0;
}

std::string electronpass::passwords::generate_random_pass(int len, int digits, int symbols, int uppercase) {
    // take random characters from initial ones
    std::string dataset = "";
    for (int i = 0; i < digits && static_cast<int>(dataset.size()) < len; ++i) {
        dataset += digits_list[true_random_int(0, digits_list.size() - 1)];
    }
    for (int i = 0; i < symbols && static_cast<int>(dataset.size()) < len; ++i) {
        dataset += special_chars_list[true_random_int(0, special_chars_list.size() - 1)];
    }
    for (int i = 0; i < uppercase && static_cast<int>(dataset.size()) < len; ++i) {
        dataset += uppercase_letters_list[true_random_int(0, uppercase_letters_list.size() - 1)];
    }
    while (len > static_cast<int>(dataset.size())){
        dataset += letters_list[true_random_int(0, letters_list.size() - 1)];
    }

    // shuffle dataset
    std::string result = "";
    while (static_cast<int>(result.size()) < len) {
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

std::string electronpass::passwords::generate_random_pass(int len) {
    std::string dataset = letters_list + digits_list + special_chars_list + uppercase_letters_list;
    std::string result = "";
    for (int i = 0; i < len; i++) {
        result += dataset[true_random_int(0, dataset.size() - 1)];
    }
    return result;
}


electronpass::passwords::strength_category electronpass::passwords::double_to_password_strength(double d) {
    if (d < 0.002) return strength_category::TERRIBLE;
    else if (d < 0.005) return strength_category::BAD;
    else if (d < 0.05) return strength_category::MODERATE;
    else if (d < 0.7) return strength_category::GOOD;
    else return strength_category::VERY_STRONG;
}

std::string electronpass::passwords::password_strength_category_to_str(strength_category e) {
    switch (e) {
        case strength_category::TERRIBLE:
            return "terrible";
        case strength_category::BAD:
            return "bad";
        case strength_category::MODERATE:
            return "moderate";
        case strength_category::GOOD:
            return "good";
        case strength_category::VERY_STRONG:
            return "very strong";
    }
    assert(false && "No such enum state!");
}

double electronpass::passwords::password_strength(std::string password) {
    std::set<char> all_chars = {};
    int digits = 0;
    int lowercase = 0;
    int uppercase = 0;
    int symbols = 0;
    for (char a : password) {
        all_chars.insert(a);

        if (digits_list.find(a) != std::string::npos) {
            digits++;
        } else if (letters_list.find(a) != std::string::npos) {
            lowercase++;
        } else if (uppercase_letters_list.find(a) != std::string::npos) {
            uppercase++;
        } else if (uppercase_letters_list.find(a) != std::string::npos) {
            symbols++;
        }
    }

    // sum of all possible chars
    const double all_possible_chars = static_cast<double>(digits_list.size() + letters_list.size() +
                                                    uppercase_letters_list.size() + special_chars_list.size());

    //average shares
    const double avg_digits_share = static_cast<double>(digits_list.size()) / all_possible_chars;
    const double avg_lowercase_share = static_cast<double>(letters_list.size()) / all_possible_chars;
    const double avg_uppercase_share = static_cast<double>(uppercase_letters_list.size()) / all_possible_chars;
    const double avg_symbols_share = static_cast<double>(special_chars_list.size()) / all_possible_chars;

    double digits_share = 0, lowercase_share = 0, uppercase_share = 0, symbols_share = 0;
    if (password.size() > 0) {
        //actual shares
        digits_share = static_cast<double>(digits) / static_cast<double>(password.size());
        lowercase_share = static_cast<double>(lowercase) / static_cast<double>(password.size());
        uppercase_share = static_cast<double>(uppercase) / static_cast<double>(password.size());
        symbols_share = static_cast<double>(symbols) / static_cast<double>(password.size());
    }

    //calculate max result and current max
    long double max_result = pow(2, 58);
    long double max_current_len = pow(2, long(password.size() - 6 + all_chars.size()));

    //decrease max_current_len accordingly to how bad character distribution in password is
    long double result = max_current_len -
                         max_current_len * 1e-8 * std::abs(avg_digits_share - digits_share) -
                         max_current_len * 1e-8 * std::abs(avg_lowercase_share - lowercase_share) -
                         max_current_len * 1e-8 * std::abs(avg_uppercase_share - uppercase_share) -
                         max_current_len * 1e-8 * std::abs(avg_symbols_share - symbols_share);

    //for each "bad phrase" in password, divide result with 2
    for (std::string phrase : bad_phrases) {
        result /= std::pow(0.5, number_of_occurrences(password, phrase));
    }

    //scale and return result
    return static_cast<double>(std::min(static_cast<double>((result / (max_result / pow(10, 11)))), 1.0));
}


electronpass::passwords::strength_category electronpass::passwords::password_strength_category(std::string password) {
    return double_to_password_strength(password_strength(password));
}

std::string electronpass::passwords::human_readable_password_strength_category(std::string password) {
    return password_strength_category_to_str(password_strength_category(password));
}
