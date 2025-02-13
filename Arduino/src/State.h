#ifndef STATE_H
#define STATE_H

#include <Arduino.h>
#include "Com.h"
#include "Global.h"

/*------------------------------ Constantes ---------------------------------*/
static constexpr int bt = 8;
static constexpr int ai = 2;
static constexpr int diPins[bt] = {22, 24, 23, 9, 8, 7, 6, 5};
static constexpr const char* diName[] = {"Bouton1", "Bouton2", "Bouton3", "Bouton4","Bouton5", "Bouton6", "Bouton7", "Bouton8"};
static int constexpr aiPins[5]= {0, 1, 3, 4, 5};
static constexpr const char* aiName[] = {"Accelerometre", "Joystick"};
static constexpr const char* change[] = {"Appuye", "Relacher","Bouger","Erreur"};
static constexpr const char* axe[] = {"X:", "Y:","Z:"};
static constexpr short defaultValueAcc[3] = {412,335,340};
static constexpr short defaultValueJoy[2] = {500,500};
static constexpr short timerFilter=100;//temps de filtre pour ne pas faire de fausse detection

enum{
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
    private:
        int diState[bt] = {INIT, INIT, INIT, INIT, INIT, INIT, INIT, INIT};
        int aiState[ai]={INIT,INIT};
        unsigned long timer=0;//pour get le temps du dernier scan
        bool returned[2]{true,true};

        int* GetStateDI();
        void UpdateStateDI();
        int* GetStateAI();
        void UpdateStateAI();
};

#endif // STATE_H