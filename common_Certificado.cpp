//
// Created by santi on 25/04/19.
//

#include "common_Certificado.h"

Certificado::Certificado() {
}

void Certificado::setearSerialNumber(uint32_t s) {
    this->serial_number = s;
}

void Certificado::setearSubject(const std::string &s) {
    this->subject = &s;
}

void Certificado::setearIssuer(const std::string &i) {
    this->issuer = &i;
}

void Certificado::setearFechaIni(const std::string &i) {
    this->fecha_ini = &i;
}

void Certificado::setearFechaFin(const std::string &f) {
    this->fecha_fin = &f;
}

void Certificado::setearMod(uint16_t m) {
    this->mod = m;
}

void Certificado::setearExp(uint8_t e) {
    this->exp = e;
}

void Certificado::armarCertificado() {
    char hexa[20];
    this->certificado.clear();
    this->certificado.append("certificate:");
    this->certificado.append("\n\t");
    this->certificado.append("serial number:");
    this->certificado.push_back(' ');
    this->certificado.append(std::to_string(this->serial_number));
    this->certificado.push_back(' ');
    snprintf(hexa, sizeof(hexa), "(0x%08x)", this->serial_number);
    this->certificado.append(std::string(hexa));
    this->certificado.append("\n\t");
    this->certificado.append("subject:");
    this->certificado.push_back(' ');
    this->certificado.append(*this->subject);
    this->certificado.append("\n\t");
    this->certificado.append("issuer:");
    this->certificado.push_back(' ');
    this->certificado.append(*this->issuer);
    this->certificado.append("\n\t");
    this->certificado.append("validity:");
    this->certificado.append("\n\t\t");
    this->certificado.append("not before:");
    this->certificado.push_back(' ');
    this->certificado.append(*this->fecha_ini);
    this->certificado.append("\n\t\t");
    this->certificado.append("not after:");
    this->certificado.push_back(' ');
    this->certificado.append(*this->fecha_fin);
    this->certificado.append("\n\t");
    this->certificado.append("subject public key info:");
    this->certificado.append("\n\t\t");
    this->certificado.append("modulus:");
    this->certificado.push_back(' ');
    this->certificado.append(std::to_string(this->mod));
    this->certificado.push_back(' ');
    snprintf(hexa, sizeof(hexa), "(0x%04x)", this->mod);
    this->certificado.append(std::string(hexa));
    this->certificado.append("\n\t\t");
    this->certificado.append("exponent:");
    this->certificado.push_back(' ');
    this->certificado.append(std::to_string(this->exp));
    this->certificado.push_back(' ');
    snprintf(hexa, sizeof(hexa), "(0x%02x)", this->exp);
    this->certificado.append(std::string(hexa));
}

std::string &Certificado::obtenerCertificado() {
    return this->certificado;
}
