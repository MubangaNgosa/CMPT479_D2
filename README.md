
How to run the program so far.
navigate to the "core" directory
run


g++ -o jobPool jobPool.cc -lzmq


g++ -o worker worker.cc -lzmq


then run

sbatch testScript.sh



Useful links
https://mpitutorial.com/tutorials/mpi-hello-world/

https://research.google/research-areas/distributed-systems-and-parallel-computing/

https://github.com/thomasWeise/distributedComputingExamples

https://book.mixu.net/distsys/single-page.html


https://zeromq.org/
https://www.youtube.com/watch?v=UrwtQfSbrOs
Zero MQ tutorial 


/-----------------------------------------------------------------------\
    Task Generation: Upon executing bin/count data/citeseer 3-motifs 8, the peregrine.cc application starts by generating tasks for counting 3-motifs in the Citeseer dataset. Each task would represent a portion of the graph to be processed for motif counting.

    Job Packet Creation: For each task, the modified loop in peregrine.cc creates a JobPacket with all necessary information for the task (like vertex indices and counts).

    Sending to jobPool: These JobPackets are then serialized and sent to jobPool.cc. This dispatch is handled by a communication mechanism (such as ZeroMQ) that sends the data packets from the peregrine application to the jobPool.

    Distributed Processing: The jobPool acts as a coordinator, distributing these tasks to available worker nodes in the distributed system. Each worker node, running an instance of your modified worker.cc code, receives a job packet, deserializes it, and processes the specified graph segment for 3-motif counting.

    Result Aggregation: As worker nodes complete their tasks, they send back the results to the jobPool or directly to the peregrine application, depending on your system's design. This could involve counting motifs in the specified graph segment.

    Final Output: Once all tasks are completed and results are gathered, peregrine.cc aggregates these results to produce the final count of 3-motifs in the Citeseer dataset.

Key Changes in Behavior:

    Distributed Processing: Instead of processing the entire task on a single node, the work is distributed across multiple nodes.
    Asynchronous Operation: The system can handle tasks asynchronously, improving scalability and potentially increasing efficiency.
    Dynamic Scalability: The system's performance can scale with the number of available worker nodes.

Important Considerations:

    Correctness and Completeness: Ensuring that all parts of the graph are processed correctly and completely, without overlaps or gaps, is crucial.
    Error Handling: Robust error handling is necessary to deal with potential failures in distributed nodes.
    Performance Monitoring: Depending on network latency and the efficiency of worker nodes, the performance may vary. Monitoring and optimizing for these factors will be important.
