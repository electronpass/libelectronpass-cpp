#include <iostream>

#include "serialization.hpp"

int main() {
    // Serializing wallet:
    electronpass::serialization::serialize(electronpass::Wallet());

    // Deserializing wallet:
    electronpass::Wallet wallet = electronpass::serialization::deserialize("{items: []}");

    // Save empty wallet
    electronpass::Crypto crypto("random pass");

    int error;
    std::string saved_wallet = electronpass::serialization::save(electronpass::Wallet(), crypto, error);
    // std::cout << error << std::endl << saved_wallet << std::endl;

    // Load empty wallet
    wallet = electronpass::serialization::load(saved_wallet, crypto, error);
    // std::cout << error << std::endl;

    wallet = electronpass::Wallet();
    electronpass::Wallet::Item google("Google");
    google.fields.push_back(electronpass::Wallet::Field("Password", "moja mami", electronpass::Wallet::FieldType::PASSWORD, true));
    google.fields.push_back(electronpass::Wallet::Field("URL", "gooogle.com", electronpass::Wallet::FieldType::URL, false));
    google.fields.push_back(electronpass::Wallet::Field("Email", "mami@mail.com", electronpass::Wallet::FieldType::EMAIL, false));

    electronpass::Wallet::Item wire("Wire");
    wire.fields.push_back(electronpass::Wallet::Field("Geslo", "žigatova mami", electronpass::Wallet::FieldType::PASSWORD, true));
    wire.fields.push_back(electronpass::Wallet::Field("URL", "wire.com", electronpass::Wallet::FieldType::URL, false));
    wire.fields.push_back(electronpass::Wallet::Field("Email", "fotr@mami.com", electronpass::Wallet::FieldType::EMAIL, false));

    wallet.add_item(google);
    wallet.add_item(wire);

    std::cout << electronpass::serialization::csv_export(wallet) << std::endl;

    return 0;
}
