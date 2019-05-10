//
// Created by santi on 28/04/19.
//

#include <arpa/inet.h>
#include <string>

#include "common_Mensajero.h"

#define UNBYTE 1
#define DOSBYTES 2
#define CUATROBYTES 4

Mensajero::Mensajero(Skt &skt) : skt(skt) {
}

Mensajero &Mensajero::operator<<(uint8_t numero) {
    skt.enviarMensaje((char *) &numero, UNBYTE);
    return *this;
}

Mensajero &Mensajero::operator<<(uint16_t numero) {
    numero = htons(numero);
    skt.enviarMensaje((char *) &numero, DOSBYTES);
    return *this;
}

Mensajero &Mensajero::operator<<(uint32_t numero) {
    numero = htonl(numero);
    skt.enviarMensaje((char *) &numero, CUATROBYTES);
    return *this;
}

Mensajero &Mensajero::operator<<(std::string &cadena) {
    uint32_t longitud = cadena.size();
    *this << longitud;
    skt.enviarMensaje(&cadena[0], longitud);
    return *this;
}

Mensajero &Mensajero::operator<<(Certificado &certificado) {
    *this << certificado.obtenerSerialNumber() << certificado.obtenerSubject();
    *this << certificado.obtenerIssuer() << certificado.obtenerFechaIni();
    *this << certificado.obtenerFechaFin() << certificado.obtenerMod();
    *this << certificado.obtenerExp();
    return *this;
}

Mensajero &Mensajero::operator>>(uint8_t &numero) {
    skt.leerMensaje((char *) &numero, UNBYTE);
    return *this;
}

Mensajero &Mensajero::operator>>(uint16_t &numero) {
    uint16_t aux;
    skt.leerMensaje((char *) &aux, DOSBYTES);
    numero = ntohs(aux);
    return *this;
}

Mensajero &Mensajero::operator>>(uint32_t &numero) {
    uint32_t aux;
    skt.leerMensaje((char *) &aux, CUATROBYTES);
    numero = ntohl(aux);
    return *this;
}

Mensajero &Mensajero::operator>>(std::string &cadena) {
    uint32_t longitud;
    *this >> longitud;
    cadena.resize(longitud);
    skt.leerMensaje((char *) &cadena[0], longitud);
    return *this;
}

Mensajero &Mensajero::operator>>(Certificado &certificado) {
    uint32_t serial_number;
    *this >> serial_number;

    std::string subject;
    *this >> subject;

    std::string issuer;
    *this >> issuer;

    std::string fecha_ini;
    std::string fecha_fin;
    *this >> fecha_ini >> fecha_fin;

    uint16_t mod;
    uint8_t exp;
    *this >> mod >> exp;

    certificado.setearSerialNumber(serial_number);
    certificado.setearSubject(subject);
    certificado.setearIssuer(issuer);
    certificado.setearFechaIni(fecha_ini);
    certificado.setearFechaFin(fecha_fin);
    certificado.setearExp(exp);
    certificado.setearMod(mod);
    certificado.armarCertificado();
    return *this;
}
