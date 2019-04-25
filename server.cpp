#include <string>
#include <iostream>
#include <cstring>
#include "server_SktSv.h"

//
// Created by santi on 22/04/19.
//
int main(int argc, char* argv[]) {
    SktSv skt_sv(argv[1]);
    std::string buffer(200,'\0');
    skt_sv.escucharClientes();
    skt_sv.aceptarCliente();
    skt_sv.leer_mensaje(&buffer[0], 200);
    buffer.resize(strlen(buffer.c_str()));
    std::cout << buffer << std::endl;

    std::string prueba = "bien y vos";
    size_t longitud = prueba.size();

    skt_sv.enviar_mensaje(&prueba[0], longitud);

    skt_sv.cerrar_canal_escritura();

    return 0;
}
