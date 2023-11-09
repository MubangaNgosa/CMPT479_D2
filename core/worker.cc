#include <zmq.hpp>// Worker node pseudocode using ZeroMQ

#include <iostream>
#include <string>
#include <cassert>

void process_task(uint64_t task_id) {
    // ... perform the task ...
}

int main(int argc, char* argv[]) {
    assert(argc > 1); // Ensure worker ID is passed as an argument
    std::string worker_id = argv[1];

    zmq::context_t context(1);

    // PULL socket to receive tasks
    zmq::socket_t receiver(context, ZMQ_PULL);
    receiver.connect("tcp://master_ip:5555");

    // PUSH socket to send requests for tasks
    zmq::socket_t requester(context, ZMQ_PUSH);
    requester.connect("tcp://master_ip:5556");

    while (true) {
        // Send a request for a task
        zmq::message_t request(worker_id.data(), worker_id.size());
        requester.send(request, zmq::send_flags::none);

        // Receive a task
        zmq::message_t task;
        receiver.recv(task, zmq::recv_flags::none);
        std::string task_str = task.to_string();

        // Check for termination message
        if (task_str == "Done") {
            break;
        }

        // Parse task ID and process it
        uint64_t task_id = std::stoull(task_str);
        process_task(task_id);
    }

    return 0;
}
