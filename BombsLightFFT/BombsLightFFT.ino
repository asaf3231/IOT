
#include <arduinoFFT.h>
#include <Adafruit_NeoPixel.h>

// LED strip settings
#define PIN 15               // Pin connected to the LED strip
#define NUMPIXELS 12         // Number of LEDs in the strip
Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Microphone settings
#define MIC_PIN 26           // Pin connected to the microphone
#define SAMPLES 128          // Number of samples for FFT
#define SAMPLING_FREQUENCY 1000 // Sampling frequency (Hz)
arduinoFFT FFT = arduinoFFT();
double vReal[SAMPLES];
double vImag[SAMPLES];

// Alarm frequency pattern definition
const double alarmPattern[] = {140.0, 161.0, 180.0, 210.0, 238.0, 245.0, 266.0, 273.0, 280.0, 287.0, 294.0, 301.0, 308.0, 371.0, 378.0};
const int patternSize = sizeof(alarmPattern) / sizeof(alarmPattern[0]);
const double thresholds[] = {3000, 8000, 5000, 4000, 7000, 7500, 8000, 7000, 6500, 6000, 5500, 5000, 4500, 10000, 9000}; // Thresholds for each frequency

int detectedPatternIndex = 0; // Index of the current frequency in the sequence
unsigned long lastDetectionTime = 0; // Time of the last detected frequency
const unsigned long patternTimeout = 2000; // Maximum time to complete the sequence (milliseconds)

bool isAlarmPlaying = false; // Flag to indicate if the alarm is detected

// Clock settings
int currentHourLed = 0; // The LED representing the current hour
int minutesCounter = 0; // Counter for minutes (0 to 59)

void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.show(); // Ensure all LEDs are off initially
}

void loop() {
  if (isAlarmPlaying) {
    // If the alarm is playing, run the explosion effect
    triggerExplosionEffect();
    isAlarmPlaying = false; // After the effect, switch back to clock mode
  } else {
    // Check for the alarm
    checkForAlarm();

    // If no alarm, continue running the clock
    if (!isAlarmPlaying) {
      updateClock();
    }
  }

  delay(50); // Short delay to prevent overloading the processor
}

void updateClock() {
  strip.clear(); // Clear all LEDs

  // Light up the LED representing the current hour
  strip.setPixelColor(currentHourLed, strip.Color(255, 0, 0)); // Red light for the hour

  // Calculate how many green LEDs to light up for the minutes
  int greenLeds = minutesCounter / 5; // Light up one green LED for every 5 minutes

  // Light up green LEDs for the minutes
  for (int i = 1; i <= greenLeds; i++) {
    int greenLedIndex = (currentHourLed + i + NUMPIXELS) % NUMPIXELS; // Calculate position from the hour LED
    strip.setPixelColor(greenLedIndex, strip.Color(0, 255, 0)); // Green light
  }

  strip.show(); // Display the changes on the LEDs

  // Update the time
  minutesCounter++;

  if (minutesCounter >= 60) { // If an hour has passed
    minutesCounter = 0; // Reset the minute counter
    currentHourLed = (currentHourLed + 1) % NUMPIXELS; // Move to the next LED for the next hour
  }
}

void checkForAlarm() {
  // Collect FFT data
  for (int i = 0; i < SAMPLES; i++) {
    vReal[i] = analogRead(MIC_PIN);
    vImag[i] = 0;
    delayMicroseconds(1000000 / SAMPLING_FREQUENCY);
  }

  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);

  // Check the current frequency in the sequence
  double targetFrequency = alarmPattern[detectedPatternIndex];
  int targetIndex = (targetFrequency * SAMPLES) / SAMPLING_FREQUENCY;
  double amplitude = vReal[targetIndex];

  Serial.print("Checking Frequency: ");
  Serial.print(targetFrequency);
  Serial.print(" Hz, Amplitude: ");
  Serial.println(amplitude);

  // If the frequency exceeds the threshold
  if (amplitude > thresholds[detectedPatternIndex]) {
    // If it's the correct frequency in the sequence
    detectedPatternIndex++;
    lastDetectionTime = millis();
    Serial.println("Frequency matched!");

    // If the sequence is complete
    if (detectedPatternIndex >= patternSize) {
      isAlarmPlaying = true; // Trigger the explosion effect
      detectedPatternIndex = 0; // Reset the sequence
    }
  } else if (millis() - lastDetectionTime > patternTimeout) {
    // If the time between frequencies exceeds the timeout, reset
    detectedPatternIndex = 0;
    Serial.println("Pattern reset due to timeout.");
  }
}

void triggerExplosionEffect() {
  Serial.println("Alarm Detected! Triggering explosion effect...");
  
  unsigned long startTime = millis(); // Record the time when the effect starts
  
  while (millis() - startTime < 40000) { // 40 seconds = 40000 milliseconds
    for (int j = 0; j < NUMPIXELS; j++) {
      strip.setPixelColor(j, strip.Color(random(255), random(255), random(255))); // Random colors
    }
    strip.show();
    delay(100);
  }

  strip.clear(); // Turn off all LEDs after 40 seconds
  strip.show();
} 
