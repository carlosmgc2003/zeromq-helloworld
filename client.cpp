//
//  Ejemplo modificado de la guia de ZeroMQ ahora recibimod JSON!
//  Hello World client in C++
//  Connects REQ socket to tcp://localhost:5555
//  Sends "Hello" to server, expects "World" back
//
#include <zmq.hpp>
#include <nlohmann/json.hpp>
#include <string>
#include <iostream>

int main ()
{
    //  Preparamos el contexto y el socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, zmq::socket_type::req);
    std::cout << "Conectandose al helloworld server modificado..." << std::endl;
    socket.connect ("tcp://localhost:5555");

    //  Do 10 requests, waiting each time for a response
    for (int request_nbr = 0; request_nbr != 10; request_nbr++) {
        zmq::message_t request (5);
        memcpy (request.data (), "holas", 5);
        std::cout << "Sending Hello " << request_nbr << "…" << std::endl;
        socket.send (request, zmq::send_flags::none);

        //  Atrapemos el JSON!!!
        //  Preparamos un objeto mensaje
        zmq::message_t reply;
        //  Guardamos en el lo recv del servidor.
        socket.recv (reply);
        std::cout << "Received JSON!!! " << request_nbr << std::endl;

        //  Receta: Para rearmar el json, parseamos el string, que construimos con los datos que parseamos como char.
        nlohmann::json rpl = nlohmann::json::parse(std::string(static_cast<char*>(reply.data()), reply.size()));
        //  Imprimimos la bella respuesta como permite el objeto json
        std::cout << rpl << std::endl;
    }
    return 0;
}