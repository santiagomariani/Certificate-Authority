//
// Created by santi on 25/04/19.
//

#ifndef TP3_SERVER_INDICE_H
#define TP3_SERVER_INDICE_H

#include <string>
#include <map>
#include <fstream>
#include <mutex>

#include "common_Clave.h"

// Al crearse el objeto lee el archivo índice y guarda en memoria
// la información de todos los subjects y claves. Permite tener registro
// de los certificados, así como también agregar y borrar los
// mismos. Luego podemos pedirle que guarde el índice actualizado.
class Indice {
private:
    std::string nombre_archivo;
    std::map<std::string, Clave> indice;
    uint32_t prox_num_serie;
    std::mutex m;

public:
    explicit Indice(std::string &archivo);
    // Agrega al mapa un par (subject, clave) si no esta el subject
    // , y devuelve un booleano indicando si se pudo agregar.
    bool agregarSiNoEsta(std::string &subject, Clave clave);
    // Agrega al mapa un par (subject, clave) sin aumentar el numero
    // de serie.
    void agregarSinAumentarNumSerie(std::string &subject, Clave clave);
    // Permite obtener la clave asociada con el subject.
    Clave obtenerClave(std::string &subject);
    // Elimina del mapa al par (subject, clave) si se encuentra
    // el subject, y devuelve un booleano indicando si se pudo
    // quitar.
    bool quitarSiEsta(std::string &subject);
    // Devuelve un booleano indicando si se encuentra el subject.
    bool estaCertificado(std::string &subject);
    // Guarda el indice actualizado en el archivo.
    void guardarIndice();
    // Permite obtener el proximo numero de serie (el que se
    // guarda en el archivo).
    uint32_t obtenerProxNumSerie();
    ~Indice() = default;
};

#endif //TP3_SERVER_INDICE_H
