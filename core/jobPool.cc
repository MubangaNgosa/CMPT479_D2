#include <zmq.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

int main() {
    // Initialize the ZeroMQ context and PUSH socket
    zmq::context_t context;
    zmq::socket_t socket(context, zmq::socket_type::push);

    try {
        // Bind the socket to the address and port
        socket.bind("tcp://127.0.0.53:5555");
        std::cout << "Server is ready listening on port 7000" << std::endl;
        std::cout << "Press ENTER to start sending the jobs!" << std::endl;

        // Wait for the user to press ENTER
        std::cin.get();

        std::cout << "About to send jobs!" << std::endl;
        for (int i = 0; i < 100; ++i) {
            // Create the job message
            std::string job = "sending job " + std::to_string(i);

            // Send the job message
            socket.send(zmq::buffer(job), zmq::send_flags::none);

            // Wait for 500 milliseconds
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
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