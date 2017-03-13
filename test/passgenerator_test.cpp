#include <iostream>
#include "passgenerator.hpp"

using namespace electronpass::passgenerator;

int main() {
    std::cout << generate_pass(24, true, true, true) << std::endl;
    return 0;
}
