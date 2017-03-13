#ifndef SRC_CRYPTO_HPP_
#define SRC_CRYPTO_HPP_

#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/err.h>

#include <string>

namespace electronpass {
    namespace crypto {
        std::string aes_encrypt(const std::string& plain_text, const std::string& password);
        std::string aes_decrypt(const std::string& cipher_text, const std::string& password);
    }
}


#endif // SRC_CRYPTO_HPP_
