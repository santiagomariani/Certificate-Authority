//
// Created by santi on 01/05/19.
//

#ifndef TP3_THAUTORIDADCERTIFICANTE_H
#define TP3_THAUTORIDADCERTIFICANTE_H


#include "server_Thread.h"
#include "server_Indice.h"
#include "common_Skt.h"
#include "common_Mensajero.h"
#include "common_InfoClave.h"

// Objecto activo que se encarga de la comunicacion con un cliente
// en especifico para la creacion o revocacion de un certificado.
class ThCliente : public Thread {
private:
    Skt skt;
    Indice &indice;
    InfoClave &claves_server;
    bool finalizo;
public:
    ThCliente(Skt skt, Indice &indice, InfoClave &claves);
    // Ejecuta logica correspondiente para crear/revocar certificado.
    virtual void run();
    // Ejecuta logica correspondiente para crear un certificado.
    void crearCertificado(Mensajero &mensajero);
    // Ejecuta logica correspondiente para revocar un certificado.
    void revocarCertificado(Mensajero &mensajero);
    // Devuelve un booleano indicando si finalizo.
    bool isDead();
    // Cambia el estado del objeto indicando que se finalizo.
    void finalizado();
    void stop();
    ~ThCliente() = default;
};


#endif //TP3_THAUTORIDADCERTIFICANTE_H
