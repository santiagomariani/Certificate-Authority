//
// Created by santi on 01/05/19.
//

#ifndef TP3_SOCKETERROR_H
#define TP3_SOCKETERROR_H

#include <stdexcept>

class SocketError : public std::runtime_error {
public:
    explicit SocketError(const char* error) : runtime_error(error) {}
};

#endif //TP3_SOCKETERROR_H
