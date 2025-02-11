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
        
        else if (valeur == 'q')
            jsonMessage[BTN_QUITTER] = BTN_RELACHE;

        msg = jsonMessage.dump();  // La m�thode dump() convertit le JSON en une cha�ne de caract�res
        return true;  // Retourne true si une touche a �t� press�e et trait�e
    }

    return false;  // Retourne false si aucune touche n'a �t� press�e
}




/*
bool ComClavier::recevoirMessage(std::string& msg) {
    nlohmann::json jsonMessage;
    bool modification = false;

    std::unordered_map<char, std::string> correspondance = {
        {'1', BTN_ROUGE}, {'2', BTN_BLEU}, {'3', BTN_VERT},
        {'4', BTN_JAUNE}, {'5', BTN_MAUVE}
    };

    char valeur = 0;  // Initialisation pour �viter une variable non d�finie

    if (_kbhit()) {
        valeur = _getch();

        if (correspondance.find(valeur) != correspondance.end()) {
            std::string bouton = correspondance[valeur];

            // V�rifie si la touche �tait d�j� enfonc�e
            if (!toucheEnfoncee[valeur]) {
                etatBoutons[bouton] = true;  // Passe en mode APPUY�
                jsonMessage[bouton] = BTN_APPUYE;
                modification = true;
            }

            toucheEnfoncee[valeur] = true;  // Marque la touche comme enfonc�e
        }
    }

    // V�rifier les touches qui ne sont plus d�tect�es et les passer en mode rel�ch�
    for (auto it = toucheEnfoncee.begin(); it != toucheEnfoncee.end(); ) {
        char touche = it->first;
        if (!(_kbhit() && _getch() == touche)) {  // V�rifie si la touche n'est plus press�e
            std::string bouton = correspondance[touche];
            jsonMessage[bouton] = BTN_RELACHE;
            etatBoutons[bouton] = false;
            it = toucheEnfoncee.erase(it);  // Supprime la touche de la map
            modification = true;
        }
        else {
            ++it;
        }
    }

    if (modification) {
        msg = jsonMessage.dump();
        return true;
    }

    return false;
}
*/