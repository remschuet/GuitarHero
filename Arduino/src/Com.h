#ifndef COM_H
#define COM_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

/*---------------------------- Classe ComBluetooth ----------------------------*/
class Com {
    public:
        Com();
        virtual~Com();
        virtual bool envoyerMessageString(const String &key, const String &message)=0;
        virtual bool envoyerMessage(int potValue)=0;
        virtual bool lireMessage(int &ledState);
};

#endif // COM_H