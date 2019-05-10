//
// Created by santi on 25/04/19.
//

#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "common_Certificado.h"

Certificado::Certificado() {
}

void Certificado::setearSerialNumber(uint32_t s) {
    this->serial_number = s;
}

void Certificado::setearSubject(const std::string &s) {
    this->subject = s;
}

void Certificado::setearIssuer(const std::string &i) {
    this->issuer = i;
}

void Certificado::setearFechaIni(const std::string &i) {
    this->fecha_ini = i;
}

void Certificado::setearFechaFin(const std::string &f) {
    this->fecha_fin = f;
}

void Certificado::setearMod(uint16_t m) {
    this->mod = m;
}

void Certificado::setearExp(uint8_t e) {
    this->exp = e;
}

void Certificado::armarCertificado() {
    this->certificado.clear();
    std::ostringstream ss;
    ss << "certificate:\n\tserial number: " << this->serial_number << ' ';
    ss << "(0x" << std::setfill('0') << std::setw(8) << std::hex;
    ss << this->serial_number << std::dec << ')';
    ss << "\n\tsubject: " << this->subject << "\n\tissuer: " << this->issuer;
    ss << "\n\tvalidity:\n\t\tnot before: " << this->fecha_ini << "\n\t\t";
    ss << "not after: " << this->fecha_fin << "\n\t";
    ss << "subject public key info:\n\t\tmodulus: " << this->mod << ' ';
    ss << "(0x" << std::setfill('0') << std::setw(4) << std::hex;
    ss << this->mod << std::dec << ")\n\t\texponent: " << unsigned(this->exp);
    ss << ' ' << "(0x" << std::setfill('0') << std::setw(2) << std::hex;
    ss << unsigned(this->exp) << ')';
    this->certificado = ss.str();
}

std::string& Certificado::obtenerCertificado() {
    return this->certificado;
}

void Certificado::guardarCertificado() {
    std::string nombre_archivo(this->subject);
    nombre_archivo.append(".cert");
    std::ofstream archivo(nombre_archivo);
    archivo << this->certificado;
}

void Certificado::leerCertificado(std::string &nombre) {
    // Leo certificado completo.
    std::ifstream archivo(nombre);
    std::stringstream buffer;
    buffer << archivo.rdbuf();
    this->certificado = buffer.str();
    archivo.seekg(0, std::ios::beg);

    std::string linea;
    std::string numero;

    // certificate:
    std::getline(archivo, linea);

    // serial number
    std::getline(archivo, linea);
    numero = this->obtenerCampoNumerico(linea);
    this->setearSerialNumber((uint32_t)std::stoi(numero));

    // subject
    std::getline(archivo, linea);
    this->setearSubject(this->obtenerCampoTexto(linea));

    // issuer
    std::getline(archivo, linea);
    this->setearIssuer(this->obtenerCampoTexto(linea));

    // validity
    std::getline(archivo, linea);

    // fecha inicial
    std::getline(archivo, linea);
    this->setearFechaIni(this->obtenerCampoTexto(linea));

    // fecha final
    std::getline(archivo, linea);
    this->setearFechaFin(this->obtenerCampoTexto(linea));

    // subject public key info
    std::getline(archivo, linea);

    // modulus
    std::getline(archivo, linea);
    numero = this->obtenerCampoNumerico(linea);
    this->setearMod((uint16_t)std::stoi(numero));

    // exponent
    std::getline(archivo, linea);
    numero = this->obtenerCampoNumerico(linea);
    this->setearExp((uint8_t)std::stoi(numero));
}

std::string Certificado::obtenerCampoTexto(std::string &linea) {
    std::size_t posi = linea.find(':') + 2;
    return linea.substr(posi);
}

std::string Certificado::obtenerCampoNumerico(std::string &linea) {
    std::size_t posi = linea.find(':') + 2;
    std::size_t posf = linea.find(' ', posi);
    return linea.substr(posi, posf - posi);
}

uint32_t Certificado::obtenerSerialNumber() {
    return this->serial_number;
}

std::string& Certificado::obtenerSubject() {
    return this->subject;
}

std::string& Certificado::obtenerIssuer() {
    return this->issuer;
}

std::string& Certificado::obtenerFechaIni() {
    return this->fecha_ini;
}

std::string& Certificado::obtenerFechaFin() {
    return this->fecha_fin;
}

uint16_t Certificado::obtenerMod() {
    return this->mod;
}

uint8_t Certificado::obtenerExp() {
    return this->exp;
}
