//
// Created by santi on 21/04/19.
//


#define _POSIX_C_SOURCE 200112L

#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>

#include <iostream>

#include "server_SktSv.h"
#include "common_Skt.h"

#define MAX_CLIENTES 10

SktSv::SktSv(const char *port) {
    size_t longitud = std::strlen(port);
    this->port = (char*)malloc(longitud + 1);
    memcpy(this->port, port, longitud + 1);
    this->skt = -1;
    this->skt_cliente = -1;
}

int SktSv::escucharClientes() {
    struct addrinfo hints;
    struct addrinfo *ptr;

    int s = 0;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    s = getaddrinfo(nullptr, this->port, &hints, &ptr);

    if (s != 0) {
        std::cout << "Error en getaddrinfo: "<< gai_strerror(s) << std::endl;
        return 1;
    }
    int skt; // Socket aceptador.
    skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

    if (skt == -1) {
        std::cout << "Error: "<< strerror(errno) << std::endl;
        freeaddrinfo(ptr);
        return 1;
    }
    int val = 1;
    s = setsockopt(skt, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

    if (s == -1) {
        std::cout << "Error: "<< strerror(errno) << std::endl;
        freeaddrinfo(ptr);
        Skt::cerrar_socket(skt);
        return 1;
    }
    s = bind(skt, ptr->ai_addr, ptr->ai_addrlen);

    if (s == -1) {
        std::cout << "Error: "<< strerror(errno) << std::endl;
        freeaddrinfo(ptr);
        Skt::cerrar_socket(skt);
        return 1;
    }
    freeaddrinfo(ptr);
    s = listen(skt, MAX_CLIENTES);

    if (s == -1) {
        std::cout << "Error: "<< strerror(errno) << std::endl;
        Skt::cerrar_socket(skt);
        return 1;
    }
    this->skt = skt;
    return 0;
}

int SktSv::aceptarCliente() {
    int skt_cliente;
    skt_cliente = accept(this->skt, nullptr, nullptr);
    if (skt_cliente == -1) {
        std::cout << "Error: "<< strerror(errno) << std::endl;
        return 1;
    }
    this->skt_cliente = skt_cliente;
    return 0;
}

void SktSv::despedirCliente() {
    if (this->skt_cliente != -1) {
        Skt::cerrar_socket(this->skt_cliente);
        this->skt_cliente = -1;
    }
}

int SktSv::enviar_mensaje(char *buffer, int longitud) {
    return Skt::enviar_mensaje(this->skt_cliente, buffer, longitud);
}

int SktSv::leer_mensaje(char *buffer, int longitud) {
    return Skt::leer_mensaje(this->skt_cliente, buffer, longitud);
}

void SktSv::cerrar_canal_escritura() {
    Skt::cerrar_canal_escritura(this->skt_cliente);
}

SktSv::~SktSv() {
    if (this->port != nullptr) {
        free(this->port);
    }
    if (this->skt != -1) {
        cerrar_socket(this->skt);
    }
    if (this->skt_cliente != -1) {
        cerrar_socket(this->skt_cliente);
    }
}
