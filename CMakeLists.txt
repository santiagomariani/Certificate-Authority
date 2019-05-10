cmake_minimum_required(VERSION 3.13)
project(tp3)

set(CMAKE_CXX_STANDARD 11)

add_executable(tp3 client.cpp common_Hash.cpp common_Hash.h common_Encriptador.cpp common_Encriptador.h common_Clave.cpp common_Clave.h client_InfoCertificado.cpp client_InfoCertificado.h common_InfoClave.cpp common_InfoClave.h common_Skt.cpp common_Skt.h server_SktAceptador.cpp server_SktAceptador.h server.cpp common_Certificado.cpp common_Certificado.h server_Indice.cpp server_Indice.h client_Cliente.cpp client_Cliente.h common_Mensajero.cpp common_Mensajero.h server_Server.cpp server_Server.h server_Thread.cpp server_Thread.h server_ThCliente.cpp server_ThCliente.h server_ThAceptador.cpp server_ThAceptador.h common_SocketError.cpp common_SocketError.h)