#!/bin/bash
#
#SBATCH --cpus-per-task=8
#SBATCH --time=10:00
#SBATCH --mem=5G
#SBATCH --partition=slow

# Run the command
./bin/count data/citeseer 4-motifs 4