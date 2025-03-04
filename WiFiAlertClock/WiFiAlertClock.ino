#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <HTTPClient.h>

// LED strip settings
#define PIN 15              // Pin connected to the LED strip
#define NUMPIXELS 12        // Number of LEDs in the strip
Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Wi-Fi settings
const char* ssid = "YaelMoses";          // Replace with your Wi-Fi SSID
const char* password = "10203040";       // Replace with your Wi-Fi password
const char* apiUrl = "https://www.oref.org.il/WarningMessages/alert/alerts.json";
bool isAlarmPlaying = false;

// Clock settings
int currentHourLed = 0;        // The LED representing the current hour
int minutesCounter = 0;        // Counter for minutes (0 to 59)

void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.show(); // Ensure all LEDs are off initially
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.println("\nConnecting");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(100);
  }
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
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(apiUrl);

    int httpCode = http.GET();
    if (httpCode > 0) {
      // HTTP request successful
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString(); // Get the response payload
        Serial.println("Response:");
        Serial.println(payload);

        // Check if there are active alerts
        if (payload.indexOf("alerts") > -1) { // Basic check for alerts
          Serial.println("ALERT DETECTED! Triggering explosion effect...");
          isAlarmPlaying = true;
        } else {
          Serial.println("No alerts detected.");
        }
      } else {
        // HTTP request failed
        Serial.printf("HTTP GET failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
    }
  } else {
    Serial.println("Wi-Fi disconnected!");
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
