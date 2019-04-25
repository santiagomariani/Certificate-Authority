//
// Created by santi on 21/04/19.
//

#include <string>
#include <iostream>

#include "common_InfoClave.h"

InfoClave::InfoClave(std::string &nombre) :
    archivo(nombre),
    clavePub(nullptr),
    clavePriv(nullptr) {
}

void InfoClave::obtenerInfo() {
    std::string cad_exp_pub;
    std::string cad_exp_priv;
    std::string cad_modulo;

    this->archivo >> cad_exp_pub;
    this->archivo >> cad_exp_priv;
    this->archivo >> cad_modulo;

    uint8_t exp_pub = 0;
    uint8_t exp_priv = 0;
    uint16_t modulo = 0;

    exp_pub = (uint8_t)std::stoi(cad_exp_pub);
    if (cad_modulo.empty()) {
        modulo = (uint16_t)std::stoi(cad_exp_priv);
        this->clavePub = new Clave(exp_pub, modulo);
        return;
    }
    exp_priv = (uint8_t)std::stoi(cad_exp_priv);
    modulo = (uint16_t)std::stoi(cad_modulo);
    this->clavePub = new Clave(exp_pub, modulo);
    this->clavePriv = new Clave(exp_priv, modulo);
}

Clave *InfoClave::obtenerClavePub() {
    return clavePub;
}

Clave *InfoClave::obtenerClavePriv() {
    return clavePriv;
}

InfoClave::~InfoClave() {
    if (this->clavePub) {
        delete this->clavePub;
    }
    if (this->clavePriv) {
        delete this->clavePriv;
    }
}
