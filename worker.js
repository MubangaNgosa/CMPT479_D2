const zmq = require("zeromq");
const sock = new zmq.Pull();

run();
async function run() {

    await sock.connect("tcp://127.0.0.1:7000");
    console.log("Connected to server.")

   if (job.type === "peregrine_run") {
            console.log(`Received job ${job.jobId}: ${job.command} ${job.parameters.join(" ")}`);

            // Execute the command
            exec(`${job.command} ${job.parameters.join(" ")}`, (error, stdout, stderr) => {
                console.log(`Command output: ${stdout}`);
                if (error) {
                    console.error(`Command error: ${stderr}`);
                }
            });
        } 
}