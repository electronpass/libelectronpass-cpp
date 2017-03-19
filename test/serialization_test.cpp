#include "gtest/gtest.h"
#include "wallet.hpp"
#include "serialization.hpp"

electronpass::Wallet test_wallet() {
    electronpass::Wallet wallet;
    electronpass::Wallet::Item google("Google");
    electronpass::Wallet::Field google_username("Username", "open_user", electronpass::Wallet::FieldType::USERNAME, false);
    electronpass::Wallet::Field google_password("Password", "secret_pa55", electronpass::Wallet::FieldType::PASSWORD, true);
    google.set_fields({google_username, google_password});

    electronpass::Wallet::Item firefox("Google");
    electronpass::Wallet::Field firefox_email("E-mail", "electron.pass@mail.com", electronpass::Wallet::FieldType::EMAIL, false);
    electronpass::Wallet::Field firefox_password("Password", "reallynotsecurepass123", electronpass::Wallet::FieldType::PASSWORD, true);
    firefox.set_fields({firefox_email, firefox_password});

    wallet.set_items({google, firefox});
    return wallet;
}

TEST(SerializationTest, SerializationTest) {
    std::string json = electronpass::serialization::serialize(test_wallet());
    std::string json_string = "{\"items\":[{\"fields\":[{\"name\":\"Username\",\"sensitive\":false,\"type\":\"username\",\"value\":\"open_user\"},{\"name\":\"Password\",\"sensitive\":true,\"type\":\"password\",\"value\":\"secret_pa55\"}],\"name\":\"Google\"},{\"fields\":[{\"name\":\"E-mail\",\"sensitive\":false,\"type\":\"email\",\"value\":\"electron.pass@mail.com\"},{\"name\":\"Password\",\"sensitive\":true,\"type\":\"password\",\"value\":\"reallynotsecurepass123\"}],\"name\":\"Google\"}]}";
    EXPECT_EQ(json, json_string);
}

TEST(SerializationTest, DeserializationTest) {
    std::string json_string = "{\"items\":[{\"fields\":[{\"name\":\"Username\",\"sensitive\":false,\"type\":\"username\",\"value\":\"open_user\"},{\"name\":\"Password\",\"sensitive\":true,\"type\":\"password\",\"value\":\"secret_pa55\"}],\"name\":\"Google\"},{\"fields\":[{\"name\":\"E-mail\",\"sensitive\":false,\"type\":\"email\",\"value\":\"electron.pass@mail.com\"},{\"name\":\"Password\",\"sensitive\":true,\"type\":\"password\",\"value\":\"reallynotsecurepass123\"}],\"name\":\"Google\"}]}";
    electronpass::Wallet wallet = electronpass::serialization::deserialize(json_string);

    std::vector<electronpass::Wallet::Item> items = wallet.get_items();
    for (unsigned int i = 0; i < items.size(); ++i) {
        ASSERT_TRUE(items[i].name == test_wallet().get_items()[i].name);
        std::vector<electronpass::Wallet::Field> fields = items[i].get_fields();
        for (unsigned int j = 0; j < fields.size(); ++j) {
            EXPECT_EQ(fields[j].name, test_wallet().get_items()[i].get_fields()[j].name);
            EXPECT_EQ(fields[j].field_type, test_wallet().get_items()[i].get_fields()[j].field_type);
            EXPECT_EQ(fields[j].value, test_wallet().get_items()[i].get_fields()[j].value);
            EXPECT_EQ(fields[j].sensitive, test_wallet().get_items()[i].get_fields()[j].sensitive);
        }
    }
}