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

using namespace electronpass;

Wallet::Item::Item() {
    id = Crypto::generate_uuid();
}

Wallet::Item::Item(const std::string &name_, std::string id_): name{name_} {
    if (id_ == "") id = Crypto::generate_uuid();
    else id = id_;
}

Wallet::Item::Item(const std::string &name_, const std::vector<Field> &fields_, std::string id_): fields {fields_},
                                                                                                  name{name_} {
    if (id_ == "") id = Crypto::generate_uuid();
    else id = id_;
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
    for (std::map<std::string, Item>::const_iterator it = items.begin(); it != items.end(); ++it) {
        ids[i] = it->first;
        ++i;
    }

    return ids;
}

Wallet::Item Wallet::operator[](const std::string& id) const {
    return items.at(id);
}

bool Wallet::add_item(const Item &item) {
    std::map<std::string, Item>::iterator it = items.find(item.get_id());
    if (it == items.end()) {
        items[item.get_id()] = item;
        return true;
    }

    return false;
}

void Wallet::edit_item(const std::string& id, const std::string& name, const std::vector<Field>& fields) {
    items[id].name = name;
    items[id].fields = fields;
}

Wallet::Item Wallet::delete_item(const std::string& id) {
    Item item = items[id];
    items.erase(id);
    return item;
}

unsigned long Wallet::size() const {
    return items.size();
}

void Wallet::update_timestamp() {
    auto now = std::chrono::system_clock::now();
    auto new_timestamp = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());
    timestamp = static_cast<uint64_t>(new_timestamp.count());
}
