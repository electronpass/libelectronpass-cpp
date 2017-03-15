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
        return Wallet::FieldType::USERNAME;
    if (type_string == "password")
        return Wallet::FieldType::PASSWORD;
    if (type_string == "email")
        return Wallet::FieldType::EMAIL;
    if (type_string == "url")
        return Wallet::FieldType::URL;
    if (type_string == "pin")
        return Wallet::FieldType::PIN;

    return Wallet::FieldType::UNDEFINED;
}


Wallet serialization::deserialize(const std::string& json) {
    Json::Value root;
    Json::Reader reader;
    reader.parse(json.c_str(), root);

    std::vector<Wallet::Item> items;

    Json::Value raw_items = root["items"];
    for (Json::Value raw_item : raw_items) {
        std::string name = raw_item["name"].asString();

        std::vector<Wallet::Field> fields;

        Json::Value raw_fields = raw_item["fields"];
        for (Json::Value raw_field : raw_fields) {
            std::string field_name = raw_field["name"].asString();
            std::string field_value = raw_field["value"].asString();
            bool sensitive = raw_field["sensitive"].asBool();
            Wallet::FieldType field_type = string_to_field_type(raw_field["type"].asString());

            Wallet::Field field(field_name, field_value, field_type, sensitive);
            fields.push_back(field);
        }

        Wallet::Item item(name, fields);
        items.push_back(item);
    }

    return Wallet(items);
}
