#pragma once

#include <windows.h>
#include <iostream>
#include "ComArduino.h"
/* CLASSE GESTION DE COMMUNICATION PAR BLUETOOTH
* Il faut activer le bluetooth � l'arduino
* Il faut d�j� �tre connecter par bluetooth au arduino
* Il faut v�rfier que la connection au HC-05 est stable
* Si une chose n'est pas ok, c'est inutile de tester ce module
* 
* CETTE CLASSE DOIT H�RITER DE ComArduino ET RESPECTER SON H�RITAGE
* 
*/

class ComBluetooth {
private:
    HANDLE hSerial;
    std::string portName;

public:
    ComBluetooth(const std::string& port) : portName(port), hSerial(INVALID_HANDLE_VALUE) {}

    bool ouvrirPort() {
        hSerial = CreateFileA(portName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
        if (hSerial == INVALID_HANDLE_VALUE) {
            std::cerr << "Erreur lors de l'ouverture du port " << portName << std::endl;
            exit(1); // crash le programme
            return false;
        }
        return configurerPort();
    }

    bool configurerPort() {
        DCB dcbSerialParams = { 0 };
        dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
        if (!GetCommState(hSerial, &dcbSerialParams)) {
            std::cerr << "Erreur lors de la r�cup�ration des param�tres du port." << std::endl;
            fermerPort();
            return false;
        }

        dcbSerialParams.BaudRate = CBR_9600;
        dcbSerialParams.ByteSize = 8;
        dcbSerialParams.StopBits = ONESTOPBIT;
        dcbSerialParams.Parity = NOPARITY;

        if (!SetCommState(hSerial, &dcbSerialParams)) {
            std::cerr << "Erreur lors de la configuration du port." << std::endl;
            fermerPort();
            return false;
        }
        return true;
    }

    bool envoyerMessage(const std::string& message) {
        if (hSerial == INVALID_HANDLE_VALUE) {
            std::cerr << "Le port n'est pas ouvert." << std::endl;
            return false;
        }
        DWORD bytesWritten;
        if (!WriteFile(hSerial, message.c_str(), message.size(), &bytesWritten, NULL)) {
            std::cerr << "Erreur lors de l'�criture sur le port s�rie." << std::endl;
            return false;
        }
        return true;
    }

    bool lireMessage(std::string& message) {
        /*  EXEMPLE UTILISATION
            std::string message;
            if (bluetooth.lireMessage(message)) {
                std::cout << "Message re�u : " << message << std::endl;
            }
        */
        if (hSerial == INVALID_HANDLE_VALUE) {
            std::cerr << "Le port n'est pas ouvert." << std::endl;
            return false;
        }

        char buffer[128];
        DWORD bytesRead;

        if (!ReadFile(hSerial, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
            std::cerr << "Erreur lors de la lecture du port s�rie." << std::endl;
            return false;
        }

        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';
            message = std::string(buffer);
            return true;
        }

        return false;
    }

    void fermerPort() {
        if (hSerial != INVALID_HANDLE_VALUE) {
            CloseHandle(hSerial);
            hSerial = INVALID_HANDLE_VALUE;
        }
    }

    ~ComBluetooth() {
        fermerPort();
    }
};

/*
* OPTIMISATION PLUS TARD POSSIBLE MAIS RISQU�
*
bool attendreMessage(int timeoutMs) {
    if (hSerial == INVALID_HANDLE_VALUE) return false;

    COMMTIMEOUTS timeouts = { 0 };
    timeouts.ReadIntervalTimeout = MAXDWORD;
    timeouts.ReadTotalTimeoutConstant = timeoutMs;
    timeouts.ReadTotalTimeoutMultiplier = 0;
    SetCommTimeouts(hSerial, &timeouts);

    char buffer[128];
    DWORD bytesRead;
    return ReadFile(hSerial, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0;
}

*/