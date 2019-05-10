//
// Created by santi on 28/04/19.
//

#ifndef TP3_CLIENT_CLIENTE_H
#define TP3_CLIENT_CLIENTE_H


#include <string>
#include <vector>

#include "common_Mensajero.h"

// Se encarga de la comunicacion con el server
// para la creacion y la revocacion de un certificado.
class Cliente {
private:
    int argc;
    std::vector<std::string> argumentos;
    // Se comunica con el server para crear un certificado.
    void crearCertificado(Mensajero& mensajero);
    // Se comunica con el server para revocar un certificado.
    void revocarCertificado(Mensajero &mensajero);
    // Devuelve booleano indicando si la cantidad de parametros es valida.
    bool cant_params_valida();
    // Devuelve booleano indicando si el modo es valido.
    bool modo_valido();
public:
    Cliente(int argc, char **argv);
    // Comienza a ejecutar la logica correspondiente para
    // crear o revocar un certificado .
    void iniciar();
    ~Cliente() = default;
};


#endif //TP3_CLIENT_CLIENTE_H
