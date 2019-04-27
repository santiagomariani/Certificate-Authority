//
// Created by santi on 25/04/19.
//

#ifndef TP3_COMMON_CERTIFICADO_H
#define TP3_COMMON_CERTIFICADO_H


#include <stdint-gcc.h>
#include <string>

class Certificado {
private:
    uint32_t serial_number;
    const std::string *subject;
    const std::string *issuer;
    const std::string * fecha_ini;
    const std::string *fecha_fin;
    uint16_t mod;
    uint8_t exp;
    std::string certificado;
public:
    Certificado();
    void setearSerialNumber(uint32_t s);
    void setearSubject(const std::string &s);
    void setearIssuer(const std::string &i);
    void setearFechaIni(const std::string &i);
    void setearFechaFin(const std::string &f);
    void setearMod(uint16_t m);
    void setearExp(uint8_t e);
    void armarCertificado();
    std::string& obtenerCertificado();
};


#endif //TP3_COMMON_CERTIFICADO_H
