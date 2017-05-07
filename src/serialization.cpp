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

#define kWalletVersion 0

using namespace electronpass;

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
            Wallet::FieldType field_type = Wallet::string_to_field_type(raw_field["type"].asString());

            Wallet::Field field(field_name, field_value, field_type, sensitive);
            fields.push_back(field);
        }

        Wallet::Item item(name, fields, id);
        items[id] = item;
    }

    return Wallet(items);
}

std::string serialization::serialize(const Wallet& wallet) {
    Json::Value root;
    root["items"] = Json::Value();

    std::vector<std::string> ids = wallet.get_ids();
    for (std::string id : ids) {
        Json::Value item;
        item["name"] = wallet[id].name;

        std::vector<Wallet::Field> fields = wallet[id].fields;
        Json::Value json_fields;
        for (unsigned int j = 0; j < fields.size(); ++j) {
            Json::Value field;
            field["name"] = fields[j].name;
            field["type"] = Wallet::field_type_to_string(fields[j].field_type);
            field["value"] = fields[j].value;
            field["sensitive"] = fields[j].sensitive;
            json_fields[j] = field;
        }

        item["fields"] = json_fields;
        root["items"][id] = item;
    }

    Json::StreamWriterBuilder builder;
    builder.settings_["indentation"] = "";
    return Json::writeString(builder, root);
}

electronpass::Wallet serialization::load(const std::string &data, const Crypto &crypto, int &error) {
    Json::Value json;
    Json::Reader reader;
    if (!reader.parse(data, json)) {
        error = 2;
        return Wallet();
    }

    if (json["timestamp"].empty() || json["data"].empty() || json["version"].empty()) {
        error = 2;
        return Wallet();
    }

    uint64_t timestamp = json["timestamp"].asUInt64();

    bool decrypt;
    std::string wallet_string = crypto.decrypt(json["data"].asString(), decrypt);
    if (!decrypt) {
        error = 1;
        return Wallet(timestamp);
    }

    Wallet wallet = deserialize(wallet_string);
    wallet.timestamp = timestamp;
    error = 0;
    return wallet;
}

std::string serialization::save(const Wallet &wallet, const Crypto &crypto, bool &success) {
    bool encrypt;
    std::string data = crypto.encrypt(serialize(wallet), encrypt);
    if (!encrypt) {
        success = false;
        return "{}";
    }

    success = true;

    Json::Value json;
    json["timestamp"] = wallet.timestamp;
    json["version"] = kWalletVersion;
    json["data"] = data;

    Json::StreamWriterBuilder builder;
    builder.settings_["indentation"] = "";
    return Json::writeString(builder, json);
}
