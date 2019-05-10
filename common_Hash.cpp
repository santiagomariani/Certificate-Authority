//
// Created by santi on 20/04/19.
//

#include <string>

#include "common_Hash.h"

uint16_t Hash::hashear(std::string &cadena) {
    uint16_t hash = 0;
    auto it = cadena.begin();
    for (; it != cadena.end(); ++it) {
        hash += *it;
    }
    return hash;
}
