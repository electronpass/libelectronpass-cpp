#include <iostream>

#include "serialization.hpp"
#include "wallet.hpp"
#include "crypto.hpp"

int main() {
    // Serializing wallet:
    electronpass::serialization::serialize(electronpass::Wallet());

    // Deserializing wallet:
    electronpass::Wallet wallet = electronpass::serialization::deserialize("{items: []}");

    // Save empty wallet
    electronpass::Crypto crypto("random pass");

    int error;
    std::string saved_wallet = electronpass::serialization::save(electronpass::Wallet(), crypto, error);
    std::cout << error << std::endl << saved_wallet << std::endl;

    // Load empty wallet
    wallet = electronpass::serialization::load(saved_wallet, crypto, error);
    std::cout << error << std::endl;

    return 0;
}
