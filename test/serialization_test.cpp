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

    std::vector<std::string> items = wallet.get_items();
    for (unsigned int i = 0; i < items.size(); ++i) {
        std::cout << items[i] << std::endl;
        std::cout << "Fields:" << std::endl;

        int error;
        Wallet::Item item = wallet.get_item(i, error);
        std::vector<std::string> fields = item.get_fields();
        for (unsigned int j = 0; j < fields.size(); ++j) {
            std::cout << "- " << fields[j] << std::endl;
        }
        std::cout << std::endl;
    }




    return 0;
}
