# Bombs Light Clock with FFT and Wi-Fi

## Overview

The **Bombs Light Clock with FFT and Wi-Fi** is an innovative project that combines real-time clock functionality with sound detection using **Fast Fourier Transform (FFT)** to trigger visual alarm notifications. The device utilizes a **NeoPixel LED strip** to display time, with additional features to detect alarm signals over Wi-Fi from an external API. This system helps ensure users are alerted to alarms (such as air raid sirens) through a combination of light effects and sound detection.

## Features

- **Real-Time Clock Display**: The NeoPixel LED strip displays the current time, where red LEDs represent the current hour and green LEDs represent the minutes.
- **Sound Detection**: The system listens for alarm sounds using FFT analysis to detect specific frequencies related to alarms.
- **Wi-Fi Connectivity**: The device connects to a Wi-Fi network to fetch live alerts from a remote server using a REST API. If an alarm is detected, it triggers a visual explosion effect.
- **Explosion Effect**: When an alarm is detected, the LEDs flash with random colors for 40 seconds to alert the user.
- **Automatic Clock Resumption**: After the explosion effect, the system automatically returns to displaying the time.

## Setup

### Hardware Required

- **Microcontroller**: ESP32 or any microcontroller that supports Wi-Fi and can interface with NeoPixel strips.
- **NeoPixel LED Strip**: At least 12 LEDs.
- **Microphone**: For sound detection (connected to an analog pin).
- **Wi-Fi Network**: For receiving alerts from an external API.

### Software Required

- **Arduino IDE**: To program the microcontroller.
- **Libraries**: You will need the following libraries:
  - `Adafruit_NeoPixel`
  - `WiFi.h`
  - `HTTPClient.h`
  - `arduinoFFT`

### How to Use

1. Connect the NeoPixel LED strip to your microcontroller, ensuring that you have connected the data input pin to the specified pin in the code (`PIN 15`).
2. Connect the microphone to an analog input pin on the microcontroller.
3. Replace the Wi-Fi credentials in the code with your own SSID and password.
4. Upload the code to your microcontroller via the Arduino IDE.
5. The device will begin running the clock, and it will listen for alarm signals. If an alert is detected, the LEDs will display an explosion effect.

## Code Explanation

The system works by:

1. Displaying the current time using a NeoPixel LED strip. Red LEDs are used to represent the current hour, while green LEDs represent minutes.
2. The system uses FFT to analyze sounds picked up by the microphone. If the frequency matches a predefined alarm signal, the explosion effect is triggered.
3. The device continuously checks for new alerts through Wi-Fi and updates the LED display accordingly.

## Troubleshooting

- **Wi-Fi Connection Issues**: Ensure that the correct SSID and password are set in the code. Check the Wi-Fi signal strength and connectivity.
- **LED Strip Not Working**: Verify that the NeoPixel strip is correctly connected and that you have installed the necessary libraries (`Adafruit_NeoPixel`).
- **No Alarm Detection**: Make sure the microphone is picking up sound properly and that the FFT analysis is set to the correct frequency range for the alarm sound.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.
