/*
*Authored by: Chris Rook
*
*
*/

#include "shared.h"
#include <semaphore.h>
#include <pthread.h>
#include "cryptoexchange.h"

/// @brief BuyOrder class that gets added to the broker queue for processing
/// @param type Enum that specifies which kind of trade request is in the queue
BuyOrder::BuyOrder(RequestType type){
    cryptoType = type;
}

/// @brief Constructor to explicitly initialize members for the broker Shared Data object
SHARED_DATA::SHARED_DATA()
{
    sem_init(&mutex, SHAREDSEMAPHORE, MUTEX); //mutex semaphore
    sem_init(&brokerCapacity, SHAREDSEMAPHORE, BROKER_QUEUE_CAPACITY); //limits capacity of broker queue
    sem_init(&bitcoinCapacity, SHAREDSEMAPHORE, BITCOIN_MAXIMUM); //limits amount of Bitcoin trade request
    sem_init(&unconsumed, SHAREDSEMAPHORE, ZERO); //semaphore to signal Consumers to begin consumption
    sem_init(&barrier, SHAREDSEMAPHORE, ZERO); //semaphore for precedence constraint of main
    processLimit = DEFAULT_TRADE_REQUESTS; 
    tradesProcessed = ZERO;
    tradesConsumed = ZERO;

    //for loop to explicitly initialize counting array indeces to ZERO and nullptr
    for(int i=0; i<BLOCKCHAIN_TYPES; i++){
        produced[i] =  ZERO;
        inRequestQueue[i] = ZERO;
        consumed[i] = nullptr;
    }
}

/// @brief Function used to convert milliseconds to nanoseconds of long data type
/// for nanosleep() arguments.
/// @param num int millisecond value
/// @return returns nanosecond of type long
long milliToNano(int num){
    return num * FACTOR;
}