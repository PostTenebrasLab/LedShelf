/*
  This a simple example of the aREST Library for the ESP8266 WiFi chip.
  See the README file for more details.

  Written in 2015 by Marco Schwartz under a GPL license.
*/

// Import required libraries
#include <ESP8266WiFi.h>
#include <aREST.h>
#include <SPI.h>

// Create aREST instance
aREST rest = aREST();
const int dataReadyPin = 6;
const int chipSelectPin = 7;

// WiFi parameters
const char* ssid = "PTL";

// The port to listen for incoming TCP connections
#define LISTEN_PORT           8080

#define RESETTEENSY(x) (digitalWrite(x, LOW); digitalWrite(x, HIGH))
#define WAKEUPTEENSY(x) (digitalWrite(x, HIGH); digitalWrite(x, LOW))

// Create an instance of the server
WiFiServer server(LISTEN_PORT);

// Variables to be exposed to the API
int temperature;
int humidity;

uint8_t data[] = "Hello World";

// Declare functions to be exposed to the API
int ledControl(String command);
int shelfOn(String command);    // Turn led strip power on (MOSFET transistor)


void setup(void)
{
  // Start Serial
  Serial.begin(115200);

  // Init variables and expose them to REST API
  temperature = 24;
  humidity = 40;
  rest.variable("temperature",&temperature);
  rest.variable("humidity",&humidity);

  // Function to be exposed
  rest.function("ptl",ledControl);
  //rest.function("ptlshelf",ledControl);
  
  // Give name and ID to device
  rest.set_id("1");
  rest.set_name("PTL_led_shelf");

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

  /* SPI */
  pinMode(dataReadyPin, OUTPUT);
  SPI.begin();  
//  SPI.setBitOrder(MSBFIRST);
  
  
}

void loop() {

  delay(1);
  digitalWrite(dataReadyPin, LOW);
//  SPI.transfer();
  delay(0.5);
  digitalWrite(dataReadyPin, HIGH);
  delay(1);
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

  Serial.print(command);

  int op, grp;
  int lst, g, r, b;
  String list;
  int len = command.length();
  
  if(len > 0){
      op = (command[0] >> 4);     // could be 0 or 1
      grp = (command[0] & 0x0f);
  } else
      return 1;
  
  switch(grp){    
    case 1:
        if(len > 1)
            lst = command[1];
        if( op && (len > 4) ){
            g = command[2];
            r = command[3];
            b = command[4];
        } else
            return 1;
        Serial.print("led " + lst + g + r + b);
        break;
    case 2:
        if(len > 2)
            lst = (int)((command[1] << 8) | command[2]);
        if( op && (len > 5) ){
            g = command[3];
            r = command[4];
            b = command[5];
        } else
            return 1;
        Serial.print("column " + lst + g + r + b);
        break;
    case 3:
        if(len > 1)
            lst = (int)command[1];
        if( op && (len > 4) ){
            g = command[2];
            r = command[3];
            b = command[4];
        } else
            return 1;
        Serial.print("line " + lst + g + r + b);
        break;
    case 4:
        if(len > 24){
            list = (int)command[1];
            list[24] = '\0';
        } else
            return 1;
        if( op && (len > 27) ){
            g = command[2];
            r = command[3];
            b = command[4];
        } else
            return 1;
        Serial.print("group " + lst + g + r + b);
        break;
    case 15:
      Serial.print("Turn everything off\n");
      break;                  
    defaul:
      Serial.print("Non reconnu");
      return -1;
  }
  
  return 0;
}

