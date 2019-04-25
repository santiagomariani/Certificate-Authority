//
// Created by santi on 20/04/19.
//

#include <cstdint>

#ifndef TP3_ENCRIPTADOR_H
#define TP3_ENCRIPTADOR_H


class Encriptador {
    public:
    uint32_t encriptar(uint16_t hash, uint8_t exp, uint16_t mod);
};


#endif //TP3_ENCRIPTADOR_H
