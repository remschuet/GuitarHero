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
