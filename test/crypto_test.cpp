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

    const std::string text = "Hello, World!";

    // String text decrypted multiple times, with same password.
    const std::vector<std::string> v = {
            "9y9PkspGUZgI56KGhYUmHu7XG9LYDLG/1ayXLXKNxZ+33A7tryDGy2O15fgRpPgKOIOwJ9O5bLb8EOfQkHyPJg==",
            "QgrIro1dl9WqJXidN6ED9VXwf632G9AKesL3W39Rx/Pac1TGbLLMAmfWsS/4HmIvLCJS9hlP5y/W0+7/QP42nQ==",
            "NUybIMbpKvEuCtVHqrZIEYQO19W3TQz5uNfuHo+PwnGQPxe1Vpta5AHLNqx3b5KKdoM4EyJbmkCxu57a1bLP8Q==",
            "qXdP55txqW85hKe/m3HqR4WB5WndTxZ4qQbrTGHrYaxytDesT3NMAcX9N9hoETfUZyBkPfe6FtJsg9qhv8xF0w==",
            "kkS7cXILNqUIDzl8fxbtnnIpVyymVGWGw8c4yO7IYAb1w1t3XwsT8tPWN2uPQs592gB1vp84+KMHbWnx3qEpgA==",
            "Tz7Yjn1LrBzRNwLnjF4Zn1L/q+Dp2ATFgMRFHt8dIC1/aI7nMLXQJvXBeZC/nRAaxndE0JOWwom9bny8+quYxA==",
            "+ZNp2ee1UKFNz824mhgsOQBrgkeiQWmzVNaM9OUw/sk/R/S4+ZX7riqlb/jCVO3iVuzee1lNsi5s2yMW4fS0Ng==",
            "UJIkf5r3MunJ+PGDOK3PkDpnocycUvPS+EgSK16R7KNvLihhWOUcP/eSOT9gt7L9ZGKzxP6AIKcIczAAqjOssg==",
            "OePFEnIhjUjoY4UYje12yfdcK96PM+MlrkJnH0+SfGGiVqjDRTriMxq7SXA37EiJv0VLgyOHr83eXRI25IOClw==",
            "HWx/9PNYgS3nk4Z8a+z4TEZTnMLYQMlAJZgKOkdrCIXlxhWXq9M0VCyIGeLva4jZaa5U5ZYOcCaYXhlsSwLghQ==",
            "Qg3j4a6ku7GTfkTX77rvnnLiY4RRRtZXwUZLJD8Wo6wkay1nsjL9ocjoEILoRj+9dUqcrvijY7kOpwLi+JyS/g==",
            "vft2VJ09hUw/SnDEVd+EZoOt4c/avrVmVa5bqf+FEvS9KbdO5HViKJpzG+F6iDS7Q7MDbOBkuIH22wXX6aCJVQ==",
            "zMvVdRC/ypKzxkpwYs65ynkgDGi+z18njiXty/j9BWOPf+XRkGLIDxTWIqaZl7OnD2L4aLvAE5FFYSCJRIA+yA==",
            "0gFOFrkjPd0UIzJenBZ8jvUcKFNqND7MB+ASyDq4sM4jBYlCYSW2SPpu2dPcjsyhQso1vCrH9A9kK2Z8wQyYtg==",
            "L54Jr043IjgaFhjUGef1biwNXstBeVDyNowK5ivLirRfS1FmMinzJQipd4yr7xU80MPJ+pbHruWbo7ioPYrLvg==",
            "7F8lQe82rs2VYwHb0QYUijxyEThqlWbJCcHMaUg6JaRARCxiDHyOJkbJOFl0atejR9demI2TXz0ipCwZCRv7Dg==",
            "ssNWOeyr9L2DXrWhIAIqCY134DhvNFhfyjRHPRuHR+QrwwuPDcA+PDOAzB8r43qGTJStLDMce8JDyzDxo5Mwpw==",
            "wMCgWbBMQJelJhzfGagSogrB5/nhHA7epkNYR1l3NCF4ljtJq1zwSTSqBKaLMWyKEdCRvl+YegYYJrblq4BJfg==",
            "/7rkGnu5eAUkBr9ggmN9h46Fj66xof8UUiHDD8XKpQwBRI3ZwUzSt7F2pTCvl7DKRClH2KALDlu4zNFQOlXtdA==",
            "2r6iA5hlN9KVFM4flkIrXST1lfcUaVmBIfcjYkJAWQooz4U/gufg3Im5IauEqeeEvsfBW2O/DJCECYYsNEdtXw==",
            "8zxlyAuQ7ua7grvJrMIqAP0y0Ul7KE4tVJRvyccVaePaQvJ7IlOC9Qd51endYQQvjMYX6VyzYa9DbaVXrLEO5A==",
            "mXUJ7M1ml0uafn5xtgEorCYtkcOWVHRmYf4Y2JHOM1CKwCf0ymAc1dd41U/dVUhvvh6OYmL+kbK0iMuu1RhWUQ==",
            "p8/Arh44Ng+MZIL1eCYG0i5n3qKBpX5aJ6YzoZnUCIUQPamX8cEX6kMbPeoG2aLb7oa24AqV9n+S/6RQKPpcrA==",
            "JUeUTFDk759UxbxkwxdT4MvMIaIp7U0JZqs7Y8Te6VuIClAUPPiEy2Qrn+5QFwLyr80e1HMIsX2Xsf5Uzjie8g==",
            "PNYJM+cYLvHBF5dbKoID0ID/qdMjf+ib7U01/6Idb+ENvUq73NglS2ITDZiSmPplAS7BZ3KuFlMgiRllnFrCEg==",
            "v7LIJesog6m/k0j+KnHQ2YLSC+rVSi9WuVul3l8BJ3w5CcC7k6SX14Mz9QUrxGGec2Dow0oBWKRt4xKFvYlFJg==",
            "xK8bnAXK9kj6K4wHZCN/94vBORU8YI8GerbP/lxe+obHEEdypIu+KVBr1jCdznPLjnY8P0tun/Ir4d486JGW7A==",
            "v0Fm5FTHdEMiLyo+Qs5oGG4oA8bF8O7ZnnVEWeVORUUvtcRQZsEAlSYaVy3MCAbMu78gNZoxdxule6aH+jX07Q==",
            "ntSkEh/+GSPZ44QZUNBi+J9x7r0bXrr+D2oI37ASM0BTttCjAFJihjWNCqOD8HGwEE1VtEq0NO02+yvvyIG6Zg==",
            "VQXM1jt6MSB+hi4gv4zpYu7cvrZt1GSHiEuzC13ZUT1xa3M3S+t8Qcg4XvreCl+Y5QkUUMFIC+iPPEMM3DftHA==",
            "O4toqaCFTmhfox2b2cJ7z4Ha4y/vXuAOrzoXu6377wAV7B41rH6TlCtp0dnH4eAk54/ejR5Jb7rfG+dtlSu0oA==",
            "d94VWLSPj//7hFumU9SemeGdYGUJ1JQp6u/TSQZfz6kEEqqgN2RBltC7bJ+6d4715x3IcYTyAi0XGEjT78rpYA==",
            "VxBhZY079nt/f0wBRzeYDV2EArQE5fiRSLL705NZm2TbxKs5X/YgWkxIdj4QchETYD5l0Wl9Y+KNwz+Pp/Pn7Q==",
            "eMc/KU/TQp+FdyfTEi9+ZqTKSCdEUMUgHjj3X1kdjzBV88GqflNy+75GWIgUEetFNnH+QRIwEZw3lAxVsWkKKQ==",
            "Kgo3ZXC2pvMCTidSy7cCIk5+V1oNSzHGoAnR0MNvpVXVsmUCRuia66dIbgHSPAFN30ClGR8GXXSgFdFhZGhhgQ==",
            "ccf32K6U6uMR0O9G8aLDUbz5eeK/OcvN5rjBdXmwYZ7FulCH/zHVVs8/C040OGJhHQYL2LD/Kzp4zW4xFDpboA==",
            "bnTMjCLUE5xBiSXymNFxenFYRWmvgO2OVF0DNkWYm0yoUGvAmJFqxko1AxSZpOgVN3PLZCRY11/LpwhiAxLdog==",
            "fh4DPlWWc2nbLTpxpkDMeHFPhHI6eJobVtywxKje+dlvNS/KQ47Azy+Gts/H7nZMD1qyh5xuTBGe+z6R6O1AhA==",
            "qf4Lz8WsdM45VwdNoSvtD3x5euts+nV8xzpRlL9evTzWUUHszR9NPezFF5HuZMV5js9EC8G1ZuGGBkBEDpM1XA==",
            "IkRxy9nmhdvFIxGIN6wrvZWwDI4aSXJHNv1+143/iS5ftTXGJaGuuFLMVAhbkWyyu9IyJW1IxMwfq/1lY0rdgQ==",
            "qHpNNIPqtAk6MF/VflorrejVTpOsEQ1Jxby7yAWBggOz+9cmE6lL2ic8VyCDLg9aYtapvHIez7n9kdJcDJS04g==",
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
