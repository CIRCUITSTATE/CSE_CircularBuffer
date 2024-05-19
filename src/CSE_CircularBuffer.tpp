
//==========================================================================================//
/**
 * @file CSE_CircularBuffer.cpp
 * @author Vishnu Mohanan (@vishnumaiea, @vizmohanan)
 * @maintainer CIRCUITSTATE Electronics (@circuitstate)
 * @brief Main source file for the CSE_CircularBuffer Arduino library.
 * @version 0.0.2
 * @date Last Modified: +05:30 21:47:05 PM 19-05-2024, Sunday
 * @license MIT
 * @mainpage https://github.com/CIRCUITSTATE/CSE_CircularBuffer
 */
//==========================================================================================//

// #include "CSE_CircularBuffer.hpp"

//==========================================================================================//
/**
 * @brief Creates a new circular buffer with user-defined buffer. The length should be the
 * length of the actual buffer. The actual usable length is length - 1. For example, if you
 * want 32 items for the data you must create a buffer with a capacity of 33 and send 33 as the
 * length parameter.
 * 
 * The data size will be determined by the data type you set. For byte buffer, use uint8_t.
 * 
 * Old values in the buffer are not discarded by default.
 * 
 * @param buffer A pointer to the buffer.
 * @param length The length of the buffer in data size.
 * @return CSE_CircularBuffer:: 
 */
template <typename CSE_CB_t>
CSE_CircularBuffer <CSE_CB_t> :: CSE_CircularBuffer (CSE_CB_t* buffer, int length) {
  this->buffer = buffer;
  maxlen = (length - 1);  // Usable length is length - 1
  head = 0;
  tail = 0;
  discardOld = false;
}

//==========================================================================================//
/**
 * @brief Creates a new circular buffer with a dynamically allocated buffer. The length is
 * the number of usable data items. So the function allocates length + 1 for the buffer.
 * 
 * Old values in the buffer are not discarded by default.
 * 
 * @param length The number of usable data items.
 * @return CSE_CircularBuffer:: 
 */
