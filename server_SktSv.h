//
// Created by santi on 21/04/19.
//

#ifndef TP3_SKTSV_H
#define TP3_SKTSV_H

#include "common_Skt.h"

class SktSv : public Skt{
    private:
    char *port;
    int skt;
    int skt_cliente;
    public:
    // Inicializa con el puerto indicado.
    explicit SktSv(const char *port);
    // Server listo para recibir clientes.
    int escucharClientes();
    // Acepta un cliente.
    int aceptarCliente();
    // Despide un cliente (cierra el socket).
    void despedirCliente();
    // Envia un mensaje al cliente.
    int enviar_mensaje(char *buffer, int longitud);
    // Lee un mensaje del cliente.
    int leer_mensaje(char *buffer, int longitud);
    void cerrar_canal_escritura();
    // Libera la cadena que tiene el puerto.
    ~SktSv();
};

#endif //TP3_SKTSV_H
