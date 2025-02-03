/*------------------------------ Librairies ---------------------------------*/
#include <Arduino.h>
#include <ArduinoJson.h>
#include "ComFilaire.h"
/*------------------------------ Constantes ---------------------------------*/
#define BAUD 115200        // Fréquence de transmission série
#define PIN_LED 7          // Broche de la LED
#define PIN_POT A0         // Broche du potentiomètre
ComFilaire com(BAUD);
int ledState = LOW;

/*---------------------------- Fonctions principales ------------------------*/
void setup() {
  Serial.begin(115200);
  delay(2000);
}

void loop() {
    com.envoyerMessageString("message", "coucou message du arduino");
    com.envoyerMessageString("bouton1", "released");
    // if (com.lireMessage(ledState)) {
    //    digitalWrite(PIN_LED, ledState);
    // }
}
