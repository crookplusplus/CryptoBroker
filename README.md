# CryptoBroker
&nbsp;&nbsp;This project serves as a simulation of a cryptocurrency brokerage dedicated to managing purchase and sale requests for a pair of digital currencies. To ensure efficient transaction processing, the project leverages the concept of concurrent producer and consumer threads
&nbsp;&nbsp; The purpose of this project is to demonstrate proficiency in creating multithreaded programs that implement semaphores for synchronization and data integrity in C++ programming within a Linux environment.
## Purpose

## Concurrency Model
&nbsp;&nbsp;In this system, producer threads are responsible for the generation of buy orders, which are then placed into a shared queue functioning as a bounded buffer. Specifically, there exist two producer threads, each responsible for producing buy orders for distinct cryptocurrencies, namely Bitcoin and Ethereum.

&nbsp;&nbsp;On the other side, two consumer threads are tasked with processing these buy orders via separate simulated blockchains, referred to as Blockchain X and Blockchain Y.

## Synchronization and Data Control
&nbsp;&nbsp;To maintain the integrity of the shared queue and prevent potential race conditions, semaphores are employed to enforce critical sections around the queue. Given the bounded nature of the buffer, which permits a maximum of 16 total sale requests and 5 Bitcoin requests, semaphores are strategically employed to prevent overproduction of requests by producer threads. Additionally, a semaphore is employed as a barrier, ensuring synchronized completion of all threads.



## DevelopmentEnvironment
&nbsp;&nbsp;This project is executed within a Linux environment to harness the capabilities of the POSIX thread library.

- **<u>Operating System:</u>** [Ubuntu 20.04 LTS on Windows Subsytem for Linux.](https://ubuntu.com/tutorials/install-ubuntu-on-wsl2-on-windows-10#1-overview)
- **<u>IDE: </u>** [Visual Studio Code (VS Code)](https://code.visualstudio.com/download)
- **<u>Compiler</u>**[Visual Studio Code (VS Code)](https://gcc.gnu.org/)
- **<u>C++ Standard:</u>** C++11 (extension in VS Code)
- **<u>Build Tool:</u>** GNU Make 4.2.1 (extension in VS Code)

#### Dependencies
- **<u>pthread.h</u>** - Used to implement individual threads.
- **<u>unistd.h</u>** - Used to parse command line arguments.
- **<u>semaphore.h</u>** - Used to for thread synchronization and data integrity.
- **<u>time.h</u>** - The nanosleep function is used by each producer and consumer thread to simulate each process of the brokerage taking a different amount of arbitrary time to complete.
- **<u>queue</u>** - The producer and consumer threads share a queue for orders of the same coin.

## Features
- **<u>Multi-Threading (Producer-Consumer):</u>** This program implements a main thread, two Producer threads and two Consumer Threads. The Producer threads create buy orders and adds them to the queue while the corresponding Consumer thread pulls the order from the queue and fullfils the order.

- **<u>Bounded Buffer Implementation</u>:** Employs a bounded buffer, ensuring a limited capacity for sale requests (16 total, 5 Bitcoin) and employing semaphores to prevent overproduction

- **<u>Semaphore-Based Synchronization</u>:**  Implements semaphores to prevent race conditions, creating critical sections around the shared queue, and ensures synchronized completion of all threads.

- **<u>Command-Line Argument Parsing:</u>**  The program offers user-friendly command-line interface functionality for building and executing the program.

- **<u>Linux Environment:</u>** Designed to run on a Linux environment, taking advantage of the POSIX thread library for optimal multi-threaded execution and synchronization.

## Getting Started
&nbsp;&nbsp; The program requires a Unix based operating system for the program to execute with the POSIX library for concurrent threads using pthreads.h.

### Prerequisites

Before you can execute this program, make sure you have the following:
- GNU Make 4.2.1 or newer: required to execute the Make instructions to build the program executables.
- g++ Compiler: The GNU compiler is used to build and run the program. the compiler must support C++11. 

### Installation
**Download the following files into the same folder:**
- 'Makefile': Used for building the program
- 'consumer.h' and 'consumer.cpp': Contains the Consumer object and constructor as well as the Consumer thread function implementation
- 'producer.h' and 'producer.cpp': Contains the Producer object constructor as well as the Producer thread function implementation
- 'shared.h' and 'shared.cpp': Contains a BuyOrder object and the SHARED_DATA object that contains the semaphores, the shared queue, and the arrays that contain information to logged at the end of the simulation.
- 'log.h' and 'log.cpp': Contains functions to output information about the program and its execution stats
- 'cryptoexchange.h': Contains enums that correspond to the index of the two coin types and the two blockchain types.
- 'main.cpp': Main driver function for the program. Parses command line arguments, creates and calls producer and consumer threads and manages memory. 

## Usage
This project is built and operated through the command line interface.
- Open a terminal window and navigate to the folder that contains the project files. 
- Run the following command to build the program:
    _make ./cryptoexc_
- Run the following command to run the program: 
    _./cryptoexc_ and any optional arguments.; refer to the **Optional Arguments** section below.

    ##### <u>**Optional Arguments**</u>
    - **_-r N_**: &nbsp;&nbsp; _N_ is the total number of trade request. Default value is 100.
    - **_-x N_**: &nbsp;&nbsp; _N_ is the number of milliseconds that the consumer thread using **Blockchain X** requires to process a trade reqest. Default is 0.
    - **_-y N_**: &nbsp;&nbsp; _N_ is the number of milliseconds that the consumer thread using **Blockchain Y** requires to process a trade request. Default is 0.
    - **_-b N_**: &nbsp;&nbsp; _N_ is the number of milliseconds that is required to produce and publish a **Bitcoin** request. Default is 0.
    - **_-e N_**: &nbsp;&nbsp; _N_ is the number of milliseconds that is requied to produce and publish an **Ethereum** request. Default is 0.

## Output
&nbsp;&nbsp; The output of the program is displayed to the terminal at the end of execution.
