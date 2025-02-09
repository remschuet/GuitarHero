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


/*
#include "ComClavier.h"
#include <CONST.h>
#include <iostream>
#include <string>
#include <json.hpp>
#include <conio.h>
#include <unordered_map>

std::unordered_map<char, bool> touchesActives;  // État des touches

bool ComClavier::recevoirMessage(std::string& msg) {
    nlohmann::json jsonMessage;

    while (_kbhit()) {  // Vérifie s'il y a des touches pressées
        char valeur = _getch();  // Récupère la touche

        // Vérifie si c'est une touche de note
        if (valeur >= '1' && valeur <= '5') {
            if (touchesActives[valeur] == false) {
                // Si elle n'était pas pressée avant, c'est un appui
                jsonMessage[valeur] = BTN_APPUYE;
                touchesActives[valeur] = true;
            }
        }
    }

    // Vérifie si une touche a été relâchée
    for (auto& [touche, etat] : touchesActives) {
        if (etat && !_kbhit()) {  // Si elle était pressée mais qu'aucune touche n'est actuellement détectée
            jsonMessage[touche] = BTN_RELACHE;
            etat = false;  // Réinitialise l'état
        }
    }

    if (!jsonMessage.empty()) {
        msg = jsonMessage.dump();
        return true;
    }

    return false;
}



*/