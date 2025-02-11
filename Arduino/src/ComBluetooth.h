#ifndef COM_BLUETOOTH_H
#define COM_BLUETOOTH_H

#include <Com.h>

/*---------------------------- Classe ComBluetooth ----------------------------*/
class ComBluetooth:public Com{
    public:
        ComBluetooth(long baudRate=9600);//9600 le baudRate par défaut a voir si on garde ca
        ~ComBluetooth();//9600 le baudRate par défaut a voir si on garde ca
        bool envoyerMessageString(const String &key, const String &message) override;
        bool envoyerMessage(int potValue) override;
        bool lireMessage(int &ledState) override;

    private:
        const int bluetoothTx = 11;  // TX HC-05 -> RX Arduino ##pin arduino à redéfinir
        const int bluetoothRx = 10;  // RX HC-05 -> TX Arduino ##pin arduino à redéfinir
        SoftwareSerial bluetooth;

};

#endif // COM_BLUETOOTH_H