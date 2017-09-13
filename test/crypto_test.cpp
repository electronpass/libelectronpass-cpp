#include <gtest/gtest.h>
#include <string>
#include <map>
#include <vector>
#include <set>


#include "electronpass/crypto.hpp"

std::string random_string(int len) {
    std::string out(len, ' ');
    // rand() is not actual random, but it is probalby ok for testing.
    for (int i = 0; i < len; ++i) out[i] = static_cast<char>(rand() % 256);
    return out;
}

TEST(CryptoTest, EncryptionDecryptionTest) {
    electronpass::Crypto c1("password");
    electronpass::Crypto c2("Password");  // small change in password
    ASSERT_TRUE(c1.check() && c2.check());

    for (int i = 0; i < 1000; ++i) {
        bool ok1 = false, ok2 = false;
        const std::string text = random_string(100);

        std::string enc1, enc2;
        enc1 = c1.encrypt(text, ok1);
        enc2 = c2.encrypt(text, ok2);
        EXPECT_TRUE(ok1 && ok2);

        ok1 = false, ok2 = false;
        // normal decryption
        EXPECT_EQ(c1.decrypt(enc1, ok1), text);
        EXPECT_EQ(c2.decrypt(enc2, ok2), text);
        EXPECT_TRUE(ok1 && ok2);

        // decryption with wrong password
        EXPECT_EQ(c1.decrypt(enc2, ok1), "");
        EXPECT_EQ(c2.decrypt(enc1, ok2), "");
        EXPECT_FALSE(ok1 || ok2);
    }
}

TEST(CryptoTest, EncryptionDecryptionEmptyTest) {
    electronpass::Crypto c("password");
    ASSERT_TRUE(c.check());

    bool ok = false;
    std::string enc = c.encrypt("", ok);
    ASSERT_TRUE(ok);

    ok = false;
    EXPECT_EQ(c.decrypt(enc, ok), "");
    ASSERT_TRUE(ok);
}

TEST(CryptoTest, EncryptionUniqueTest) {
    electronpass::Crypto c("password");
    ASSERT_TRUE(c.check());

    const std::string text = "Hello, World!";

    // Checks if every encryption with same password is unique.
    std::map<std::string, bool> encrypted;
    for (int i = 0; i < 1000; ++i) {
        bool success = false;
        std::string enc = c.encrypt(text, success);

        EXPECT_FALSE(encrypted[enc]);
        EXPECT_TRUE(success);
        encrypted[enc] = true;
    }
}

TEST(CryptoTest, DecryptionUniqueTest) {
    electronpass::Crypto c("password");
    ASSERT_TRUE(c.check());

    const std::string text = "Hello, World!";

    // String text decrypted multiple times, with same password.
    const std::vector<std::string> v = {
            "JXR9gNdT2jPAChnKkVAJalZu0bx3Fec1lSsloA9XzTq6S3D9yw==",
            "LnIyhCzBCSUYg5hYGDIAlYYBle1Rw6IPP5Y3PytpJUoaGziuww==",
            "zufJB/J1uzF/efUBi3MkhGFT2j5189t7gdL76oq0MZsTFaddQw==",
            "hOfYxsrp98DR6bQeAC8x7/k1zgY/OFULFADKAo5on/lMibAW/Q==",
            "FO2Lf6rTV00lYw8sTyCNaHwxTYLG+rpHr+2osIDmd2xPxDEBEQ==",
            "bA0T/JC2xJtX/L2Ljxos+oPdJg0PHz6PtE/FMv5LqAIfv9Glew==",
            "q7xAe4fjUTjwwQeATJbFotiiy1x00aZ6iipaHWStS3is28Xqig==",
            "fSo5TU6mFPuGC8kIBSxQNSZ7PaB6aT6eb76fVbEPQlsRqtM6eg==",
            "E9hFcJb3UdsiR2IbBjIrDaxUm5EgTnl/M5zcFwdWTvGXIW33kg==",
            "KL3XOYwF+Jv2ljsYd/k4/XXZTtlxbrfaokOUorxCkoB4qrGaxA==",
            "KcfPgRdMPDIu2TQeT/vF1KfY9KCZzZC/ovEvRxG6dd+sCMpkcQ==",
            "MZBMkuGl82MmFTl9ZOQ+Dx3o0NRpyUKqjP8o4PxyF8GjfDVezA==",
            "hGniqmFNgDk/L9+RnGfRoTxLvC9oXknjBjl50ni++UDhLn+8AQ==",
            "U2Mp4kkT1kdL3II9MYlIZH+g2pzV6QFuA0ZXIriYiY4S2kyprg==",
            "ueRAlrk8i/jJqlF++3UqfSr/so7uU1uxvbp0KNYNEmxVWLmPKw==",
            "0hBE/pZZ/vhelp7lTe/ZY0DU7oUf8umfGJNSkuxj8Pj8ywp6PQ==",
            "+6/4A+ifs6dlKk6Bon6TyGDw1q5REV2i4R6SP4kMbKLlxMtpCw==",
            "ie/G2pxCRYi7Kzwsiua+/6vmf43ZdL1YXtiaz1xSNxpDMWfqZQ==",
            "8/aPhNZ48kRfdCeAIQleV7sel6GVwgea03tqZQIgtiKsnsz5bA==",
            "NRDApCbtCFCWnahAQ4Qdvn2SwTeP0saxTqetG54vwWpnPd0/Sw==",
            "3GLNknfTjDK0DwJbXnNAjea0rWI5HduIvJcdp6+4si1Gfwaxew==",
            "KIoOWyc/RuqvVgpZDw5VxQvuHapMAN2u8hbfJsyhwYqy6v0urQ==",
            "lnzH8qVW7rklfMMlJf6QqISxD9QW0YDABqPJPE/0aLzvNK8xBQ==",
            "wvx2Xa6K4GPW2YVZnDTya8Pgec/AHS03SJdY//ms/IPu9xr7Iw==",
            "jj3+kOBk970U3RHOfTLSLRaL8AUHKfwgvxUk0OaGedKw+4QuaQ==",
            "dHSUT/oes4UcOyq8AUS4kdbignb2KPu460jqonQ+9YXc2rMo8Q==",
            "zcrGKe+ncAOe1iO/FXe3Dv9/ZIGk8VhuDzCbSzNJgt5g0D5FAA==",
            "Vu4c6HhTwXjw3qZCO3xEPum0hZRCkPI/H1SHQL/H/WI9GMH6Kg==",
            "r+xsNXdzT2IdHOegdMw4WTjj1YHf2R0qi52JwIKhzgY3ZRX3kQ==",
            "M6mNnDPdNIK1Bjtl87HHPXooQlWpIAcnhui4CVGdLizKte4veQ==",
            "KrOmhJGuId1SVvK+msGqsKnj52SuMR06OJnyKzuP7cPUnBZSHw==",
        };

    // Checks if every decryption with same password returns correct value.
    for (unsigned int i = 0; i < v.size(); ++i) {
        bool success = false;
        std::string dec = c.decrypt(v[i], success);

        EXPECT_EQ(dec, text);
        EXPECT_TRUE(success);
    }
}

TEST(CryptoTest, UniqueIDTest) {
    const unsigned long size = 500000;
    std::set<std::string> generated_ids;
    for (unsigned long i = 0; i < size; ++i) generated_ids.insert(electronpass::Crypto::generate_uuid());
    EXPECT_EQ(size, generated_ids.size());
}
