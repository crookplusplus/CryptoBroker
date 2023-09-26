# CryptoBroker
&nbsp;&nbsp; This project emulates a cryptocurrency brokerage tasked with handling purchase and sale requests for a pair of digital currencies. To manage these transactions efficiently, the project employs concurrent producer and consumer threads. The producer threads are responsible for generating buy orders and depositing them into a shared queue, specific to the respective cryptocurrency. Semaphores are utilized to prevent any potential race conditions and to ensure seamless thread synchronization. This project is executed within a Linux environment to harness the capabilities of the POSIX thread library.

## Purpose
&nbsp;&nbsp; The purpose of this project is to demonstrate proficiency in creating multithreaded programs that implement semaphores for synchronization and data integrity in C++ programming within a Linux environment.

## DevelopmentEnvironment
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
- **<u>Multi-Threading (Producer-Consumer)</u>** This program implements a main thread, two Producer threads and two Consumer Threads. The Producer threads create buy orders and adds them to the queue while the corresponding Consumer thread pulls the order from the queue and fullfils the order.

- **<u>Semaphores</u>** Semaphores are used to wrap critical sections within threads that are manipulating shared data. Semaphores are also used for thread synchronization and thread communication.

- **<u>Command-Line Argument Parsing:</u>** - The program offers user-friendly command-line interface functionality for building and executing the program.

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