#ifndef SRC_PASSGENERATOR_HPP_
#define SRC_PASSGENERATOR_HPP_

#include <string>

class PassGenerator {
private:
    // Set of characters to include when generating passwords
    static const std::string digits;
    static const std::string letters;
    static const std::string special_chars;
public:
    static std::string generate_pass(int len, bool digits, bool symbols, bool uppercase);
};


#endif //ELECTRONPASS_RANDOM_H
