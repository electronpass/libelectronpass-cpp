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

const std::string& Wallet::Item::get_id() const {
    return id;
}

const std::vector<Wallet::Item> &Wallet::get_items() const {
    return items;
}

void Wallet::set_items(const std::vector<Item> &items_) {
    items = items_;
}

Wallet::Item Wallet::get_item(unsigned int index, int &error) const {
    if (index >= items.size()) {
        error = 1;
        return Item();
    }

    error = 0;
    return items[index];
}

void Wallet::set_item(unsigned int index, const Item &item, int &error) {
    if (index >= items.size()) {
        error = 1;
        return;
    }

    error = 0;
    items[index] = item;
}

void Wallet::add_item(const Item &item) {
    items.push_back(item);
}

Wallet::Item Wallet::delete_item(unsigned int index, int &error) {
    if (index >= items.size()) {
        error = 1;
        return Item();
    }

    Item item = items[index];
    items.erase(items.begin() + index);
    return item;
}

const std::vector<Wallet::Field> &Wallet::Item::get_fields() const {
    return fields;
}

void Wallet::Item::set_fields(const std::vector<Field> &fields_) {
    fields = fields_;
}

unsigned long Wallet::size() {
    return items.size();
}

Wallet::Item &Wallet::operator[](unsigned long index) {
    return items[index];
}

const Wallet::Item &Wallet::operator[](unsigned long index) const {
    return items[index];
}

unsigned long Wallet::Item::size() {
    return fields.size();
}

Wallet::Field &Wallet::Item::operator[](unsigned long index) {
    return fields[index];
}

const Wallet::Field &Wallet::Item::operator[](unsigned long index) const {
    return fields[index];
}
