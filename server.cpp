#include <string>
#include <iostream>
#include <cstring>
#include "server_SktAceptador.h"
#include "server_Indice.h"
#include "common_Mensajero.h"
#include "server_Server.h"

//
// Created by santi on 22/04/19.
//
int main(int argc, char* argv[]) {
    Server server(argc, argv);
    server.iniciar();
}
