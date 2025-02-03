#pragma once
#include "ComFichierTexte.h"

Joueur* ComFichierTexte::setJoueur(std::string nom)
{
	// Lire fichier texte et trouver les valeurs associé au nom
	// Si aucun joueur appeler creer joueur
	int maxScore = 0;
	std::string image = "";
	if (image != "") {
		return new Joueur(nom, maxScore, image);
	}
	else {
		return new Joueur(nom, maxScore);
	}
}

bool ComFichierTexte::setNouveauNomJoueur(std::string ancienNom, std::string nouveauNom)
{
	// Changer le nom du joueur par un nouveau nom
	return false;
}

bool ComFichierTexte::setNouveauMaxScoreJoueur(std::string nom)
{
	// Modifier le max score
	return false;
}

Joueur* ComFichierTexte::creerJoueur(std::string nom)
{
	// Créer le joueur dans le fichier texte
	// retourner l objet Joueur creer avec les valeurs par default
	return new Joueur(nom);
}
