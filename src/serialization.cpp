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

std::string field_type_to_string(const Wallet::FieldType& field_type) {
    switch (field_type) {
        case Wallet::FieldType::USERNAME:
            return "username";
        case Wallet::FieldType::PASSWORD:
            return "password";
        case Wallet::FieldType::EMAIL:
            return "email";
        case Wallet::FieldType::URL:
            return "url";
        case Wallet::FieldType::PIN:
            return "pin";
        default:
            return "undefined";
    }
}


Wallet serialization::deserialize(const std::string& json) {
    Json::Value root;
    Json::Reader reader;
    reader.parse(json.c_str(), root);

    std::map<std::string, Wallet::Item> items;

    Json::Value::Members raw_items = root["items"].getMemberNames();
    for (std::string id : raw_items) {
        Json::Value raw_item = root["items"][id];
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

        Wallet::Item item(name, fields, id);
        items[id] = item;
    }
    uint64_t timestamp = root["timestamp"].asUInt64();

    return Wallet(timestamp, items);
}

std::string serialization::serialize(const Wallet& wallet) {
    Json::Value root;
    root["timestamp"] = wallet.timestamp;
    root["items"] = Json::Value();

    std::map<std::string, Wallet::Item> items = wallet.items;
    for (auto i = items.begin(); i != items.end(); ++i) {
        Json::Value item;
        item["name"] = i->second.name;

        std::vector<Wallet::Field> fields = i->second.fields;
        Json::Value json_fields;
        for (unsigned int j = 0; j < fields.size(); ++j) {
            Json::Value field;
            field["name"] = fields[j].name;
            field["type"] = field_type_to_string(fields[j].field_type);
            field["value"] = fields[j].value;
            field["sensitive"] = fields[j].sensitive;
            json_fields[j] = field;
        }

        item["fields"] = json_fields;
        root["items"][i->first] = item;
    }

    Json::StreamWriterBuilder builder;
    builder.settings_["indentation"] = "";
    return Json::writeString(builder, root);
}
