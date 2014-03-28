/*  Axel Fahy - 27.12.2013
 *  First try to command the leds of the shelf (PTL)
 *  Since I don't have the leds or an arduino with me, 
 *  this code is probably full of bug...
 *  (And I don't know anything about arduino programming...)
 *
 *  All the leds are in series.
 *  The easier way should be to see the led as an array.
 *
 *  */

#include <Adafruit_NeoPixel.h>

// The pin 6 is used to command the leds.
#define PIN 6

// The number led in a column. 
#define LED_BY_COL 11
// The number led in a line. 
#define LED_BY_LINE 3 

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_BY_COL * LED_BY_LINE, PIN, NEO_GRB + NEO_KHZ800);

int tabShelf[LED_BY_LINE, LED_BY_COL];

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(115200); // For the serial link...

  initShelf(tabShelf);
}

void loop() {
    delay(500);
  
  /*colorPart(0, 2, strip.Color(255, 0, 0), WAIT); // Red
  colorPart(3, 5, strip.Color(0, 255, 0), WAIT); // Green
  colorPart(6, 8, strip.Color(0, 0, 255), WAIT); // Blue
  colorPart(9, 11, strip.Color(0, 255, 255), WAIT); // Blue
  colorPart(12, 14, strip.Color(255, 0, 255), WAIT); // Blue*/


  
}

void serialEvent() {
    // Read data from the console.
    char charRead = 0;
    int buffer = 0;

    buffer = Serial.available();

    while (buffer > 0) {
        charRead = Serial.read();
        // Ligth on a led from the first column in red...
        colorLed(1, charRead, strip.Color(255, 0, 0);
    }


void initShelf(int *tab) {
    // Axel Fahy - 27.12.2013
    // Procedure to initialize the array.
    // For the initalization, all the array is green.
    uint16_t i, j;

    for (i = 0; i < LED_BY_LINE){
        for (j = 0; j < LED_BY_COL){
            colorLed(i, j, strip.Color(0, 255, 0);
        }
    }

}

uint16_t getLedNumber(uint16_t x, uint16_t y) {
    // Axel Fahy - 27.12.2013
    // Function to get the led number.
    return x * LED_BY_COL + y;
}


void colorLed(uint16_t x, uint16_t y, uint32_t color) {
    // Axel Fahy - 27.12.2013
    // Procedure to color a led.
    // Parameters : - Position (x, y)
    //              - Color (Adafruit_NeoPixel.Color(R, G, B)
    uint16_t ledNumber = getLedNumber(x, y);
    strip.setPixelColor(ledNumber, color);
    strip.show;
}







/*  ---------------------------------------
 *  ---------------------------------------
 *  OLD OR USELESS FUNCTION ---------------
 *  DELETE LATER --------------------------
 *  ---------------------------------------
 *  */




// AF - 13.12.2013 : Color part of the strip
void colorPart(uint16_t starti, uint16_t endi, uint32_t c, uint8_t wait) {
  for(uint16_t i=starti; i<=endi; i++) {
      //Serial.println(i);
      strip.setPixelColor(i, c);
      strip.show();
      //delay(wait); // If delay is low, leds are blinking... hurts the eyes...
  }
}

// Fill the dots one after the other with a color
void colorWipeTest(uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      if (i % 2 == 0){
        strip.setPixelColor(i, strip.Color(255, 0, 0));
      }
      else{
        strip.setPixelColor(i, strip.Color(0, 255, 255));
      }
      strip.show();
      delay(wait);
  }
}


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
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

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
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

