#include "ComClavier.h"
#include <CONST.h>
#include <iostream>
#include <string>
#include <json.hpp>
#include <conio.h> // Pour _kbhit() et _getch()

bool ComClavier::recevoirMessage(std::string& msg) {
    // Création du JSON avec la clé "btnRouge" et la valeur entrée
    nlohmann::json jsonMessage;

    if (_kbhit()) {  // Vérifie si une touche est pressée sans bloquer l'exécution
        char valeur = _getch();  // Récupère la touche sans bloquer

        // Traitement de la touche pressée
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

        msg = jsonMessage.dump();  // La méthode dump() convertit le JSON en une chaîne de caractères
        return true;  // Retourne true si une touche a été pressée et traitée
    }

    return false;  // Retourne false si aucune touche n'a été pressée
}
