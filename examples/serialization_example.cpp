#include <iostream>

#include "serialization.hpp"
#include "wallet.hpp"

int main() {
    // Serializing wallet:
    electronpass::serialization::serialize(electronpass::Wallet());

    // Deserializing wallet:
    electronpass::Wallet wallet = electronpass::serialization::deserialize("{items: []}");

    return 0;
}