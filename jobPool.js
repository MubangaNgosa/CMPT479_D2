const zmq = require("zeromq");

const sock = new zmq.Push();
run();

async function run() {
    await sock.bind("tcp://127.0.0.1:7000"); // Corrected port number
    console.log("Server is ready listening on port 7000"); // Corrected log message
    console.log("Press any key to start sending the jobs!");
    process.stdin.once("data", send);
}

// Sending the jobs to the workers
async function send() {
    console.log("About to send jobs!");
    for (let i = 0; i < 100; i++) {
        await sock.send(`sending job ${i}`);
        await new Promise(resolve => setTimeout(resolve, 500));
    }
}
