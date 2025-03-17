#ifndef COM_BLUETOOTH_H
#define COM_BLUETOOTH_H

#include <Com.h>

/*---------------------------- Classe ComBluetooth ----------------------------*/
class ComBluetooth:public Com{
    public:
        ComBluetooth(long baudRate=115200);//115200 le baudRate par défaut a voir si on garde ca
        ~ComBluetooth();//9600 le baudRate par défaut a voir si on garde ca
        bool envoyerMessage(const MyJson &json) override;
        MyJson lireMessage() override;

    private:
        const int bluetoothTx = 18;  // TX Arduino -> RX HC-05
        const int bluetoothRx = 19;  // RX Arduino -> TX HC-05

};

#endif // COM_BLUETOOTH_H