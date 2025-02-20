#include "Output.h"

/*---------------------------- Classe Output ----------------------------*/
Output::Output(){}
Output::~Output(){}

void Output::Set(Com* comDevice)
{
    MyJson json=comDevice->lireMessage();

    if (json.key=="LCD")
    {
        SetLCD(json.message);
    }
    else if (json.key=="BarreGraph")
    {
        int i=0;
        bool led[bg];
        for(i=0;i<bg;i++)
        {
            if (json.message[i]=='1')
            {
                led[i]=1;
            }
            else if (json.message[i]=='0')
            {
                led[i]=0;
            }
            else
            {
                errorLogger.AddError("Message invalide"+json.message+"BG index "+String(i),3);
                led[i]=0;
            }
        }
        SetBarreGraph(led);
    }
    else
    {
        errorLogger.AddError("Cle invalide"+json.message,3);
    }
    
}
void Output::SetLCD(String message)
{
    ////////a coder////////
}
void Output:: SetBarreGraph(bool led[])
{
    int i=0;
    for (i = 0; i < bg; i++)
    {
        digitalWrite(bgPins[i],led[i]);
    }
}
