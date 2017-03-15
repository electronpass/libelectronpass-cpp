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

/*
 * TODO: Class methods to operate with data
 * Wallet:
 *   - constructor & deconstructor
 *   - get_items (names only)
 *   - set_items (override all items)
 *   - get_item (get data for specific item)
 *   - set_item (set data for specific items)
 *   - add_item/s (add one or more items to the wallet)
 *   - delete_item/s (delete one or more items to the wallet)
 *
 * Item:
 *   - add_field/s (add one or more fields to the item)
 *   - delete_field/s (delete one or more fields from the item)
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
         * - username: for storing usernames
         * - password: for storing passwords
         * - email: for storing email addresses
         * - url: for storing url of website on which the password is used
         * - pin: for storing numeric values
         */
        enum class FieldType {
            username, password, email, url, pin, undefined
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
             * @param name Display name of the field.
             * @param value Value stored in the field.
             * @param field_type Type of the field. For more about field types read documentation for
             * Wallet::FieldType enum.
             * @param sensitive Should the value stored in the field by hidden by default in the UI.
             */
            Field(std::string name, std::string value,
                  FieldType field_type, bool sensitive): name{name},
                                                         value{value},
                                                         field_type{field_type},
                                                         sensitive{sensitive} {}
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
            std::vector<Field> _fields;
          public:
            /// Constructor for creating an empty item.
            Item() {}
            /**
             * @brief Constructor for creating fully populated item.
             * @param name Display name for the item.
             * @param fields Fields in the item. For more info about fields read Wallet::Field.
             */

            Item(std::string name, std::vector<Field> fields): _fields{fields}, name{name} {}

            /**
             * @brief Constructor for creating item with name and empty fields.
             * @param name Display name for the item.
             */
            Item(std::string name): name{name} {}

            /// Display name for the item.
            std::string name;

            /**
             * @brief Method for reading the fields.
             *
             * This method returns the names of the fields for this item. Only names are returned for primarily security
             * reasons and also memory optimization. You should not rearrange the elements in the vector, because the
             * index of the element in this vector is used to access more information about the field.
             *
             * @return Vector of field names.
             */
            std::vector<std::string> get_fields() const;

            /**
             * @brief Method for setting the fields.
             *
             * This methods overrides all existing fields with the fields that you provide as the parameter. It can be
             * used if you want to populate the fields of the item after it has been initialized.
             *
             * @param fields Fields that should be set to this item.
             */
            void set_fields(std::vector<Field> fields);

            /**
             * @brief Get a specific field from item.
             *
             * Error codes:
             * - 0: success
             * - 1: index out of bounds error
             *
             * @param index Index of the field. Index is the same as the index from get_fields method.
             * @param error Error is set to 0 if no error occurred. For other error codes look at the detailed description.
             * @return Field that you requested.
             */
            Field get_field(int index, int& error) const;

            /**
             * @brief Set a field at specific index to new Field.
             *
             * Field with this index must already exist. This method is used to override the field when, for instance,
             * user edits the field.
             *
             * Error codes:
             * - 0: success
             * - 1: index out of bounds error
             *
             * @param index Index of the field that should be set.
             * @param field New field that will be saved.
             * @param error Error is set to 0 if no error occurred. For other error codes look at the detailed description.
             */
            void set_field(int index, const Field& field, int& error);

            /**
             * @brief Add a field to the item.
             *
             * This method is used to append a field to the item (for instance when user adds another field to the item).
             * For adding multiple fields at the same time look at the add_fields() method.
             *
             * @param field Field that should be added.
             */
            void add_field(const Field& field);

            /**
             * @brief Delete a field from the item.
             *
             * This method is used to delete the field from the item (for instance, when user deletes the field).
             *
             * Error codes:
             * - 0: success
             * - 1: index out of bounds
             *
             * @param index Index of the item that should be deleted.
             * @param error Error is set to 0 if no error occurred. For other error codes look at the detailed description.
             * @return Deleted field.
             */
            Field delete_field(int index, int& error);
        };

      private:
        std::vector<Item> _items;
    };
}


#endif //ELECTRONPASS_WALLET_HPP
