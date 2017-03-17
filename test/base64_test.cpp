#include "crypto.hpp"
#include "gtest/gtest.h"

TEST(Base64Encode, Basic) {
    EXPECT_EQ("VGVzdA==", electronpass::Crypto::base64_encode("Test"));
}
