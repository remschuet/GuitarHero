#include "ComClavier.h"
#include <CONST.h>

bool ComClavier::recevoirMessage(std::string& msg)
{
    // Lecture du message via cin
    std::string valeur;
    std::cin >> valeur;

    // Création du JSON avec la clé "btnRouge" et la valeur entrée
    nlohmann::json jsonMessage;

    if (valeur == "1")
        jsonMessage[BTN_ROUGE] = BTN_RELACHE;
    else if (valeur == "2")
        jsonMessage[BTN_BLEU] = BTN_RELACHE;
    else if (valeur == "3")
        jsonMessage[BTN_VERT] = BTN_RELACHE;
    else if (valeur == "4")
        jsonMessage[BTN_JAUNE] = BTN_RELACHE;
    else if (valeur == "5")
        jsonMessage[BTN_MAUVE] = BTN_RELACHE;

    msg = jsonMessage.dump();  // La méthode dump() convertit le JSON en une chaîne de caractères

    return true;
}
