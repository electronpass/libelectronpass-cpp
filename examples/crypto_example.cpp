#include "crypto.hpp"
#include <iostream>
#include <string>
#include <cassert>

int main() {
    bool success;
    std::string message, password, encrypted, decrypted;

    std::cout << "Enter secret message:" << '\n';
    getline(std::cin, message);

    std::cout << "Enter password:" << '\n';
    getline(std::cin, password);

    electronpass::Crypto crypto(password);
    assert(crypto.check());  // Checks if sodium init was successful.

    encrypted = crypto.encrypt(message, success);
    assert(success);
    std::cout << "Encrypted message: " << encrypted << '\n';

    success = false;
    while (!success) {
        std::cout << "Enter password to decrypt the message:" << '\n';
        getline(std::cin, password);

        electronpass::Crypto new_crypto(password);
        assert(crypto.check());

        decrypted = new_crypto.decrypt(encrypted, success);
        if (success) std::cout << "Decrypted message: " << decrypted << '\n';
        else std::cout << "Wrong password." << '\n';
    }

    return 0;
}
