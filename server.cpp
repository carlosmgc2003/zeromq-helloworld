//
//  Modificado de los ejemplo de zmq
//  Hello World server in C++
//  responde con un JSON!!!
//
#include <zmq.hpp>
#include <string>
#include <iostream>
#include <nlohmann/json.hpp>
#include <unistd.h>


int main () {
    //  Creamos un objeto de contexto con la cantidad de hilos de com
    zmq::context_t context (1);
    //  Creamos un objeto socket con ese contexto y la constante de TIPO de socket
    zmq::socket_t socket (context, zmq::socket_type::rep);
    //  Bindeamos un puerto y un protocolo (recordar que zmq sirve para varios tipos de com)
    socket.bind ("tcp://*:5555");

    while (true) {
        //  Creamos un objeto message_t para alojar el request
        zmq::message_t request;
        //  Espera al request del cliente
        socket.recv (request);
        std::cout << "Recibimos Hola" << std::endl;
        //  No se puede pasar del mensaje recibido directo a string por eso tenemos que castearlo.
        std::string rqst = std::string(static_cast<char*>(request.data()), request.size());
        std::cout << rqst << std::endl;
        //  Do some 'work'
        sleep(1);
        //  Creamos un objeto json
        nlohmann::json j;
        //  Le agregamos una clave
        j["Hola"] = "Mundo";
        //  Se puede imprimir de forma directa en pantalla y bonita
        std::cout << j << std::endl;

        //  Receta: para facilitar el intercambio con ZeroMQ la convertimos a string
        std::string mensaje = j.dump();
        //  La pasamos directo al mensaje
        zmq::message_t reply(& mensaje, sizeof(mensaje));
        socket.send (reply,zmq::send_flags::none);
    }
    return 0;
}