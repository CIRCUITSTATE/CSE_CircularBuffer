
# CSE_CircularBuffer

**CSE_CircularBuffer** is a simple circular buffer library from [*CIRCUITSTATE Electronics*](https://www.circuitstate.com/) for the Arduino platform. It supports multiple data types and has most of the methods you will need.

## Example

The following example shows how to read values through an ADC pin and store them in a circular buffer to find the average. This example uses the [**CSE_MillisTimer**](https://github.com/CIRCUITSTATE/CSE_MillisTimer) library for timing.

```cpp
#include <CSE_CircularBuffer.hpp>
#include <CSE_MillisTimer.h>  // Requires the timer library

#define  ADC_PIN   A0

CSE_CircularBuffer <int> cbuffer (100);
CSE_MillisTimer printTimer (500);

void setup() {
  Serial.begin (115200);
  pinMode (ADC_PIN, INPUT);
  printTimer.start();
}

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
```

## Documentation

Please see the [API.md](/docs/API.md) file for the documentation.

## References

- [CircularBuffer - Another circular buffer library for Arduino](https://github.com/rlogiacco/CircularBuffer) - GitHub
