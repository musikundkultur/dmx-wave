/*Comments 

   Dieses Programm interpretiert 1 Buttonwert als DMX Wert für den
   DMX-Startkanal.

   Konzipiert für
   Arduino Nano V3, old Bootloader
   1Button
   OLED Display
   SN75176 IC (seriell -> DMX)
   1x DMX Out
   5V USB Input


   Verkabelung DMX senden mit SN75176 (MAX-485 geht auch)
   1 - RO   GND mit 100Ohm Widerstand
   2 - RE   GND
   3 - DE   5V
   4 - DI   von TX Port Arduino (abziehen wenn er programmiert wird)
   5 - GnD  GND (auch DMX GND)
   6 - A    DMX Signal hot    Pin3
   7 - B    DMX Signal cold   Pin2
   8 - Vcc  5V

*/

//RS485 Protokoll für SN75176 IC
#include <ArduinoRS485.h>
//DMX Library
#include <ArduinoDMX.h>

// #define TESTING
// #define DIMMER

#ifdef TESTING
#include <AUnit.h>
#endif
// ====================================================================================================================

#define Button 11  //D11

#define Led 2  //unbenutzt
int button_state = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;
  delay(100);

  //----------------------------------------------

  //INPUTS
  pinMode(Button, INPUT_PULLUP);

  //Outputs
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  // DMX mit eingestellter Adressgröße initialisieren
  if (!DMX.begin(512)) {
    Serial.println(F("Failed to initialize DMX!"));
    while (1)
      ;  // wait for ever
  }
#ifndef DIMMER
  init_par_leds();
#endif
}

// ====================================================================================================================

void loop() {
#ifdef TESTING
 aunit::TestRunner::run();
#else
  button_state = digitalRead(Button);
  if (button_state == LOW) {
#ifdef DIMMER
    dimmer_wave();
#else
    par_wave();
#endif
  }
#endif
}
