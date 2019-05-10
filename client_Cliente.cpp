//
// Created by santi on 28/04/19.
//

#include <iostream>
#include <string>

#include "client_Cliente.h"
#include "client_InfoCertificado.h"
#include "common_Skt.h"
#include "common_Clave.h"
#include "common_InfoClave.h"
#include "common_Mensajero.h"
#include "common_Encriptador.h"
#include "common_Certificado.h"
#include "common_Hash.h"

// CANTIDAD PARAMETROS
#define CANT_ARGS_NEW 7
#define CANT_ARGS_REVOKE 7

// CAMPOS
#define HOST 1
#define PORT 2
#define MODO 3
#define INFO_CERTIFICADO 4
#define CERTIFICADO 4
#define CLAVES_CLIENTE 5
#define CLAVE_PUBLICA_SERVER 6

// MODO
#define NEW "new"
#define REVOKE "revoke"

// COMANDOS
#define COMANDO_NEW 0
#define COMANDO_REVOKE 1

// RESPUESTAS
#define CERTIFICADO_EXISTE 0
#define CORRECTA_RECEPCION 0
#define INCORRECTA_RECEPCION 1
#define HASH_NO_COINCIDE 2
#define NO_EXISTE_CERTIFICADO 1

Cliente::Cliente(int argc, char **argv) {
    this->argc = argc;

    for (int i = 0; i < argc; ++i) {
        this->argumentos.emplace_back(argv[i]);
    }
}

void Cliente::iniciar() {
    if (!cant_params_valida() || !modo_valido()) {
        std::cout << "Error: argumentos invalidos.\n";
        return;
    }

    Skt skt_cli(std::move(this->argumentos[HOST]),
            std::move(this->argumentos[PORT]));
    skt_cli.conectar();

    Mensajero mensajero(skt_cli);

    if (this->argumentos[MODO] == NEW) {
        this->crearCertificado(mensajero);
    } else if (this->argumentos[MODO] == REVOKE) {
        this->revocarCertificado(mensajero);
    }
}

bool Cliente::cant_params_valida() {
    return (this->argc == CANT_ARGS_NEW) || (this->argc == CANT_ARGS_REVOKE);
}

bool Cliente::modo_valido() {
    return (this->argumentos[MODO] == NEW) ||
    (this->argumentos[MODO] == REVOKE);
}

void Cliente::crearCertificado(Mensajero &mensajero) {
    InfoClave claves_cliente(this->argumentos[CLAVES_CLIENTE]);
    claves_cliente.obtenerInfo();

    InfoClave clave_server(this->argumentos[CLAVE_PUBLICA_SERVER]);
    clave_server.obtenerInfo();

    InfoCertificado info_certificado(this->argumentos[INFO_CERTIFICADO]);
    info_certificado.obtenerInfo();

    // Mando cosas necesarias para crear certificado.

    uint8_t comando = COMANDO_NEW;
    mensajero << comando;

    mensajero << info_certificado.obtenerSubject();

    mensajero << claves_cliente.obtenerClavePub()->mod;
    mensajero << claves_cliente.obtenerClavePub()->exp;

    mensajero << info_certificado.obtenerFechaIni();
    mensajero << info_certificado.obtenerFechaFin();

    uint8_t respuesta;
    mensajero >> respuesta;

    if (respuesta == CERTIFICADO_EXISTE) {
        std::cout << "Error: ya existe un certificado.\n";
        return;
    }

    // Recibo certificado.

    Certificado certificado;
    mensajero >> certificado;

    // Recibo hash encriptado.

    uint32_t hash_encriptado;
    mensajero >> hash_encriptado;

    // Desencripto huella.

    Encriptador encriptador;

    Clave clave_priv_cli = *claves_cliente.obtenerClavePriv();
    uint32_t aux = encriptador.encriptar(hash_encriptado, clave_priv_cli);
    Clave clave_pub_sv = *clave_server.obtenerClavePub();
    aux = encriptador.encriptar(aux, clave_pub_sv);
    uint16_t hash_desencriptado = (uint16_t) aux;

    // Calculo el hash.

    Hash hash;
    uint16_t hash_calculado = hash.hashear(certificado.obtenerCertificado());

    std::cout << "Huella del servidor: " << hash_encriptado << std::endl;
    std::cout << "Hash del servidor: " << hash_desencriptado << std::endl;
    std::cout << "Hash calculado: " << hash_calculado << std::endl;

    uint8_t recepcion_certificado;
    if (hash_calculado != hash_desencriptado) {
        std::cout << "Error: los hashes no coinciden.\n";
        recepcion_certificado = INCORRECTA_RECEPCION;
    } else {
        recepcion_certificado = CORRECTA_RECEPCION;
        certificado.guardarCertificado();
    }
    mensajero << recepcion_certificado;
}

void Cliente::revocarCertificado(Mensajero &mensajero) {
    uint8_t comando = COMANDO_REVOKE;
    mensajero << comando;

    Certificado certificado;
    certificado.leerCertificado(this->argumentos[CERTIFICADO]);

    // Envio certificado.

    mensajero << certificado;

    Hash hash;
    Encriptador encriptador;

    uint16_t hash_calc = hash.hashear(certificado.obtenerCertificado());

    InfoClave claves_cliente(this->argumentos[CLAVES_CLIENTE]);
    claves_cliente.obtenerInfo();

    InfoClave clave_server(this->argumentos[CLAVE_PUBLICA_SERVER]);
    clave_server.obtenerInfo();

    Clave clave_priv_cli = *claves_cliente.obtenerClavePriv();
    uint32_t hash_encr_priv = encriptador.encriptar(hash_calc, clave_priv_cli);

    Clave clave_pub_sv = *clave_server.obtenerClavePub();
    uint32_t huella = encriptador.encriptar(hash_encr_priv, clave_pub_sv);

    // Envio huella.

    mensajero << huella;

    uint8_t cod_res;
    mensajero >> cod_res;

    std::cout << "Hash calculado: " << hash_calc << std::endl;
    std::cout << "Hash encriptado con la clave privada: " << hash_encr_priv;
    std::cout << std::endl;
    std::cout << "Huella enviada: " << huella << std::endl;

    if (cod_res == HASH_NO_COINCIDE) {
        std::cout << "Error: los hashes no coinciden.\n";
    } else if (cod_res == NO_EXISTE_CERTIFICADO) {
        std::cout << "Error: usuario no registrado.\n";
    }
}


