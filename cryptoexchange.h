#ifndef CRYPTOEXCHANGE_H
#define CRYPTOEXCHANGE_H

/*
 * Arrays with producer and consumer names
 * The indices correspond to the coin type
 */
extern const char *producerNames[];
extern const char *producerAbbrevs[];  
extern const char *consumerNames[]; 

/**
 * The broker can hold up to a maximum of 16 unconsumed requests 
 * in its request queue at any given time.
 * e.	As a Bitcoin transaction costs more fee, 
 * there can be no more than 5 transaction requests for 
 * Bitcoins in the broker request queue at any given time. 
*/

/*
 * Two trade request services (producers of requests) are offered: 
 *   one for publishing (producing) a bitcoin trader request, 
 *   one for publishing (producing) an ethereum trader request.
 * Each trade request service (producer) only publishes (produces) 
 * one type of requests,
 * so RequestType is synomonous with the producer type
 */
typedef enum{
  Bitcoin = 0,        // Bitcoin trade request
  Ethereum = 1,       // Ethereum trade request 
  RequestTypeN = 2,   // number of trade request types
} RequestType;

/* 
 * Two trade transaction services (consumers of requests) are available using 
 * different block chains
 *   one uses blockchain X
 *   one uses blockchain Y 
 *   Requests are taken off from the broker request queue (by consumers) 
 *   in the order that they are published (produced).
*/
typedef enum {
  BlockchainX = 0,   // process request transaction on blockchain X 
  BlockchainY = 1,   // process request transaction on blockchain Y 
  ConsumerTypeN = 2, // Number of consumers
} Consumers;


#endif