#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

int byte[14];

void loadByteTable(){
    for (int i = 0; i < 14; ++i){
        byte[i] = pow(2, i);
    }
}

unsigned char mull[256][256];

unsigned char MulHonest(unsigned char a, unsigned char b, unsigned short p = 0x11d){
    unsigned short r = 0;
    for (int i = 0; i <= 14; ++i){
        int j = i - 7 > 0 ? i - 7 : 0;
        while(i - j >= 0 && j <= 7){
            unsigned char byteA = a & byte[j];
            unsigned char byteB = b & byte[i - j];
            unsigned char ch_byteA = byteA >> j;
            unsigned char ch_byteB = byteB >> (i - j);
            unsigned char res = ch_byteA & ch_byteB;
            r ^=  static_cast<unsigned short>(res) << i;
            ++j;
        }
    }
    for (int i = 13; i > 7; --i)
        if (((r >> i) & 0x1) == 0x1)
            r ^= (p << (i - 8));
    return r;
}

void loadMulTable(unsigned short p = 0x11d){
    for (unsigned short a = 0; a < 256; ++a){
        for (unsigned short b = 0; b < 256; ++b){
            mull[a][b] = MulHonest(a, b, p);
        }
    }
}

#define a0 0x13
#define a9 0xe5
#define a13 0xdf
#define a31 0x93

char S[34];
int last;

unsigned char getNextS(){
    last = (last + 1) % 34;
    S[last] = mull[a0][S[(last+1)%34]] ^ mull[a9][S[(last+10)%34]] ^ mull[a13][S[(last+14)%34]] ^ mull[a31][S[(last+30)%32]];
    return S[last];
}

void init(char* B/*33*/){
    last = 32; //start
    for (int i = 0; i < 33; ++i){
        S[i] = B[i];
    }
    
}

void crypt(char* src, char* dest, size_t l){
    for (int i = 0; i < l; ++i){
        dest[i] = src[i]^getNextS();
    }
}

// argv[1] = Имя файла
// argv[2] = Пароль

int main(int argc, char** argv) {
    
    if (argc != 3){
        std::cout << "\n\tНЕВЕРНЫЕ ПАРАМЕТРЫ\n\targv[1] = Имя файла\n\targv[2] = Пароль\n\n";
        return 0;
    }
    
    loadByteTable();
    loadMulTable();
    
    std::ifstream file(argv[1], std::ios::in | std::ios::ate);
    std::size_t size = file.tellg();
    file.seekg(std::ios::end);
    char* buf = new char[size];
    file.seekg(0);
    file.read(buf, size);
    
    char B[33];
    size_t lengthOfPassword = strlen(argv[2]);
    for (int i = 0; i < lengthOfPassword; ++i)
        B[i] = argv[2][i];
    for (size_t i = lengthOfPassword; i < 33; ++i){
        B[i] = 0;
    }
    init(B);
    crypt(buf, buf, size);
    
    std::ofstream file2(strcat(argv[1], "_crypted.txt"));
    file2.write(buf, size);
    
    file.close();
    file2.close();
    
    return 0;
}
