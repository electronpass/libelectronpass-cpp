#include <iostream>
#include "passwords.hpp"

using namespace electronpass::passwords;

const std::vector<std::string> sample_passwords = {
        "neki", "lineageosas", "lineageosas101",
        "lineageosasasd", "asdfasdfasdf101",
        "danesjelepdan123", "danesjelepdanasd"

};

int main() {
    // test random passwords
    for (int i = 1; i < 35; i++) {
        std::string pass = generate_random_pass(i, 3, 5, 5);
        std::cout << i << " " << pass << " = " << password_strength(pass) << " "
                  << human_readable_password_strength_category(pass) << std::endl;
    }

    // test some real passwords
    for (std::string pass : sample_passwords) {
        std::cout << pass << " = " << password_strength(pass) << " " << human_readable_password_strength_category(pass)
                  << std::endl;
    }

    // let user pick some passwords to test
    std::string pass;
    std::cout << std::endl;
    while (true) {
        std::cout << "Pick a password to test: " << std::endl;
        std::getline(std::cin, pass);
        std::cout << pass << " = " << password_strength(pass) << " " << human_readable_password_strength_category(pass)
                  << std::endl;
    }
    return 0;
}
