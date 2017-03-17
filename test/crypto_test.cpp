#include <iostream>
#include <string>
#include <cassert>
#include "crypto.hpp"

int main() {
    std::string message, pass;
    // std::cout << "Enter secret message:";
    // std::cin >> message;
    // std::cout << "Enter password:";
    // std::cin >> pass;
    message = "Hello, world";
    pass = "SecurePassword39";

    electronpass::Crypto c(pass);
    std::string enc = c.aes_encrypt(message);
    std::cout << enc << std::endl;

    std::string dec = c.aes_decrypt(enc);
    std::cout << dec << std::endl;

    assert(message == dec);
    std::cout << "OK" << std::endl;

    for (int i = 0; i < 10; ++i) {
        std::cout << "Enter text:" << std::endl;
        getline(std::cin, message);
        std::cout << "Password: ";
        std::cin >> pass;

        electronpass::Crypto c(pass);
        enc = c.aes_encrypt(message);
        std::cout << enc << std::endl;
        dec = c.aes_decrypt(enc);
        std::cout << "OK" << std::endl;
        assert(message == dec);
    }
    return 0;
}
