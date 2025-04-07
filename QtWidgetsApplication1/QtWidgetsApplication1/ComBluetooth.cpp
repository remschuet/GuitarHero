// ComBluetooth.cpp
#include "ComBluetooth.h"

ComBluetooth::ComBluetooth(const std::string& port) : portName(port), hSerial(INVALID_HANDLE_VALUE) {
    ouvrirPort();
}

ComBluetooth::~ComBluetooth() {
    fermerPort();
}

bool ComBluetooth::ouvrirPort() {
    hSerial = CreateFileA(portName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Erreur lors de l'ouverture du port " << portName << std::endl;
        return false;
    }
    return configurerPort();
}

void ComBluetooth::fermerPort() {
    if (hSerial != INVALID_HANDLE_VALUE) {
        CloseHandle(hSerial);
        hSerial = INVALID_HANDLE_VALUE;
    }
}

bool ComBluetooth::configurerPort() {
    if (hSerial == INVALID_HANDLE_VALUE) return false;

    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Erreur lors de la récupération des paramètres du port." << std::endl;
        fermerPort();
        return false;
    }

    dcbSerialParams.BaudRate = CBR_115200;
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

bool ComBluetooth::envoyerMessage(const json& j_msg) {
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Le port n'est pas ouvert envoyer." << std::endl;
        return false;
    }

    std::string message = j_msg.dump() + "\n"; // Convertir le JSON en string avec un saut de ligne
    DWORD bytesWritten;
    if (!WriteFile(hSerial, message.c_str(), message.size(), &bytesWritten, NULL)) {
        std::cerr << "Erreur lors de l'écriture sur le port série." << std::endl;
        return false;
    }
    return true;
}

bool ComBluetooth::recevoirMessage(std::string& msg) {
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Le port n'est pas ouvert." << std::endl;
        return false;
    }

    DWORD errors;
    COMSTAT status;
    ClearCommError(hSerial, &errors, &status);

    if (status.cbInQue > 0) {
        char charBuffer[1024];
        DWORD bytesRead;
        if (ReadFile(hSerial, charBuffer, sizeof(charBuffer) - 1, &bytesRead, NULL)) {
            if (bytesRead > 0) {
                msg.assign(charBuffer, bytesRead);
                size_t pos = msg.find('\n');
                if (pos != std::string::npos) {
                    msg = msg.substr(0, pos);
                    return true;
                }
            }
        }
        else {
            std::cerr << "Erreur lors de la lecture du port série." << std::endl;
        }
    }
    return false;
}

void ComBluetooth::fushPopre()
{
    fermerPort();
}
