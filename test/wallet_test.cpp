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
