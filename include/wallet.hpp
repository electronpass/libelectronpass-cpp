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
#include <chrono>

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
     *
     * Accessing items can be done by using operator[] on the wallet. Some common operations for working with the
     * wallet are:
     *
     * - **Listing ids**: get_ids()
     * - **Getting an item**: operator[](const std::string&) const
     * - **Adding an item**: add_item(const Item&)
     * - **Editing an item**: edit_item(const std::string&, const std::string&, const std::vector<Field>&) to preserve the
     * id of the item being edited.
     * - **Deleting an item**: delete_item(const std::string&)
     * - **Wallet size**: size()
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
         * - DATE: for storing date
         * - OTHER: for storing other than what is listed above
         */
        enum class FieldType {
            USERNAME, PASSWORD, EMAIL, URL, PIN, DATE, OTHER, UNDEFINED
        };

        /**
         * @brief Convert FieldType to string.
         * @param field_type FieldType to be converted.
         * @return FieldType as string.
         */
        static std::string field_type_to_string(FieldType field_type);

        /**
         * @brief Convert string to field type.
         * @param field_type String to be converted.
         * @return String as FieldType
         */
        static FieldType string_to_field_type(const std::string& field_type);

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
            unsigned long size() const;

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


        /**
         * @brief Constructor for creating empty wallet.
         * @param timestamp_ Wallet timestamp. If 0, then update_timestamp() is called.
         */
        Wallet(uint64_t timestamp_ = 0);

        /**
         * @brief Constructor for creating wallet populated with items.
         * @param timestamp_ Wallet timestamp. If 0, then update_timestamp() is called.
         * @param items_ Items that are stored in the wallet.
         */
        Wallet(const std::map<std::string, Item>& items_, uint64_t timestamp_ = 0);

        /**
         * @brief Method for editing items.
         *
         * This method should be used for editing the item, because it keeps the id of the item you are editing.
         *
         * @param id Id of the item being edited.
         * @param name Changed name of the item.
         * @param fields New fields in the item.
         */
        void edit_item(const std::string& id, const std::string& name, const std::vector<Field>& fields);

        /**
         * @brief Get all ids of all the items stored in the wallet.
         * @return Vector of all ids.
         */
        std::vector<std::string> get_ids() const;

        /**
         * @brief Add item to the wallet.
         *
         * Use this method for adding an item to the wallet. You could also do this by calling ```wallet.items[item.get_id()] = item```.
         *
         * If the item already exists in the wallet, then it will not be added. In this case the method returns false.
         *
         * @param item Item to add to the wallet.
         * @return True if the item was added to the wallet otherwise false.
         */
        bool add_item(const Item& item);

        /**
         * @brief Delete item from the wallet.
         * @param id Id of the Item to be deleted.
         * @return Deleted Item.
         */
        Item delete_item(const std::string& id);

        /**
         * @brief Get Item from the wallet
         *
         * Retrieved item is not a reference, therefore you cannot set a new item this way. For that you should use add_item(const Item&).
         * Changes done to the retrieved item are also not stored in the wallet. For that you should use
         * edit_item(const std::string&, const std::string&, const std::vector<Field>&). This is so you cannot change the
         * item to a new id without changing the key in the wallet to the new id.
         *
         * @param id Id of the item.
         * @return Item in the wallet. Empty if it doesn't exist.
         */
        Item operator[](const std::string& id) const;

        /**
         * @brief Get number of items in the wallet.
         * @return Number of items in the wallet.
         */
        unsigned long size() const;

        /// Method for setting wallet timestamp to current system time.
        void update_timestamp();

        /// Date when the Wallet was saved.
        uint64_t timestamp;
    private:
        std::map<std::string, Item> items;
    };
}


#endif //ELECTRONPASS_WALLET_HPP
