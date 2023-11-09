#include <zmq.hpp>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_ROUTER); // Router socket to communicate with multiple clients
    socket.bind("tcp://*:5555");

    int jobNumber = 1;

    while (true) {
        zmq::message_t request;

        // Wait for next request from client
        zmq::message_t identity;
        socket.recv(identity);
        socket.recv(request);

        std::string request_str(static_cast<char*>(request.data()), request.size());

        if (request_str == "request job") {
            std::cout << "Received job request" << std::endl;

            // Send job number as string
            std::string jobString = std::to_string(jobNumber++);
            zmq::message_t reply(jobString.size());
            memcpy(reply.data(), jobString.c_str(), jobString.size());

            socket.send(identity, zmq::send_flags::sndmore);
            socket.send(reply);

            std::cout << "Sent job " << jobString << std::endl;
        }
    }
    return 0;
}
