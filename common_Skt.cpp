//
// Created by santi on 21/04/19.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

#include "common_Skt.h"

int Skt::leer_mensaje(int skt, char *buffer, int longitud) {
    int byt_leidos = 0;
    int s = 0;

    if ((buffer == nullptr) || (longitud < 1)) {
        return -1;
    }
    while (byt_leidos < longitud) {
        s = recv(skt, buffer + byt_leidos, longitud-byt_leidos, MSG_NOSIGNAL);

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

int Skt::enviar_mensaje(int skt, char *buffer, int longitud) {
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

void Skt::cerrar_canal_escritura(int skt) {
    shutdown(skt, SHUT_WR);
}

void Skt::cerrar_socket(int skt) {
    close(skt);
}
