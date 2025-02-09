#pragma once
#include <iostream>
#include "Joueur.h"
#include <iostream>
#include <vector>
#include "Note.h"
using namespace std;

class ComFichierTexte
{
public:
	static Joueur* setJoueur(std::string nom);
	static bool setNouveauNomJoueur(std::string ancienNom, std::string nouveauNom);
	static bool setNouveauMaxScoreJoueur(std::string nom);
	static std::vector<Note>* setListeNotes(std::string nomFichier, std::vector<Note>& vrouge, std::vector<Note>& vvert, std::vector<Note>& vjaune, std::vector<Note>& vbleu, std::vector<Note>& vmauve);

private:
	static Joueur* creerJoueur(std::string nom);
};