/*
*Authored by: Chris Rook
*
*
*/

#include "consumer.h"
#include "cryptoexchange.h"
#include "shared.h"
#include "log.h"
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <queue>
#include <time.h>


/// @brief Consumer constructor that assigns the broker shared data to a pointer member
/// @param brokerInfo pointer to the Shared Data object
/// @param blockChain enum that specifies which Blockchain (X or Y) the Consumer is
Consumer::Consumer(SHARED_DATA* brokerInfo, Consumers blockChain){
    broker = brokerInfo;
    processingTime = DEFAULT_OPTIONAL_ARGS;
    blockChainType = blockChain;
    for (int i=0; i<0; i++){
        consumed[i] = ZERO;
    }
}


/// @brief Consumer Thread function that removes trade requests(BuyOrders) and sleeps for the time parameter assigned to it
/// @param arg This is a Consumer object that provides the data for the type of Blockchain (X or Y) that is consuming the requests
/// @return The function does not return a void* as there is not a need for one
void* tradeRequestConsumer(void* arg) {
    //typecast void* to Consumer*
    Consumer* pConsumer = static_cast<Consumer*>(arg);
    struct timespec sleepTime = {SECONDS, pConsumer->processingTime}; //data type used for nanosleep()

    while ((pConsumer->broker->tradesConsumed) < (pConsumer->broker->processLimit)) {

        //Block for trade request to consume
        sem_wait(&(pConsumer->broker->unconsumed));

        //start critical section 
        sem_wait(&(pConsumer->broker->mutex));
        BuyOrder order = pConsumer->broker->brokerQueue.front();
        pConsumer->broker->brokerQueue.pop();
        pConsumer->broker->tradesConsumed++; 
        pConsumer->consumed[static_cast<int>(order.cryptoType)]++;
        pConsumer->broker->inRequestQueue[static_cast<int>(order.cryptoType)]--;
        //print statements
        log_request_removed(pConsumer->blockChainType, order.cryptoType, pConsumer->consumed, pConsumer->broker->inRequestQueue);
        sem_post(&(pConsumer->broker->mutex));
        //end critical section
        
        //simulated consumption of trade request
        nanosleep(&sleepTime, NULL);

        //increment bitcoin capacity semaphore        
        if (static_cast<int>(order.cryptoType) == BITCOIN){
            sem_post(&(pConsumer->broker->bitcoinCapacity));
        }

        //increment broker capacity semaphore
        sem_post(&(pConsumer->broker->brokerCapacity));
        
    }
    //check for end of program condition
    if((pConsumer->broker->brokerQueue.empty()) && ((pConsumer->broker->tradesConsumed)==(pConsumer->broker->processLimit))){
        sem_post(&(pConsumer->broker->barrier));
    }

    pthread_exit(NULL);
}