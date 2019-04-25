//
// Created by santi on 20/04/19.
//

#ifndef TP3_HASH_H
#define TP3_HASH_H

#include <string>
#include <cstdint>

class Hash {
    public:
    // Para hashear aplica la sumatoria del valor ASCII de todos
    // los caracteres que componen la cadena en un entero sin
    // signo de 2 bytes.
    uint16_t hashear(std::string &cadena);
};

#endif //TP3_HASH_H
