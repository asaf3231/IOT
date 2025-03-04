Bombs Light Clock with FFT and Wi-Fi

Overview

The Bombs Light Clock with FFT and Wi-Fi is an innovative project that combines real-time clock functionality with sound detection using Fast Fourier Transform (FFT) to trigger visual alarm notifications. The device utilizes a NeoPixel LED strip to display time, with additional features to detect alarm signals over Wi-Fi from an external API. This system helps ensure users are alerted to alarms (such as air raid sirens) through a combination of light effects and sound detection.

Features
	•	Real-Time Clock Display: The NeoPixel LED strip displays the current time, where red LEDs represent the current hour and green LEDs represent the minutes.
	•	Sound Detection: The system listens for alarm sounds using FFT analysis to detect specific frequencies related to alarms.
	•	Wi-Fi Connectivity: The device connects to a Wi-Fi network to fetch live alerts from a remote server using a REST API. If an alarm is detected, it triggers a visual explosion effect.
	•	Explosion Effect: When an alarm is detected, the LEDs flash with random colors for 40 seconds to alert the user.
	•	Automatic Clock Resumption: After the explosion effect, the system automatically returns to displaying the time.

Components
	•	NeoPixel LED Strip (12 LEDs): Displays time and the alarm effect.
	•	Microphone Module: Captures sound for FFT analysis.
	•	Wi-Fi Module (e.g., ESP32): Connects to the Wi-Fi and fetches alarm data from a remote server.
	•	arduinoFFT Library: Used for FFT analysis to detect alarm frequencies.
	•	HTTPClient Library: Used to interact with the remote server and retrieve real-time alerts.

Setup
	1.	Hardware Setup:
	•	Connect the NeoPixel LED strip to the appropriate pin on your microcontroller (e.g., ESP32).
	•	Connect the microphone module to an analog input pin (e.g., pin 26).
	2.	Software Setup:
	•	Install the following libraries in the Arduino IDE:
	•	Adafruit_NeoPixel for controlling the LED strip.
	•	arduinoFFT for performing FFT-based sound analysis.
	•	WiFi and HTTPClient for Wi-Fi functionality and API communication.
	3.	Wi-Fi Configuration:
	•	Modify the code with your Wi-Fi credentials (SSID and password).
	•	Set the appropriate URL for fetching the real-time alerts (the current API URL is for an Israeli alert service).
	4.	Microcontroller:
	•	Upload the code to an ESP32 or any compatible microcontroller with Wi-Fi support.

How It Works
	1.	Clock Display: The NeoPixel LED strip lights up to display the current time. Red LEDs represent the current hour, and green LEDs represent the minutes.
	2.	Sound Detection: The microphone module captures ambient sound, and the arduinoFFT library processes the data to detect alarm frequencies.
	3.	Wi-Fi Integration: The system connects to a Wi-Fi network and checks for live alerts from the specified API. If an alarm is detected, it triggers the explosion effect.
	4.	Explosion Effect: When an alarm is detected, the LEDs flash randomly for 40 seconds to visually alert the user.
	5.	Automatic Clock Resumption: After the explosion effect, the system resumes displaying the time.

Installation
	1.	Clone or download the repository.
	2.	Open the BombLightClockWiFi.ino file in the Arduino IDE.
	3.	Install the required libraries:
	•	Adafruit_NeoPixel
	•	arduinoFFT
	•	WiFi
	•	HTTPClient
	4.	Modify the ssid, password, and apiUrl with your Wi-Fi credentials and API URL.
	5.	Upload the code to your ESP32 or compatible microcontroller.
	6.	Connect the hardware components as per the circuit diagram.

Circuit Diagram

Here is a simple schematic for the hardware setup:
	•	Microphone: Connect the microphone module to the analog input pin (e.g., pin 26).
	•	NeoPixel LED Strip: Connect the data input of the NeoPixel strip to a digital pin (e.g., pin 15) on the microcontroller.

Code Description

The code reads audio data from the microphone, processes it using FFT to detect the alarm sound, and controls the LED strip accordingly. Additionally, it connects to a Wi-Fi network, fetches live alerts from a remote server, and triggers the explosion effect if an alarm is detected.

Key Functions:
	•	updateClock(): Updates the time on the NeoPixel LED strip.
	•	checkForAlarm(): Checks for an alarm by performing FFT on the microphone data and fetching live alerts from the API.
	•	triggerExplosionEffect(): Activates the explosion effect when an alarm is detected.

Troubleshooting
	•	Wi-Fi Connection Issues: Double-check your Wi-Fi credentials and ensure the device is within range of the network.
	•	No Alarm Detected: Ensure the microphone is correctly connected and that the alarm frequency is within range.
	•	LEDs Not Lighting Up: Check the NeoPixel wiring and power supply to ensure the LEDs are functioning.

License

This project is licensed under the MIT License - see the LICENSE file for details.

Acknowledgements
	•	The arduinoFFT library for performing FFT analysis.
	•	The Adafruit NeoPixel library for controlling the LED strip.
	•	The WiFi and HTTPClient libraries for enabling Wi-Fi and fetching remote alerts.
	•	This project was developed by Asaf Ramati and Rony Rabinovitz.
