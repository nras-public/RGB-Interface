#include <Arduino.h>

// Nathan Rasbold
// MAKR -- RGB Interface

// Potentiometer inputs
const uint8_t POT_RED = A6;
const uint8_t POT_GREEN = A3;
const uint8_t POT_BLUE = A0;

// Individual LEDs show each potentiometer's color level.
const uint8_t RED_LED_PIN = 8;
const uint8_t GREEN_LED_PIN = 10;
const uint8_t BLUE_LED_PIN = 12;

// The RGB LED combines the same three color levels.
const uint8_t RGB_RED_PIN = 2;
const uint8_t RGB_GREEN_PIN = 3;
const uint8_t RGB_BLUE_PIN = 4;

uint8_t readBrightness(uint8_t analogPin) {
  int rawValue = analogRead(analogPin);
  return static_cast<uint8_t>(map(rawValue, 0, 1023, 0, 255));
}

// This function writes one color channel of the RGB LED.
void writeRgbChannel(uint8_t outputPin, uint8_t brightness) {
  analogWrite(outputPin, brightness);
}

// This function sets all three RGB channels at the same time.
// It makes the LED show a single color based on the three brightness values.
void setRgbColor(uint8_t red, uint8_t green, uint8_t blue) {
  writeRgbChannel(RGB_RED_PIN, red);
  writeRgbChannel(RGB_GREEN_PIN, green);
  writeRgbChannel(RGB_BLUE_PIN, blue);
}

void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(RGB_RED_PIN, OUTPUT);
  pinMode(RGB_GREEN_PIN, OUTPUT);
  pinMode(RGB_BLUE_PIN, OUTPUT);

  // Optional: start the serial monitor for debugging.
  Serial.begin(9600);
}

void loop() {
  // Read the pot values. Each one gives us a brightness level from 0 to 255.
  uint8_t redBrightness = readBrightness(POT_RED);
  uint8_t greenBrightness = readBrightness(POT_GREEN);
  uint8_t blueBrightness = readBrightness(POT_BLUE);

  // Print the values to the Serial Monitor so students can see the numbers change.
  Serial.print("Red: ");
  Serial.print(redBrightness);
  Serial.print("  Green: ");
  Serial.print(greenBrightness);
  Serial.print("  Blue: ");
  Serial.println(blueBrightness);

  // Each individual LED displays its own channel; the RGB LED combines them.
  analogWrite(RED_LED_PIN, redBrightness);
  analogWrite(GREEN_LED_PIN, greenBrightness);
  analogWrite(BLUE_LED_PIN, blueBrightness);
  setRgbColor(redBrightness, greenBrightness, blueBrightness);

  // Small delay so the values are easier to read and the LED changes smoothly.
  delay(50);
}
