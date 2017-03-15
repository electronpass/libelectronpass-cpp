#include <iostream>
#include "passwords.hpp"

using namespace electronpass::passwords;

int main() {
    // test random passwords
    for (int i = 1; i < 35; i++) {
        std::string pass = generate_random_pass(i, 3, 5, 5);
        std::cout << i << " " << pass << " = " << password_strength(pass) << std::endl;
    }

    // test some real passwords
    std::string pass = "neki";
    std::cout << pass << " = " << password_strength(pass) << std::endl;
    pass = "lineageosas";
    std::cout << pass << " = " << password_strength(pass) << std::endl;
    pass = "lineageosas101";
    std::cout << pass << " = " << password_strength(pass) << std::endl;
    pass = "lineageosas";
    std::cout << pass << " = " << password_strength(pass) << std::endl;
    pass = "lineageosasasd";
    std::cout << pass << " = " << password_strength(pass) << std::endl;
    pass = "asdfasdfasdf101";
    std::cout << pass << " = " << password_strength(pass) << std::endl;
    pass = "danesjelepdan123";
    std::cout << pass << " = " << password_strength(pass) << std::endl;
    pass = "danesjelepdanasd";
    std::cout << pass << " = " << password_strength(pass) << std::endl;

    return 0;
}
