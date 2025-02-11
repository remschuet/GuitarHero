#include "ComFilaire.h"

ComFilaire::ComFilaire(long baudRate)//9600 le baudRate par défaut a voir si on garde ca
{
    Serial.begin(baudRate);
}

ComFilaire::~ComFilaire()
{
}

bool ComFilaire::envoyerMessageString(const String &key, const String &message) {
    StaticJsonDocument<500> doc;
    doc["time"] = millis();
    doc[key] = message;
    serializeJson(doc, Serial);
    Serial.println();
    delay(1000); // TODO : ATTENTION MAIS NE PAS DESCENDRE EN DESSOUS DE 50 mili
    return true;
}

bool ComFilaire::envoyerMessage(int potValue) {
    StaticJsonDocument<500> doc;
    doc["time"] = millis();
    doc["analog"] = potValue;
    serializeJson(doc, Serial);
    Serial.println();
    return true;
}

bool ComFilaire::lireMessage(int &ledState) {
    if (Serial.available()) {
        StaticJsonDocument<500> doc;
        DeserializationError error = deserializeJson(doc, Serial);
        
        if (error) {
            Serial.print("Erreur JSON: ");
            Serial.println(error.c_str());
            return false;
        }
        
        if (doc.containsKey("led")) {
            ledState = doc["led"].as<bool>();
            return true;
        }
    }
    return false;
}