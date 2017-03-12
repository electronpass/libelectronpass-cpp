#include "passgenerator.hpp"
#include <string>

// Set of characters to include when generating passwords
const std::string PassGenerator::digits = "0123456789";
const std::string PassGenerator::letters = "abcdefghijklmnopqrstuvwxyz";
const std::string PassGenerator::special_chars = "!\"#$%&'()*+,-./:;<=>?@[\\]^_{|}";

std::string PassGenerator::generate_pass(int len, bool digits, bool symbols, bool uppercase) {
    return "random";
}