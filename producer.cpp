/*
*Authored by: Chris Rook
*
*/

#include "producer.h"
#include "cryptoexchange.h"
#include "shared.h"
#include "log.h"
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <queue>
#include <time.h>



/// @brief Producer constructor that assigns the broker Shared Data object to a pointer
/// @param brokerInfo pointer to the broker Shared Data object
/// @param coin Enum that specifies which kind of trade request will be produced
Producer::Producer(SHARED_DATA* brokerInfo, RequestType coin){
    broker = brokerInfo;
    processingTime = DEFAULT_OPTIONAL_ARGS;
    coinType = coin;
}

/// @brief Thread function for Producers. Function produce trade requests (BuyOrders) and adds them to a queue
/// @param arg pointer that points the Producer object that holds the data for the thread
/// @return The void* is not returned as it is not needed
void* tradeRequestProducer(void* arg) {
    //typecast arg pointer to Producer*
    Producer* pProducerData = static_cast<Producer*>(arg);
    int position = static_cast<int>(pProducerData->coinType); //used for shared data array indexing and Coin type
    struct timespec sleepTime = {SECONDS, pProducerData->processingTime}; //used for nanosleep() arg

    while ((pProducerData->broker->tradesProcessed) < (pProducerData->broker->processLimit)) {
        BuyOrder cryptoRequest(pProducerData->coinType); //item to be added to the queue as trade request

        //simulated production of trade request
        nanosleep(&sleepTime, NULL);
        
        //check bitcoin limit
        if (pProducerData->coinType == Bitcoin) {
            sem_wait(&(pProducerData->broker->bitcoinCapacity));
        }

        //check broker queue capacity for room
        sem_wait(&(pProducerData->broker->brokerCapacity));

        //start of critical section
        sem_wait(&(pProducerData->broker->mutex));
        //checks for edge case of both producer threads in the while loop with one awaiting mutex access
        if ((pProducerData->broker->tradesProcessed) < (pProducerData->broker->processLimit)){
            pProducerData->broker->brokerQueue.push(cryptoRequest);
        }
        //increment shared data counters
        pProducerData->broker->tradesProcessed++; 
        pProducerData->broker->produced[position]++;
        pProducerData->broker->inRequestQueue[position]++;
        //print statements 
        log_request_added(pProducerData->coinType, pProducerData->broker->produced, pProducerData->broker->inRequestQueue);
        sem_post(&(pProducerData->broker->mutex));
        //end of critical section
        //signal to consumers
        sem_post(&(pProducerData->broker->unconsumed));
    }

    pthread_exit(NULL);
}