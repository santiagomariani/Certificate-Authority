//
// Created by santi on 25/04/19.
//

#ifndef TP3_COMMON_CERTIFICADO_H
#define TP3_COMMON_CERTIFICADO_H

#include <stdint-gcc.h>
#include <string>


// Permite armar el certificado. Se pueden setear cada uno de los
// campos y luego obtener una cadena con el certificado completo.
// También es posible armar el certificado leyendo un archivo.
// Además permite guardar el certificado en un archivo.
class Certificado {
private:
    uint32_t serial_number;
    std::string subject;
    std::string issuer;
    std::string fecha_ini;
    std::string fecha_fin;
    std::string certificado;
    uint16_t mod;
    uint8_t exp;
    // Se utiliza para obtener un campo textual del archivo.
    std::string obtenerCampoTexto(std::string &linea);
    // Se utiliza para obtener un campo numerico del archivo.
    std::string obtenerCampoNumerico(std::string &linea);

public:
    Certificado();
    // Setea el atributo serial number.
    void setearSerialNumber(uint32_t s);
    // Setea el atributo subject.
    void setearSubject(const std::string &s);
    // Setea el atributo issuer.
    void setearIssuer(const std::string &i);
    // Setea el atributo fecha inicial.
    void setearFechaIni(const std::string &i);
    // Setea el atributo fecha final.
    void setearFechaFin(const std::string &f);
    // Setea el atributo modulo.
    void setearMod(uint16_t m);
    // Setea el atributo exponente
    void setearExp(uint8_t e);
    // Permite obtener el serial number.
    uint32_t  obtenerSerialNumber();
    // Permite obtener el subject.
    std::string& obtenerSubject();
    // Permite obtener el issuer.
    std::string& obtenerIssuer();
    // Permite obtener la fecha inicial.
    std::string& obtenerFechaIni();
    // Permite obtener la fecha final.
    std::string& obtenerFechaFin();
    // Permite obtener el modulo.
    uint16_t obtenerMod();
    // Permite obtener el exponente.
    uint8_t obtenerExp();
    // Arma el certificado con cada uno de los campos.
    void armarCertificado();
    // Permite obtener el certificado completo.
    std::string& obtenerCertificado();
    // Guarda el certificado en un archivo.
    void guardarCertificado();
    // Lee el certificado de un archivo y guarda cada uno de los campos.
    void leerCertificado(std::string &nombre);
    ~Certificado() = default;
};


#endif //TP3_COMMON_CERTIFICADO_H
