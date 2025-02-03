#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11); // RX, TX (Brancher TX HC-05 sur 10, RX HC-05 sur 11)

void setup() {
    Serial.begin(9600);   // Moniteur Série (PC)
    BT.begin(38400);      // Baudrate par défaut du mode AT du HC-05

    Serial.println("Envoi de la commande AT+ROLE=1...");
    // BT.println("AT+ROLE=1");  // Changer en mode maître
    delay(1000);
    
    Serial.println("Vérification du mode...");
    // BT.println("AT+ROLE?"); // Vérifier si le mode a changé
}

void loop() {
    if (BT.available()) {
        Serial.write(BT.read());  // Affiche la réponse du HC-05 dans le moniteur série
    }
    if (Serial.available()) {
        BT.write(Serial.read());  // Permet d'envoyer des commandes AT manuellement
    }
}
