//
// Created by santi on 28/04/19.
//

#ifndef TP3_MENSAJERO_H
#define TP3_MENSAJERO_H


#include <cstdint>
#include <string>

#include "common_Skt.h"
#include "common_Certificado.h"

// Sabe como enviar y recibir distintos tipos de datos.
class Mensajero {
private:
    Skt &skt;

public:
    explicit Mensajero(Skt &skt);
    // Envia un uint8_t.
    Mensajero& operator<<(uint8_t numero);
    // Envia un uint16_t.
    Mensajero& operator<<(uint16_t numero);
    // Envia un uint32_t.
    Mensajero& operator<<(uint32_t numero);
    // Envia una cadena. Enviando primero la longitud
    // en un uint32_t.
    Mensajero& operator<<(std::string &cadena);
    // Envia cada uno de los campos del certificado.
    Mensajero& operator<<(Certificado &certificado);
    // Recibe un uint8_t.
    Mensajero& operator>>(uint8_t& numero);
    // Recibe un uint16_t.
    Mensajero& operator>>(uint16_t& numero);
    // Recibe un uint32_t.
    Mensajero& operator>>(uint32_t& numero);
    // Recibe una cadena.
    Mensajero& operator>>(std::string &cadena);
    // Recibe cada uno de los campos del certificado y
    // los setea en certificado.
    Mensajero& operator>>(Certificado &certificado);
    ~Mensajero() = default;
};


#endif //TP3_MENSAJERO_H
