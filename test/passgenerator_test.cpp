#include <iostream>
#include "passgenerator.hpp"

int main() {
    std::cout << PassGenerator::generate_pass(2, true, true, true) << std::endl;
    return 0;
}
