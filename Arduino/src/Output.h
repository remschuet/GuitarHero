#ifndef OUTPUT_H
#define OUTPUT_H

#include <Arduino.h>
#include "Com.h"
#include "Global.h"

static constexpr int bg=10;
static constexpr int bgPins[bg] = {22, 24, 23, 9, 8, 7, 6, 5};// a changer

/*---------------------------- Classe Output ----------------------------*/
class Output {
    public:
        Output();
        ~Output();
        void Set(Com* comDevice);
    private:
        void SetBarreGraph(bool led[bg]);
        void SetLCD( String message);
};

#endif // OUTPUT_H