#include <Arduino.h>

constexpr uint8_t red_in = A0;
constexpr uint8_t grn_in = A1;
constexpr uint8_t blue_in = A2;

// The Nano's six PWM pins drive the three individual LEDs and RGB channels.
constexpr uint8_t red_in = 3;
constexpr uint8_t grn_in = 5;
constexpr uint8_t blue_in = 7;
constexpr uint8_t rgb_red = 9;
constexpr uint8_t rgb_green = 10;
constexpr uint8_t rgb_blue = 11;

// Set true when using a common-anode RGB LED; common-cathode LEDs use false.
constexpr bool RGB_COMMON_ANODE = false;

uint8_t readBrightness(uint8_t potentiometerPin) {
  const int reading = analogRead(potentiometerPin);
  return static_cast<uint8_t>(map(reading, 0, 1023, 0, 255));
}

void writeRgbChannel(uint8_t pin, uint8_t brightness) {
  const uint8_t output = RGB_COMMON_ANODE ? 255 - brightness : brightness;
  analogWrite(pin, output);
}

void setup() {
  pinMode(red_in, OUTPUT);
  pinMode(grn_in, OUTPUT);
  pinMode(blue_in, OUTPUT);
  pinMode(rgb_red, OUTPUT);
  pinMode(rgb_green, OUTPUT);
  pinMode(rgb_blue, OUTPUT);
}

void loop() {
  const uint8_t redBrightness = readBrightness(red_in);
  const uint8_t greenBrightness = readBrightness(grn_in);
  const uint8_t blueBrightness = readBrightness(blue_in);

  analogWrite(red_in, redBrightness);
  analogWrite(grn_in, greenBrightness);
  analogWrite(blue_in, blueBrightness);

  writeRgbChannel(rgb_red, redBrightness);
  writeRgbChannel(rgb_green, greenBrightness);
  writeRgbChannel(rgb_blue, blueBrightness);
}
