//
// Created by santi on 21/04/19.
//

#ifndef TP3_INFOCLIENTE_H
#define TP3_INFOCLIENTE_H

#include <iostream>
#include <fstream>
#include <string>

#include "common_Clave.h"

// Lee el archivo que tiene la información de la/las clave/claves
// del server/cliente. Luego es posible obtener dichas claves por separado.
class InfoClave {
    private:
    std::ifstream archivo;
    Clave *clavePub;
    Clave *clavePriv;
    public:
    explicit InfoClave(std::string &nombre);
    // Obtiene la informacion del archivo.
    void obtenerInfo();
    // Permite obtener la clave publica.
    Clave* obtenerClavePub();
    // Permite obtener la clave privada.
    Clave* obtenerClavePriv();
    ~InfoClave();
};


#endif //TP3_INFOCLIENTE_H
