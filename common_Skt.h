//
// Created by santi on 21/04/19.
//

#ifndef TP3_SKTCLI_H
#define TP3_SKTCLI_H

#include <string>

#include "server_SktAceptador.h"

// Permite la comunicacion entre 2 objetos de
// la misma clase.
class Skt {
private:
    std::string host;
    std::string port;
    int skt;
    // Inicializa con un socket (file descriptor).
    explicit Skt(int skt);
    friend class SktAceptador;
public:
    // Inicializa con un host y un puerto.
    Skt(std::string host, std::string port);
    // Constructor por movimiento.
    Skt(Skt&& other);
    // Se conecta con el servidor.
    int conectar();
    // Envia un mensaje al servidor.
    int enviarMensaje(char *buffer, int longitud);
    // Lee un mensaje del servidor.
    int leerMensaje(char *buffer, int longitud);
    // Cierra el canal de escritura.
    void cerrarCanalEscritura();
    // Cierra el canal de lectura.
    void cerrarCanalLectura();
    // Cierra el canal de escritura y el de lectura.
    void cerrarCanales();
    // Cierra el socket.
    void cerrarSocket();
    // No tiene sentido copiar un Socket.
    Skt(const Skt&) = delete;
    Skt& operator=(const Skt&) = delete;
    // Libera los recursos.
    ~Skt();
};


#endif //TP3_SKTCLI_H
