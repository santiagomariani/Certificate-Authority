//
// Created by santi on 20/04/19.
//

#include "common_Clave.h"

Clave::Clave(uint8_t exp, uint16_t mod) : exp(exp), mod(mod){
}

uint8_t Clave::obtenerExp() {
    return this->exp;
}

uint16_t Clave::obtenerMod() {
    return this->mod;
}
