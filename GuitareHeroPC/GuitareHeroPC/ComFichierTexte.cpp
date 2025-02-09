#pragma once
#include "ComFichierTexte.h"

Joueur* ComFichierTexte::setJoueur(std::string nom)
{
	// Lire fichier texte et trouver les valeurs associ� au nom
	// Si aucun joueur appeler creer joueur
	
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

std::vector<Note>* ComFichierTexte::setListeNotes(char* nomFichier, std::vector<Note>& vrouge, std::vector<Note>& vvert, std::vector<Note>& vjaune, std::vector<Note>& vbleu, std::vector<Note>& vmauve)
{
	FILE* fichierEntree;
	if ((fichierEntree = fopen(nomFichier, "r")) == NULL)
	{
		fclose(fichierEntree);
		return 0;
	}
	
	int chose, bien, inutile;
	int couleurTemp, d�butTemp, dur�eTemp;
	int i = 0;
	while (!feof)
	{
		if(i == 0 || i==1)
		{
			fscanf(fichierEntree, "%d %d %d", chose, bien, inutile);
			i++;
		}
		else 
		{
			fscanf(fichierEntree, "%d %d %d", couleurTemp,d�butTemp,dur�eTemp);
			if (couleurTemp == 1)
			{
				vrouge.push_back(Note(0, d�butTemp, dur�eTemp, CouleurBouton::ROUGE));
			}
			else if (couleurTemp == 2)
			{
				vvert.push_back(Note(0, d�butTemp, dur�eTemp, CouleurBouton::VERT));
			}
			else if (couleurTemp == 3)
			{
				vjaune.push_back(Note(0, d�butTemp, dur�eTemp, CouleurBouton::JAUNE));
			}
			else if (couleurTemp == 4)
			{
				vbleu.push_back(Note(0, d�butTemp, dur�eTemp, CouleurBouton::BLEU));
			}
			else if (couleurTemp == 5)
			{
				vmauve.push_back(Note(0, d�butTemp, dur�eTemp, CouleurBouton::MAUVE));
			}
			i++;
		}
	}

	return nullptr;
}


Joueur* ComFichierTexte::creerJoueur(std::string nom)
{
	// Cr�er le joueur dans le fichier texte
	// retourner l objet Joueur creer avec les valeurs par default
	return new Joueur(nom);
}
