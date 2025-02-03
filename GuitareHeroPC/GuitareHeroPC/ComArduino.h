#pragma once
#include <iostream>
#include <string>
#include "SerialPort.h"
#include "json.hpp"

using json = nlohmann::json;

class ComArduino {
    virtual bool envoyerMessage(const json& j_msg) = 0;
    virtual bool recevoirMessage(std::string& msg) = 0;
};

