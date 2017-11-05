#include <gtest/gtest.h>
#include <string>
#include <map>
#include <vector>
#include <set>


#include "crypto.hpp"

std::string random_string(int len) {
    std::string out(len, ' ');
    // rand() is not actual random, but it is probalby ok for testing.
    for (int i = 0; i < len; ++i) out[i] = static_cast<char>(rand() % 256);
    return out;
}

TEST(CryptoTest, EncryptionDecryptionTest) {
    electronpass::Crypto c1("password");
    electronpass::Crypto c2("Password");  // small change in password

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

    bool ok = false;
    std::string enc = c.encrypt("", ok);
    ASSERT_TRUE(ok);

    ok = false;
    EXPECT_EQ(c.decrypt(enc, ok), "");
    ASSERT_TRUE(ok);
}

TEST(CryptoTest, EncryptionUniqueTest) {
    electronpass::Crypto c("password");

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

    const std::string text = "Hello, Encryption!";

    // String text decrypted multiple times, with same password.
    const std::vector<std::string> v = {
            "OynXbZPP4m/dlAznNpxtoYt8hAkQRn95Sk31pAYi31aiKnYb9Q6HZ43pf5x8CDLlTb4GcVtvQUmskz4jH0PCS3mfambN4QJ1RKCQxxbqGFE=",
            "uKVZNhebvPhIp7O2jbaV7VPNT2h3Pw5d5S02Sv1AA+m23offcOZxGRVzFAeUzrc1pkRyCTpiEAyKprvEqbhqmPaQ0pKfDIB7K2H48OVQJ8c=",
            "M5fd9hY68MjhvAcRE2WdM/HI0bcl/AhYBT4otkOIc9+cxexKOYa5gcRvc9nKI7C9zOtxMOC/Y8lgkyY5B9hRpnGdqGPecD1syZIFvQzYKAI=",
            "W+QwA06aegCuCYoSPLIilH0S5MsEWFYQg7rI2Vo3GX19/RrMS0X9sOGuzUxKU/eULX4zhoJHnG746Ax11F3n+Z6y685/NSixQ3n3efqUhGY=",
            "gvrhEl6WHyx8pYWp3Yuav204tfiCA1M8cD1XqU2WyWttQz8dYQpAeGl3mxXfUfk9vfk56b5t+jUlh94wcKU0Oe9GwRXhwm85FTjpqhG4snc=",
            "uwJAp94bX1ktlfWb5bKoBHTDMyyYP/GjkBZvZhsMs8PRJYkl0OXBj+vnptNnS28SzNEvutLcVWYqmdi5tZ3uKXtFKsYN5wNRXZB6SHajcI0=",
            "V/GMCO5C65+IEy+cBVm1SnKjEm78vBO7qPCclJhVQfhDLa91qbxWLZ8sKZBiTEWEra0ZNfBx6QdBPqHY+AizW0cMQInwHfF9V7nru/0if3w=",
            "1tMqwj6W7kg0b8oKvgi9rl571kGTo4JelZP6bakw3/PQsgdulWHicFiwpE1lE0LxWMv6LHJeUY1K/veaKOCrnTLhoP9QIQDYaw6Xd3koWNg=",
            "mrWBZ15GLYxYOWI9I8vs5uXR/+sZBwfzP2Cdmryb4jXWvcbN6QKxVCScxVzJCaLdsunJW2hRABQAG0lCvQlrnk8rX6dr3aiwdQV12GEiCCY=",
            "++b102i/Yk4pyeLBHUtngFo8ERwHj1oGM1lDgTP0ulXu103cF9nI/WSLso5nWR98iRElxvZAHBA4BO+Q6qN2FHBjzolbWgpkcMZWOj/CYoc=",
            "qnoV1WTkEy8gsYQfQdHdGSxvCszOOJJUHePS8MNMZqk6fqMdURH0pj8jC45vWWYOTUailWDrRnmUPKXM7X3HM2U+iLr3ktinjxEyPlp5Li4=",
            "pZbQix+QDgvWW4FhjAK4oOxwC4BGjWY73dz/SnoSqCjlgd53jEUDUlC9QWRalM7WP0CcuBZ3P5TM4ABhT8w0iYSLSr+Y/BQ/wzDSx0xO95Y=",
            "qHj2CgpYkboZu7JoHBz/rnsFcw1X2U4wDzutf0qOfqsgeaIKYUO09eyzSwd2aFModkkzOgjn8uvrcolmolpWSSCOX2gRchIwUw3LHLRGDeY=",
            "ncL0S8r5jWSYvcxgOh3UA99nrQViqtibxVd2b80CiT/J6Y5RnDb2bMdSOdME7lATfTH7dW0eQEyl+qXABhzCv2tEfrqQPSjew+yJG1qLuAs=",
            "WtwL4VC17eOoW3haBItvAOcfSFSLbc2bQhaanbwjSR1Wx846Z2h/OPa+7NnXGBKO9fl6ycaeDmrCedK01Lr014xDstxM8SjutvI9tzWnAdg=",
            "NFUHGvsDzyW9yJNuqUCWgUfMW1PhZakpeV3PI+4717KXcY4al1TACmhtRi2AtKICZUFc4b6o6H0Tw4hT6ed3Fs95kq/IojORN614qszDaXQ=",
            "Rb2eqfYAfq56x0Ve/CoviwLuZWDP8Uzm1kY0UYrxDtWC8wlghgCnVjL2h4LoiE5RcunvOgMvE5PLtJWyPhmXztRgg6eJ58gkXgatNCDLApw=",
            "8C4anUXPO/FQwV8lryNF5H22PoT5rwcU6wvp7fCKr++BqZEGxzsAEdQCYfXM4Uuhq/1NJWoxUAXKJYUZhvRe8rl+wyP5sU+YsNt8p+ZpidU=",
            "jiO13Y/aztkTv9IIqXiYDcKjfirPG6KZpU6qpL0nQVE1wx5zYAvfEImgXzC7cq+7tVXO3bD/ofQuXROihYcEoF8gFrChEt2eVgzpm/3/6w8=",
            "UXjuE34MYwz4mwXYcIOp5V33IrhNtIfwhQz4f3udIvNDtxMqq9/NwxumiugW25NE/vJC+K7KV6CH0mFIL4dlnVkONppF+cwCow/kVLGuR4w=",
            "wlM4MIRA5VAyqGS5XjNBNcks7ihYSIyUBt05S4C+dMHP9uftQPJ10ZoRzsJZgK0JycdTSCX562dk4++Y4dFJ0xPS/E+NKlwe9E9Bt1C5GkQ=",
            "hGvQeI+XnbHQseCK59QwGSa4EbsQckCMl4+hxjJqmDFfswMF/n78fnGsLvgFZ1BCfQNyjjr4w5gyJcZCT4+FPLJsNC+IaZwzjV3qkG74cG4=",
            "yoEzSe5sXerdNPperjeAni7Q3Cj2+/ZCNQTnnRtawu3jhavT0DUJaK+LySyUHwKJMm1BnAVv+WCgUO0fhr7ImbEM699+htGjCOKi0R6sbIY=",
            "bDn1yBkhbaaZXlIwE0cWLGy/wgSWLaqtmxW54Z8ggs3SOK9uOUafHvmRfzya4/d36ZdPnb39KuG+z/HPar8cYBRbTmMVstNEROUWrVNp3Is=",
            "MDCV2QBb5Dc9dRom3sXjaPI1nruceli+3EHm+V9VX0o/lWK7i6mQFRJk2aBIV7+XE9oRpF15XpitmjQWvBfdoTt1oQ99z/0/M/oFQCjdBJA=",
            "oLi6W/sPpkUDA0kcRNTwcqXM5d6lxM8rJct+F+YwakOGs8TZEwWSdzGSLrCNLlWkCy5qR7LjZ2McEBKscEiqBPu8wErMyM02cPqPkS9HFX4=",
            "k9LKM9FAHCtjZVmLeqv2+tzru+b40QQZHa1CfzGayiMZMg2WcFaZ1Jrvi//gz5PhzTaqK9i+lcDScxwEEFLCQ+OQ+NdUrIYPAYwGhNU9R4s=",
            "OZlSdZWQTYXTMLgKWjD6zDpVwEePGWgElSRWmOl9Ym5FEQkXO6/A5TnhA0frHFasa+FjKnMi92dNKfjeskG65RfVo+npBorolpNmPdLmX6A=",
            "HX2KHyzIhMAOgjhzIHnCbsyldHyTkQHrCtwr676Ulap7MfcqvdfwEeLrvAQXYYY4ANokz6JWRjrqrhkJJnpnR1P62ffMhPIrtqwITxe43Ng=",
            "m/BwxF7X/DhWv42UO6zg/JXRb1heNHDJM5ognxpD9vir+eRcgEt69H29ZqnRRSjgKGyVfWj1a82pPGdulk9L2+RscKgP2avNXxyIMVGFFvE="
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
    const unsigned long size = 10000;
    std::set<std::string> generated_ids;
    for (unsigned long i = 0; i < size; ++i) generated_ids.insert(electronpass::Crypto::generate_uuid());
    EXPECT_EQ(size, generated_ids.size());
}
