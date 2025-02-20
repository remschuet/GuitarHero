#include "ComFilaire.h"

/*---------------------------- Classe ComFilaire ----------------------------*/
ComFilaire::ComFilaire(long baudRate)//9600 le baudRate par défaut a voir si on garde ca
{
    Serial.begin(9600);
}

ComFilaire::~ComFilaire()
{
}

bool ComFilaire::envoyerMessageString(const MyJson &json) 
{
    StaticJsonDocument<500> doc;
    doc["time"] = millis();
    doc[json.key] = json.message;
    serializeJson(doc, Serial);
    Serial.println();
    delay(10);
    return true;
}

bool ComFilaire::envoyerMessage(int potValue) 
{
    StaticJsonDocument<500> doc;
    doc["time"] = millis();
    doc["analog"] = potValue;
    serializeJson(doc, Serial);
    Serial.println();
    return true;
}

MyJson ComFilaire::lireMessage()
{
    MyJson json;
    if (Serial.available())
    {
        StaticJsonDocument<500> doc;
        DeserializationError error = deserializeJson(doc, Serial);
        
        if (error)
        {
            errorLogger.AddError("Erreur Filaire msg ERROR",1);
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
        errorLogger.AddError("Erreur Filaire non-dispo",1);
    }
    return json;
}