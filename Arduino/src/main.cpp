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
  static Com* comType[] = {&comFilaire, &comBluetooth};

  enum com {
    FILAIRE,
    BLUETOOTH
  };

/*---------------------------- Fonctions principales ------------------------*/
void setup()
{
    Serial.begin(9600);
    delay(2000);
    state.SetDefault();
}
void loop() 
{
  com selectedCom=BLUETOOTH;
  Com* comDevice;

  if (selectedCom==FILAIRE)
  {
    comDevice=comType[0];
  }
  else if (selectedCom==BLUETOOTH)
  {
    comDevice=comType[1];
  }
  else
  {
    errorLogger.AddError("Erreur Selection com",1);
  }
  state.GetChange(comDevice);
}
