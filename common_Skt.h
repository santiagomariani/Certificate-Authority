//
// Created by santi on 21/04/19.
//

#ifndef TP3_SKT_H
#define TP3_SKT_H


class Skt {
    public:
    // Permite leer como mucho longitud bytes del socket y
    // guardarlos en el buffer indicado.
    int leer_mensaje(int skt, char *buffer, int longitud);

    // Permite enviar al socket longitud bytes que estan en
    // el buffer indicado.
    int enviar_mensaje(int skt, char *buffer, int longitud);

    // Cierra canal de escritura.
    void cerrar_canal_escritura(int skt);

    // Cierra socket.
    void cerrar_socket(int skt);
};

#endif //TP3_SKT_H
