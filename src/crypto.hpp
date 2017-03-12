#ifndef SRC_CRYPTO_HPP_
#define SRC_CRYPTO_HPP_

#include <openssl/evp.h>
#include <openssl/aes.h>
#include <string>

class Crypto {
private:
public:
    Crypto() {};
    ~Crypto();

    bool init(const std::string& key);
    std::string aes_encrypt(const std::string& plain_text);
    std::string aes_decrypt(const std::string& chiper_text);

};

#endif // SRC_CRYPTO_HPP_
