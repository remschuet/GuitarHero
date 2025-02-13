#include "ComBluetooth.h"

/*---------------------------- Classe ComBluetooth ----------------------------*/
    ComBluetooth::ComBluetooth(long baudRate)//9600 le baudRate par défaut a voir si on garde ca
        : bluetooth(bluetoothRx, bluetoothTx)
    {
        bluetooth.begin(baudRate);
    }

    ComBluetooth::~ComBluetooth()
    {
    }

    bool ComBluetooth::envoyerMessageString(const String &key, const String &message)
    {
        StaticJsonDocument<500> doc;
        doc["time"] = millis();
        doc[key] = message;
        serializeJson(doc, bluetooth);
        bluetooth.println();
        delay(100); // TODO : ATTENTION MAIS NE PAS DESCENDRE EN DESSOUS DE 50 mili
        return true;
    }

    bool ComBluetooth::envoyerMessage(int potValue) 
    {
        StaticJsonDocument<500> doc;
        doc["time"] = millis();
        doc["analog"] = potValue;
        serializeJson(doc, Serial);
        bluetooth.println();
        return true;
    }

    bool ComBluetooth::lireMessage(int &ledState) 
    {
      if (bluetooth.available()) {
            StaticJsonDocument<500> doc;
            DeserializationError error = deserializeJson(doc, bluetooth);
            
            if (error) {
                bluetooth.print("Erreur JSON: ");
                bluetooth.println(error.c_str());
                return false;
            }
            
            if (doc.containsKey("led")) {
                ledState = doc["led"].as<bool>();
                return true;
            }
        }
        errorLogger.AddError("Erreur Lire Message Bluetooth",1);
        return false;
    }
