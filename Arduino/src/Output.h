#ifndef OUTPUT_H
#define OUTPUT_H

#include <Arduino.h>
#include "Com.h"
#include "Global.h"
#include <Wire.h>

static constexpr int bg=10;
static constexpr int bgPins[bg] = {44, 46,48,50,52,45,47,49,51,53};
static constexpr int mot=2;
static constexpr int motPins[mot] = {43, 34};

/*---------------------------- Classe Output ----------------------------*/
class Output {
    public:
        Output();
        ~Output();
        void Set(Com* comDevice,com* selectedCom);
    private:
        void SetBarreGraph(bool led[bg]);
        void SetLCD(String message);
        void SetMoteur(bool motVibrant[mot]);
        void SetCom(String message,com* selectedCom);
};

#endif // OUTPUT_H