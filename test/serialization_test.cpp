#include <iostream>
#include <fstream>
#include "wallet.hpp"
#include "serialization.hpp"

using namespace electronpass;

int main() {
    std::ifstream infile("/home/vidd/Desktop/test.json");
    std::string json;
    std::string line;
    while (std::getline(infile, line)) {
        json += line;
    }

    Wallet wallet = electronpass::serialization::deserialize(json);

    std::string generated_json = electronpass::serialization::serialize(wallet);
    std::cout << generated_json << std::endl;




    return 0;
}
