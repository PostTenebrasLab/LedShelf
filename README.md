
Description :
-------------

WS2801 utilise data et une clock (deux fils)
WS2811, WS2812b n'utilisent pas de clock (elle est interne) mais juste un bus data


information sur le bus :

l'état d'une LED est codée sur 24bits soit ; 
8bits Red, 8bits Green, 8bits Blue, chanq'un avec une intensité de 0 à 255
(à noter que cette échelle n'est pas forcement linéaire).

Attention, l'ordre des bits ne correspond pas à RGB mais GRB :
G7 G6 G5 G4 G3 G2 G1 G0 R7 R6 R5 R4 R3 R2 R1 R0 B7 B6 B5 B4 B3 B2 B1 B0


Protocole du bus :

chaque bit dure 2.5us, c'est le ratio H/L qui contient l'information :

    0b = 0,5us (Vcc) + 2,0 us (low)
    1b = 1,2 (Vcc) + 1,3us (low)

un cycle de 2,5us low (100% low) est utilisé comme signal de validation (reset)

quand une LED a reçu 3 octets pour elle, elle relaie les suivants...Si A(n) = 3octets

Envoyer A(1),A(2),A(3),...,A(n) => 

  L1 garde A(1) et relaie A(2),A(3),...,A(n) -> L2 garde A(2) et relaie A(3),...,A(n) 
  et ainsi de suite.


à 16Mhz, un cycle dure 62,5ms => or 0,5us = 500ms = 8cycles*62,5ms on est donc assez
proche de la limite du micro-contrôler et de la tolerence des LED (72,5ms). Une
différence minime peut compromettre le signal.



Documentation :
--------------

    wget https://www.adafruit.com/datasheets/WS2801.pdf
    wget http://www.adafruit.com/datasheets/WS2812B.pdf

   - http://bleaklow.com/2012/12/02/driving_the_ws2811_at_800khz_with_a_16mhz_avr.html


Librairies :
-----------


  ( - https://github.com/adafruit/Adafruit_NeoPixel )
   - http://www.pjrc.com/teensy/td_libs_OctoWS2811.html


