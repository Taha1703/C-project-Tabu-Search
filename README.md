# Tabu Search for Knapsack Problem

This project implements a **Tabu Search** algorithm to solve a variant of the knapsack problem. It reads item data from a file, where each item has a profit and a weight, and tries to maximize the total profit while keeping the total weight under a specified capacity.

## Features

- Reads problem data from a text file
- Uses a Tabu Search metaheuristic with dynamic tabu tenure
- Initializes the solution greedily based on profit-to-weight ratio
- Prints progress every `m` iterations (configurable)
- Outputs the best found solution with total profit and weight

## Usage

Compile the program (e.g., using g++):

```bash
g++ -o tabu tabu.cpp

Run the executable with the following parameters:

bash
Kopieren
Bearbeiten
./tabu <datafile> <tabu_duration> <iterations> <print_every>
datafile: Path to the input file containing the problem data

tabu_duration: Base tabu tenure duration (integer)

iterations: Maximum number of iterations to run

print_every: Frequency of progress output (set to 0 for no intermediate output)

Example
bash
Kopieren
Bearbeiten
./tabu data.1 3 100 10
