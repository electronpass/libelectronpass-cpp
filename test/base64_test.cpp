#include <iostream>
#include <string>
#include <cassert>
#include "crypto.hpp"

int main() {
    std::string decoded = "Hello World!";
    std::string encoded = "SGVsbG8gV29ybGQh";

    std::cout << electronpass::Crypto::base64_encode(decoded) << " " << decoded << std::endl;
    std::cout << encoded << " " << electronpass::Crypto::base64_decode(encoded) << std::endl;
    return 0;
}
