/*
  This a simple example of the aREST Library for the ESP8266 WiFi chip.
  See the README file for more details.

  Written in 2015 by Marco Schwartz under a GPL license.
*/

// Import required libraries
#include <ESP8266WiFi.h>
#include <aREST.h>
#include "rest_srv_ESP8266.h"


// Create aREST instance
aREST rest = aREST();


// WiFi parameters
const char* ssid = WSSID;
const char* password = PASSWD;


/* Create an instance of the server */
WiFiServer server(LISTEN_PORT);


void setup(void)
{
    // Start Serial
    Serial.begin(115200);
    //Serial.setDebugOutput(true)      // set wifi debug


    // Function to be exposed
    rest.function("ptl",ledControl);
  
    // Give name and ID to device
    rest.set_id("1");
    rest.set_name("PTL_shelf");

    // Connect to WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");

    // Start the server
    server.begin();
    Serial.println("Server started");

    // Print the IP address
    Serial.println(WiFi.localIP());

    // Swap to pin 13(RX),15(TX)
    Serial.swap();
}

void loop() {

    // Handle REST calls
    WiFiClient client = server.available();
    if (!client) {
        return;
    }
    
    while(!client.available()){
        delay(1);
    }
    rest.handle(client);

}

// Custom function accessible by the API
int ledControl(String command){
    
    String cmd = getValue(command, ':', 0);
    unsigned long color = (unsigned long)strtol(getValue(command, ':', 1).c_str(), NULL, 16);
    
    if( cmd == SET_LED ) {
        unsigned int x = atoi(getValue(command, ':', 2).c_str()) % 8;
        unsigned int y = atoi(getValue(command, ':', 3).c_str()) % 15;
        set_led(color, x, y);
    }

    if( cmd == SET_LINE ) {
        unsigned int line_nb = atoi(getValue(command, ':', 2).c_str()) % 15;
        set_line(color, line_nb);
    }

    if( cmd == SET_COLUMN ) {
        unsigned int col_nb = atoi(getValue(command, ':', 2).c_str()) % 8;
        set_column(color, col_nb);
    }
    
    if( cmd == SET_ALL )
        set_all(color);

    if( cmd == CLEAR_ALL )
        set_all(0x000000);
}

/* Set a led */
int set_led(unsigned long color, unsigned int x, unsigned int y) {

    char buff[6];

    buff[0] = 0x1;
    buff[1] = 0xFF & (color >> 16);
    buff[2] = 0xFF & (color >> 8);
    buff[3] = 0xFF & color;
    buff[4] = x;
    buff[5] = y;

    Serial.write(buff, 6);
    
    return 0;
}


/* Set a whole line */
int set_line(unsigned long color, unsigned int num) {

    int i;
    char buff[5];
    
    char nb = 0x8;    // 8 leds
    
    Serial.write(nb);
    
    buff[0] = 0xFF & (color >> 16);
    buff[1] = 0xFF & (color >> 8);
    buff[2] = 0xFF & color;
    
    for ( i = 0; i < 8; i++) {
        
        buff[3] = i;
        buff[4] = num;
        Serial.write(buff, 5);
    }

    return 0;
}

/* Set a whole line */
int set_column(unsigned long color, unsigned int num) {

    int i;

    for( int i = 0; i < 15; i++ )
        set_led(color, num, i);

    return 0;
}

/* Set whole shelf */
int set_all(unsigned long color) {
    
    /* set all led to color */
    for(int i = 0; i < 120; i++ )
        set_led(color, i/15, i%15);

    return 0;
}


String getValue(String data, char separator, int index)
{
 int found = 0;
  int strIndex[] = {
0, -1  };
  int maxIndex = data.length()-1;
  for(int i=0; i<=maxIndex && found<=index; i++){
  if(data.charAt(i)==separator || i==maxIndex){
  found++;
  strIndex[0] = strIndex[1]+1;
  strIndex[1] = (i == maxIndex) ? i+1 : i;
  }
 }
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

