#ifndef COM_H
#define COM_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

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
        virtual bool envoyerMessageString(const MyJson &json)=0;
        virtual bool envoyerMessage(int potValue)=0;
        virtual MyJson lireMessage()=0;
};

#endif // COM_H