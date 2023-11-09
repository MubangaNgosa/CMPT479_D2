#!/bin/bash
#SBATCH --job-name=zeromq_example
#SBATCH --nodes=6
#SBATCH --ntasks-per-node=1
#SBATCH --time=00:10:00
#SBATCH --output=zeromq_example_%j.log

# Load ZeroMQ module if available
# module load zeromq

# Determine the IP address of the first node (which we'll use as the master)
MASTER_IP=$(srun --nodes=1 --ntasks=1 hostname -i)

# Start the master node application
if [[ "$SLURM_NODEID" -eq 0 ]]; then
  ./master_node $MASTER_IP
else
  # Start the worker node applications on all other nodes
  ./worker_node $MASTER_IP
fi
