
//==========================================================================================//
/**
 * @file CSE_CircularBuffer.h
 * @author Vishnu Mohanan (@vishnumaiea, @vizmohanan)
 * @maintainer CIRCUITSTATE Electronics (@circuitstate)
 * @brief Header file for the CSE_CircularBuffer Arduino library.
 * @version 0.0.2
 * @date Last Modified: +05:30 21:55:33 PM 19-05-2024, Sunday
 * @license MIT
 * @mainpage https://github.com/CIRCUITSTATE/CSE_CircularBuffer
 */
//==========================================================================================//

#ifndef CSE_CIRCULARBUFFER_H
#define CSE_CIRCULARBUFFER_H

#include <Arduino.h>

//==========================================================================================//
/**
 * @brief The main circular buffer class.
 * 
 */
template <typename CSE_CB_t = uint8_t>
class CSE_CircularBuffer {
  private:
    CSE_CB_t* buffer;  // Pointer to the buffer
    int maxlen; // Maximum length of the buffer
    int head; // Head position
    int tail; // Tail position

  public:
    bool discardOld;  // Wheather to discard old data when the buffer is full

    CSE_CircularBuffer (int length); // Dynamically create a data buffer
    CSE_CircularBuffer (CSE_CB_t* buffer, int length); // Accept a user defined buffer
    ~CSE_CircularBuffer(); // Destructor

    int getHead (void); // Get the head position
    int getTail (void); // Get the tail position
    int getCapacity (void); // Get the capacity of the buffer

    bool isFull (void); // Check if the buffer is full
    bool isEmpty (void); // Check if the buffer is empty
    int getOccupiedLength (void); // Get the number of occupied locations in the buffer
    int getVacantLength (void); // Get the number of vacant locations in the buffer
    int push (CSE_CB_t data); // Push a single data item into the buffer
    int push (CSE_CB_t* data, int length, int dataOrder = 0); // Push a data array into the buffer
    int pop (CSE_CB_t* data); // Pop a single data from the buffer
    int pop (CSE_CB_t* data, int length); // Pop a data array from the buffer
    int bufferCopy (CSE_CB_t* data, int length = 0, int dataOrder = 0); // Copy the buffer to a data array, without popping
    int clear (void); // Clear the buffer
    int peek (CSE_CB_t* data); // Peek a single data from the buffer without popping
};

#include "CSE_CircularBuffer.tpp"

//==========================================================================================//

#endif
