//
// Created by santi on 01/05/19.
//

#ifndef TP3_THACEPTADOR_H
#define TP3_THACEPTADOR_H

#include <vector>

#include "server_SktAceptador.h"
#include "server_ThCliente.h"
#include "common_InfoClave.h"

// Objecto activo que se encarga de aceptar clientes y
// crear/eliminar objectos activos ThCliente.
class ThAceptador : public Thread {
private:
    SktAceptador skt_acep;
    Indice &indice;
    InfoClave &claves_server;
    std::vector<ThCliente*> clientes;
    bool finalizo;
public:
    ThAceptador(SktAceptador skt_acep, Indice &indice, InfoClave &claves);
    virtual void run();
    void stop();
    ~ThAceptador() = default;
};


#endif //TP3_THACEPTADOR_H
