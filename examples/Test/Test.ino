
//==========================================================================================//
/**
 * @file Test.ino
 * @author Vishnu Mohanan (@vishnumaiea, @vizmohanan)
 * @maintainer CIRCUITSTATE Electronics (@circuitstate)
 * @brief Test file for the CSE_CircularBuffer Arduino library.
 * @version 0.0.2
 * @date Last Modified: +05:30 20:59:07 PM 19-05-2024, Sunday
 * @license MIT
 * @mainpage https://github.com/CIRCUITSTATE/CSE_CircularBuffer
 */
//==========================================================================================//

#include <Arduino.h>
#include <CSE_CircularBuffer.h>

typedef int CSE_Data_t;

//==========================================================================================//

CSE_Data_t dataItem = 0;
CSE_Data_t printBuffer [10] = {0};

CSE_CircularBuffer <CSE_Data_t> cBuffer (10);  // Create a circular buffer object with the data buffer and length.

//==========================================================================================//

void printCircBuffer();
void printCircBufferStats();

void test_ClearAndFillRandom();
void test_ClearAndFillSequential();
void test_PopEach();
void test_PopAll();
void test_PopPart();
void test_CopyAll();
void test_CopyPart();
void test_PeekAndPop();
void test_PushOneEach();

void setup();
void loop();

//==========================================================================================//
/**
 * @brief Fills the circular buffer with random data and prints it. Use this to verify
 * that the circular buffer is working properly.
 * 
 */
void test_ClearAndFillRandom() {
  Serial.println();
  Serial.println ("clearAndFillRandom(): Filling circular buffer with random data..");
  // Serial.println();

  cBuffer.clear();  // Clear the circular buffer.

  // Fill it with random data.
  while (!cBuffer.isFull()) {
    CSE_Data_t randomData = (CSE_Data_t) random (-255, 255);  // Get a random number between 0 and 255.
    cBuffer.push (randomData);  // Push the random number to the circular buffer.
    // Serial.print ("Data: " + String (randomData) + ", Filled: " + String (cBuffer.getOccupiedLength()) + ", Free: " + String (cBuffer.getVacantLength()));  // Print the data to the serial port.
    // Serial.println (", Head: " + String (cBuffer.getHead()) + ", Tail: " + String (cBuffer.getTail()));  // Print the head and tail to the serial port.
    // delay (100);
  }

  printCircBuffer();
  // Serial.println();
}

//==========================================================================================//
/**
 * @brief Fills the circular buffer with sequential data and prints it. Use this to verify
 * that the circular buffer is working properly.
 * 
 */
void test_ClearAndFillSequential() {
  Serial.println();
  Serial.println ("clearAndFillSequential(): Filling circular buffer with sequential data..");
  // Serial.println();

  cBuffer.clear();  // Clear the circular buffer.
  uint8_t fillData = 10;

  while (!cBuffer.isFull()) {
    cBuffer.push (fillData);  // Push the random number to the circular buffer.
    fillData++;
    // Serial.print ("Data: " + String (randomData) + ", Filled: " + String (cBuffer.getOccupiedLength()) + ", Free: " + String (cBuffer.getVacantLength()));  // Print the data to the serial port.
    // Serial.println (", Head: " + String (cBuffer.getHead()) + ", Tail: " + String (cBuffer.getTail()));  // Print the head and tail to the serial port.
    // delay (100);
  }

  printCircBuffer();
  Serial.println();
}

//==========================================================================================//
/**
 * @brief Prints the circular buffer contents to the serial port.
 * 
 */
void printCircBuffer() {  
  Serial.print ("printCircBuffer(): ");
  int copyCount = cBuffer.bufferCopy (printBuffer, cBuffer.getOccupiedLength());

  Serial.print ("[" + String (copyCount) + "] ");

  for (int i = 0; i < copyCount; i++) {
    Serial.printf ("%d ", printBuffer [i]);  // Print the data to the serial port.
  }

  Serial.println();  // Print a new line.
  // printCircBufferStats();
}

//==========================================================================================//
/**
 * @brief Prints the circular buffer contents by popping one value at a time. This can
 * verify if the popping function is working properly.
 * 
 */
void test_PopEach() {
  Serial.println ("popEach(): Printing the circular buffer by popping individually..");

  while (!cBuffer.isEmpty()) {
    int popError = cBuffer.pop (&dataItem);  // Pop a single byte from the circular buffer.
    Serial.printf ("%d ", dataItem);  // Print the data to the serial port.
  }
  Serial.println();  // Print a new line.
  printCircBufferStats();
}

//==========================================================================================//
/**
 * @brief Prints the circular buffer contents by popping all values at once. This can
 * verify if the popping function is working properly.
 * 
 */
