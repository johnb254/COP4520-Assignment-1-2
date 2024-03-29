# COP4520 Assignment 1-2

## Description
This program was written for the Concepts of Parallel and Distributed Processing course at the
    University of Central Florida.

Your non-technical manager assigns you the task to find all primes between 1 and
    10^8. The assumption is that your company is going to use a parallel machine that
    supports eight concurrent threads. Thus, in your design you should plan to spawn 8
    threads that will perform the necessary computation. 

### Approach and Reasoning
The simplest way to solve the problem is to create a vector of primes to fill as the threads do
    work. The work is split into equal pieces among the threads. There there's a function to check
    if a number is prime and a function to add to the list. After the thread is done with its
    calculations it rejoins the main thread. Once all threads are back, the vector is merged into
    one, sorted, and the info is printed to primes.txt.

## Installation
1. Download and unzip the source files.

## Usage
1. Open a terminal or command prompt.
2. Navigate to the project directory.
3. Compile the `A1-2.cpp` file using the following command:
    ```bash
    g++ A1-2.cpp -o output
    ```
    Replace `A1-2.cpp` with the name of your C++ file and `output` with the desired name of the executable.
4. Run the compiled file using the following command:
    ```bash
    ./output
    ```
    Replace `output` with the name of the executable you specified in the previous step.
