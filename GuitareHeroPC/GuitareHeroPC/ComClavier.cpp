#include "ComClavier.h"

bool ComClavier::recevoirMessage(std::string& msg)
{
    // Lecture du message via cin
    std::string valeur;
    std::cin >> valeur;

    // Création du JSON avec la clé "btnRouge" et la valeur entrée
    nlohmann::json jsonMessage;

    if (valeur == "1") {
        valeur = "released";
    }

    jsonMessage["btnRouge"] = valeur;  // Ajoute la valeur entrée sous la clé "btnRouge"
    msg = jsonMessage.dump();  // La méthode dump() convertit le JSON en une chaîne de caractères

    return true;
}