void test_PopAll() {
  Serial.println ("popAll(): Printing the circular buffer by popping all..");
  
  int popCount = cBuffer.pop (printBuffer, cBuffer.getOccupiedLength());

  for (int i = 0; i < popCount; i++) {
    Serial.printf ("%d ", printBuffer [i]);  // Print the data to the serial port.
  }

  Serial.println();  // Print a new line.
  printCircBufferStats();
}

//==========================================================================================//
/**
 * @brief Prints partial circular buffer content by popping a number of bytes at a time.
 * 
 */
void test_PopPart() {
  Serial.println ("popPart(): Printing the circular buffer by popping some..");
  
  int popCount = cBuffer.pop (printBuffer, 5);

  for (int i = 0; i < popCount; i++) {
    Serial.printf ("%d ", printBuffer [i]);  // Print the data to the serial port.
  }

  Serial.println();  // Print a new line.
  printCircBufferStats();
}

//==========================================================================================//
/**
 * @brief Prints the contents of the circular buffer by copying all data to a new buffer.
 * 
 */
void test_CopyAll() {
  Serial.println ("copyAll(): Printing the circular buffer by copying..");
  
  int copyCount = cBuffer.bufferCopy (printBuffer, cBuffer.getOccupiedLength());

  for (int i = 0; i < copyCount; i++) {
    Serial.printf ("%d ", printBuffer [i]);  // Print the data to the serial port.
  }

  Serial.println();  // Print a new line.
  printCircBufferStats();
}

//==========================================================================================//
/**
 * @brief Prints partial circular buffer content by copying a number of bytes at a time.
 * 
 */
void test_CopyPart() {
  Serial.println ("copyPart(): Printing the circular buffer by copying part of it..");
  
  int copyCount = cBuffer.bufferCopy (printBuffer, 5);

  for (int i = 0; i < copyCount; i++) {
    Serial.printf ("%d ", printBuffer [i]);  // Print the data to the serial port.
  }

  Serial.println();  // Print a new line.
  printCircBufferStats();
}

//==========================================================================================//
/**
 * @brief Prints the contents of the circular buffer by peeking and popping one value at a time.
 * 
 */
void test_PeekAndPop() {
  Serial.println ("peekAndPop(): Printing the circular buffer by peeking and popping..");
  
  int bytesToRead = cBuffer.getOccupiedLength();

  for (int i = 0; i < bytesToRead; i++) {
    cBuffer.peek (&dataItem);
    printBuffer [i] = dataItem;
    cBuffer.pop (&dataItem);
  }

  for (int i = 0; i < bytesToRead; i++) {
    Serial.printf ("%d ", printBuffer [i]);  // Print the data to the serial port.
  }

  Serial.println();  // Print a new line.
  printCircBufferStats();
}

//==========================================================================================//
/**
 * @brief Pushes a random value to the circular buffer and prints the details.
 * 
 */
void test_PushOneEach() {
  Serial.println ("pushOneEach(): Pushing a random value to the circular buffer..");
  cBuffer.discardOld = true;

  uint8_t randomData = (uint8_t) random (0, 255);  // Get a random number between 0 and 255.
  cBuffer.push (randomData);  // Push the random number to the circular buffer.
  Serial.print ("Value: " + String (randomData) + ", Filled: " + String (cBuffer.getOccupiedLength()) + ", Free: " + String (cBuffer.getVacantLength()));  // Print the data to the serial port.
  Serial.println (", Head: " + String (cBuffer.getHead()) + ", Tail: " + String (cBuffer.getTail()));  // Print the head and tail to the serial port.

  int copyCount = cBuffer.bufferCopy (printBuffer, cBuffer.getOccupiedLength());

  Serial.print ("Data: T-[");
  for (int i = 0; i < copyCount; i++) {
    Serial.printf ("%d ", printBuffer [i]);  // Print the data to the serial port.
  }

  Serial.println("]-H");
  Serial.println();  // Print a new line.
  // printCircBufferStats();
}

//==========================================================================================//
/**
 * @brief Prints the stats of the circular buffer.
 * 
 */
void printCircBufferStats() {
  Serial.print ("printCircBufferStats(): ");
  Serial.print ("Filled: " + String (cBuffer.getOccupiedLength()) + ", Free: " + String (cBuffer.getVacantLength()));  // Print the data to the serial port
  Serial.println (", Head: " + String (cBuffer.getHead()) + ", Tail: " + String (cBuffer.getTail()));
  // Serial.println();
}

//==========================================================================================//

void setup() {
  Serial.begin (115200);
  delay (1000);
}

//==========================================================================================//

void loop() {
  cBuffer.discardOld = true;

  test_ClearAndFillRandom();

  // test_PopEach();
  // test_PopAll();
  // test_PopPart();

  // test_CopyAll();
  // test_CopyPart();
  // cBuffer.clear();

  // cBuffer.peek (&dataItem);
  // Serial.println ("Peeked: " + String (dataItem));
  // cBuffer.clear();

  // test_PeekAndPop();
  test_PushOneEach();

  delay (1000);
}

//==========================================================================================//
