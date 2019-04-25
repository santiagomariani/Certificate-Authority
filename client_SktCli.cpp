//
// Created by santi on 21/04/19.
//
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>

#include <iostream>

#include "client_SktCli.h"

SktCli::SktCli(const char *host, const char *port) {
    size_t longitud = strlen(host);
    this->host = (char*)malloc(longitud + 1);
    memcpy(this->host, host, longitud + 1);
    longitud = strlen(port);
    this->port = (char*)malloc(longitud + 1);
    memcpy(this->port, port, longitud + 1);
}

int SktCli::conectar() {
    struct addrinfo hints;
    struct addrinfo *result, *ptr;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;

    int s;
    s = getaddrinfo(this->host, this->port, &hints, &result);

    if (s != 0) {
        std::cout << "Error en getaddrinfo: \n" << gai_strerror(s);
        return 1;
    }

    int skt = -1;
    bool conectado = false;

    for (ptr = result; ptr != nullptr && !conectado; ptr = ptr->ai_next) {
        skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

        if (skt == -1) {
            std::cout << "Error: " << strerror(errno) << std::endl;
        } else {
            s = connect(skt, ptr->ai_addr, ptr->ai_addrlen);
            if (s == -1) {
                std::cout << "Error: " << strerror(errno) << std::endl;
                Skt::cerrar_socket(skt);
                continue;
            }
            conectado = true;
        }
    }
    freeaddrinfo(result);
    if (skt == -1) {
        return 1;
    } else if (!conectado) {
        Skt::cerrar_socket(skt);
        return 1;
    }
    this->skt = skt;
    return 0;
}

int SktCli::enviar_mensaje(char *buffer, int longitud) {
    return Skt::enviar_mensaje(this->skt, buffer, longitud);
}

int SktCli::leer_mensaje(char *buffer, int longitud) {
    return Skt::leer_mensaje(this->skt, buffer, longitud);
}
SktCli::~SktCli() {
    if (this->host != nullptr) {
        free(this->host);
    }
    if (this->port != nullptr) {
        free(this->port);
    }
    if (this->skt != -1) {
        Skt::cerrar_socket(this->skt);
    }
}

void SktCli::cerrar_canal_escritura() {
    Skt::cerrar_canal_escritura(this->skt);
}
