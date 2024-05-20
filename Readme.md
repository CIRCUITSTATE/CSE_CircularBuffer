
# CSE_CircularBuffer

**CSE_CircularBuffer** is a simple circular buffer library from [*CIRCUITSTATE Electronics*](https://www.circuitstate.com/) for the Arduino platform. It supports multiple data types and has most of the methods you will need.

## Installation

This library is available from the official **Arduino Library Manager**. Open the Arduino IDE, search for "CSE_CircularBuffer" and install the latest version of the library.

Additionally, you can download the latest release package from the GitHub repository and install it manually. To do so, open the Arduino IDE, go to *Sketch > Include Library > Add .ZIP Library* and select the downloaded file.

Another method is to clone the GitHub repository directly into your `libraries` folder. The development branch will have the latest features, bug fixes and other changes. To do so, navigate to your `libraries` folder (usually located at *Documents/Arduino/libraries* on Windows and *~/Documents/Arduino/libraries* on macOS) and execute the following command:

```
git clone https://github.com/CIRCUITSTATE/CSE_CircularBuffer.git
```

## Example

The following example shows how to read values through an ADC pin and store them in a circular buffer to find the average. This example uses the [**CSE_MillisTimer**](https://github.com/CIRCUITSTATE/CSE_MillisTimer) library for timing.

```cpp
#include <CSE_CircularBuffer.hpp>
#include <CSE_MillisTimer.h>  // Requires the timer library

#define  ADC_PIN   A0

CSE_CircularBuffer <int> cbuffer (100); // Create a buffer with capacity of 100
CSE_MillisTimer printTimer (500); // Create a timer with a 500 ms interval

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

## API Reference

Please see the [API.md](/docs/API.md) file for the API reference.

## References

- [CircularBuffer - Another circular buffer library for Arduino](https://github.com/rlogiacco/CircularBuffer) - GitHub
