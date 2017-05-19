#include <gtest/gtest.h>

#include "wallet.hpp"
#include "serialization.hpp"

electronpass::Wallet test_wallet() {
    electronpass::Wallet::Item google1("Google", "YTBZGOOr/w13Vef8zFkm+YHGsutFGzSp", 1493189705);
    electronpass::Wallet::Field google_username("Username", "open_user", electronpass::Wallet::FieldType::USERNAME, false);
    electronpass::Wallet::Field google_password("Password", "secret_pa55", electronpass::Wallet::FieldType::PASSWORD, true);
    google1.fields = {google_username, google_password};

    electronpass::Wallet::Item google2("Google", "epW6aIyR6eBLmyQkgYG/KIDKWr0w0vba", 1493189650);
    electronpass::Wallet::Field google2_email("E-mail", "electron.pass@mail.com", electronpass::Wallet::FieldType::EMAIL, false);
    electronpass::Wallet::Field google2_password("Password", "reallynotsecurepass123", electronpass::Wallet::FieldType::PASSWORD, true);
    google2.fields = {google2_email, google2_password};

    std::map<std::string, electronpass::Wallet::Item> items;
    items["YTBZGOOr/w13Vef8zFkm+YHGsutFGzSp"] = google1;
    items["epW6aIyR6eBLmyQkgYG/KIDKWr0w0vba"] = google2;
    electronpass::Wallet wallet(items, 1493189805);

    return wallet;
}

TEST(SerializationTest, SerializationTest) {
    std::string json = electronpass::serialization::serialize(test_wallet());
    std::string json_string = "{\"items\":{\"YTBZGOOr/w13Vef8zFkm+YHGsutFGzSp\":{\"fields\":[{\"name\":\"Username\",\"sensitive\":false,\"type\":\"username\",\"value\":\"open_user\"},{\"name\":\"Password\",\"sensitive\":true,\"type\":\"password\",\"value\":\"secret_pa55\"}],\"last_edited\":1493189705,\"name\":\"Google\"},\"epW6aIyR6eBLmyQkgYG/KIDKWr0w0vba\":{\"fields\":[{\"name\":\"E-mail\",\"sensitive\":false,\"type\":\"email\",\"value\":\"electron.pass@mail.com\"},{\"name\":\"Password\",\"sensitive\":true,\"type\":\"password\",\"value\":\"reallynotsecurepass123\"}],\"last_edited\":1493189650,\"name\":\"Google\"}}}";
    EXPECT_EQ(json, json_string);
}

TEST(SerializationTest, EmptySerializationTest) {
    std::string json = electronpass::serialization::serialize(electronpass::Wallet());
    EXPECT_EQ(json, "{\"items\":null}");
}

TEST(SerializationTest, DeserializationTest) {
    std::string json_string = "{\"items\":{\"YTBZGOOr/w13Vef8zFkm+YHGsutFGzSp\":{\"fields\":[{\"name\":\"Username\",\"sensitive\":false,\"type\":\"username\",\"value\":\"open_user\"},{\"name\":\"Password\",\"sensitive\":true,\"type\":\"password\",\"value\":\"secret_pa55\"}],\"last_edited\":1493189705,\"name\":\"Google\"},\"epW6aIyR6eBLmyQkgYG/KIDKWr0w0vba\":{\"fields\":[{\"name\":\"E-mail\",\"sensitive\":false,\"type\":\"email\",\"value\":\"electron.pass@mail.com\"},{\"name\":\"Password\",\"sensitive\":true,\"type\":\"password\",\"value\":\"reallynotsecurepass123\"}],\"last_edited\":1493189650,\"name\":\"Google\"}}}";
    electronpass::Wallet wallet = electronpass::serialization::deserialize(json_string);

    std::vector<std::string> ids = wallet.get_ids();
    for (std::string id : ids) {
        electronpass::Wallet::Item item = wallet[id];

        EXPECT_EQ(id, item.get_id());

        EXPECT_EQ(item.name, test_wallet()[id].name);
        EXPECT_EQ(item.last_edited, test_wallet()[id].last_edited);
        std::vector<electronpass::Wallet::Field> fields = item.fields;
        std::vector<electronpass::Wallet::Field> test_fields = test_wallet()[id].fields;
        for (unsigned int j = 0; j < fields.size(); ++j) {
            EXPECT_EQ(fields[j].name, test_fields[j].name);
            EXPECT_EQ(fields[j].field_type, test_fields[j].field_type);
            EXPECT_EQ(fields[j].value, test_fields[j].value);
            EXPECT_EQ(fields[j].sensitive, test_fields[j].sensitive);
        }
    }
}

TEST(SerializationTest, EmptyDeserializationTest) {
    std::string json = "{\"items\":null,\"timestamp\":1}";
    electronpass::Wallet wallet = electronpass::serialization::deserialize(json);
    EXPECT_EQ(wallet.size(), static_cast<unsigned int>(0));
}

TEST(SerializationTest, LoadSaveTest) {
    electronpass::Crypto crypto("password");
    electronpass::Wallet wallet1 = test_wallet();
    int error, error2;
    electronpass::Wallet wallet2 = electronpass::serialization::load(electronpass::serialization::save(wallet1, crypto, error), crypto, error2);

    EXPECT_EQ(wallet1.timestamp, wallet2.timestamp);
    EXPECT_EQ(error, 0);
    EXPECT_EQ(error2, 0);

    std::vector<std::string> ids = wallet2.get_ids();
    for (std::string id : ids) {
        electronpass::Wallet::Item item = wallet2[id];

        EXPECT_EQ(id, item.get_id());

        EXPECT_EQ(item.name, wallet1[id].name);
        EXPECT_EQ(item.last_edited, wallet1[id].last_edited);
        std::vector<electronpass::Wallet::Field> fields = item.fields;
        std::vector<electronpass::Wallet::Field> fields2 = wallet2[id].fields;
        for (unsigned int j = 0; j < fields.size(); ++j) {
            EXPECT_EQ(fields[j].name, fields2[j].name);
            EXPECT_EQ(fields[j].field_type, fields2[j].field_type);
            EXPECT_EQ(fields[j].value, fields2[j].value);
            EXPECT_EQ(fields[j].sensitive, fields2[j].sensitive);
        }
    }
}

TEST(SerializationTest, InvalidJSONTest) {
    std::string json = "\"\"";
    electronpass::Crypto crypto("");
    int error;
    electronpass::Wallet wallet = electronpass::serialization::load(json, crypto, error);
    EXPECT_EQ(error, 2);
}
