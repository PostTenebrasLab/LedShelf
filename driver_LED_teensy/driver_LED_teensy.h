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
 * =====================================================================================
*/

#define NB_LEDS         15
#define CE_PIN          9
#define CSN_PIN         10
#define WAKEUP_PIN      17
#define RELAY_PIN       18
#define HWSERIAL        Serial2

#define RelayOn digitalWrite(RELAY_PIN, HIGH)
#define RelayOff digitalWrite(RELAY_PIN, LOW)

#define RED    0xFF0000
#define GREEN  0x00FF00
#define BLUE   0x0000FF
#define YELLOW 0xFFFF00
#define PINK   0xFF1088
#define ORANGE 0xE05800
#define WHITE  0xFFFFFF
