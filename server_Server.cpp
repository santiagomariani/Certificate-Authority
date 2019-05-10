//
// Created by santi on 29/04/19.
//

#include <string>

#include "server_Server.h"
#include "server_Indice.h"
#include "common_Certificado.h"
#include "common_Encriptador.h"
#include "common_Hash.h"
#include "common_InfoClave.h"
#include "server_ThAceptador.h"

// CARACTER SALIDA
#define CARACTER_SALIDA 'q'

// CANTIDAD PARAMETROS
#define CANT_ARGS 4

// CAMPOS
#define PORT 1
#define CLAVES_SERVER 2
#define INDICE 3

Server::Server(int argc, char **argv) {
    this->argc = argc;

    for (int i = 0; i < argc; ++i) {
        this->argumentos.emplace_back(argv[i]);
    }
}

int Server::iniciar() {
    if (!cant_params_valida()) {
        return 1;
    }
    Indice indice(this->argumentos[INDICE]);

    SktAceptador skt_aceptador(std::move(this->argumentos[PORT]));
    skt_aceptador.escucharClientes();

    InfoClave claves_server(this->argumentos[CLAVES_SERVER]);
    claves_server.obtenerInfo();

    ThAceptador hiloAceptador(std::move(skt_aceptador), indice, claves_server);
    hiloAceptador.start();

    char caracter;
    do {
        std::cin >> caracter;
    } while (caracter != CARACTER_SALIDA);

    hiloAceptador.stop();
    hiloAceptador.join();
    indice.guardarIndice();
    return 0;
}

bool Server::cant_params_valida() {
    return this->argc == CANT_ARGS;
}
