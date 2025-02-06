#pragma once

#include "ComArduino.h"

class ComClavier : public ComArduino {
private:

public:
    bool envoyerMessage(const json& j_msg) override { std::cerr << "NON IMPLEMENTER"; return false; };
    bool recevoirMessage(std::string& msg) override;
};

