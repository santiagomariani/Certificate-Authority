#include <string>
#include <cstring>
#include <iostream>

#include "client_SktCli.h"
#include "common_Certificado.h"
#include "common_Hash.h"

int main(int argc, char* argv[]) {
    Certificado certificado;
    uint32_t serial_number = 11;
    std::string subject = "Federico Manuel Gomez Peter";
    std::string issuer = "Taller de programacion 1";
    std::string fecha_ini = "Mar 28 21:33:04 2019";
    std::string fecha_fin = "May 27 21:33:04 2019";
    uint16_t mod = 253;
    uint8_t exp = 17;
    certificado.setearSerialNumber(serial_number);
    certificado.setearSubject(subject);
    certificado.setearIssuer(issuer);
    certificado.setearFechaIni(fecha_ini);
    certificado.setearFechaFin(fecha_fin);
    certificado.setearMod(mod);
    certificado.setearExp(exp);
    certificado.armarCertificado();
    std::cout << certificado.obtenerCertificado() << std::endl;
    Hash x;
    std::cout << x.hashear(certificado.obtenerCertificado()) << std::endl ;
    return 0;
}
