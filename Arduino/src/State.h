#ifndef STATE_H
#define STATE_H

#include <Arduino.h>
#include "Com.h"

static constexpr int bt = 8;
static constexpr int ai = 2;
static constexpr int diPins[bt] = {12, 11, 10, 9, 8, 7, 6, 5};
static constexpr const char* diName[] = {"Bouton1", "Bouton2", "Bouton3", "Bouton4","Bouton5", "Bouton6", "Bouton7", "Bouton8"};
static int constexpr aiPins[5]= {0, 1, 3, 4, 5};
static constexpr const char* aiName[] = {"Accelerometre", "Joystick"};
static constexpr const char* change[] = {"Appuye", "Relacher","Erreur"};
static constexpr const char* axe[] = {"X:", "Y:","Z:"};

/*enum{
    AucunChangement,
    Appuye,
    Relache,
    Bouger,
    Erreur
};
*/
enum{
    OFF,
    ON,
    ERROR,
    INIT
};

struct StateAI
{
    int AccX;
    int AccY;
    int AccZ;
    int JoystickH;
    int JoystickV;
};


/*---------------------------- Classe State ----------------------------*/
class State {
    public:
        State();
        ~State();
        
        void GetState(Com* comDevice);
        void GetChange(Com* comDevice);
        void UpdateState();
    private:
        int diState[bt] = {INIT, INIT, INIT, INIT, INIT, INIT, INIT, INIT};
        int aiState[ai]={INIT,INIT};

        //StateAI AI;
        int* GetStateDI();
        void UpdateStateDI();
        int* GetStateAI();
        void UpdateStateAI();
};

#endif // STATE_H