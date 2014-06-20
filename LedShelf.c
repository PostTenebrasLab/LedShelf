/*
 * =====================================================================================
 *
 *       Filename:  LedShelf.c
 *
 *    Description:  Programme to use the led of the shelf @PTL
 *
 *        Version:  1.0
 *        Created:  06/20/2014 10:11:25 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Axel Fahy (), axel.fahy@etu.hesge.ch
 *   Organization:  HES-SO hepia section ITI
 *
 * =====================================================================================
 */

/* Library for the leds. */
#include <OctoWS2811.h>

/* The pin 6 is used to command the leds. */
#define PIN_ARDUINO 6

/* The led of shelf is like an array. */
/* Number of columns. */
#define NB_COL 8

/* Number of rows. */
#define NB_ROW 15

/* Serial connection. */
#define HWSERIAL Serial1
#define BAUD_RATE 9600

/* Setup of the leds. */
const int ledsPerStrip = NB_COL * NB_ROW 

DMAMEM int displayMemory[ledsPerStrip * 6];
int drawingMemory[ledsPerStrip * 6];

const int config = WS2811_GRB | WS2811800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config); 


/* Prototypes */
void initLed();
void getData();


void setup()
{
    leds.begin();
    leds.show();
    HWSERIAL.begin(BAUD_RATE);
}


void loop() 
{
    initLed();
}


void initLed() 
{
    /* Axel Fahy - 19.06.2014
     * Function to initialize the array of leds. 
     * Let's test with all the leds green. */
    int i;

    for (i = 0; i < ledsPerStrip; i++) {
        leds.setPixel(i, 0, 255, 0);
    }
}


void getData()
{
    /* Axel Fahy - 19.06.2014
     * Function to get the data from the serial connection.
     * Will get the number of the led to light and the color. */
    char charRead = 0; 
    int buffer = 0;

    buffer = HWSERIAL.available();

    while (buffer > 0) {
        charRead = HWSERIAL.read();
    }
}
