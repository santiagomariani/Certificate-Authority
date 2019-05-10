//
// Created by santi on 20/04/19.
//

#include <cstdint>

#include "common_Clave.h"

#ifndef TP3_ENCRIPTADOR_H
#define TP3_ENCRIPTADOR_H

// El encriptador usa el algoritmo RSA para encriptar y desencriptar.
// Se usa luego para encriptar con una clave publica o privada.
class Encriptador {
    public:
    // Encripta con una clave dada.
    uint32_t encriptar(uint32_t hash, Clave clave);
};


#endif //TP3_ENCRIPTADOR_H
