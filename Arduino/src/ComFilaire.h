#ifndef COM_FILAIRE_H
#define COM_FILAIRE_H

#include <Arduino.h>
#include <ArduinoJson.h>

/*---------------------------- Classe ComFilaire ----------------------------*/
class ComFilaire {
public:
    ComFilaire(long baudRate) {
        Serial.begin(baudRate);
    }

    void envoyerMessageString(const String &key, const String &message) {
        StaticJsonDocument<500> doc;
        doc["time"] = millis();
        doc[key] = message;
        serializeJson(doc, Serial);
        Serial.println();
        delay(1000); // TODO : ATTENTION MAIS NE PAS DESCENDRE EN DESSOUS DE 50 mili
    }

    void envoyerMessage(int potValue) {
        StaticJsonDocument<500> doc;
        doc["time"] = millis();
        doc["analog"] = potValue;
        serializeJson(doc, Serial);
        Serial.println();
    }

    bool lireMessage(int &ledState) {
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
};

#endif // COM_FILAIRE_H