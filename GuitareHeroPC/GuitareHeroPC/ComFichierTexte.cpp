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

std::vector<Note>* ComFichierTexte::setListeNotes(std::string nomFichier, std::vector<Note>& vrouge, std::vector<Note>& vvert, std::vector<Note>& vjaune, std::vector<Note>& vbleu, std::vector<Note>& vmauve)
{
	FILE* fichierEntree;
	fopen_s(&fichierEntree, nomFichier.c_str(), "r");
	if (!fichierEntree || fichierEntree == NULL)
	{
		fclose(fichierEntree);
		return nullptr;
	}
	int couleurTemp, débutTemp, duréeTemp;
	while (!feof(fichierEntree))
	{

			fscanf_s(fichierEntree, "%i %i %i", &couleurTemp, &débutTemp, &duréeTemp);
			if (couleurTemp == 1)
			{
				vrouge.push_back(Note(0, débutTemp, duréeTemp, CouleurBouton::ROUGE));
			}
			else if (couleurTemp == 2)
			{
				vvert.push_back(Note(0, débutTemp, duréeTemp, CouleurBouton::VERT));
			}
			else if (couleurTemp == 3)
			{
				vjaune.push_back(Note(0, débutTemp, duréeTemp, CouleurBouton::JAUNE));
			}
			else if (couleurTemp == 4)
			{
				vbleu.push_back(Note(0, débutTemp, duréeTemp, CouleurBouton::BLEU));
			}
			else if (couleurTemp == 5)
			{
				vmauve.push_back(Note(0, débutTemp, duréeTemp, CouleurBouton::MAUVE));
			}
	}

	fclose(fichierEntree);
	return nullptr;
}


Joueur* ComFichierTexte::creerJoueur(std::string nom)
{
	// Créer le joueur dans le fichier texte
	// retourner l objet Joueur creer avec les valeurs par default
	return new Joueur(nom);
}
