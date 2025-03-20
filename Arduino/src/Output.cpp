#include "Output.h"

/*---------------------------- Classe Output ----------------------------*/
Output::Output()
{
}

Output::~Output()
{
}

void Output::Set(Com* comDevice,com *selectedCom)
{
    int i=0;
    MyJson json=comDevice->lireMessage();

    if (json.key=="LCD")
    {
        SetLCD(json.message);
    }
    else if (json.key=="bG")
    {
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
    else if (json.key=="mot")
    {
        bool motVibrant[mot];
        for(i=0;i<mot;i++)
        {
            if (json.message[i]=='1')
            {
                motVibrant[i]=1;
            }
            else if (json.message[i]=='0')
            {
                motVibrant[i]=0;
            }
            else
            {
                errorLogger.AddError("Message invalide"+json.message+"Mot index "+String(i),3);
                motVibrant[i]=0;
            }
        }
        SetMoteur(motVibrant);
    }
    else if (json.key=="COM")
    {
        SetCom(json.message,selectedCom);
    }
    else
    {
        errorLogger.AddError("Cle invalide"+json.message,3);
    }
    
}
void Output::SetLCD(String message)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(message);
    analogWrite(48,150);
}
void Output:: SetBarreGraph(bool led[])
{
    int i=0;
    for (i = 0; i < bg; i++)
    {
        analogWrite(bgPins[i],led[i]*150);
    }
}
void Output:: SetMoteur(bool motVibrant[])
{
    int i=0;
    for (i = 0; i < mot; i++)
    {
        digitalWrite(motPins[i],motVibrant[i]);
    }
}
void Output::SetCom(String message,com *selectedCom)
{
    if (message=="FILAIRE")
    {
        *selectedCom=FILAIRE;
    }
    else if (message=="BLUETOOTH")
    {
        *selectedCom=BLUETOOTH;
    }
}