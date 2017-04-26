#include <gtest/gtest.h>

#include "wallet.hpp"
#include "serialization.hpp"

electronpass::Wallet test_wallet() {
    electronpass::Wallet wallet;
    electronpass::Wallet::Item google1("Google", "YTBZGOOr/w13Vef8zFkm+YHGsutFGzSp");
    electronpass::Wallet::Field google_username("Username", "open_user", electronpass::Wallet::FieldType::USERNAME, false);
    electronpass::Wallet::Field google_password("Password", "secret_pa55", electronpass::Wallet::FieldType::PASSWORD, true);
    google1.fields = {google_username, google_password};

    electronpass::Wallet::Item google2("Google", "epW6aIyR6eBLmyQkgYG/KIDKWr0w0vba");
    electronpass::Wallet::Field google2_email("E-mail", "electron.pass@mail.com", electronpass::Wallet::FieldType::EMAIL, false);
    electronpass::Wallet::Field google2_password("Password", "reallynotsecurepass123", electronpass::Wallet::FieldType::PASSWORD, true);
    google2.fields = {google2_email, google2_password};

    wallet.items[google1.get_id()] = google1;
    wallet.items[google2.get_id()] = google2;
    wallet.timestamp = 1493189805;

    return wallet;
}

TEST(SerializationTest, SerializationTest) {
    std::string json = electronpass::serialization::serialize(test_wallet());
    std::string json_string = "{\"items\":{\"YTBZGOOr/w13Vef8zFkm+YHGsutFGzSp\":{\"fields\":[{\"name\":\"Username\",\"sensitive\":false,\"type\":\"username\",\"value\":\"open_user\"},{\"name\":\"Password\",\"sensitive\":true,\"type\":\"password\",\"value\":\"secret_pa55\"}],\"name\":\"Google\"},\"epW6aIyR6eBLmyQkgYG/KIDKWr0w0vba\":{\"fields\":[{\"name\":\"E-mail\",\"sensitive\":false,\"type\":\"email\",\"value\":\"electron.pass@mail.com\"},{\"name\":\"Password\",\"sensitive\":true,\"type\":\"password\",\"value\":\"reallynotsecurepass123\"}],\"name\":\"Google\"}},\"timestamp\":1493189805}";
    EXPECT_EQ(json, json_string);
}

TEST(SerializationTest, EmptySerializationTest) {
    std::string json = electronpass::serialization::serialize(electronpass::Wallet(1));
    EXPECT_EQ(json, "{\"items\":null,\"timestamp\":1}");
}

TEST(SerializationTest, DeserializationTest) {
    std::string json_string = "{\"items\":{\"YTBZGOOr/w13Vef8zFkm+YHGsutFGzSp\":{\"fields\":[{\"name\":\"Username\",\"sensitive\":false,\"type\":\"username\",\"value\":\"open_user\"},{\"name\":\"Password\",\"sensitive\":true,\"type\":\"password\",\"value\":\"secret_pa55\"}],\"name\":\"Google\"},\"epW6aIyR6eBLmyQkgYG/KIDKWr0w0vba\":{\"fields\":[{\"name\":\"E-mail\",\"sensitive\":false,\"type\":\"email\",\"value\":\"electron.pass@mail.com\"},{\"name\":\"Password\",\"sensitive\":true,\"type\":\"password\",\"value\":\"reallynotsecurepass123\"}],\"name\":\"Google\"}},\"timestamp\":1493189805}";
    electronpass::Wallet wallet = electronpass::serialization::deserialize(json_string);

    EXPECT_EQ(wallet.timestamp, static_cast<uint64_t>(1493189805));
    for (auto it = wallet.items.begin(); it != wallet.items.end(); ++it) {
        std::string id = it->first;
        electronpass::Wallet::Item item = it->second;

        EXPECT_EQ(id, item.get_id());

        EXPECT_EQ(item.name, test_wallet().items[id].name);
        std::vector<electronpass::Wallet::Field> fields = item.fields;
        std::vector<electronpass::Wallet::Field> test_fields = test_wallet().items[id].fields;
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
    EXPECT_EQ(wallet.items.size(), static_cast<unsigned int>(0));
    EXPECT_EQ(wallet.timestamp, static_cast<uint64_t>(1));
}
