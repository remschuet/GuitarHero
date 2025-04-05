#pragma once

#include <windows.h>
#include <iostream>
#include <vector>
#include "Note.h"
#include <ctime> 
#include <chrono>
#include <mmsystem.h>
#include <Enum.h>

using namespace std;
using namespace std::chrono;

class Chanson
{
private:
	string nomChansonMp3 = "";
	string nomChansonTxt = "";


	float deltaEntreNote = 0;
	long long chronoDemarrage;
	vector<Note> vecteurRouge;
	vector<Note> vecteurVerte;
	vector<Note> vecteurBleu;
	vector<Note> vecteurJaune;
	vector<Note> vecteurMauve;
	vector<Note> vecteurEnCours;
	void departMusique();
	const char* chanson1Nom = "psycho.mp3";
	long long durreeBackup = 0;

public:
	string getNomChanson();
	long long getDureeChanson();
	long long getChrono();
	void resetChrono();
	vector<Note>* getVecteurNotesEnCours();
	std::string enleverCrochets(const std::string& input);
	long long getTempsRestantChanson();
	
	void setUpVecteur(string nomTxt);
	Chanson(std::string nom);
	void tick(int delaiAffichage);
	void startChrono();
	void arretMusique();
};


