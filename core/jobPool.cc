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
        socket.bind("tcp://142.58.103.2:5555");
        std::cout << "Server is ready listening on port 5555" << std::endl;
        std::cout << "Waiting 15 seconds before sending jobs..." << std::endl;

        // Wait for 15 seconds
        std::this_thread::sleep_for(std::chrono::seconds(15));

        std::cout << "About to send jobs!" << std::endl;

        // change this section to send jobs based on Peregrine.hh line 97 while loop.
        for (int i = 0; i < 100; ++i) {
            // Create the job message
            std::string job = "sending job " + std::to_string(i);

            // Send the job message
            zmq::message_t message(job.data(), job.size());
            socket.send(message);
            
            // Wait for 500 milliseconds between each job
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
