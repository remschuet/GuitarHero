#include "ComClavier.h"

bool ComClavier::recevoirMessage(std::string& msg)
{
    // Lecture du message via cin
    std::string valeur;
    std::cin >> valeur;

    // Cr�ation du JSON avec la cl� "btnRouge" et la valeur entr�e
    nlohmann::json jsonMessage;

    if (valeur == "1") {
        valeur = "released";
    }

    jsonMessage["btnRouge"] = valeur;  // Ajoute la valeur entr�e sous la cl� "btnRouge"
    msg = jsonMessage.dump();  // La m�thode dump() convertit le JSON en une cha�ne de caract�res

    return true;
}
