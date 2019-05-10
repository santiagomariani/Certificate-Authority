//
// Created by santi on 21/04/19.
//
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <string>

#include <iostream>

#include "common_Skt.h"

Skt::Skt(std::string host, std::string port) :
    host(std::move(host)),
    port(std::move(port)),
    skt(-1) {
}

Skt::Skt(int skt) : skt(skt) {
}

Skt::Skt(Skt &&other) {
    this->host = std::move(other.host);
    this->port = std::move(other.port);
    this->skt = other.skt;
    other.skt = -1;
}

int Skt::conectar() {
    struct addrinfo hints;
    struct addrinfo *result, *ptr;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;

    int s;
    s = getaddrinfo(this->host.c_str(), this->port.c_str(), &hints, &result);

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
            this->skt = skt;
            s = connect(skt, ptr->ai_addr, ptr->ai_addrlen);
            if (s == -1) {
                std::cout << "Error: " << strerror(errno) << std::endl;
                this->cerrarSocket();
                continue;
            }
            conectado = true;
        }
    }
    freeaddrinfo(result);
    if (skt == -1) {
        return 1;
    }
    return 0;
}

int Skt::enviarMensaje(char *buffer, int longitud) {
    int byt_enviados = 0;
    int s = 0;

    if ((buffer == nullptr) || (longitud < 1)) {
        return -1;
    }
    while (byt_enviados < longitud) {
        s = send(skt, buffer+byt_enviados, longitud-byt_enviados, MSG_NOSIGNAL);

        if (s == 0) {
            return byt_enviados;
        } else if (s == -1) {
            std::cout << "Error al enviar mensaje: " << strerror(errno) << "\n";
            return -1;
        }
        byt_enviados += s;
    }
    return byt_enviados;
}

int Skt::leerMensaje(char *buffer, int longitud) {
    int byt_leidos = 0;
    int s = 0;

    if ((buffer == nullptr) || (longitud < 1)) {
        return -1;
    }
    while (byt_leidos < longitud) {
        s = recv(this->skt, buffer + byt_leidos,
                longitud-byt_leidos, MSG_NOSIGNAL);

        if (s == 0) {
            return byt_leidos;
        } else if (s == -1) {
            std::cout << "Error al leer mensaje: " << strerror(errno) << "\n";
            return -1;
        }
        byt_leidos += s;
    }
    return byt_leidos;
}

void Skt::cerrarCanalEscritura() {
    shutdown(this->skt, SHUT_WR);
}

void Skt::cerrarCanalLectura() {
    shutdown(this->skt, SHUT_RD);
}

void Skt::cerrarCanales() {
    shutdown(this->skt, SHUT_RDWR);
}

void Skt::cerrarSocket() {
    close(this->skt);
    this->skt = -1;
}

Skt::~Skt() {
    if (this->skt != -1) {
        shutdown(this->skt, SHUT_RDWR);
        this->cerrarSocket();
    }
}
