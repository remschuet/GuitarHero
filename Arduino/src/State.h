#ifndef STATE_H
#define STATE_H

#include <Arduino.h>
#include "Com.h"
#include "Global.h"

/*------------------------------ Constantes ---------------------------------*/
static constexpr int bt = 8;
static constexpr int ai = 5;
static constexpr int diPins[bt] = {12, 11, 10, 9, 8, 7, 6, 5};
static constexpr const char* diName[] = {"BtRouge", "BtBleu", "BtVert", "BtJaune","BMauve", "Bouton6", "Bouton7", "Bouton8"};
static int constexpr aiPins[5]= {0, 1, 3, 4, 5};
static constexpr const char* aiName[] = {"Accelerometre", "Joystick"};
static constexpr const char* change[] = {"Relache", "Appuye","Bouge","Erreur"};
static constexpr const char* axe[] = {"X:", "Y:","Z:"};
static constexpr short timerFilterGen=100;//temps de filtre pour ne pas faire de fausse detection
static constexpr short timerFilterJoy=500;
static constexpr short timerFilterAcc=500;

enum Position{
    OFF,
    ON,
    ERROR,
    INIT
};

/*---------------------------- Classe State ----------------------------*/
class State {
    public:
        State();
        ~State();
        
        void GetState(Com* comDevice);
        void GetChange(Com* comDevice);
        void UpdateState();
        void SetDefault();
    private:
        short diState[bt] = {INIT, INIT, INIT, INIT, INIT, INIT, INIT, INIT};
        int aiState[ai]={INIT,INIT,INIT,INIT,INIT};
        int defaultValueAI[5];
        unsigned long timer=0;//pour get le temps du dernier scan
        unsigned long timerAcc=0;
        unsigned long timerJoy=0;
        bool returned=true;

        int* GetStateDI();
        void UpdateStateDI();
        int* GetStateAI();
        void UpdateStateAI();
};

#endif // STATE_H