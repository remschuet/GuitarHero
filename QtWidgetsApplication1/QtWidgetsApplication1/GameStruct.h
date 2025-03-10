#pragma once
#include "Joueur.h"
#include <iostream>
#include "Chanson.h"

struct GameStruct {
	Joueur* joueur = nullptr;
	int score = 0;
	Chanson* chansonEnCours = nullptr;
};