//
// Created by santi on 21/04/19.
//

#ifndef TP3_INFOCLIENTE_H
#define TP3_INFOCLIENTE_H

#include <iostream>
#include <fstream>
#include <string>

#include "common_Clave.h"

class InfoClave {
    private:
    std::ifstream archivo;
    Clave *clavePub;
    Clave *clavePriv;
    public:
    explicit InfoClave(std::string &nombre);
    void obtenerInfo();
    Clave* obtenerClavePub();
    Clave* obtenerClavePriv();
    ~InfoClave();
};


#endif //TP3_INFOCLIENTE_H
