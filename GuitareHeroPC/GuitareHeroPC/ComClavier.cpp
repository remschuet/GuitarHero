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
        
        else if (valeur == 'q')
            jsonMessage[BTN_QUITTER] = BTN_RELACHE;

        msg = jsonMessage.dump();  // La méthode dump() convertit le JSON en une chaîne de caractères
        return true;  // Retourne true si une touche a été pressée et traitée
    }

    return false;  // Retourne false si aucune touche n'a été pressée
}




/*
bool ComClavier::recevoirMessage(std::string& msg) {
    nlohmann::json jsonMessage;
    bool modification = false;

    std::unordered_map<char, std::string> correspondance = {
        {'1', BTN_ROUGE}, {'2', BTN_BLEU}, {'3', BTN_VERT},
        {'4', BTN_JAUNE}, {'5', BTN_MAUVE}
    };

    char valeur = 0;  // Initialisation pour éviter une variable non définie

    if (_kbhit()) {
        valeur = _getch();

        if (correspondance.find(valeur) != correspondance.end()) {
            std::string bouton = correspondance[valeur];

            // Vérifie si la touche était déjà enfoncée
            if (!toucheEnfoncee[valeur]) {
                etatBoutons[bouton] = true;  // Passe en mode APPUYÉ
                jsonMessage[bouton] = BTN_APPUYE;
                modification = true;
            }

            toucheEnfoncee[valeur] = true;  // Marque la touche comme enfoncée
        }
    }

    // Vérifier les touches qui ne sont plus détectées et les passer en mode relâché
    for (auto it = toucheEnfoncee.begin(); it != toucheEnfoncee.end(); ) {
        char touche = it->first;
        if (!(_kbhit() && _getch() == touche)) {  // Vérifie si la touche n'est plus pressée
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