#include "ComFilaire.h"

/*---------------------------- Classe ComFilaire ----------------------------*/
ComFilaire::ComFilaire(long baudRate)//9600 le baudRate par défaut a voir si on garde ca
{
    Serial.begin(baudRate);
}

ComFilaire::~ComFilaire()
{
}

bool ComFilaire::envoyerMessage(const MyJson &json) 
{
    StaticJsonDocument<500> doc;
    //doc["time"] = millis();
    doc[json.key] = json.message;
    serializeJson(doc, Serial);
    Serial.println();
    delay(10);
    return true;
}

MyJson ComFilaire::lireMessage()
{
    MyJson json;
    StaticJsonDocument<500> doc;
    String jsonMessage = "";
    // Lire les données du port Bluetooth
    if (Serial.available()) {
        jsonMessage = Serial.readString();  // Lire le message Bluetooth
    } else {
        //Serial.print("YOP");
        return json;  // Si aucune donnée reçue, on retourne un objet vide
    }

    // Désérialisation du JSON
    DeserializationError error = deserializeJson(doc, jsonMessage);
    if (error)
    {
        Serial.print("❌ Erreur de parsing JSON : ");
        Serial.println(error.c_str());
        return json;
    }

    // Récupérer la première clé et sa valeur
    for (JsonPair keyValue : doc.as<JsonObject>())
    {
        json.key = keyValue.key().c_str();  // Stocker la clé
        json.message = keyValue.value().as<String>(); // Stocker la valeur sous forme de String
        break; // Prend seulement la première clé trouvée
    }

/*    // ✅ Afficher la clé et la valeur
    Serial.print("📥 Clé reçue : ");
    Serial.println(json.key);
    Serial.print("📥 Valeur reçue : ");
    Serial.println(json.message);
*/
    return json;
}
