#pragma once
#include <iostream>
#include "Joueur.h"

class ComFichierTexte
{
public:
	static Joueur* setJoueur(std::string nom);
	static bool setNouveauNomJoueur(std::string ancienNom, std::string nouveauNom);
	static bool setNouveauMaxScoreJoueur(std::string nom);
private:
	static Joueur* creerJoueur(std::string nom);
};