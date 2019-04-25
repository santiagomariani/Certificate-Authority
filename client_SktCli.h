//
// Created by santi on 21/04/19.
//

#ifndef TP3_SKTCLI_H
#define TP3_SKTCLI_H

#include "common_Skt.h"

class SktCli : public Skt{
    private:
    char *host;
    char *port;
    int skt;
    public:
    // Inicializa con un host y un puerto.
    SktCli(const char *host, const char *port);
    // Se conecta con el servidor.
    int conectar();
    // Envia un mensaje al servidor.
    int enviar_mensaje(char *buffer, int longitud);
    // Lee un mensaje del servidor.
    int leer_mensaje(char *buffer, int longitud);
    void cerrar_canal_escritura();
    ~SktCli();
};

#endif //TP3_SKTCLI_H
