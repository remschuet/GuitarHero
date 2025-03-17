#include "ComBluetooth.h"

/*---------------------------- Classe ComBluetooth ----------------------------*/
ComBluetooth::ComBluetooth(long baudRate)//9600 le baudRate par défaut a voir si on garde ca
{
    Serial1.begin(baudRate);
}

ComBluetooth::~ComBluetooth()
{
    Serial1.end();
}

bool ComBluetooth::envoyerMessage(const MyJson &json)
{
    StaticJsonDocument<500> doc;
    //doc["time"] = millis();
    doc[json.key] = json.message;
    serializeJson(doc, Serial1);
    Serial1.println();
    delay(10); // TODO : ATTENTION MAIS NE PAS DESCENDRE EN DESSOUS DE 50 mili
    return true;
}

MyJson ComBluetooth::lireMessage()
{
    MyJson json;
    StaticJsonDocument<500> doc;
    String jsonMessage = "";
    // Lire les données du port Bluetooth
    if (Serial1.available()) {
        jsonMessage = Serial1.readString();  // Lire le message Bluetooth
    } else {
        return json;  // Si aucune donnée reçue, on retourne un objet vide
    }

    // Désérialisation du JSON
    DeserializationError error = deserializeJson(doc, jsonMessage);
    if (error)
    {
        Serial1.print("❌ Erreur de parsing JSON : ");
        Serial1.println(error.c_str());
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
    bluetooth.print("📥 Clé reçue : ");
    bluetooth.println(json.key);
    bluetooth.print("📥 Valeur reçue : ");
    bluetooth.println(json.message);
*/
    return json;
}
