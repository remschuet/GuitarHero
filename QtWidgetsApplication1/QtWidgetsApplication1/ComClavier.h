#pragma once

#include "ComArduino.h"
#include "CONST.h"

class ComClavier : public ComArduino {
private:
    std::unordered_map<std::string, bool> etatBoutons = {
    {BTN_ROUGE, false}, {BTN_BLEU, false}, {BTN_VERT, false},
    {BTN_JAUNE, false}, {BTN_MAUVE, false}
    };

    std::unordered_map<char, bool> toucheEnfoncee;  // Empêche la répétition

public:
    bool envoyerMessage(const json& j_msg) override { std::cerr << "NON IMPLEMENTER"; return false; };
    bool recevoirMessage(std::string& msg) override;
};

