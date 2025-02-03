#pragma once

#include <windows.h>
#include <iostream>
#include <vector>
#include "Note.h"
#include <ctime> 
#include <chrono>

using namespace std;
using namespace std::chrono;

class Chanson
{
private:
	void setUpVecteur(std::vector<Note> vecteur);
	vector<Note> getVecteurNotesEnCours();
	string nomChanson = "";
	float deltaEntreNote = 0;
	vector<Note> vecteurRouge;
	vector<Note> vecteurVerte;
	vector<Note> vecteurBleu;
	vector<Note> vecteurEnCours;

public:
	Chanson(std::string nom);
	void tick();
};


