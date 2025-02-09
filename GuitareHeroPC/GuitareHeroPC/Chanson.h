#pragma once

#include <windows.h>
#include <iostream>
#include <vector>
#include "Note.h"
#include <ctime> 
#include <chrono>
#include <mmsystem.h>

using namespace std;
using namespace std::chrono;

class Chanson
{
private:
	string nomChanson = "";
	float deltaEntreNote = 0;
	long long chronoDemarrage;
	vector<Note> vecteurRouge;
	vector<Note> vecteurVerte;
	vector<Note> vecteurBleu;
	vector<Note> vecteurEnCours;
	void departMusique();
	const char* chanson1Nom = "son1.mp3";


public:
	string getNomChanson();
	long long getChrono();
	vector<Note> getVecteurNotesEnCours();
	long long getTempsRestantChanson();
	
	void setUpVecteur();
	Chanson(std::string nom);
	void tick(int delaiAffichage);
	void startChrono();
	void arretMusique();
};


