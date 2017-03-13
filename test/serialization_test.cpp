#include <iostream>
#include "data.hpp"
#include "serialization.hpp"

int main() {
    const char* json = "{\"test\": true}";
    electronpass::serialization::deserialize(json);

    return 0;
}
