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

    bool ComBluetooth::envoyerMessageString(const MyJson &json)
    {
        StaticJsonDocument<500> doc;
        doc["time"] = millis();
        doc[json.key] = json.message;
        serializeJson(doc, bluetooth);
        bluetooth.println();
        delay(10); // TODO : ATTENTION MAIS NE PAS DESCENDRE EN DESSOUS DE 50 mili
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

    MyJson ComBluetooth::lireMessage()
    {
        MyJson json;
        if (bluetooth.available())
        {
            StaticJsonDocument<500> doc;
            DeserializationError error = deserializeJson(doc, bluetooth);
            
            if (error)
            {
                //bluetooth.println(error.c_str());
                errorLogger.AddError("Erreur Btooth msg ERROR",1);
            }
            else
            {
                for (JsonPair kv : doc.as<JsonObject>())
                {
                    json.key = kv.key().c_str(); // Stocker la clé
                    json.message = kv.value().as<String>(); // Stocker la valeur comme String
                    break; // Supposer que nous voulons seulement la première paire clé-valeur
                }
            }
        }
        else
        {
            errorLogger.AddError("Erreur Btooth non-dispo",1);
        }
        return json;
    }
