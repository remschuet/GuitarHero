#pragma once
#include "Enum.h"

struct Note {
	const int tempsAffichage;
	const int tempsDepart;
	const int tempsFin;
	const CouleurBouton couleur;
	NotesEtats etat = EN_ATTENTE;
};