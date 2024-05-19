
//==========================================================================================//
/**
 * @file CSE_CircularBuffer.h
 * @author Vishnu Mohanan (@vishnumaiea, @vizmohanan)
 * @maintainer CIRCUITSTATE Electronics (@circuitstate)
 * @brief Header file for the CSE_CircularBuffer Arduino library.
 * @version 0.0.1
 * @date Last Modified: +05:30 11:51:46 AM 19-05-2024, Sunday
 * @license MIT
 * @mainpage https://github.com/CIRCUITSTATE/CSE_CircularBuffer
 */
//==========================================================================================//

#ifndef CSE_CIRCULARBUFFER_H
#define CSE_CIRCULARBUFFER_H

#include <Arduino.h>

//==========================================================================================//

class CSE_CircularBuffer {
  private:
    uint8_t* buffer;  // Pointer to the buffer
    int maxlen; // Maximum length of the buffer
    int head; // Head position
    int tail; // Tail position

  public:
    bool discardOld;  // Wheather to discard old data when the buffer is full

    CSE_CircularBuffer (int length); // Dynamically create the buffer
    CSE_CircularBuffer (uint8_t* buffer, int length); // Accept a user defined buffer
    ~CSE_CircularBuffer(); // Destructor

    int getHead (void); // Get the head position
    int getTail (void); // Get the tail position
    int getCapacity (void); // Get the capacity of the buffer

    bool isFull (void); // Check if the buffer is full
    bool isEmpty (void); // Check if the buffer is empty
    int getOccupiedLength (void); // Get the number of occupied bytes in the buffer
    int getVacantLength (void); // Get the number of vacant bytes in the buffer
    int push (uint8_t data); // Push a single byte into the buffer
    int push (uint8_t* data, int length, int byteOrder = 0); // Push a byte array into the buffer
    int pop (uint8_t* data); // Pop a single byte from the buffer
    int pop (uint8_t* data, int length); // Pop a byte array from the buffer
    int bufferCopy (uint8_t* data, int length = 0, int byteOrder = 0); // Copy the buffer to a byte array, without popping
    int clear (void); // Clear the buffer
    int peek (uint8_t* data); // Peek a single byte from the buffer without popping
};

//==========================================================================================//

#endif
