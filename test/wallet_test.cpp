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
    electronpass::Wallet wallet1;
    electronpass::Wallet wallet2;
    ++wallet2.timestamp;

    EXPECT_EQ(electronpass::Wallet::merge(wallet1, wallet2).timestamp, wallet2.timestamp);

    wallet1.timestamp += 2;
    EXPECT_EQ(electronpass::Wallet::merge(wallet2, wallet1).timestamp, wallet1.timestamp);
}
