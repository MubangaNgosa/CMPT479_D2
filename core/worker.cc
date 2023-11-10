#include <zmq.hpp>
#include <iostream>
#include <string>
#include <thread>

int main() {
    // Initialize the ZeroMQ context and socket
    zmq::context_t context;
    zmq::socket_t socket(context, zmq::socket_type::pull);

    try {
        // Connect to the server
        socket.connect("tcp://127.0.0.53:5555");
        std::cout << "Connected to server." << std::endl;

        // Enter a loop of receiving messages
        while (true) {
            zmq::message_t message;
            socket.recv(message, zmq::recv_flags::none);
            std::string msg_str(static_cast<char*>(message.data()), message.size());
            std::cout << "Received job: " << msg_str << std::endl;
        }
    } catch (const zmq::error_t& e) {
        std::cerr << "ZeroMQ error: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Standard exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
