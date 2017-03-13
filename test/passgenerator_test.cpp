#include <iostream>
#include "passgenerator.hpp"

using namespace electronpass::passgenerator;

int main() {
    std::cout << generate_pass(24, 3, 5, 5) << std::endl;
    return 0;
}
