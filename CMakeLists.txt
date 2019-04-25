cmake_minimum_required(VERSION 3.13)
project(tp3)

set(CMAKE_CXX_STANDARD 11)

add_executable(tp3 client.cpp common_Hash.cpp common_Hash.h common_Encriptador.cpp common_Encriptador.h common_Clave.cpp common_Clave.h client_InfoCertificado.cpp client_InfoCertificado.h common_InfoClave.cpp common_InfoClave.h client_SktCli.cpp client_SktCli.h common_Skt.cpp common_Skt.h server_SktSv.cpp server_SktSv.h server.cpp)