//
// Created by santi on 20/04/19.
//

#ifndef TP3_INFOCERTIFICADO_H
#define TP3_INFOCERTIFICADO_H

#include <string>
#include <fstream>

class InfoCertificado {
private:
    std::ifstream archivo;
    std::string subject;
    std::string fechaIni;
    std::string fechaFin;
public:
    explicit InfoCertificado(std::string &nombre);
    void obtenerInfo();
    std::string&obtenerSubject();
    std::string& obtenerFechaIni();
    std::string& obtenerFechaFin();
};

#endif //TP3_INFOCERTIFICADO_H
