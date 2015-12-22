/*
 * =====================================================================================
 *
 *       Filename:  LedShelf_server.ino
 *
 *    Description:  WS2801 LED's server for PTL (PostTenebrasLab) Shelf
 *
 *        Version:  1.0
 *        Created:  21/06/2014 17:37:58
 *       Revision:  none
 *       Compiler:  gcc-avr
 *
 *         Author:  Sebastien Chassot (sinux), seba.ptl@sinux.net
 *        Company:  Post Tenebras Lab (Geneva's Hackerspace)
 *
 * =====================================================================================

    Required Connections  on teensy 3.0 (3.1)
    ------------------------------------------

    pin 2:  LED Strip #1    OctoWS2811 drives 8 LED Strips.
    pin 14: LED strip #2    All 8 are the same length.
    pin 7:  LED strip #3
    pin 8:  LED strip #4    A 100 ohm resistor should used
    pin 6:  LED strip #5    between each Teensy pin and the
    pin 20: LED strip #6    wire to the LED strip, to minimize
    pin 21: LED strip #7    high frequency ringining & noise.
    pin 5:  LED strip #8
    pin 15 & 16 - Connect together, but do not use
    pin 4 - Do not use
    pin 3 - Do not use as PWM.  Normal use is ok.
    pin 1 - Output indicating CPU usage, monitor with an oscilloscope,
            logic analyzer or even an LED (brighter = CPU busier)

    pin 9   nRF24L01 (SPI)   CE     (depend on mode - enable data emission )
    pin 10  nRF24L01 (SPI)   CSN    (Cable Select Not - low when selected )
    pin 11  nRF24L01 (SPI)   MOSI   data to nRF24L01
    pin 12  nRF24L01 (SPI)   MISO   data comming from nRF24L01
    pin 13  nRF24L01 (SPI)   SLK    clock (teensy SPI clock)
    pin 17  nRF24L01 (SPI)   interrupt

    pin 18  RELAY            disable LED alimentation
*/


#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#include <OctoWS2811.h>
#include "driver_LED_teensy.h"

const int ledsPerStrip = NB_LEDS;     // 8 * 15 shelfs

/* OctoWS2811 */
DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

const int config = WS2811_GRB | WS2811_800kHz;
OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);


unsigned long time = 0;

/* SPI buffer */
//char buf [100];
//volatile byte pos;
//volatile boolean process_it;

void setup() {

    /*=======================
      init Serial
    =======================*/
    Serial.begin(115200);
    Serial.println("Listening...");

    /* serial for NodeMCU communication */
    HWSERIAL.begin(115200);


    /*=======================
      init OctoWS2811
    =======================*/
    leds.begin();
    Serial.println("LED strip initialized...");

    int i = 0;
    for (i = 0; i < 8*ledsPerStrip; i++)
        leds.setPixel(i, 0x000000);
}


void loop() {

    if(HWSERIAL.available() > 4) {

        unsigned int i;
        unsigned int len = atoi(HWSERIAL.read());
  
        for( i = 0; i < len; i++) {
            
            unsigned long color = 0;
            unsigned int x, y;
            
            while(HWSERIAL.available() < 5){};
            
            color = HWSERIAL.read();
            color = (color << 8) | HWSERIAL.read();
            color = (color << 8) | HWSERIAL.read();

            x = HWSERIAL.read();
            y = HWSERIAL.read();
            x = x*15 + (ledsPerStrip-y) - 1;
            leds.setPixel(x, color);
        }
    }
    
    /*  apply LEDs' status */
    if(!leds.busy()){
        leds.show();
    }
}

