#include "State.h"

State::State()
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
    for (i=0;i<bt;i++)
    {
        comDevice->envoyerMessageString(diName[i],String(stateTempDI[i]));
    }
     for (i=0;i<2;i++)
    {
        comDevice->envoyerMessageString(aiName[0],axe[1-i]+String(stateTempAI[i]));
    }
    for (i=2;i<5;i++)
    {
        comDevice->envoyerMessageString(aiName[1],axe[4-i]+String(stateTempAI[i]));
    }
    delete[] stateTempDI;
    delete[] stateTempAI;
}
void State::GetChange(Com* comDevice)

{
    int* stateTempDI= GetStateDI();
    int* stateTempAI= GetStateAI();
    int i;

    //Boutons
    for (i=0;i<bt;i++)
    {
        if (diState[i]!= stateTempDI[i])
        {
            if (diState[i]==0)
            {
                comDevice->envoyerMessageString(diName[i],change[1]);
            }
            else if(diState[i]==1)
            {
                comDevice->envoyerMessageString(diName[i],change[0]);
            }
            else
            {
                comDevice->envoyerMessageString(diName[i],change[3]);
            }
        }
        else
        {
        }
    }
    //Boutons Joystick
     for (i=0;i<2;i++)
    {
        if ((aiState[i]>stateTempAI[i]+500 || aiState[i]<stateTempAI[i]-500) && stateTempAI[i]-500 > 0) //doit avoir un mouvement soit en x ou en y et ne pas être au milieu
        {
                comDevice->envoyerMessageString(aiName[0],change[2]);
                break;
        }
    }
    //Boutons Accelerometre
    for (i=2;i<5;i++)
    {
        if (aiState[i]>stateTempAI[i]+500 || aiState[i]<stateTempAI[i]-500) //doit avoir un mouvement soit en, en y ou en Z
        {
                comDevice->envoyerMessageString(aiName[1],change[2]);
                break;
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