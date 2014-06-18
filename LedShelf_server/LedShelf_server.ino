/*
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

#include <OctoWS2811.h>
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>


#define NB_LEDS         15
#define CE_PIN          9
#define CSN_PIN         10
#define INTERRUPT_PIN   17
#define RELAY_PIN       18


const int ledsPerStrip = NB_LEDS;     // 15 shelfs

/* OctoWS2811 */
DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];
const int config = WS2811_GRB | WS2811_800kHz;
OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

int rainbowColors[180];
unsigned long time = 0;



void setup() {
    /*=======================
      init Serial
    =======================*/

    Serial.begin(115200);
    Serial.println("Listening...");
  

    /*=======================
      init OctoWS2811
    =======================*/

    pinMode(1, OUTPUT);
    digitalWrite(1, HIGH);
    for (int i=0; i<180; i++) {
        int hue = i * 2;
        int saturation = 100;
        int lightness = 50;
        // pre-compute the 180 rainbow colors
        rainbowColors[i] = makeColor(hue, saturation, lightness);
    }
    digitalWrite(1, LOW);
    leds.begin();
    attachInterrupt();


    /*=======================
      init nRF24L01 as server
    =======================*/
    
    Mirf.cePin = CE_PIN;
    Mirf.csnPin = CSN_PIN;
    Mirf.spi = &MirfHardwareSpi;
    Mirf.init();
    Mirf.setRADDR((byte *)"LedShelf");
Mirf.payload = sizeof(unsigned long);
    Mirf.config();
    
    /*====== RELAY =======*/
    pinMode(RELAY_PIN, OUTPUT);
  
}


void loop() {
  
    //  time += millis();

    /*  apply LEDs' status */
    if(!leds.busy()){
        leds.show();
    }
  
}


void receiving_data( byte R, byte G, byte B, byte add ){

    byte data[Mirf.payload];

    if(!Mirf.isSending() && Mirf.dataReady()){
        Mirf.getData(data);
        leds.setPixel(data[0], data[1], data[2], data[3]);
     }

    /* TODO send data back to client to reduce data lost
       and confirm the server's up

    if(client_sent){
        Mirf.setTADDR((byte *)"clie1");
        Mirf.send(data);   // confirm receipt
    }
    */        
}
