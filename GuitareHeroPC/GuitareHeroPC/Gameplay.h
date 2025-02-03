#pragma once
#include <iostream>
#include "ComBluetooth.h"
#include "ComFilaire.h"
#include "Joueur.h"

class Gameplay
{
public:
	Gameplay(std::string comPort = "COM5", bool bluetooth = true, bool verbose = false, bool admin = false);
	void gotoxy(int x, int y);
	void loopGame();
	void loopMenu();

	void voirMeilleurScore();

	bool configBluetooth(std::string nomPort);
	bool configFilaire(std::string nomPort);
	void interpreterMsg(std::string);

private:
	ComBluetooth* comBluetooth;
	ComFilaire* comFilaire;
	bool estBluetooth;
	bool verbose;
	bool admin;
	Joueur* joueur;
};