#include <string>
#include <cstring>
#include <iostream>

#include "client_Cliente.h"
#include "common_Certificado.h"

int main(int argc, char* argv[]) {
    Cliente cliente(argc, argv);
    cliente.iniciar();
}
