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

#include <map>
#include <vector>
#include <string>

#include "crypto.hpp"

/**
 * @file wallet.hpp
 * @author Vid Drobnič <vid.drobnic@protonmail.com>
 * @brief Defined wallet class for storing passwords and interacting with them.
 */

/**
 * @brief Namespace for all functions and classes in libelectronpass.
 *
 * This is the main namespace that libelectronpass uses for its classes and functions.
 */
namespace electronpass {
    /**
     * @brief Class for storing and interacting with passwords.
     */
    class Wallet {
      public:

        /**
         * @brief Possible field types.
         *
         * - USERNAME: for storing usernames
         * - PASSWORD: for storing passwords
         * - EMAIL: for storing email addresses
         * - URL: for storing url of website on which the password is used
         * - PIN: for storing numeric values
         */
        enum class FieldType {
            USERNAME, PASSWORD, EMAIL, URL, PIN, UNDEFINED
        };

        /**
         * @brief Struct for storing field data.
         *
         * Wallet item is constructed of multiple fields, where each field represents one information about the item
         * eg.: username, password, email, etc.
         */
        struct Field {
            /**
             * @brief Constructor for creating fields with data.
             * @param name_ Display name of the field.
             * @param value_ Value stored in the field.
             * @param field_type_ Type of the field. For more about field types read documentation for
             * Wallet::FieldType enum.
             * @param sensitive_ Should the value stored in the field be hidden by default in the UI.
             */
            Field(const std::string& name_, const std::string& value_,
                  const FieldType& field_type_, bool sensitive_): name{name_},
                                                                  value{value_},
                                                                  field_type{field_type_},
                                                                  sensitive{sensitive_} {}
            /// Constructor for creating an empty field.
            Field() {}

            /// Display name of the field.
            std::string name;
            /// Value that is stored in the field.
            std::string value;
            /// Type of the field. You can read more about field types in documentation for Wallet::FieldType enum.
            FieldType field_type;
            /// Used by UI to hide sensitive information (eg. password).
            bool sensitive;
        };

        /**
         * @brief Each item represents an entry in the Wallet.
         *
         * Wallet item is constructed of multiple fields. For security reasons, interaction with the fields is only
         * allowed using the class methods.
         */
        class Item {
            std::string id;
          public:
            /// Item fields.
            std::vector<Field> fields;

            /// Constructor for creating an empty item. New id will be set to the item.
            Item();

            /**
             * @brief Constructor for creating item with name and empty fields.
             *
             * If id is not set, then random id will be generated.
             *
             * @param id_ Item id.
             * @param name_ Display name for the item.
             */
            Item(const std::string& name_, std::string id_ = "");

            /**
             * @brief Constructor for creating fully populated item.
             *
             * If id is not set, then random id will be generated.
             *
             * @param id_ Item id.
             * @param name_ Display name for the item.
             * @param fields_ Fields in the item. For more info about fields read Wallet::Field.
             */
            Item(const std::string& name_, const std::vector<Field>& fields_, std::string id_ = "");

            /// Display name for the item.
            std::string name;

            /**
             * @brief Method for getting item id.
             * @return Item id.
             */
            std::string get_id() const;

            /**
             * @brief Generate new id.
             */
            std::string set_id();

            /**
             * @brief Number of fields in item.
             * @return Number of fields
             */
            unsigned long size();

            /**
             * @brief Array subscript for field in item.
             * @param index Index of field
             * @return Field
             */
            Field& operator[](unsigned long index);

            /**
             * @brief Array subscript for field in item when item is constant.
             * @param index Index of field
             * @return Field
             */
            const Field& operator[](unsigned long index) const;
        };


        /// Constructor for creating empty wallet.
        Wallet() {};

        /**
         * @brief Constructor for creating wallet populated with items.
         * @param items_ Items that should be stored in the wallet.
         */
        Wallet(const std::map<std::string, Item>& items_): items{items_} {}

        /**
         * @brief Constructor for creating wallet populated with items and timestamp.
         * @param timestamp_ Wallet timestamp.
         * @param items_ Items that are stored in the wallet.
         */
        Wallet(uint64_t timestamp_, const std::map<std::string, Item>& items_): timestamp(timestamp_), items{items_} {}

        /// Date when the Wallet was saved.
        uint64_t timestamp = 0;
        std::map<std::string, Item> items;
    };
}


#endif //ELECTRONPASS_WALLET_HPP
