#include <gtest/gtest.h>
#include <tuple>

#include "passwords.hpp"


// passwords to test evaluation against
const std::vector<std::tuple<std::string, electronpass::passwords::strength_category>> sample_passwords = {
        std::make_tuple("neki", electronpass::passwords::strength_category::TERRIBLE),
        std::make_tuple("lineageosas", electronpass::passwords::strength_category::BAD),
        std::make_tuple("lineageosas101", electronpass::passwords::strength_category::GOOD),
        std::make_tuple("lineageosasasd", electronpass::passwords::strength_category::MODERATE),
        std::make_tuple("asdfasdfasdf101", electronpass::passwords::strength_category::MODERATE),
        std::make_tuple("danesjelepdan123", electronpass::passwords::strength_category::VERY_STRONG),
        std::make_tuple("danesjelepdanasd", electronpass::passwords::strength_category::GOOD),
        std::make_tuple(":L0^O[=X%O89", electronpass::passwords::strength_category::MODERATE),
        std::make_tuple("0y)T2ALv&Rdg:cP;]bx0", electronpass::passwords::strength_category::VERY_STRONG),
};

TEST(PasswordsTest, PassGenerationTest) {
    // test if passwords contain all the desired chars
    for (int i = 13; i < 100; i++) {
        std::string pass = electronpass::passwords::generate_random_pass(i, 3, 5, 5);

        //count chars
        int digits = 0;
        int lowercase = 0;
        int uppercase = 0;
        int symbols = 0;
        for (char a : pass) {
            if (electronpass::passwords::digits_list.find(a) != std::string::npos) {
                digits++;
            } else if (electronpass::passwords::letters_list.find(a) != std::string::npos) {
                lowercase++;
            } else if (electronpass::passwords::uppercase_letters_list.find(a) != std::string::npos) {
                uppercase++;
            } else if (electronpass::passwords::special_chars_list.find(a) != std::string::npos) {
                symbols++;
            }
        }

        EXPECT_EQ(static_cast<int>(pass.size()), i);
        EXPECT_EQ(static_cast<int>(digits), 3);
        EXPECT_EQ(static_cast<int>(symbols), 5);
        EXPECT_EQ(static_cast<int>(uppercase), 5);
        EXPECT_EQ(static_cast<int>(lowercase), static_cast<int>(pass.size()) - 13);
    }
}

TEST(PasswordsTest, PassEvaluationTest) {
    // test if passwords are evaluated the way we want
    for (int i = 0; i < static_cast<int>(sample_passwords.size()); i++) {
        std::tuple<std::string, electronpass::passwords::strength_category> pass = sample_passwords[i];
        EXPECT_EQ(electronpass::passwords::password_strength_category(std::get<0>(pass)), std::get<1>(pass));
    }

}
