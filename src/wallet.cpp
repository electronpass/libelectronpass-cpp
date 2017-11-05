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

#include "wallet.hpp"

#define kFieldTypeUsername "username"
#define kFieldTypePassword "password"
#define kFieldTypeEmail "email"
#define kFieldTypeUrl "url"
#define kFieldTypePin "pin"
#define kFieldTypeDate "date"
#define kFieldTypeOther "other"
#define kFieldTypeUndefined "undefined";

using namespace electronpass;

uint64_t current_timestamp() {
    auto now = std::chrono::system_clock::now();
    auto new_timestamp = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());
    return static_cast<uint64_t>(new_timestamp.count());
}

Wallet::FieldType Wallet::string_to_field_type(const std::string &field_type) {
    if (field_type == kFieldTypeUsername) return FieldType::USERNAME;
    if (field_type == kFieldTypePassword) return FieldType::PASSWORD;
    if (field_type == kFieldTypeEmail) return FieldType::EMAIL;
    if (field_type == kFieldTypeUrl) return FieldType::URL;
    if (field_type == kFieldTypePin) return FieldType::PIN;
    if (field_type == kFieldTypeDate) return FieldType::DATE;
    if (field_type == kFieldTypeOther) return FieldType::OTHER;
    return FieldType::UNDEFINED;
}

std::string Wallet::field_type_to_string(FieldType field_type) {
    switch (field_type) {
        case FieldType::USERNAME: return kFieldTypeUsername;
        case FieldType::PASSWORD: return kFieldTypePassword;
        case FieldType::EMAIL: return kFieldTypeEmail;
        case FieldType::URL: return kFieldTypeUrl;
        case FieldType::PIN: return kFieldTypePin;
        case FieldType::DATE: return kFieldTypeDate;
        case FieldType::OTHER: return kFieldTypeOther;
        default: return kFieldTypeUndefined;
    }
}

Wallet::Item::Item(uint64_t last_edited_) {
    id = Crypto::generate_uuid();
    last_edited = last_edited_ ? last_edited_ : current_timestamp();
}

Wallet::Item::Item(const std::string &name_, std::string id_, uint64_t last_edited_): name{name_} {
    id = id_.empty() ? Crypto::generate_uuid() : id_;
    last_edited = last_edited_ ? last_edited_ : current_timestamp();
}

Wallet::Item::Item(const std::string &name_, const std::vector<Field> &fields_, std::string id_, uint64_t last_edited_): fields {fields_},
                                                                                                                         name{name_} {
    id = id_ == "" ? Crypto::generate_uuid() : id_;
    last_edited = last_edited_ ? last_edited_ : current_timestamp();
}

std::string Wallet::Item::get_id() const {
    return id;
}

std::string Wallet::Item::set_id() {
    id = Crypto::generate_uuid();
    return id;
}

unsigned long Wallet::Item::size() const {
    return fields.size();
}

Wallet::Field &Wallet::Item::operator[](unsigned long index) {
    return fields[index];
}

const Wallet::Field &Wallet::Item::operator[](unsigned long index) const {
    return fields[index];
}

Wallet::Wallet(uint64_t timestamp_) {
    if (timestamp_ == 0) update_timestamp();
    else timestamp = timestamp_;
}

Wallet::Wallet(const std::map<std::string, Item> &items_, uint64_t timestamp_): items{items_} {
    if (timestamp_ == 0) update_timestamp();
    else timestamp = timestamp_;
}

std::vector<std::string> Wallet::get_ids() const {
    std::vector<std::string> ids(items.size());
    int i = 0;
    for (const auto &item : items) {
        ids[i] = item.first;
        ++i;
    }

    return ids;
}

Wallet::Item Wallet::operator[](const std::string& id) const {
    return items.at(id);
}

bool Wallet::add_item(const Item &item) {
    auto it = items.find(item.get_id());
    if (it == items.end()) {
        items[item.get_id()] = item;
        items[item.get_id()].last_edited = current_timestamp();
        return true;
    }
    update_timestamp();
    return false;
}

void Wallet::edit_item(const std::string& id, const std::string& name, const std::vector<Field>& fields) {
    items[id].name = name;
    items[id].fields = fields;
    items[id].last_edited = current_timestamp();
    update_timestamp();
}

Wallet::Item Wallet::delete_item(const std::string& id) {
    Item item = items[id];
    items.erase(id);
    update_timestamp();
    return item;
}

unsigned long Wallet::size() const {
    return items.size();
}

void Wallet::update_timestamp() {
    timestamp = current_timestamp();
}

Wallet Wallet::merge(const Wallet &wallet1, const Wallet &wallet2) {
    std::vector<std::string> wallet1_ids = wallet1.get_ids();
    std::vector<std::string> wallet2_ids = wallet2.get_ids();
    std::set<std::string> newer_wallet, older_wallet;
    if (wallet1.timestamp >= wallet2.timestamp) {
        newer_wallet = std::set<std::string>(wallet1_ids.begin(), wallet1_ids.end());
        older_wallet = std::set<std::string>(wallet2_ids.begin(), wallet2_ids.end());
    } else {
        newer_wallet = std::set<std::string>(wallet2_ids.begin(), wallet2_ids.end());
        older_wallet = std::set<std::string>(wallet1_ids.begin(), wallet1_ids.end());
    }

    std::map<std::string, Wallet::Item> items;

    for (const auto &item : newer_wallet) {
        if (older_wallet.find(item) == older_wallet.end()) {
            electronpass::Wallet wallet = wallet1.timestamp >= wallet2.timestamp ? wallet1 : wallet2;
            items[item] = wallet[item];
            continue;
        }

        Wallet::Item item1 = wallet1[item];
        Wallet::Item item2 = wallet2[item];
        items[item] = item1.last_edited >= item2.last_edited ? item1 : item2;
    }

    uint64_t timestamp = wallet1.timestamp > wallet2.timestamp ? wallet1.timestamp : wallet2.timestamp;
    return Wallet(items, timestamp);
}
