//
// Created by santi on 20/04/19.
//

#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <string>

#include "client_InfoCertificado.h"

InfoCertificado::InfoCertificado(std::string &nombre) : archivo(nombre) {
}

void InfoCertificado::obtenerInfo() {
    std::string *linea = &this->subject;
    std::getline(this->archivo, *linea);
    linea = &this->fechaIni;
    if (!std::getline(this->archivo, *linea)) {
        std::time_t t = std::time(nullptr);
        std::tm *fecha = std::localtime(&t);
        std::stringstream oss;
        oss << std::put_time(fecha, "%b %d %H:%M:%S %Y");
        this->fechaIni = oss.str();
        fecha->tm_mday += 30;
        std::mktime(fecha);
        oss.str(std::string());
        oss << std::put_time(fecha, "%b %d %H:%M:%S %Y");
        this->fechaFin = oss.str();
        return;
    }
    linea = &this->fechaFin;
    std::getline(this->archivo, *linea);
}

std::string &InfoCertificado::obtenerSubject() {
    return this->subject;
}

std::string &InfoCertificado::obtenerFechaIni() {
    return this->fechaIni;
}

std::string &InfoCertificado::obtenerFechaFin() {
    return this->fechaFin;
}
