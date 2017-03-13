#include <iostream>
#include <string>
#include "crypto.hpp"

int main() {
    std::string message, pass;
    std::cout << "Enter secret message:";
    std::cin >> message;
    std::cout << "Enter password:";
    std::cin >> pass;

    std::string s = electronpass::crypto::aes_encrypt(message, pass);
    std::cout << s << std::endl;
    return 0;
}
