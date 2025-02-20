#ifndef COM_FILAIRE_H
#define COM_FILAIRE_H

#include <Com.h>
#include "Global.h"

/*---------------------------- Classe ComFilaire ----------------------------*/
class ComFilaire:public Com {
    public:
        ComFilaire(long baudRate=9600);//9600 le baudRate par défaut a voir si on garde ca
        ~ComFilaire();//9600 le baudRate par défaut a voir si on garde ca
        bool envoyerMessageString(const MyJson &json) override;
        bool envoyerMessage(int potValue) override;
        MyJson lireMessage() override;
};

#endif // COM_FILAIRE_H