#!/bin/bash
#SBATCH --job-name=peregrine_job
#SBATCH --output=peregrine_%j.out
#SBATCH --error=peregrine_%j.err
#SBATCH --ntasks=5  # 1 for jobPool and 4 for workers
#SBATCH --time=10:00
#SBATCH --cpus-per-task=2  # Total 10 CPUs, within the limit of 8
#SBATCH --mem=5G  # Each task gets 5GB, adjust if needed

# Run the jobPool program
echo "Starting jobPool"
./jobPool

# Sleep for a short time to ensure jobPool is ready before starting worker#

#sleep 10

# Run the worker programs
#echo "Starting workers"
#for i in {1..4}; do
#   ./worker &
#done

# Wait for all background processes to finish
#wait
