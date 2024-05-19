
//==========================================================================================//
/**
 * @file CSE_CircularBuffer.cpp
 * @author Vishnu Mohanan (@vishnumaiea, @vizmohanan)
 * @maintainer CIRCUITSTATE Electronics (@circuitstate)
 * @brief Main source file for the CSE_CircularBuffer Arduino library.
 * @version 0.0.1
 * @date Last Modified: +05:30 11:48:06 AM 19-05-2024, Sunday
 * @license MIT
 * @mainpage https://github.com/CIRCUITSTATE/CSE_CircularBuffer
 */
//==========================================================================================//

#include "CSE_CircularBuffer.h"

//==========================================================================================//
/**
 * @brief Creates a new circular buffer with user-defined buffer. The length should be the
 * length of the actual buffer. The actual usable length is length - 1. For example, if you
 * want 32 bytes for the data you must create a buffer with 33 bytes and send 33 as the
 * length parameter.
 * 
 * Old values in the buffer are not discarded by default.
 * 
 * @param buffer A uint8_t pointer to the buffer.
 * @param length The length of the buffer.
 * @return CSE_CircularBuffer:: 
 */
CSE_CircularBuffer:: CSE_CircularBuffer (uint8_t* buffer, int length) {
  this->buffer = buffer;
  maxlen = (length - 1);  // Usable length is length - 1
  head = 0;
  tail = 0;
  discardOld = false;
}

//==========================================================================================//
/**
 * @brief Creates a new circular buffer with a dynamically allocated buffer. The length is
 * the number of usable bytes. So the function allocates length + 1 bytes.
 * 
 * Old values in the buffer are not discarded by default.
 * 
 * @param length The number of usable bytes.
 * @return CSE_CircularBuffer:: 
 */
CSE_CircularBuffer:: CSE_CircularBuffer (int length) {
  buffer = (uint8_t*) malloc (sizeof (uint8_t) * (length + 1)); // Need one extra byte
  
  for (int i = 0; i < (length + 1); i++) {
    buffer [i] = 0;
  }

  maxlen = length + 1;  // Added extra byte
  head = 0;
  tail = 0;
  discardOld = false;
}

//==========================================================================================//
/**
 * @brief Destroys the circular buffer and frees the memory.
 * 
 * @return CSE_CircularBuffer:: 
 */
CSE_CircularBuffer:: ~CSE_CircularBuffer() {
  free (buffer);
}

//==========================================================================================//
/**
 * @brief Returns the head position of the circular buffer.
 * 
 * @return int The head position.
 */
int CSE_CircularBuffer:: getHead() {
  return head;
}

//==========================================================================================//
/**
 * @brief Returns the tail position of the circular buffer.
 * 
 * @return int The tail position.
 */
int CSE_CircularBuffer:: getTail() {
  return tail;
}

//==========================================================================================//
/**
 * @brief Returns the capacity of the circular buffer. With user-defined buffer, this is the
 * length of the buffer - 1. With dynamically allocated buffer, this is the total length of the
 * buffer including the extra byte.
 * 
 * @return int The capacity of the circular buffer in bytes.
 */
int CSE_CircularBuffer:: getCapacity() {
  return maxlen;
}

//==========================================================================================//
/**
 * @brief Checks if the circular buffer is full.
 * 
 * @return true Circular buffer is full.
 * @return false Circular buffer is not full.
 */
bool CSE_CircularBuffer:: isFull() {
  // Calculate the next position for the head when it wraps around
  size_t nextHead = (head + 1) % maxlen;

  // Check if the next position for the head is equal to the tail
  if (nextHead == tail) {
    return true; // The buffer is full
  }
  
  return false; // The buffer is not full
}

//==========================================================================================//
/**
 * @brief Checks if the circular buffer is empty.
 * 
 * @return true Buffer is empty.
 * @return false Buffer is not empty.
 */
bool CSE_CircularBuffer:: isEmpty() {
  if (head == tail) {  // if the head == tail, we don't have any data
    // head = 0;
    // tail = 0;
    return true;
  }
  return false;
}

//==========================================================================================//
/**
 * @brief Returns the number of bytes occupied in the circular buffer.
 * 
 * @return int The number of bytes.
 */
int CSE_CircularBuffer:: getOccupiedLength() {
  if (head >= tail) {
    return (head - tail);
  }
  else {
    return (maxlen - (tail - head));
  }
}

//==========================================================================================//
/**
 * @brief Returns the number of bytes vacant in the circular buffer.
 * 
 * @return int The number of free bytes.
 */
int CSE_CircularBuffer:: getVacantLength() {
  return (maxlen - 1) - getOccupiedLength();
}

//==========================================================================================//
/**
 * @brief Pushes a single byte to the head end of the buffer. If the buffer is full, the oldest
 * byte (at the tail end) is discarded if discardOld is set to true. If discardOld is set to
 * false, the data is not pushed and the function returns -1.
 * 
 * @param data The data to be pushed.
 * @return int 0 if successful; -1 if unsuccessful.
 */
int CSE_CircularBuffer:: push (uint8_t data) {
  int next;

  next = head + 1;  // next is where head will point to after this write.
  
  if (next >= maxlen) {
    next = 0;
  }

  if (next == tail) {  // if the head + 1 == tail, circular buffer is full
    if (discardOld) {
      tail = (tail + 1) % maxlen;  // discard the oldest byte
    }
    else {
      return -1;
    }
  }

  buffer [head] = data;  // Load data
  head = next;  // and then move head to next data offset.
  return 0;  // return success to indicate successful push.
}

