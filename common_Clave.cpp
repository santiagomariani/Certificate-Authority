//
// Created by santi on 20/04/19.
//

#include "common_Clave.h"

Clave::Clave() {
    this->exp = 0;
    this->mod = 0;
}

Clave::Clave(uint8_t exp, uint16_t mod) : exp(exp), mod(mod){
}

