/*
*Authored by: Chris Rook
*
*/

#ifndef PRODUCER_H
#define PRODUCER_H

#include "shared.h"
#include "cryptoexchange.h"


/// @brief Producer object that specifies what kind of coin type the thread will be
/// be producing trade requests for.
class Producer{
    public:
        /// @brief Producer constructor that assigns the broker Shared Data object to a pointer and specifies
        /// which kind of coin trade request wil be produced
        /// @param brokerInfo pointer to the broker Shared Data object
        /// @param coin Enum that specifies which kind of trade request will be produced
        Producer(SHARED_DATA* brokerInfo, RequestType coin);
        SHARED_DATA* broker;
        long processingTime;
        RequestType coinType;
};

/// @brief Thread function signature for Producers
/// @param arg pointer to the Producer object
/// @return Void* is not returned as it is not need.
void* tradeRequestProducer(void* arg);


#endif