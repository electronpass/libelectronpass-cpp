#include <iostream>
#include "passwords.hpp"

using namespace electronpass::passwords;

int main() {
    std::cout << generate_random_pass(24, 3, 5, 5) << std::endl;
    std::cout << password_strength("asdaaaaaff");
    return 0;
}