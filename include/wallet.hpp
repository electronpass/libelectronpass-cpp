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

/**
 * @file wallet.hpp
 * @author Vid Drobnič <vid.drobnic@gmail.com>
 * @brief Defined wallet class for storing passwords and intecracting with them.
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
            std::vector<Field> fields;
          public:
            /// Constructor for creating an empty item.
            Item() {}
            /**
             * @brief Constructor for creating fully populated item.
             * @param name_ Display name for the item.
             * @param fields_ Fields in the item. For more info about fields read Wallet::Field.
             */

            Item(const std::string& name_, const std::vector<Field>& fields_): fields{fields_}, name{name_} {}

            /**
             * @brief Constructor for creating item with name and empty fields.
             * @param name_ Display name for the item.
             */
            Item(const std::string& name_): name{name_} {}

            /// Display name for the item.
            std::string name;

            /**
             * @brief Method for reading the fields.
             *
             * This method returns all fields in this item.
             *
             * @return Vector of fields.
             */
            std::vector<Field> get_fields() const;

            /**
             * @brief Method for setting the fields.
             *
             * This methods overrides all existing fields with the fields that you provide as the parameter. It can be
             * used if you want to populate the fields of the item after it has been initialized.
             *
             * @param fields Fields that should be set to this item.
             */
            void set_fields(const std::vector<Field>& fields);
        };


        /// Constructor for creating empty wallet.
        Wallet() {};

        /**
         * @brief Constructor for creating wallet populated with items.
         * @param items_ Items that should be stored in the wallet.
         */
        Wallet(const std::vector<Item>& items_): items{items_} {}

        /**
         * @brief Method for reading the items.
         *
         * This method returns all items in the Wallet. You should not rearrange the elements in the vector, because the
         * indices of the elements act as the ids by which you can modify specific
         * elements with other methods in this class.
         *
         * @return Vector of item names.
         */
        std::vector<Item> get_items() const;

        /**
         * @brief Method for setting the items.
         *
         * This methods overrides all existing items with the items that you provide as the parameter. It can be
         * used if you want to populate the items after the wallet has been initialized.
         *
         * @param items Items that should be stored in the wallet.
         */
        void set_items(const std::vector<Item>& items);

        /**
         * @brief Get a specific item.
         *
         * Error codes:
         * - 0: success
         * - 1: index out of bounds error
         *
         * @param index Index of the item.  Index is the same as the index from get_items method.
         * @param error Error is set to 0 if no error occured. For other error codes look at the detailed description.
         * @return
         */
        Item get_item(unsigned int index, int& error) const;

        /**
         * @brief Set an item at specific index to new Item.
         *
         * Item with this index must already exist. This method is used to override the item when, for instance, user
         * edits the item.
         *
         * Error codes:
         * - 0: success
         * - 1: index out of bounds error
         *
         * @param index Index of the field that should be set.
         * @param item The item that will be set
         * @param error Error is set to appropriate error code. For error codes look at the detailed description.
         */
        void set_item(unsigned int index, const Item& item, int& error);

        /**
         * @brief Add an item to the wallet.
         *
         * This method is used to append an item to the wallet (for instance when user adds another item(password entry)).
         *
         * @param item Item that should be added.
         */
        void add_item(const Item& item);

        /**
         * @brief Delete an item from the wallet.
         *
         * This method is used to delete an item from the wallet (for instance, when user deletes an item(password)).
         *
         * Error codes:
         * - 0: success
         * - 1: index out of bounds
         *
         * @param index Index of the item that should be deleted.
         * @param error Error is set to appropriate error code. For error codes look at the detailed description.
         * @return Deleted item.
         */
        Item delete_item(unsigned int index, int& error);

      private:
        std::vector<Item> items;
    };
}


#endif //ELECTRONPASS_WALLET_HPP
