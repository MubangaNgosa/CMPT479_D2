#include <zmq.hpp>
#include <iostream>
#include <string>
#include <cassert>

int main() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_PUSH); // PUSH socket to send tasks
    socket.bind("tcp://*:5555"); // Bind to port 5555

    uint64_t num_tasks = ...; // Total number of tasks to distribute

    // Keep track of which task each worker is on
    std::vector<uint64_t> worker_task_index(num_worker_nodes, 0);

    // Listen for requests from workers
    zmq::socket_t receiver(context, ZMQ_PULL); // PULL socket to receive requests
    receiver.bind("tcp://*:5556"); // Bind to a different port for worker requests

    while (true) {
        zmq::message_t request;
        receiver.recv(request, zmq::recv_flags::none);

        // Parse the worker ID from the request
        std::string worker_id(request.to_string());
        uint64_t worker_index = std::stoull(worker_id);

        // Check if there are still tasks to send
        if (worker_task_index[worker_index] < num_tasks) {
            // Prepare and send the next task
            zmq::message_t task(20);
            snprintf((char *)task.data(), 20, "%llu", worker_task_index[worker_index]++);

            socket.send(task, zmq::send_flags::none);
        } else {
            // No more tasks, send a termination message
            zmq::message_t done("Done", 4);
            socket.send(done, zmq::send_flags::none);
        }
    }

    return 0;
}
