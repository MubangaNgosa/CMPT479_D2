#include <zmq.hpp>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_DEALER); // Dealer socket for asynchronous request-reply

    // Socket to talk to server
    std::cout << "Connecting to hello world server…" << std::endl;
    socket.connect("tcp://localhost:5555");

    while (true) {
        // Send a request for a job
        zmq::message_t request(11);
        memcpy(request.data(), "request job", 11);
        socket.send(request);

        // Get the reply.
        zmq::message_t reply;
        socket.recv(reply);
        std::string reply_str(static_cast<char*>(reply.data()), reply.size());

        std::cout << "Received job: " << reply_str << std::endl;

        // Do some 'work'
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    return 0;
}
