/*------------------------------ Librairies ---------------------------------*/
#include <Arduino.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include "ComFilaire.h"
#include "ComBluetooth.h"
#include "State.h"
#include "ErrorLog.h"
#include "Global.h"

/*------------------------------ Constantes ---------------------------------*/
#define BAUD 115200      // Fréquence de transmission série ## à définir selon le mode je crois
  State state;
  ComFilaire comFilaire(9600);
  ComBluetooth comBluetooth(9600);
  Error errorLogger;

/*---------------------------- Fonctions principales ------------------------*/
void setup()
{
  //Serial.begin(115200); ###fait direcement dans le constructeur
  //delay(2000);
}
void loop() 
{
  bool bluetooth=true;
  if (bluetooth)
  {
    //state.GetChange(&comBluetooth);
    state.GetChange(&comBluetooth);
  }
  else
  {
    state.GetChange(&comFilaire);
  }
}
