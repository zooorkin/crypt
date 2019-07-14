//
// Created by Андрей Зорькин on 2019-07-14.
//

#include "crypt.h"

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <algorithm>

#define a0 0x13
#define a9 0xe5
#define a13 0xdf
#define a31 0x93

using byte = unsigned char;

Cryyypt::Cryyypt(std::string password/*33*/) {
    init_gamma_by_password(password);
    load_tables();
}

void Cryyypt::encrypt(char *src, char *dest, size_t l) {
    for (int i = 0; i < l; ++i) {
        dest[i] = src[i] ^ gamma_sign(i);
    }
}

void Cryyypt::init_gamma_by_password(std::string& password) {
    int lengthOfPassword = std::min(password.length(), 33ul);
    for (int i = 0; i < lengthOfPassword; ++i)
        gamma[i] = password[i];
    for (int i = lengthOfPassword; i < 33; ++i)
        gamma[i] = 0;
}

void Cryyypt::load_tables(unsigned short p) {
    for (int i = 0; i < 14; ++i)
        bytes[i] = pow(2, i);
    for (unsigned short a = 0; a < 256; ++a)
        for (unsigned short b = 0; b < 256; ++b)
            mull[a][b] = mul_honest(a, b, p);
}

byte Cryyypt::mul_honest(byte a, byte b, unsigned short p) {
    unsigned short r = 0;
    for (int i = 0; i <= 14; ++i) {
        int j = i - 7 > 0 ? i - 7 : 0;
        while (i - j >= 0 && j <= 7) {
            byte byteA = a & bytes[j];
            byte byteB = b & bytes[i - j];
            byte ch_byteA = byteA >> j;
            byte ch_byteB = byteB >> (i - j);
            byte res = ch_byteA & ch_byteB;
            r ^= static_cast<unsigned short>(res) << i;
            ++j;
        }
    }
    for (int i = 13; i > 7; --i)
        if (((r >> i) & 0x1) == 0x1)
            r ^= (p << (i - 8));
    return r;
}

byte Cryyypt::gamma_sign(int i) {
    int last = (32 + i + 1) % 34;
    gamma[last] =
            mull[a0][gamma[(last + 1) % 34]] ^
            mull[a9][gamma[(last + 10) % 34]] ^
            mull[a13][gamma[(last + 14) % 34]] ^
            mull[a31][gamma[(last + 30) % 32]];
    return gamma[last];
}
