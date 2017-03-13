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

#ifndef ELECTRONPASS_WALLET_HPP
#define ELECTRONPASS_WALLET_HPP

#include <vector>
#include <string>

namespace electronpass {
    class Wallet {
      public:
        enum class FieldType {
            username, password, email, url, pin, undefined
        };

        struct Field {
            Field(std::string name, std::string value,
                  FieldType field_type, bool sensitive): name{name},
                                                         value{value},
                                                         field_type{field_type},
                                                         sensitive{sensitive} {}
            std::string name;
            std::string value;
            FieldType field_type;
            bool sensitive;
        };

        struct Item {
            std::string name;
            std::vector<Field> fields;
        };

      private:
        std::vector<Item> _items;
    };
}


#endif //ELECTRONPASS_WALLET_HPP
