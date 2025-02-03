#pragma once
#include "Joueur.h"
#include <iostream>

struct GameStruct {
	Joueur* joueur;
	std::string chanson = "-1";
	int score = 0;
};