
![CSE_CircularBuffer](https://socialify.git.ci/CIRCUITSTATE/CSE_CircularBuffer/image?description=1&font=KoHo&forks=1&issues=1&logo=https%3A%2F%2Fwww.circuitstate.com%2Fwp-content%2Fuploads%2F2024%2F05%2FCIRCUITSTATE-R-Emblem-20052024-2.svg&name=1&pattern=Circuit%20Board&pulls=1&stargazers=1&theme=Auto)

# CSE_CircularBuffer

**CSE_CircularBuffer** is a simple circular buffer library from [*CIRCUITSTATE Electronics*](https://www.circuitstate.com/) for the Arduino platform. It supports multiple data types and has most of the methods you will need.

## Installation

This library is available from the official **Arduino Library Manager**. Open the Arduino IDE, search for "CSE_CircularBuffer" and install the latest version of the library.

Additionally, you can download the latest release package from the GitHub repository and install it manually. To do so, open the Arduino IDE, go to `Sketch > Include Library > Add .ZIP Library…` and select the downloaded file.

Another method is to clone the GitHub repository directly into your `libraries` folder. The development branch will have the latest features, bug fixes and other changes. To do so, navigate to your `libraries` folder (usually located at `Documents/Arduino/libraries` on Windows and `~/Documents/Arduino/libraries` on macOS) and execute the following command:

```
git clone https://github.com/CIRCUITSTATE/CSE_CircularBuffer.git
```

[**Git**](https://git-scm.com) should be installed on your computer.

The library can also be installed via [**PlatformIO**](https://platformio.org). All officially listed Arduino listed libraries are automatically fetched by PlatformIO. Use the [`lib_deps`](https://docs.platformio.org/en/latest/projectconf/sections/env/options/library/lib_deps.html) search option to install the library.

## Dependencies

This library does not have any external dependencies apart from the standard Arduino libraries.

## Example

- [**ADC-Average**](/examples/ADC-Average/) - This example shows how to read values through an ADC pin and store them in a circular buffer to find the average. This example uses the [**CSE_MillisTimer**](https://github.com/CIRCUITSTATE/CSE_MillisTimer) library for timing.


## API Documentation

Please see the [API.md](/docs/API.md) file for the API reference.

## References

- [CircularBuffer - Another circular buffer library for Arduino](https://github.com/rlogiacco/CircularBuffer) - GitHub
