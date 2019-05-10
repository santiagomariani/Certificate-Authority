//
// Created by santi on 25/04/19.
//

#include <iostream>
#include <string>
#include "server_Indice.h"

Indice::Indice(std::string &archivo) : nombre_archivo(archivo) {
    std::ifstream archivo_lect(archivo);
    if (archivo_lect.peek() == std::ifstream::traits_type::eof()) {
       this->prox_num_serie = 1;
       return;
    }
    archivo_lect >> this->prox_num_serie;
    char fin_linea;
    archivo_lect.get(fin_linea);

    while (archivo_lect.peek() != std::ifstream::traits_type::eof()) {
        std::string subject;
        uint8_t exp;
        uint16_t mod;
        int aux;
        getline(archivo_lect, subject, ';');
        archivo_lect >> aux;
        exp = aux;
        archivo_lect >> aux;
        mod = aux;
        archivo_lect.get(fin_linea);
        this->indice.insert({subject, Clave(exp, mod)});
    }
}

bool Indice::agregarSiNoEsta(std::string &subject, Clave clave) {
    std::lock_guard<std::mutex> lock(this->m);
    if (this->indice.count(subject) < 1) {
        this->indice.insert({subject, clave});
        ++this->prox_num_serie;
        return true;
    }
    return false;
}

void Indice::agregarSinAumentarNumSerie(std::string &subject, Clave clave) {
    std::lock_guard<std::mutex> lock(this->m);
    this->indice.insert({subject, clave});
}

Clave Indice::obtenerClave(std::string &subject) {
    std::lock_guard<std::mutex> lock(this->m);
    return this->indice.at(subject);
}

bool Indice::quitarSiEsta(std::string &subject) {
    std::lock_guard<std::mutex> lock(this->m);
    if (this->indice.count(subject) < 1) {
        return false;
    }
    this->indice.erase(subject);
    return true;
}

bool Indice::estaCertificado(std::string &subject) {
    std::lock_guard<std::mutex> lock(this->m);
    return this->indice.count(subject) == 1;
}

void Indice::guardarIndice() {
    std::ofstream archivo_escr(this->nombre_archivo);
    archivo_escr << this->prox_num_serie << std::endl;
    auto it = this->indice.begin();
    for (; it != this->indice.end(); ++it) {
        archivo_escr << it->first << "; " << unsigned(it->second.exp);
        archivo_escr << ' ' << it->second.mod << std::endl;
    }
}

uint32_t Indice::obtenerProxNumSerie() {
    return this->prox_num_serie;
}
