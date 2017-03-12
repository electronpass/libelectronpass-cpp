#include <iostream>
#include "serialization.hpp"

using namespace electronpass::serialization;

int main() {
    const char* json = "{\"test\": true}";
    deserialize(json);

    return 0;
}
