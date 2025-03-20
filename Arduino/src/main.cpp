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
  Output output;
  ComFilaire comFilaire(BAUD);
  ComBluetooth comBluetooth(BAUD);
  Error errorLogger;
  static Com* comType[] = {&comFilaire, &comBluetooth};//0:FILAIRE,1BLUETOOTH
  static com selectedCom;

/*---------------------------- Fonctions principales ------------------------*/
void setup()
{
  pinMode(34,OUTPUT);//moteur1
  pinMode(36,OUTPUT);//moteur2
  pinMode(43,OUTPUT);//test acc
  pinMode(44,OUTPUT);//bg1
  pinMode(46,OUTPUT);//bg2
  pinMode(48,OUTPUT);//bg3
  pinMode(50,OUTPUT);//bg4
  pinMode(52,OUTPUT);//bg5
  pinMode(45,OUTPUT);//bg6
  pinMode(47,OUTPUT);//bg7
  pinMode(49,OUTPUT);//bg8
  pinMode(51,OUTPUT);//bg9
  pinMode(53,OUTPUT);//bg10

  while(!Serial){;}
  Serial.begin(BAUD);//Filaire
  Serial1.begin(BAUD);//Bluetooth
  delay(2000);

  state.SetDefault();
  selectedCom=BLUETOOTH;

  lcd.init();           // S'assurer que l'initialisation n'est pas redondante si déjà faite dans Global.cpp
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Set up completed");
 
}
void loop() 
{
  Com* comDevice;

  if (selectedCom==FILAIRE)
  {
    comDevice=comType[0];
    analogWrite(44,150);
    analogWrite(46,0);
  }
  else if (selectedCom==BLUETOOTH)
  {
    analogWrite(46,150);
    analogWrite(44,0);
    comDevice=comType[1];
  }
  else
  {
    errorLogger.AddError("Erreur Selection com",1);
  }
  state.GetChange(comDevice);
  output.Set(comDevice,&selectedCom);
}
  