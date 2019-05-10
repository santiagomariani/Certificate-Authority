//
// Created by santi on 01/05/19.
//

#include "server_ThAceptador.h"
#include "server_ThCliente.h"
#include "common_SocketError.h"

ThAceptador::ThAceptador(
        SktAceptador skt_acep,
        Indice &indice,
        InfoClave &claves)
    :skt_acep(std::move(skt_acep)),
    indice(indice),
    claves_server(claves),
    finalizo(false) {
}

void ThAceptador::run() {
    while (true) {
        try {
            Skt skt = this->skt_acep.aceptarCliente();
            ThCliente *cliente = new ThCliente(std::move(skt),
                                                this->indice,
                                                this->claves_server);
            cliente->start();
            clientes.push_back(cliente);
        } catch (const SocketError &e) {
            break;
        }
        auto it = this->clientes.begin();
        while (it != this->clientes.end()) {
            if ((*it)->isDead()) {
                (*it)->join();
                delete *it;
                it = this->clientes.erase(it);
            } else {
                ++it;
            }
        }
    }
    auto it = this->clientes.begin();
    while (it != this->clientes.end()) {
        (*it)->stop();
        (*it)->join();
        delete *it;
        it = this->clientes.erase(it);
    }
}

void ThAceptador::stop() {
    this->skt_acep.cerrarCanales();
    this->skt_acep.cerrarSocket();
}
