#include "State.h"

/*---------------------------- Classe State ----------------------------*/
State::State():timer(millis())
{
    UpdateStateDI();
    UpdateStateAI();
}
State::~State(){}

void State::GetState(Com* comDevice)
{
    int i;
    int* stateTempDI= GetStateDI();
    int* stateTempAI= GetStateAI();
    //Boutons
    for (i=0;i<bt;i++)
    {
        //comDevice->envoyerMessageString(diName[i],String(stateTempDI[i]));
        diState[i]=stateTempDI[i];
    }
    //Joystick
    for (i=0;i<2;i++)
    {
        //comDevice->envoyerMessageString(aiName[1],axe[1-i]+String(stateTempAI[i]));
        aiState[i]=stateTempAI[i];
    }
    //Accelerometre
    for (i=2;i<5;i++)
    {
        comDevice->envoyerMessageString(aiName[0],axe[4-i]+String(stateTempAI[i]));
        //aiState[i]=stateTempAI[i];
    }
    delete[] stateTempDI;
    delete[] stateTempAI;
}
void State::GetChange(Com* comDevice)
{
    int* stateTempDI= GetStateDI();
    int* stateTempAI= GetStateAI();
    bool movedJoy=0;
    bool movedAcc=0;
    int i;

    //Boutons
    if(millis()>timer+timerFilterGen)
    {
        timer=millis();
        for (i=0;i<bt;i++)
        {
            if (diState[i]!= stateTempDI[i])
            {
                if (diState[i]==0)
                {
                    comDevice->envoyerMessageString(diName[i],change[0]);
                }
                else if(diState[i]==1)
                {
                    comDevice->envoyerMessageString(diName[i],change[1]);
                }
                else
                {
                    comDevice->envoyerMessageString(diName[i],change[3]);
                    errorLogger.AddError("Erreur Etat Boutons invalide",2);
                }
                diState[i]=stateTempDI[i];
            }
        }
        //Joystick
        movedJoy=false;
        movedAcc=false;
        for (i=0;i<5;i++)
        {
            if ((stateTempAI[i]< defaultValueAI[i]+50 || stateTempAI[i] > defaultValueAI[i]-50)
                && (i<2))
            {
                returned[i]=1;
            }

            //Joystick
            //doit avoir un mouvement soit en x ou en y et ne pas être au milieu
            if ((aiState[i]>stateTempAI[i]+150 || aiState[i]<stateTempAI[i]-150)
                && (stateTempAI[i] > defaultValueAI[i]+150 || stateTempAI[i] < defaultValueAI[i]-150)
                && (movedJoy==0)
                && (returned[0]==1 && returned[1]==1)
                && (i<2)
                && (timerJoy+timerFilterJoy<=millis()))
            {
                    comDevice->envoyerMessageString(aiName[1],change[2]);
                    movedJoy=1;
                    returned[0]=0;
                    returned[1]=0;
                    timerJoy=millis();
            }

            //Accelerometre
            //doit avoir un mouvement soit en, en y ou en Z
            if ((aiState[i]>defaultValueAI[i]+50 || aiState[i]<defaultValueAI[i]-50)
            && (movedAcc==0)
            && (i>=2)
            && (timerAcc+timerFilterAcc<=millis()))
            {
                comDevice->envoyerMessageString(aiName[0],change[2]);
                movedAcc=1;
                timerAcc=millis();
            }
            aiState[i]=stateTempAI[i];
        }
    }
    delete[] stateTempDI;
    delete[] stateTempAI;
}
void State::UpdateState()
{
    UpdateStateAI();
    UpdateStateDI();
}

int* State:: GetStateDI()
{
    int i;
    int* stateTemp= new int[bt];
    for (i=0;i<bt;i++)
    {
        stateTemp[i]=digitalRead(diPins[i]);
    }
    return stateTemp;
}
int* State:: GetStateAI()
{
    int i;
    int* stateTemp= new int[5];
    for (i=0;i<5;i++)
    {
        stateTemp[i]=analogRead(aiPins[i]);
    }
    return stateTemp;
}

void State:: UpdateStateDI()
{
    int i;
    for (i=0;i<bt;i++)
    {
        diState[i]=digitalRead(diPins[i]);
    }
}
void State:: UpdateStateAI()
{ 
    int i;
    for (i=0;i<5;i++)
    {
        diState[i]=analogRead(aiPins[i]);
    }
}