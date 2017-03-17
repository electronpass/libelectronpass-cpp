#include "crypto.hpp"
#include "gtest/gtest.h"
#include <string>

TEST(Crypto, AesEncryptDecrypt) {
    // a bit more real test, not only hardcoded values.
    electronpass::Crypto c("Random2348password");
    ASSERT_TRUE(c.check_keys());

    int err1 = 1, err2 = 1;
    std::string s = "";
    EXPECT_EQ(c.aes_decrypt(c.aes_encrypt(s, err1), err2), s);
    EXPECT_EQ(err1 + err2, 0);

    s = "Test case.";
    EXPECT_EQ(c.aes_decrypt(c.aes_encrypt(s, err1), err2), s);
    EXPECT_EQ(err1 + err2, 0);

    s = "No matter whether you work on Linux, Windows, or a Mac, if you write C++ code, Google Test can help you.";
    EXPECT_EQ(c.aes_decrypt(c.aes_encrypt(s, err1), err2), s);
    EXPECT_EQ(err1 + err2, 0);


    s = "String!";
    electronpass::Crypto c2("NewTotally()Random_password29013");
    std::string s1 = c.aes_encrypt(s, err1);
    std::string s2 = c2.aes_encrypt(s, err2);
    EXPECT_EQ(err1 + err2, 0);

    EXPECT_NE(s1, s2);

    // aes returns error here (4, aes final)
    // EXPECT_NE(c2.aes_decrypt(s1, err1), s);
    // EXPECT_NE(c.aes_decrypt(s2, err2), s);
    // EXPECT_EQ(err1 + err2, 0);

    EXPECT_EQ(c.aes_decrypt(s1, err2), s);
    EXPECT_EQ(c2.aes_decrypt(s2, err2), s);
    EXPECT_EQ(err1 + err2, 0);
}

TEST(Crypto, AesEncrypt) {
    electronpass::Crypto c("Password");
    ASSERT_TRUE(c.check_keys());

    int error = -1;
    EXPECT_EQ(c.aes_encrypt("Hello World!", error), "w11i25gDPJ3PSORPKWR83w==");
    EXPECT_EQ(error, 0);
    EXPECT_EQ(c.aes_encrypt("Hello World.", error), "pzeNvjZPf+u1era+1byCTw==");
    EXPECT_EQ(error, 0);

    // empty string
    EXPECT_EQ(c.aes_encrypt("", error), "BKwpddXiIQsS3u5Xw797Gw==");
    EXPECT_EQ(error, 0);

    EXPECT_EQ(c.aes_encrypt("More than 16 chars long string.", error),
        "EXZyB7NtkJHe0+UgmE6CrsqkSjcaqGQcpqKOgDW0IkA=");
    EXPECT_EQ(error, 0);

    // length 16 chars and 15 chars
    EXPECT_EQ(c.aes_encrypt("Simple test case", error), "TxYz6d8b+Zh8B69YE7IC/dxsF6ZGtUhw8pLzu1IF9G8=");
    EXPECT_EQ(error, 0);
    EXPECT_EQ(c.aes_encrypt("Simple test cas", error), "7CcQbKgVkIxtfQIU2PfDpw==");
    EXPECT_EQ(error, 0);
}

TEST(Crypto, AesDecrypt) {
    electronpass::Crypto c("Password");
    ASSERT_TRUE(c.check_keys());

    int error = -1;
    EXPECT_EQ(c.aes_decrypt("w11i25gDPJ3PSORPKWR83w==", error), "Hello World!");
    EXPECT_EQ(error, 0);
    EXPECT_EQ(c.aes_decrypt("pzeNvjZPf+u1era+1byCTw==", error), "Hello World.");
    EXPECT_EQ(error, 0);

    EXPECT_EQ(c.aes_decrypt("EXZyB7NtkJHe0+UgmE6CrsqkSjcaqGQcpqKOgDW0IkA=", error),
        "More than 16 chars long string.");
    EXPECT_EQ(error, 0);

    // length 16 chars and 15 chars
    EXPECT_EQ(c.aes_decrypt("TxYz6d8b+Zh8B69YE7IC/dxsF6ZGtUhw8pLzu1IF9G8=", error), "Simple test case");
    EXPECT_EQ(error, 0);
    EXPECT_EQ(c.aes_decrypt("7CcQbKgVkIxtfQIU2PfDpw==", error), "Simple test cas");
    EXPECT_EQ(error, 0);
}
