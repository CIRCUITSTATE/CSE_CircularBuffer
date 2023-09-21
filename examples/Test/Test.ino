
//==========================================================================================//

#include <Arduino.h>
#include <CSE_CircBuffer.h>

//==========================================================================================//

uint8_t dataByte = 0;
uint8_t printBuffer [10] = {0};

CSE_CircBuffer cBuffer (10);  // Create a circular buffer object with the data buffer and length.

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

void test_ClearAndFillRandom() {
  Serial.println();
  Serial.println ("Filling circular buffer with random data..");
  // Serial.println();

  cBuffer.clear();  // Clear the circular buffer.

  // Fill it with random data.
  while (!cBuffer.isFull()) {
    uint8_t randomData = (uint8_t) random (0, 255);  // Get a random number between 0 and 255.
    cBuffer.push (randomData);  // Push the random number to the circular buffer.
    // Serial.print ("Data: " + String (randomData) + ", Filled: " + String (cBuffer.getOccupiedLength()) + ", Free: " + String (cBuffer.getVacantLength()));  // Print the data to the serial port.
    // Serial.println (", Head: " + String (cBuffer.getHead()) + ", Tail: " + String (cBuffer.getTail()));  // Print the head and tail to the serial port.
    // delay (100);
  }

  printCircBuffer();
  Serial.println();
}

//==========================================================================================//

void test_ClearAndFillSequential() {
  Serial.println();
  Serial.println ("Filling circular buffer with sequential data..");
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

void printCircBuffer() {  
  int copyCount = cBuffer.bufferCopy (printBuffer, cBuffer.getOccupiedLength());

  Serial.print ("[" + String (copyCount) + "] ");

  for (int i = 0; i < copyCount; i++) {
    Serial.printf ("%d ", printBuffer [i]);  // Print the data to the serial port.
  }

  Serial.println();  // Print a new line.
  // printCircBufferStats();
}

//==========================================================================================//

void test_PopEach() {
  Serial.println ("Printing the circular buffer by popping individually..");

  while (!cBuffer.isEmpty()) {
    int popError = cBuffer.pop (&dataByte);  // Pop a single byte from the circular buffer.
    Serial.printf ("%d ", dataByte);  // Print the data to the serial port.
  }
  Serial.println();  // Print a new line.
  printCircBufferStats();
}

//==========================================================================================//

void test_PopAll() {
  Serial.println ("Printing the circular buffer by popping all..");
  
  int popCount = cBuffer.pop (printBuffer, cBuffer.getOccupiedLength());

  for (int i = 0; i < popCount; i++) {
    Serial.printf ("%d ", printBuffer [i]);  // Print the data to the serial port.
  }

  Serial.println();  // Print a new line.
  printCircBufferStats();
}

//==========================================================================================//

void test_PopPart() {
  Serial.println ("Printing the circular buffer by popping some..");
  
  int popCount = cBuffer.pop (printBuffer, 5);

  for (int i = 0; i < popCount; i++) {
    Serial.printf ("%d ", printBuffer [i]);  // Print the data to the serial port.
  }

  Serial.println();  // Print a new line.
  printCircBufferStats();
}

//==========================================================================================//

void test_CopyAll() {
  Serial.println ("Printing the circular buffer by copying..");
  
  int copyCount = cBuffer.bufferCopy (printBuffer, cBuffer.getOccupiedLength());

  for (int i = 0; i < copyCount; i++) {
    Serial.printf ("%d ", printBuffer [i]);  // Print the data to the serial port.
  }

  Serial.println();  // Print a new line.
  printCircBufferStats();
}

//==========================================================================================//

void test_CopyPart() {
  Serial.println ("Printing the circular buffer by copying part of it..");
  
  int copyCount = cBuffer.bufferCopy (printBuffer, 5);

  for (int i = 0; i < copyCount; i++) {
    Serial.printf ("%d ", printBuffer [i]);  // Print the data to the serial port.
  }

  Serial.println();  // Print a new line.
  printCircBufferStats();
}

//==========================================================================================//

void test_PeekAndPop() {
  Serial.println ("Printing the circular buffer by peeking and popping..");
  
  int bytesToRead = cBuffer.getOccupiedLength();

  for (int i = 0; i < bytesToRead; i++) {
    cBuffer.peek (&dataByte);
    printBuffer [i] = dataByte;
    cBuffer.pop (&dataByte);
  }

  for (int i = 0; i < bytesToRead; i++) {
    Serial.printf ("%d ", printBuffer [i]);  // Print the data to the serial port.
  }

  Serial.println();  // Print a new line.
  printCircBufferStats();
}

//==========================================================================================//

void test_PushOneEach() {
  cBuffer.discardOld = true;

  uint8_t randomData = (uint8_t) random (0, 255);  // Get a random number between 0 and 255.
  cBuffer.push (randomData);  // Push the random number to the circular buffer.
  Serial.print ("Data: " + String (randomData) + ", Filled: " + String (cBuffer.getOccupiedLength()) + ", Free: " + String (cBuffer.getVacantLength()));  // Print the data to the serial port.
  Serial.println (", Head: " + String (cBuffer.getHead()) + ", Tail: " + String (cBuffer.getTail()));  // Print the head and tail to the serial port.

  int copyCount = cBuffer.bufferCopy (printBuffer, cBuffer.getOccupiedLength());

  for (int i = 0; i < copyCount; i++) {
    Serial.printf ("%d ", printBuffer [i]);  // Print the data to the serial port.
  }

  Serial.println();  // Print a new line.
  printCircBufferStats();
}

//==========================================================================================//

void printCircBufferStats() {
  Serial.print ("Filled: " + String (cBuffer.getOccupiedLength()) + ", Free: " + String (cBuffer.getVacantLength()));  // Print the data to the serial port
  Serial.println (", Head: " + String (cBuffer.getHead()) + ", Tail: " + String (cBuffer.getTail()));
  Serial.println();
}

//==========================================================================================//

void setup() {
  Serial.begin (115200);
  delay (1000);
}

//==========================================================================================//

void loop() {
  cBuffer.discardOld = true;
  fillCircBuffer();
  printCircBuffer();

  // printCircBuffer_popEach();
  // printCircBuffer_popAll();
  // printCircBuffer_popSome();

  // printCircbuffer_copyAll();
  // printCircbuffer_copySome();
  // cBuffer.clear();

  // cBuffer.peek (&dataByte);
  // Serial.println ("Peeked: " + String (dataByte));
  // cBuffer.clear();

  // printCircBuffer_peekAll();

  // pushOneEach();

  delay (1000);
}

//==========================================================================================//
