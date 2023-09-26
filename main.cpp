/*
*Authored by: Chris Rook
*
*
*/

#include "cryptoexchange.h"
#include "log.h"
#include "shared.h"
#include "producer.h"
#include "consumer.h"
#include <iostream>
#include <queue>
#include <pthread.h>
#include <unistd.h>


/**
 * ./cryptoexc -r 150 -x 10 -y 15 -b 12 -e 7
*/


/// @brief Main driver function to run program. Instantiates SHARED_DATA, Producer, and Consumer objects and threads.
/// @param argc Number of command line arguments
/// @param argv Array that holds the command line arguments
/// @return Returns exit values indicating program behavior
int main (int argc, char* argv[])
{
    int option; //command line switch
    int rArg; //value set by -r
    int xArg; //value set by -x 
    int yArg; //value set by -y
    int bArg; //value set by -b
    int eArg; //value set by -e
    SHARED_DATA broker = SHARED_DATA(); 
    SHARED_DATA* pBroker = &broker; //pointer for shared data
    //typedef enums from cryptoexchange.h
    RequestType BTC = Bitcoin; 
    RequestType ETH = Ethereum; 
    Consumers BCX = BlockchainX; 
    Consumers BCY = BlockchainY; 
    //Producer objects and corresponding ptrs to pass data specific for each thread
    Producer* pBitcoin = new Producer(pBroker, BTC);
    Producer* pEther = new Producer(pBroker, ETH);
    //Consumer objects corresponding ptrs to pass data specific for each thread
    Consumer* pBChainX = new Consumer(pBroker, BCX);
    Consumer* pBChainY = new Consumer(pBroker, BCY);
    //assign broker.consumed[] elements to Blockchain consumed arrays
    broker.consumed[static_cast<int>(BCX)] = pBChainX->consumed;
    broker.consumed[static_cast<int>(BCY)] = pBChainY->consumed;
    //create pthread_t objects for threads
    pthread_t bitcoinThread, ethereumThread, blockchainXThread, blockchainYThread;

    //while loop that processes optional command line arguments
    //all otional arguments are checked for nonzero and zero arguments
    while ((option = getopt(argc, argv, "r:x:y:b:e:")) != -1){

        switch (option) {
            //production limit
            case 'r':
                rArg = atoi(optarg);
                if (rArg <= ZERO){
                    std::cout<<"Production limit should be greater than 0"<<std::endl;
                    exit(BAD_COMMAND_EXIT);
                }
                else {
                    broker.processLimit = rArg;
                }

                break;

            //milliseconds for Blockchain X consumption
            case 'x':
                xArg = atoi(optarg);
                if (xArg < ZERO){
                    std::cout<<"Blockchain X consumption time should be greater than 0"<<std::endl;
                    exit(BAD_COMMAND_EXIT);
                }
                else {
                    pBChainX->processingTime = milliToNano(xArg);
                }

                break;

            //milliseconds for Blockchain y consumption
            case 'y':
                yArg = atoi(optarg);
                if (yArg < ZERO){
                    std::cout<<"Blockchain Y consumption time should be greater than 0"<<std::endl;
                    exit(BAD_COMMAND_EXIT);
                }
                else {
                    pBChainY->processingTime = milliToNano(yArg);
                }

                break;

            //milliseconds for Bitcoin trade request production
            case 'b':
                bArg = atoi(optarg);
                if (bArg < ZERO){
                    std::cout<<"Bitcoin production time should be greater than 0"<<std::endl;
                    exit(BAD_COMMAND_EXIT);
                }
                else {
                    pBitcoin->processingTime = milliToNano(bArg);
                }
                break;

            //milliseconds for Ethereum trade request production
            case 'e':
                eArg = atoi(optarg);
                if (eArg < ZERO){
                    std::cout<<"Bitcoin production time should be greater than 0"<<std::endl;
                    exit(BAD_COMMAND_EXIT);
                }
                else {
                    pEther->processingTime = milliToNano(eArg);
                }
                break;

            default:
                std::cout<<"Usage: "<<argv[0]<<"[-r trafe request limit]"
                <<" [-x milliseconds for Blockchain X consumption]"
                <<" [-y milliseconds for Blockchain Y consumption]"
                <<" [-b milliseconds for Bitcoin production]"
                <<" [-e milliseconds for Ethereum production]"<<std::endl;
                exit(BAD_COMMAND_EXIT);

        }
    }

    //create the producer threads
    pthread_create(&bitcoinThread, NULL, tradeRequestProducer, static_cast<void*>(pBitcoin));
    pthread_create(&ethereumThread, NULL, tradeRequestProducer, static_cast<void*>(pEther));

    //create the consumer threads
    pthread_create(&blockchainXThread, NULL, tradeRequestConsumer, static_cast<void*>(pBChainX));
    pthread_create(&blockchainYThread, NULL, tradeRequestConsumer, static_cast<void*>(pBChainY));

    //wait for threads to produce and consume all trade requests
    sem_wait(&broker.barrier);
    //print production history
    log_production_history(broker.produced, broker.consumed);

    //release heap memory
    delete pBitcoin;
    delete pEther;
    delete pBChainX;
    delete pBChainY;

    exit(NORMALEXIT);
}