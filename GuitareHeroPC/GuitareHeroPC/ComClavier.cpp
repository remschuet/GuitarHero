#include "ComClavier.h"
#include <CONST.h>

bool ComClavier::recevoirMessage(std::string& msg)
{
    // Lecture du message via cin
    std::string valeur;
    std::cin >> valeur;

    // Cr�ation du JSON avec la cl� "btnRouge" et la valeur entr�e
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

    msg = jsonMessage.dump();  // La m�thode dump() convertit le JSON en une cha�ne de caract�res

    return true;
}
