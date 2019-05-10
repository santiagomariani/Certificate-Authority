//
// Created by santi on 01/05/19.
//

#include <string>

#include "server_ThCliente.h"
#include "common_Certificado.h"
#include "common_Hash.h"
#include "common_Encriptador.h"

#define ISSUER "Taller de programacion 1"

// COMANDOS
#define COMANDO_NEW 0
#define COMANDO_REVOKE 1

// RESPUESTAS
#define YA_EXISTE_CERTIFICADO 0
#define NO_EXISTE_CERTIFICADO 1
#define CORRECTA_RECEPCION 0
#define INCORRECTA_RECEPCION 1
#define HASH_NO_COINCIDE 2
#define CERTIFICADO_BORRADO 0

ThCliente::ThCliente(Skt skt, Indice &indice, InfoClave &claves)
        : skt(std::move(skt)),
        indice(indice),
        claves_server(claves),
        finalizo(false) {
}

void ThCliente::run() {
    Mensajero mensajero(this->skt);
    uint8_t modo;
    mensajero >> modo;

    if (modo == COMANDO_NEW) {
        this->crearCertificado(mensajero);
    } else if (modo == COMANDO_REVOKE) {
        this->revocarCertificado(mensajero);
    }
    this->finalizado();
}

void ThCliente::crearCertificado(Mensajero &mensajero) {
    std::string subject;
    uint16_t mod;
    uint8_t exp;
    std::string fecha_ini;
    std::string fecha_fin;

    mensajero >> subject >> mod >> exp >> fecha_ini >> fecha_fin;

    uint32_t serial_number = this->indice.obtenerProxNumSerie();

    Clave clave_pub_cli(exp, mod);
    uint8_t cod_res;
    if (!this->indice.agregarSiNoEsta(subject, clave_pub_cli)) {
        cod_res = YA_EXISTE_CERTIFICADO;
        mensajero << cod_res;
        return;
    }
    cod_res = NO_EXISTE_CERTIFICADO;
    mensajero << cod_res;

    // Armo certificado.

    Certificado certificado;

    certificado.setearSerialNumber(serial_number);

    certificado.setearSubject(subject);

    std::string issuer(ISSUER);
    certificado.setearIssuer(issuer);

    certificado.setearFechaIni(fecha_ini);
    certificado.setearFechaFin(fecha_fin);

    certificado.setearMod(mod);
    certificado.setearExp(exp);

    certificado.armarCertificado();

    // Calculo la huella.

    Hash hash;
    Encriptador encriptador;

    uint32_t hash_encriptado = hash.hashear(certificado.obtenerCertificado());
    Clave clave_priv_sv = *this->claves_server.obtenerClavePriv();
    hash_encriptado = encriptador.encriptar(hash_encriptado, clave_priv_sv);
    hash_encriptado = encriptador.encriptar(hash_encriptado, clave_pub_cli);

    // Mando certificado.

    mensajero << certificado;

    // Mando hash encriptado.

    mensajero << hash_encriptado;

    // Se recibio bien?

    uint8_t recepcion_certifiado;
    mensajero >> recepcion_certifiado;
    if (recepcion_certifiado == INCORRECTA_RECEPCION) {
        this->indice.quitarSiEsta(subject);
    }
}

void ThCliente::revocarCertificado(Mensajero &mensajero) {
    // Recibo certificado

    Certificado certificado;
    mensajero >> certificado;

    // Recibo hash encriptado.

    uint32_t hash_encriptado;
    mensajero >> hash_encriptado;

    std::string subject = certificado.obtenerSubject();
    Clave clave_pub_cli;
    if (this->indice.estaCertificado(subject)) {
        clave_pub_cli = this->indice.obtenerClave(subject);
    }

    uint8_t cod_res;
    if (!this->indice.quitarSiEsta(subject)) {
        cod_res = NO_EXISTE_CERTIFICADO;
        mensajero << cod_res;
        return;
    }

    Encriptador encriptador;

    Clave clave_priv_sv = *this->claves_server.obtenerClavePriv();
    uint32_t aux = encriptador.encriptar(hash_encriptado, clave_priv_sv);
    aux = encriptador.encriptar(aux, clave_pub_cli);
    uint16_t hash_desencriptado = (uint16_t) aux;

    Hash hash;
    uint16_t hash_calculado = hash.hashear(certificado.obtenerCertificado());

    if (hash_calculado != hash_desencriptado) {
        cod_res = HASH_NO_COINCIDE;
        this->indice.agregarSinAumentarNumSerie(subject, clave_pub_cli);
        mensajero << cod_res;
        return;
    }
    cod_res = CERTIFICADO_BORRADO;
    mensajero << cod_res;
}

void ThCliente::stop() {
    this->finalizo = true;
    this->skt.cerrarCanales();
    this->skt.cerrarSocket();
}

void ThCliente::finalizado() {
    this->finalizo = true;
}

bool ThCliente::isDead() {
    return this->finalizo;
}