//==========================================================================================//
/**
 * @brief Pushes a byte array to the bufer. If the byteOrder is 0, the data is pushed in the
 * same order as in the array, with index [0] being the first byte. If the byteOrder is 1,
 * the data is pushed in reverse order, with index [0] being the last byte.
 * 
 * @param data A byte buffer.
 * @param length Number of bytes in the buffer. Can be less than the actual length of the buffer.
 * @param byteOrder The order of the bytes in the buffer. 0 for same order, 1 for reverse order.
 * @return int The number of bytes pushed.
 */
int CSE_CircularBuffer:: push (uint8_t* data, int length, int byteOrder) {
  int i;

  for (i = 0; i < length; i++) {
    if (byteOrder == 0) {
      if (push (data [i]) != 0) {
        break;  // Break when there is no more space
      }
    } else {
      if (push (data [length - i - 1]) != 0) {
        break;  // Break when there is no more space
      }
    }
  }

  return i; // Return the number of bytes pushed
}

//==========================================================================================//
/**
 * @brief Pops a single byte from the tail end of the circular buffer. Returns -1 if the
 * buffer is empty. Or returns 0 if successful.
 * 
 * @param data The destination byte.
 * @return int 0 if successful; -1 if unsuccessful.
 */
int CSE_CircularBuffer:: pop (uint8_t* data) {
  int next;

  if (isEmpty()) {  // If no data
    return -1;
  }

  next = tail + 1;  // next is where tail will point to after this read.
  if (next >= maxlen) {
    next = 0;
  }

  *data = buffer [tail];  // Read data
  tail = next;  // and then move the tail to next offset.
  return 0;  // return success to indicate successful pop.
}

//==========================================================================================//
/**
 * @brief Pops a range of data from the circular buffer and returns the number of bytes popped.
 * If there is not enough data in the circular buffer, the function returns the number of
 * bytes popped before the buffer became empty.
 * 
 * @param data The destination byte array.
 * @param length The number of bytes to pop.
 * @return int -1 if buffer is empty; number of bytes popped if successful.
 */
int CSE_CircularBuffer:: pop (uint8_t* data, int length) {
  int next;
  int i;

  if (isEmpty()) { // If no data
    return -1;
  }

  for (i = 0; i < length; i++) {
    if (pop (&data [i]) != 0) {
      break;  // Break when there is no more data
    }
  }

  return i; // Return the number of bytes popped
}

//==========================================================================================//
/**
 * @brief This copies the data from the circular buffer to a linear buffer specified by
 * user. This operation doesn't pop the data from the circular buffer. The target buffer
 * must have enough space to hold the data. The length is optional and if set to 0, the entire
 * circular buffer is copied up to maxlen. If the data in the circular buffer is less than
 * maxlen, then empty data is set to 0 in the target buffer. byteOrder is also optional and
 * determines the order of the data in the target buffer. If set to 0, the data is copied
 * in the same order as in the circular buffer. If set to 1, the data is copied in reverse
 * order. This function returns the number of bytes copied (excluding the empty data).
 * 
 * @param data The destination byte array.
 * @param length The number of bytes to copy. If set to 0, the entire circular buffer is copied.
 * @param byteOrder The order of the bytes in the buffer. 0 for same order, 1 for reverse order.
 * @return int The number of bytes copied.
 */
int CSE_CircularBuffer:: bufferCopy (uint8_t* data, int length, int byteOrder) {
  int i;
  int j;
  int k;
  bool toPad = false; // To pad the empty data with 0s

  if (length == 0) {  // If length is 0, copy the entire buffer, with padded 0s
    length = maxlen;
    toPad = true;
  }

  if (byteOrder == 0) { // Copy in the same order (FIFO)
    for (i = 0, j = tail; i < length; i++, j++) {
      if (j >= maxlen) {
        j = 0;
      }
      data [i] = buffer [j];
    }
  }
  else { // Copy in reverse order (LIFO)
    for (i = 0, j = (tail + length - 1); i < length; i++, j--) {
      if (j < 0) {
        j = maxlen - 1;
      }
      data [i] = buffer [j];
    }
  }

  // Padd the remaining data with 0s.
  if (toPad) {
    for (k = i; k < maxlen; k++) {
      data [k] = 0;
    }
  }

  return i;
}

//==========================================================================================//
/**
 * @brief Clears the circular buffer by setting the head and tail to 0. The number of bytes
 * currently in the circular buffer is returned.
 * 
 * @return int The number of bytes present in the buffer before clearing.
 */
int CSE_CircularBuffer:: clear() {
  int length = getOccupiedLength();
  head = 0;
  tail = 0;
  return length;
}

//==========================================================================================//
/**
 * @brief Peeks the circular buffer by reading a single byte without popping it from the
 * circular buffer.
 * 
 * @param data The destination byte.
 * @return int 0 if successful; -1 if unsuccessful.
 */
int CSE_CircularBuffer:: peek (uint8_t* data) {
  if (head == tail) {  // if the head == tail, we don't have any data
    return -1;
  }

  *data = buffer [tail];  // Read data
  return 0;  // return success to indicate successful peek.
}

//==========================================================================================//
