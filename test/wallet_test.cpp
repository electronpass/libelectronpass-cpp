#include "gtest/gtest.h"
#include "wallet.hpp"

TEST(WalletTest, ItemInit) {
    electronpass::Wallet::Item item;
    EXPECT_TRUE(item.get_id() != "");

    item = electronpass::Wallet::Item("test");
    EXPECT_TRUE(item.get_id() != "");

    item = electronpass::Wallet::Item("test", "id");
    EXPECT_EQ(item.get_id(), "id");
}

TEST(WalletTest, GetIds) {
    electronpass::Wallet::Item item1("item1", "id1");
    electronpass::Wallet::Item item2("item2", "id2");

    electronpass::Wallet wallet;
    wallet.add_item(item1);
    wallet.add_item(item2);

    std::vector<std::string> ids = {"id1", "id2"};

    EXPECT_EQ(wallet.get_ids(), ids);
}

TEST(WalletTest, Merge) {
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
    electronpass::Wallet wallet1(items, 1493189805);

    items["YTBZGOOr/w13Vef8zFkm+YHGsutFGzSp"].last_edited += 10;
    electronpass::Wallet wallet2(items, 1493189815);
    EXPECT_EQ(electronpass::Wallet::merge(wallet1, wallet2).timestamp, static_cast<uint64_t>(1493189815));
    EXPECT_EQ(electronpass::Wallet::merge(wallet1, wallet2)["YTBZGOOr/w13Vef8zFkm+YHGsutFGzSp"].last_edited, static_cast<uint64_t>(1493189715));

    wallet2.delete_item("epW6aIyR6eBLmyQkgYG/KIDKWr0w0vba");
    wallet2.timestamp = 1493189815;
    std::vector<std::string> ids = {"YTBZGOOr/w13Vef8zFkm+YHGsutFGzSp"};
    EXPECT_EQ(electronpass::Wallet::merge(wallet1, wallet2).get_ids(), ids);

    items["YTBZGOOr/w13Vef8zFkm+YHGsutFGzSp"].last_edited -= 20;
    wallet2 = electronpass::Wallet(items, 1493189815);
    EXPECT_EQ(electronpass::Wallet::merge(wallet1, wallet2)["YTBZGOOr/w13Vef8zFkm+YHGsutFGzSp"].last_edited,
              static_cast<uint64_t>(1493189705));
}
