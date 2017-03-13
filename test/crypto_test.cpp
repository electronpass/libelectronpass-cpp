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

    std::string enc = electronpass::crypto::aes_encrypt(message, pass);
    std::cout << enc << std::endl;

    std::string dec = electronpass::crypto::aes_decrypt(enc, pass);
    std::cout << dec << std::endl;

    assert(message == dec);
    std::cout << "OK" << std::endl;
    return 0;
}
