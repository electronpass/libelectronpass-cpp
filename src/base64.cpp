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

#include "electronpass/crypto.hpp"
#include <iostream>

static bool is_base64(char c) {
  return ((isalnum(c) != 0) || (c == '+') || (c == '/'));
  // is alphanumeric
}

std::string electronpass::Crypto::base64_encode(const std::string& s) {
    std::string result;
    int len = static_cast<int>(s.length());
    int s_counter = 0;
    int i = 0;

    // each 3 bytes are converted to 4 characters in Base64
    unsigned char chars[3];
    unsigned char new_chars[4];

    while (s_counter < len) {
        chars[i++] = static_cast<unsigned char>(s[s_counter++]);

        if (i == 3) {
            new_chars[0] = (chars[0] & 0xfc) >> 2;
            new_chars[1] = ((chars[0] & 0x03) << 4) + ((chars[1] & 0xf0) >> 4);
            new_chars[2] = ((chars[1] & 0x0f) << 2) + ((chars[2] & 0xc0) >> 6);
            new_chars[3] = chars[2] & 0x3f;

            for (unsigned char new_char : new_chars) result += BASE64_CHARS[new_char];
            i = 0;
        }
    }

    if (i) {
        for (int j = i; j < 3; ++j) chars[j] = '\0';

        new_chars[0] = (chars[0] & 0xfc) >> 2;
        new_chars[1] = ((chars[0] & 0x03) << 4) + ((chars[1] & 0xf0) >> 4);
        new_chars[2] = ((chars[1] & 0x0f) << 2) + ((chars[2] & 0xc0) >> 6);
        new_chars[3] = chars[2] & 0x3f;

        for (int j = 0; j < i + 1; ++j) result += BASE64_CHARS[new_chars[j]];

        while (i++ < 3) result += '=';

     }

     return result;
}


std::string electronpass::Crypto::base64_decode(const std::string& s) {
    // String is not correctly encoded in Base64.
    if (s.size() % 4 != 0) return "";

    std::string result;
    int len = static_cast<int>(s.size());
    int i = 0, counter = 0;
    unsigned char chars[4];
    unsigned char new_chars[3];

    while ((counter < len) && (s[counter] != '=') && is_base64(s[counter])) {
        chars[i++] = static_cast<unsigned char>(s[counter++]);

        if (i == 4) {
            // find indices
            for (int j = 0; j < 4; ++j) chars[j] = static_cast<unsigned char>(BASE64_CHARS.find(chars[j]));

            new_chars[0] = (chars[0] << 2) + ((chars[1] & 0x30) >> 4);
            new_chars[1] = ((chars[1] & 0x0f) << 4) + ((chars[2] & 0x3c) >> 2);
            new_chars[2] = ((chars[2] & 0x03) << 6) + chars[3];

            for (i = 0; (i < 3); i++) result += new_chars[i];
            i = 0;
        }
    }

    if (i) {
        for (int j = i; j < 4; ++j) chars[j] = 0;

        for (int j = 0; j < 4; ++j) chars[j] = static_cast<unsigned char>(BASE64_CHARS.find(chars[j]));

        new_chars[0] = (chars[0] << 2) + ((chars[1] & 0x30) >> 4);
        new_chars[1] = ((chars[1] & 0x0f) << 4) + ((chars[2] & 0x3c) >> 2);
        new_chars[2] = ((chars[2] & 0x03) << 6) + chars[3];

        for (int j = 0; j < i - 1; ++j) result += new_chars[j];
    }

    return result;
}
