#include <string>
#include <cstring>
#include <iostream>

#include "client_SktCli.h"

int main(int argc, char* argv[]) {
    SktCli skt_cli(argv[1], argv[2]);

    skt_cli.conectar();

    std::string prueba = "Hola como estas";
    size_t longitud = prueba.size();

    skt_cli.enviar_mensaje(&prueba[0], longitud);

    skt_cli.cerrar_canal_escritura();

    std::string buffer(200, '\0');
    skt_cli.leer_mensaje(&buffer[0], 200);
    buffer.resize(strlen(buffer.c_str()));
    std::cout << buffer << std::endl;

    return 0;
}
