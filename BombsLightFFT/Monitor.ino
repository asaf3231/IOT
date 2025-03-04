#include <arduinoFFT.h>

#define MIC_PIN 26         // Microphone pin (analog)
#define SAMPLES 128        // Number of FFT samples (must be a power of 2)
#define SAMPLING_FREQUENCY 1000 // Sampling frequency in Hz

arduinoFFT FFT = arduinoFFT();

double vReal[SAMPLES]; // Real data
double vImag[SAMPLES]; // Imaginary data

void setup() {
  Serial.begin(115200); // Start serial communication
}

void loop() {
  // Collect data from the microphone
  for (int i = 0; i < SAMPLES; i++) {
    vReal[i] = analogRead(MIC_PIN); // Read microphone data
    vImag[i] = 0; // Imaginary part is always 0
    delayMicroseconds(1000000 / SAMPLING_FREQUENCY); // Sampling delay
  }

  // Perform FFT
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD); // Apply Hamming window
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);                // Compute FFT
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);                 // Compute magnitudes

  // Print frequencies and amplitudes
  for (int i = 0; i < (SAMPLES / 2); i++) { // Only half the samples are needed (Nyquist limit)
    double frequency = i * (SAMPLING_FREQUENCY / SAMPLES); // Calculate frequency
    Serial.print(frequency, 1); // Print frequency
    Serial.print(" Hz: ");
    Serial.println(vReal[i], 2); // Print amplitude
  }

  Serial.println("----------------------------------------------------"); // Separator
  delay(1000); // Wait one second between readings
}
