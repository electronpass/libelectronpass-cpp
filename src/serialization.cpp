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

#include "serialization.hpp"

using namespace electronpass;

Wallet::FieldType string_to_field_type(const std::string& type_string) {
    if (type_string == "username")
        return Wallet::FieldType::username;
    if (type_string == "password")
        return Wallet::FieldType::password;
    if (type_string == "email")
        return Wallet::FieldType::email;
    if (type_string == "url")
        return Wallet::FieldType::url;
    if (type_string == "pin")
        return Wallet::FieldType::pin;

    return Wallet::FieldType::undefined;
}


Wallet serialization::deserialize(const char* const json) {
    Json::Value root;
    Json::Reader reader;
    reader.parse(json, root);

    Json::Value items = root["items"];
    for (Json::Value item : items) {
        std::string name = item["name"].asString();

        std::vector<Wallet::Field> fields;

        Json::Value raw_fields = item["fields"];
        for (Json::Value field : raw_fields) {
            std::string field_name = field["name"].asString();
            std::string field_value = field["value"].asString();
            bool sensitive = field["sensitive"].asBool();
            Wallet::FieldType type = string_to_field_type(field["type"].asString());

            Wallet::Field field_object(field_name, field_value, type, sensitive);
        }
    }

    return {};
}
