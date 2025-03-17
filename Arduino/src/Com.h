#ifndef COM_H
#define COM_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include "Global.h"

/*---------------------------- Classe Comunication ----------------------------*/

struct MyJson
{
    String key;
    String message;
    MyJson(const String& k = "", const String& m = "") : key(k), message(m) {}
};


class Com {
    public:
        Com();
        virtual~Com();
        virtual bool envoyerMessage(const MyJson &json)=0;
        virtual MyJson lireMessage()=0;
};

#endif // COM_H