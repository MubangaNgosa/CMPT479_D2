#!/bin/bash
#SBATCH --job-name=jobPool
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1  # Adjust based on your jobPool requirements
#SBATCH --mem=5GB
#SBATCH --time=00:10:00
#SBATCH --output=jobPool_%j.log

# Load ZeroMQ module if available
# module load zeromq

# Run the master node program
./jobPool
