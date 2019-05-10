//
// Created by santi on 20/04/19.
//

#ifndef TP3_INFOCERTIFICADO_H
#define TP3_INFOCERTIFICADO_H

#include <string>
#include <fstream>

// Permite obtener de un archivo la informacion
// necesaria para la creacion de un certificado.
// Se pueden obtener cada uno de los campos por separado.
class InfoCertificado {
private:
    std::ifstream archivo;
    std::string subject;
    std::string fechaIni;
    std::string fechaFin;
public:
    explicit InfoCertificado(std::string &nombre);
    // Obtiene la informacion del archivo.
    void obtenerInfo();
    // Devuelve el subject.
    std::string&obtenerSubject();
    // Devuelve la fecha inicial.
    std::string& obtenerFechaIni();
    // Devuelve la fecha final.
    std::string& obtenerFechaFin();
    ~InfoCertificado() = default;
};

#endif //TP3_INFOCERTIFICADO_H
