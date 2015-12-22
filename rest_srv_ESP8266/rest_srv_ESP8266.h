

// The port to listen for incoming TCP connections
#define LISTEN_PORT           5000

#define WSSID         "PTL"
#define PASSWD        "P0stT3n3br4sL4b"

#define RESETTEENSY(x) (digitalWrite(x, LOW); digitalWrite(x, HIGH))
#define WAKEUPTEENSY(x) (digitalWrite(x, HIGH); digitalWrite(x, LOW))

#define SET_LED       "led"
#define SET_LINE      "line"
#define SET_COLUMN    "column"
#define SET_ALL       "set_all"
#define CLEAR_ALL     "clear_all"


/* Functions to be exposed to the API */
int ledControl(String command);

/* Primitives */
int set_led(unsigned long color, unsigned int x, unsigned int y);
int set_line(unsigned long color, unsigned int num);
int set_column(unsigned long color, unsigned int num);
int set_all(unsigned long color);


String getValue(String data, char separator, int index);


