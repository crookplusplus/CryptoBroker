/*
*Authored by: Chris Rook
*
*
*/

#ifndef SHARED_H
#define SHARED_H

#include <queue>
#include "semaphore.h"
#include "cryptoexchange.h"

#define DEFAULT_TRADE_REQUESTS 100 //default number of trade requests
#define DEFAULT_OPTIONAL_ARGS 0 //default optional args 
#define MUTEX 1//used to initialize the mutex semaphore
#define SHAREDSEMAPHORE 1 //used of sem_init
#define NORMALEXIT 0 //Normal exit case for main thread
#define BAD_COMMAND_EXIT 10 //bad command line argument
#define BROKER_QUEUE_CAPACITY 16 //maximum amount of trade requests in the queue
#define BITCOIN_MAXIMUM 5 //maximum amount of bitcoin trade requests
#define BITCOIN 0 // int to represent Bitcoin index
#define ETHEREUM 1 // int to represent Ethereum index
#define COIN_TYPES 2 //total types of coin used for initialization
#define BLOCKCHAIN_TYPES 2 //total types of coin used for initialization
#define ZERO 0 //used for initializing counting variables in constructors
#define FACTOR 1000000 //used to multiple the millisecond arg to convert to nanoseconds
const time_t SECONDS = 0; // const time_t variable at 0 used to pass to nanosleep()

/// @brief class that gets added to the broker queue for trade request processing
class BuyOrder{
    public:
        /// @brief constructor that assigns the type of the trade request created
        /// @param type Enum that specifies the trade request type
        BuyOrder(RequestType type);
        RequestType cryptoType;
};


/// @brief Class holds the broker data to be used for print statements and consumer and producer threads
class SHARED_DATA{
    public:
        /// @brief Constructor signature that explicitly initializes Shared Data members to zero or nullptr.
        SHARED_DATA(); 
        sem_t mutex; //used for mutual exclusion of queue
        sem_t brokerCapacity;  //capacity of queue
        sem_t bitcoinCapacity; //maximum amount of Bitcoin
        sem_t unconsumed; //notifies consumers there are trades to process
        sem_t barrier; //used as precedence constraint
        int processLimit; //process limit for requests
        int tradesProcessed; //int variable to count the trades processed;
        int tradesConsumed; //int variable to count the trades consumed
        unsigned int produced[COIN_TYPES]; //array to count the amount trade request that have been produced
        unsigned int *consumed[BLOCKCHAIN_TYPES]; //array of pointers to keep track of trades consumed
        //unsigned int consumed[COIN_TYPES]; //array to count the amount trade request that have been consumed by each blockchain
        unsigned int inRequestQueue[COIN_TYPES]; //array to count the amount of each coin in the queue
        std::queue<BuyOrder> brokerQueue; //may need to find a way to convert this to enums request type or consumer
};

/// @brief Function that converts millisecond arguments to nanoseconds and long data type
/// @param num Int for milliseconds 
/// @return returns nanoseconds conversion of long type
long milliToNano(int num);


#endif
