#pragma once
#include "Enum.h"

struct Note {
	const int tempsAffichage;
	const int tempsDepart;
	const int durree;
	const CouleurBouton couleur;
	NotesEtats etat = EN_ATTENTE;

	Note(int tAffichage, int tDepart, int tdurree, CouleurBouton couleurBouton)
		: tempsAffichage(tAffichage), tempsDepart(tDepart), durree(tdurree), couleur(couleurBouton) {
	}

};