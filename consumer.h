/*
*Authored by: Chris Rook
*
*
*/


#ifndef CONSUMER_H
#define CONSUMER_H

#include "shared.h"
#include "cryptoexchange.h"


/// @brief Consumer class that is used to define the different kinds of Blockchains (X or Y)
/// and pass the Shared Data from the broker.
class Consumer{
    public:
        /// @brief Consumer construct that assigns the Shared Data broker data to a pointer, and 
        /// a Consumers enum that defines the type of Blockchain (X or Y)
        /// @param brokerInfo pointer to the Shared Data broker object
        /// @param blockChain enum that defines the type of Blockchain the consumer is (X or Y).
        Consumer(SHARED_DATA* brokerInfo, Consumers blockChain);
        SHARED_DATA* broker;
        long processingTime;
        unsigned int consumed[COIN_TYPES];
        Consumers blockChainType;
};

/// @brief Thread function signature for Consumers
/// @param arg Accepts a pointer pointer to the Consumer object 
/// @return The void* is not returned as there is no need for it.
void* tradeRequestConsumer(void* arg);

#endif