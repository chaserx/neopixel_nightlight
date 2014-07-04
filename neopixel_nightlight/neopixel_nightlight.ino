#include <Adafruit_NeoPixel.h>

// Chase Southard
// July 5, 2014
// NeoPixel Nightlight

// Some code from Adafruit stand test example code
// github.com/adafruit/Adafruit_NeoPixel/master/examples/strandtest
// Some timer code from here: http://pastebin.com/YrV5t73e

#define PIN 2

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

// unsigned long max_time = 900000UL; // 15 minutes
double max_time = 15000; // 15 seconds
unsigned long last_time_check = millis();

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  if(max_time <= 0) {
    // turn all pixels off
    uint16_t i;
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, 0, 0, 0);
    }
    strip.show();
  }
  else {
    rainbow(500);
  }
  updateTimer();
}

// Update the variable that contains the number of milliseconds left on the timer.
// millis() is a built-in function that returns the number of milliseconds that have elapsed
// since the Arduino was turned on. We check how many milliseconds have elapsed since last time
// we ran this function.
void updateTimer() {
  max_time -= ((millis() - last_time_check));
  last_time_check = millis();
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

