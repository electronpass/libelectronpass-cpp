/*
This file is part of libelectronpass.

Libelectronpass is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Libelectronpass is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with libelectronpass.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "crypto.hpp"
#include <string.h>
#include <string>
#include <cassert>
#include <iostream>

// TODO: BASE64 conversion of files.
// Lot of help from: https://securityblog.gr/2803/openssl-aes-256-cbc-encryption-in-c/

bool generate_keys(const unsigned char *password, int pass_len, unsigned char *aes_key,
                                                                unsigned char *aes_iv) {
    int AES_ROUNDS = 5;
    // instead of NULL there should be salt!
    bool success = EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), NULL, password, pass_len,
                                    AES_ROUNDS, aes_key, aes_iv);
    return success;
}

std::string electronpass::crypto::aes_encrypt(const std::string& plain_text, const std::string& password) {
    // convert strings to char arrays
    const int plain_len = plain_text.length();
    const int pass_len = password.length();
    unsigned char *plain_chars = new unsigned char[plain_len];
    unsigned char *password_chars = new unsigned char[pass_len];

    strcpy(reinterpret_cast<char*>(plain_chars), plain_text.c_str());
    strcpy(reinterpret_cast<char*>(password_chars), password.c_str());

    unsigned char aes_key[32], aes_iv[16];

    int success = generate_keys(password_chars, pass_len, aes_key, aes_iv);
    if (success != 1) return "";
    free(password_chars);

	EVP_CIPHER_CTX *ctx;
    ctx = EVP_CIPHER_CTX_new();

    success = EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, aes_key, aes_iv);
    if (success != 1) {  // cleanup
        if (ctx) EVP_CIPHER_CTX_free(ctx);
        return "";
    }

    unsigned char *cipher_tmp;
    int len, cipher_len;
    cipher_tmp = (unsigned char *) malloc((plain_len + AES_BLOCK_SIZE) * sizeof(unsigned char));
	if (cipher_tmp == NULL) return 0;

    success = EVP_EncryptUpdate(ctx, cipher_tmp, &len, plain_chars, plain_len);
    free(plain_chars);
    if (success != 1) {  // cleanup
        if (ctx) EVP_CIPHER_CTX_free(ctx);
    	if (cipher_tmp) free(cipher_tmp);
    	return "";
    }

    cipher_len = len;

    success = EVP_EncryptFinal_ex(ctx, cipher_tmp + cipher_len, &len);
    if (success != 1) {  // cleanup
		if (ctx) EVP_CIPHER_CTX_free(ctx);
		if (cipher_tmp) free(cipher_tmp);
		return "";
	}

    cipher_len += len;
	if (ctx) EVP_CIPHER_CTX_free(ctx);

    cipher_tmp[cipher_len] = '\0';

    std::string cipher_text(cipher_len, ' ');
    // first set string len, because if we created string directly from cipher_tmp,
    // \0 could teminate string and we wolud lost any further data.
    for (int i = 0; i < cipher_len; ++i) {
        cipher_text.at(i) = static_cast<char>(cipher_tmp[i]);
    }

    // TODO: convert to BASE64
    // if there is value of '\0' in cipher_tmp, cipher_text will be shorter and thus wrong value.

    assert(static_cast<unsigned int>(cipher_len) == cipher_text.length());

    if (cipher_tmp) free(cipher_tmp);

    return cipher_text;
}

std::string electronpass::crypto::aes_decrypt(const std::string& cipher_text, const std::string& password) {
    // convert strings to char arrays
    const int cipher_len = cipher_text.length();
    const int pass_len = password.length();
    unsigned char *cipher_chars = new unsigned char[cipher_len];
    unsigned char *password_chars = new unsigned char[pass_len];

    // TODO: convert from Base64.

    // copy 1 char at once. Cant use strcopy here, because there could be \0 char,
    // whicw will termiate the string.
    for (int i = 0; i < cipher_len; ++i) {
        cipher_chars[i] = static_cast<unsigned char>(cipher_text.at(i));
    }

    strcpy(reinterpret_cast<char*>(password_chars), password.c_str());

    unsigned char aes_key[32], aes_iv[16];

    int success = generate_keys(password_chars, pass_len, aes_key, aes_iv);
    if (success != 1) return "";
    free(password_chars);

    EVP_CIPHER_CTX *ctx;
    ctx = EVP_CIPHER_CTX_new();

    success = EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, aes_key, aes_iv);
    if (success != 1) {  // cleanup
        if (ctx) EVP_CIPHER_CTX_free(ctx);
        return "";
    }
    unsigned char *plain_tmp;
    int len, plain_len;
    plain_tmp = (unsigned char *) malloc((cipher_len + 1) * sizeof(unsigned char));
    if (plain_tmp == NULL) return 0;

    success = EVP_DecryptUpdate(ctx, plain_tmp, &len, cipher_chars, cipher_len);
    free(cipher_chars);
    if (success != 1) {  // cleanup
        if (ctx) EVP_CIPHER_CTX_free(ctx);
        if (plain_tmp) free(plain_tmp);
        return "";
    }

    plain_len = len;

    success = EVP_DecryptFinal(ctx, plain_tmp + plain_len, &len);
    if (success != 1) {
        if (ctx) EVP_CIPHER_CTX_free(ctx);
        if (plain_tmp) free(plain_tmp);
        return "";
    }

    plain_len += len;
	if (ctx) EVP_CIPHER_CTX_free(ctx);

    plain_tmp[plain_len] = '\0';

    std::string plain_text(reinterpret_cast<char*>(plain_tmp));
    assert(static_cast<unsigned int>(plain_len) == plain_text.length());

    if (plain_tmp) free(plain_tmp);
    return plain_text;
}
