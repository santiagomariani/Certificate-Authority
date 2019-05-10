//
// Created by santi on 20/04/19.
//

#ifndef TP3_COMMON_CLAVE_H
#define TP3_COMMON_CLAVE_H


#include <cstdint>

// Esta clase representa una clave, ya sea privada o publica.
// La misma se crea con un exponente (1 byte sin signo) y
// un modulo (2 bytes sin signo).
struct Clave {
    public:
    uint8_t exp;
    uint16_t mod;
    Clave();
    Clave(uint8_t exp, uint16_t mod);
    ~Clave() = default;
};


#endif //TP3_COMMON_CLAVE_H
