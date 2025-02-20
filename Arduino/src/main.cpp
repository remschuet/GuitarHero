/*------------------------------ Librairies ---------------------------------*/
#include <Arduino.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include "ComFilaire.h"
#include "ComBluetooth.h"
#include "State.h"
#include "Output.h"
#include "ErrorLog.h"
#include "Global.h"

/*------------------------------ Constantes ---------------------------------*/
#define BAUD 115200      // Fréquence de transmission série ## à définir selon le mode je crois
  State state;
  ComFilaire comFilaire(9600);
  ComBluetooth comBluetooth(9600);
  Error errorLogger;
  Output output;

  enum com {
    FILAIRE,
    BLUETOOTH
  };

/*---------------------------- Fonctions principales ------------------------*/
void setup()
{
    Serial.begin(9600);
    delay(2000);
}
void loop() 
{
  bool com=FILAIRE;

  if (com==BLUETOOTH)
  {
    state.GetChange(&comBluetooth);
  }
  else if (com==FILAIRE)
  {
    state.GetChange(&comFilaire);
  }
  else
  {
    errorLogger.AddError("Erreur Selection com",1);
  }
}
