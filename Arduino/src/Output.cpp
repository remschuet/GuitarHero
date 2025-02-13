#include "Output.h"

/*---------------------------- Classe Output ----------------------------*/
Output::Output(){}
Output::~Output(){}

void Output::Set(const String &key, const String &message)
{
    if (key=="LCD")
    {
        SetLCD(message);
    }
    else if (key=="BarreGraph")
    {
        int i=0;
        bool led[bg];
        for(i=0;i<bg;i++)
        {
            if (message[i]=='1')
            {
                led[i]=1;
            }
            else if (message[i]=='0')
            {
                led[i]=0;
            }
            else
            {
                errorLogger.AddError("Message invalide"+message+"BG index "+String(i),3);
                led[i]=0;
            }
        }
        SetBarreGraph(led);
    }
    else
    {
        errorLogger.AddError("Cle invalide"+message,3);
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
