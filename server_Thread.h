//
// Created by santi on 01/05/19.
//

#ifndef TP3_SERVER_THREAD_H
#define TP3_SERVER_THREAD_H


#include <thread>

// Se utiliza para ejecutar un Functor en un hilo separado.
class Thread {
private:
    std::thread thread;
public:
    Thread();
    // Lanza el thread ejecutando la funcion Thread::run.
    void start();
    // Espera a que el hilo termine.
    void join();
    // El metodo run se define en una clase hija.
    virtual void run() = 0;
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;
    Thread(Thread&& other);
    Thread& operator=(Thread&& other);
    virtual ~Thread();
};


#endif //TP3_SERVER_THREAD_H
