#include <zmq.hpp>
#include <iostream>
#include <vector>
#include <string>

int main() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_ROUTER);
    socket.bind("tcp://*:5555");

    uint64_t num_tasks = 100; // For example, total number of tasks to distribute
    int num_worker_nodes = 5; // For example, number of worker nodes
    std::vector<uint64_t> worker_task_index(num_worker_nodes, 0);

    while (true) {
        zmq::message_t identity;
        zmq::message_t request;
        socket.recv(&identity);
        socket.recv(&request);

        std::string worker_id(static_cast<char*>(request.data()), request.size());

        // ... rest of your code ...

        // Use "%lu" or the correct format specifier for your variable type
        snprintf((char *)task.data(), 20, "%lu", worker_task_index[worker_index]++);

        // Send the task message
        socket.send(identity, ZMQ_SNDMORE);
        socket.send(task, 0);
    }
    return 0;
}git 