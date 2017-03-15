#include <iostream>
#include <string>
#include <cassert>
#include "base64.hpp"

int main() {
    std::string decoded = "Hello World!";
    std::string encoded = "SGVsbG8gV29ybGQh";

    std::cout << electronpass::crypto::base64_encode(decoded) << " " << decoded << std::endl;
    std::cout << encoded << " " << electronpass::crypto::base64_decode(encoded) << std::endl;
    return 0;
}
