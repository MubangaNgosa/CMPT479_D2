#!/bin/bash
#SBATCH --job-name=worker
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1  # Adjust based on your worker requirements
#SBATCH --mem=5GB
#SBATCH --time=00:10:00
#SBATCH --output=worker_%j.log

# Load ZeroMQ module if available
# module load zeromq

# The master's IP can be passed as an argument or discovered dynamically
# For the sake of this example, we're assuming it's passed as an argument
MASTER_IP=$1

# Run the worker node program
./worker $MASTER_IP
