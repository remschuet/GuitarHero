#ifndef COM_FILAIRE_H
#define COM_FILAIRE_H

#include <iostream>
#include <string>
#include "SerialPort.h"
#include "json.hpp"

using json = nlohmann::json;

class ComFilaire {
private:
    SerialPort* arduino;
    const int baudRate;
    const int msgMaxSize = 1024;

public:
    ComFilaire(const std::string& port, int baud = 115200, int msgSize = 1024)
        : baudRate(baud), msgMaxSize(msgSize) {
        arduino = new SerialPort(port.c_str(), baudRate);
        if (!arduino->isConnected()) {
            throw std::runtime_error("Impossible de se connecter au port " + port);
        }
        else {
            std::cout << "Connection r�ussite port: " << port << std::endl;
        }
    }

    ~ComFilaire() {
        delete arduino;
    }

    bool envoyerMessage(const json& j_msg) {
        std::string msg = j_msg.dump();
        return arduino->writeSerialPort(msg.c_str(), msg.length());
    }

    bool recevoirMessage(std::string& msg) {
        char charBuffer[1024];
        int bufferSize = arduino->readSerialPort(charBuffer, msgMaxSize);
        if (bufferSize > 0) {
            msg.assign(charBuffer, bufferSize);

            // V�rifier si on a re�u une ligne compl�te
            size_t pos = msg.find('\n');
            if (pos != std::string::npos) {
                msg = msg.substr(0, pos);  // Supprime tout apr�s le '\n'
                return true;
            }
        }
        return false;
    }
};

#endif // COM_FILAIRE_H