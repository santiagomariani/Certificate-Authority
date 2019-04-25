//
// Created by santi on 20/04/19.
//

#include "common_Encriptador.h"

uint32_t Encriptador::encriptar(uint16_t hash, uint8_t exp, uint16_t mod) {
    uint32_t ret = 0;
    for (unsigned int i = 0; i < 4; ++i) {
        uint32_t result = (hash >> (i * 8)) & 0xff;
        uint32_t base = result;
        for (unsigned int j = 1; j < exp; ++j) {
            result = (result * base) % mod;
        }
        ret = ret + (result << (i*8));
    }
    return ret;
}
