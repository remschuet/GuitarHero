#include "ComClavier.h"
#include <CONST.h>
#include <iostream>
#include <string>
#include <json.hpp>
#include <conio.h> // Pour _kbhit() et _getch()

bool ComClavier::recevoirMessage(std::string& msg) {
    // Cr�ation du JSON avec la cl� "btnRouge" et la valeur entr�e
    nlohmann::json jsonMessage;

    if (_kbhit()) {  // V�rifie si une touche est press�e sans bloquer l'ex�cution
        char valeur = _getch();  // R�cup�re la touche sans bloquer

        // Traitement de la touche press�e
        if (valeur == '1')
            jsonMessage[BTN_ROUGE] = BTN_RELACHE;
        else if (valeur == '2')
            jsonMessage[BTN_BLEU] = BTN_RELACHE;
        else if (valeur == '3')
            jsonMessage[BTN_VERT] = BTN_RELACHE;
        else if (valeur == '4')
            jsonMessage[BTN_JAUNE] = BTN_RELACHE;
        else if (valeur == '5')
            jsonMessage[BTN_MAUVE] = BTN_RELACHE;

        msg = jsonMessage.dump();  // La m�thode dump() convertit le JSON en une cha�ne de caract�res
        return true;  // Retourne true si une touche a �t� press�e et trait�e
    }

    return false;  // Retourne false si aucune touche n'a �t� press�e
}


/*
#include "ComClavier.h"
#include <CONST.h>
#include <iostream>
#include <string>
#include <json.hpp>
#include <conio.h>
#include <unordered_map>

std::unordered_map<char, bool> touchesActives;  // �tat des touches

bool ComClavier::recevoirMessage(std::string& msg) {
    nlohmann::json jsonMessage;

    while (_kbhit()) {  // V�rifie s'il y a des touches press�es
        char valeur = _getch();  // R�cup�re la touche

        // V�rifie si c'est une touche de note
        if (valeur >= '1' && valeur <= '5') {
            if (touchesActives[valeur] == false) {
                // Si elle n'�tait pas press�e avant, c'est un appui
                jsonMessage[valeur] = BTN_APPUYE;
                touchesActives[valeur] = true;
            }
        }
    }

    // V�rifie si une touche a �t� rel�ch�e
    for (auto& [touche, etat] : touchesActives) {
        if (etat && !_kbhit()) {  // Si elle �tait press�e mais qu'aucune touche n'est actuellement d�tect�e
            jsonMessage[touche] = BTN_RELACHE;
            etat = false;  // R�initialise l'�tat
        }
    }

    if (!jsonMessage.empty()) {
        msg = jsonMessage.dump();
        return true;
    }

    return false;
}



*/