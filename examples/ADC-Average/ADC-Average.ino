
//=================================================================================//
/**
 * @file ADC-Average.ino
 * @author Vishnu Mohanan (@vishnumaiea, @vizmohanan)
 * @maintainer CIRCUITSTATE Electronics (@circuitstate)
 * @brief Reads 100 samples from the an ADC pin and prints the average every 500ms.
 * @version 0.0.2
 * @date Last Modified: +05:30 18:10:41 PM 19-05-2024, Sunday
 * @license MIT
 * @mainpage https://github.com/CIRCUITSTATE/CSE_CircularBuffer
 */
//=================================================================================//

#include <CSE_CircularBuffer.hpp>
#include <CSE_MillisTimer.h>  // Requires the timer library

//=================================================================================//

#define  ADC_PIN   A0

//=================================================================================//

CSE_CircularBuffer <int> cbuffer (100);
CSE_MillisTimer printTimer (500);

//=================================================================================//

void setup() {
  Serial.begin (115200);
  pinMode (ADC_PIN, INPUT);
  printTimer.start();
}

//=================================================================================//

void loop() {
  int reading = analogRead (ADC_PIN); // Read the analog pin
  cbuffer.push (reading); // Push the reading to the circular buffer

  if (printTimer.isElapsed()) {  // Print every 500 ms
    int readingSum = 0;  // The sum of all readings
    int sampleCount = cbuffer.getOccupiedLength();  // The number of readings

    for (int i = 0; i < sampleCount; i++) { // Calculate the sum of all readings
      int value = 0;
      cbuffer.pop (&value);  // Pop the reading
      readingSum += value;  // Add the reading to the sum
    }

    float average = (float) readingSum / sampleCount;  // Calculate the average

    Serial.print ("Average is ");
    Serial.println (average);

    printTimer.start(); // Reset the timer
  }
}

//=================================================================================//
