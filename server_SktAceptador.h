//
// Created by santi on 21/04/19.
//

#ifndef TP3_SKTSV_H
#define TP3_SKTSV_H

#include <string>

#include "common_Skt.h"

class Skt;
// El SktAceptador lo usa el server primero para escuchar a los clientes
// (clientes ya pueden quedar en lista de espera) y luego ya puede aceptar
// clientes. Al aceptar un cliente se obtiene un Skt con el cual nos vamos
// a poder comunicar con el cliente que corresponda.
class SktAceptador {
    private:
    std::string port;
    int skt;
    public:
    // Inicializa con el puerto indicado.
    explicit SktAceptador(std::string port);
    // Constructor por movimiento.
    SktAceptador(SktAceptador &&other);
    // No tiene sentido copiar.
    SktAceptador(const SktAceptador&) = delete;
    SktAceptador& operator=(const SktAceptador&) = delete;
    // Listo para recibir clientes.
    int escucharClientes();
    // Acepta un cliente.
    Skt aceptarCliente();
    // Cierra canal de escritura y el de lectura.
    void cerrarCanales();
    // Cierra el socket.
    void cerrarSocket();
    ~SktAceptador();
};

#endif //TP3_SKTSV_H
