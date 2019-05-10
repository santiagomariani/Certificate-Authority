//
// Created by santi on 29/04/19.
//

#ifndef TP3_SERVER_SERVER_H
#define TP3_SERVER_SERVER_H

#include <vector>
#include <string>

#include "common_Mensajero.h"
#include "server_Indice.h"

// Esta clase se encarga de validar los parámetros (cant. de parámetros)
// y de la comunicación con el cliente.
class Server {
private:
    int argc;
    std::vector<std::string> argumentos;
    // Devuelve un booleano indicando si la cantidad de parametros
    // es valida.
    bool cant_params_valida();
public:
    Server(int argc, char **argv);
    int iniciar();
    ~Server() = default;
};


#endif //TP3_SERVER_SERVER_H
