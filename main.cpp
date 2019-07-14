#include <iostream>
#include <fstream>
#include <string>
#include "crypt.h"

void print_parameters() {
    std::string offset = "\t";
    std::cout
            << offset << "\n"
            << offset << "НЕВЕРНЫЕ ПАРАМЕТРЫ\n"
            << offset << "argv[1] = Имя шифруемого файла\n"
            << offset << "argv[2] = Имя шифрованного файла\n"
            << offset << "argv[3] = Пароль\n"
            << offset << "\n";
}

int main(int argc, char **argv) {
    if (argc != 4)
        return print_parameters(), 1;
    
    std::string input_file{argv[1]};
    std::string output_file{argv[2]};
    std::string password{argv[3]};

    std::ifstream file(input_file, std::ios::in | std::ios::ate);
    std::size_t size = file.tellg();
    file.seekg(std::ios::end);

    char *buf = new char[size];
    file.seekg(0);
    file.read(buf, size);

    Cryyypt encryptor(password);
    encryptor.encrypt(buf, buf, size);

    std::ofstream file2(output_file);
    file2.write(buf, size);

    file.close();
    file2.close();

    return 0;
}
