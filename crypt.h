//
// Created by Андрей Зорькин on 2019-07-14.
//

#ifndef CRYPT_CRYPT_H
#define CRYPT_CRYPT_H

#include <array>

class Cryyypt {
public:

    Cryyypt(std::string password/*33*/);

    void encrypt(char *src, char *dest, size_t l);

private:

    using byte = unsigned char;

    std::array<int, 14> bytes;

    std::array<std::array<byte, 256>, 256> mull;

    std::array<char, 34> gamma;

    void init_gamma_by_password(std::string& password);

    void load_tables(unsigned short p = 0x11d);

    byte gamma_sign(int i);

    byte mul_honest(byte a, byte b, unsigned short p);

};

#endif //CRYPT_CRYPT_H
