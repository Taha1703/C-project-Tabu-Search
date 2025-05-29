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
