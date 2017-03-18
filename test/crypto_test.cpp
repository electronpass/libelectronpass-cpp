#include "crypto.hpp"
// #include "gtest/gtest.h"
#include <string>
#include <iostream>
#include <cassert>

int main() {
    electronpass::Crypto c("password");
    assert(c.check());

    std::string text, enc, dec;
    bool ok1, ok2;
    text = "Hello, World!";

    enc = c.encrypt(text, ok1);

    electronpass::Crypto anoher_c_which_will_not_be_used("another password");
    assert(anoher_c_which_will_not_be_used.check());

    dec = c.decrypt(enc, ok2);


    std::cout << ok1 << " " << ok2 << std::endl;
    std::cout << enc << std::endl;
    std::cout << dec << std::endl;
    assert(dec == text);
    return 0;

}
