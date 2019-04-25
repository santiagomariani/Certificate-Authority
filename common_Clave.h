//
// Created by santi on 20/04/19.
//

#ifndef TP3_COMMON_CLAVE_H
#define TP3_COMMON_CLAVE_H


#include <cstdint>

class Clave {
    private:
    uint8_t exp;
    uint16_t mod;
    public:
    Clave(uint8_t exp, uint16_t mod);
    uint8_t obtenerExp();
    uint16_t obtenerMod();
};


#endif //TP3_COMMON_CLAVE_H