template <typename CSE_CB_t>
CSE_CircularBuffer <CSE_CB_t> :: CSE_CircularBuffer (int length) {
  buffer = (CSE_CB_t*) malloc (sizeof (CSE_CB_t) * (length + 1)); // Need one extra location
  
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
template <typename CSE_CB_t>
CSE_CircularBuffer <CSE_CB_t> :: ~CSE_CircularBuffer() {
  free (buffer);
}

//==========================================================================================//
/**
 * @brief Returns the head position of the circular buffer. Head position is where new data is
 * pushed to.
 * 
 * @return int The head position.
 */
template <typename CSE_CB_t>
int CSE_CircularBuffer <CSE_CB_t> :: getHead() {
  return head;
}

//==========================================================================================//
/**
 * @brief Returns the tail position of the circular buffer. Tail position is where data is
 * popped from.
 * 
 * @return int The tail position.
 */
template <typename CSE_CB_t>
int CSE_CircularBuffer <CSE_CB_t> :: getTail() {
  return tail;
}

//==========================================================================================//
/**
 * @brief Returns the capacity of the circular buffer. With user-defined buffer, this is the
 * length of the buffer - 1. With dynamically allocated buffer, this is the total length of the
 * buffer including the extra location.
 * 
 * @return int The capacity of the circular buffer in data count.
 */
template <typename CSE_CB_t>
int CSE_CircularBuffer <CSE_CB_t> :: getCapacity() {
  return maxlen;
}

//==========================================================================================//
/**
 * @brief Checks if the circular buffer is full.
 * 
 * @return true Circular buffer is full.
 * @return false Circular buffer is not full.
 */
template <typename CSE_CB_t>
bool CSE_CircularBuffer <CSE_CB_t> :: isFull() {
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
template <typename CSE_CB_t>
bool CSE_CircularBuffer <CSE_CB_t> :: isEmpty() {
  if (head == tail) {  // if the head == tail, we don't have any data
    // head = 0;
    // tail = 0;
    return true;  // Buffer is empty
  }
  return false; // Buffer is not empty
}

//==========================================================================================//
/**
 * @brief Returns the number of data occupied in the circular buffer.
 * 
 * @return int The number of data.
 */
template <typename CSE_CB_t>
int CSE_CircularBuffer <CSE_CB_t> :: getOccupiedLength() {
  if (head >= tail) {
    return (head - tail);
  }
  else {
    return (maxlen - (tail - head));
  }
}

//==========================================================================================//
/**
 * @brief Returns the number of locations vacant in the circular buffer.
 * 
 * @return int The number of free locations.
 */
template <typename CSE_CB_t>
int CSE_CircularBuffer <CSE_CB_t> :: getVacantLength() {
  return (maxlen - 1) - getOccupiedLength();
}

//==========================================================================================//
/**
 * @brief Pushes a single data to the head end of the buffer. If the buffer is full, the oldest
 * byte (at the tail end) is discarded if `discardOld` is set to `true`. If `discardOld` is set to
 * `false`, the data is not pushed and the function returns -1.
 * 
 * @param data The data to be pushed of type CSE_CB_t.
 * @return int 0 if successful; -1 if otherwise.
 */
template <typename CSE_CB_t>
int CSE_CircularBuffer <CSE_CB_t> :: push (CSE_CB_t data) {
  int next;

  next = head + 1;  // Next is where head will point to after this write.
  
  if (next >= maxlen) {
    next = 0;
  }

  if (next == tail) {  // If the head + 1 == tail, circular buffer is full
    if (discardOld) {
      tail = (tail + 1) % maxlen;  // Discard the oldest data
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
 * @brief Pushes a data array to the buffer. If the dataOrder is 0, the data is pushed in the
 * same order as in the array, with index [0] being the first data. If the dataOrder is 1,
 * the data is pushed in reverse order, with index [0] being the last data.
 * 
 * @param data A data buffer of CSE_CB_t.
 * @param length Number of data in the buffer. Can be less than the actual length of the buffer.
 * @param dataOrder The order of the data in the buffer. 0 for same order, 1 for reverse order.
 * @return int The number of data items pushed.
 */
template <typename CSE_CB_t>
int CSE_CircularBuffer <CSE_CB_t> :: push (CSE_CB_t* data, int length, int dataOrder) {
  int i;

  for (i = 0; i < length; i++) {
    if (dataOrder == 0) {
      if (push (data [i]) != 0) {
        break;  // Break when there is no more space
      }
    } else {
      if (push (data [length - i - 1]) != 0) {
        break;  // Break when there is no more space
      }
    }
  }

  return i; // Return the number of data items pushed
}

//==========================================================================================//
/**
 * @brief Pops a single data from the tail end of the circular buffer. Returns -1 if the
 * buffer is empty, or 0 if successful.
 * 
 * @param data The destination data of type CSE_CB_t.
 * @return int 0 if successful; -1 if unsuccessful.
 */
template <typename CSE_CB_t>
int CSE_CircularBuffer <CSE_CB_t> :: pop (CSE_CB_t* data) {
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
 * @brief Pops a range of data from the circular buffer and returns the number of data popped.
 * If there is not enough data in the circular buffer, the function returns the number of
 * data popped before the buffer became empty.
 * 
 * @param data The destination data array of type CSE_CB_t.
 * @param length The number of data items to pop.
 * @return int -1 if the buffer is empty; number of data popped if successful.
 */
template <typename CSE_CB_t>
int CSE_CircularBuffer <CSE_CB_t> :: pop (CSE_CB_t* data, int length) {
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

  return i; // Return the number of data popped
}

//==========================================================================================//
/**
 * @brief This copies the data from the circular buffer to a linear buffer specified by
 * user. This operation doesn't pop the data from the circular buffer. The target buffer
 * must have enough space to hold the data. The length is optional and if set to 0, the entire
 * circular buffer is copied up to maxlen. If the data in the circular buffer is less than
 * maxlen, then empty data is set to 0 in the target buffer. dataOrder is also optional and
 * determines the order of the data in the target buffer. If set to 0, the data is copied
 * in the same order as in the circular buffer. If set to 1, the data is copied in reverse
 * order. This function returns the number of data items copied (excluding the empty data).
 * 
 * @param data The destination data array of type CSE_CB_t.
 * @param length The number of data items to copy. If set to 0, the entire circular buffer is copied.
 * @param dataOrder The order of the data in the buffer. 0 for same order, 1 for reverse order.
 * @return int The number of data copied.
 */
template <typename CSE_CB_t>
int CSE_CircularBuffer <CSE_CB_t> :: bufferCopy (CSE_CB_t* data, int length, int dataOrder) {
  int i;
  int j;
  int k;
  bool toPad = false; // To pad the empty data with 0s

  if (length == 0) {  // If length is 0, copy the entire buffer, with padded 0s
    length = maxlen;
    toPad = true;
  }

  if (dataOrder == 0) { // Copy in the same order (FIFO)
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
 * @brief Clears the circular buffer by setting the head and tail to 0. The number of data
 * currently in the circular buffer is returned.
 * 
 * @return int The number of data present in the buffer before clearing.
 */
template <typename CSE_CB_t>
int CSE_CircularBuffer <CSE_CB_t> :: clear() {
  int length = getOccupiedLength();
  head = 0;
  tail = 0;
  return length;
}

//==========================================================================================//
/**
 * @brief Peeks the circular buffer by reading a single data without popping it from the
 * circular buffer.
 * 
 * @param data The destination data of type CSE_CB_t.
 * @return int 0 if successful; -1 if unsuccessful.
 */
template <typename CSE_CB_t>
int CSE_CircularBuffer <CSE_CB_t> :: peek (CSE_CB_t* data) {
  if (head == tail) {  // If the head == tail, we don't have any data
    return -1;
  }

  *data = buffer [tail];  // Read data
  return 0;  // Return success to indicate successful peek.
}

//==========================================================================================//
