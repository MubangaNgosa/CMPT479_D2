
#!/bin/bash
#
#SBATCH --cpus-per-task=1
#SBATCH --time=05:00
#SBATCH --mem=2
#SBATCH --partition=slow

# Run the command
./bin/count data/citeseer 4-motifs 4