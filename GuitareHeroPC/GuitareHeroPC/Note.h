#pragma once
#include "Enum.h"

struct Note {
    int tempsAffichage;
    int tempsDepart;
    int duree;
    CouleurBouton couleur;
    NotesEtats etat = EN_ATTENTE;
    NotesAction action = INITIALE;

    Note(int tAffichage, int tDepart, int tdurree, CouleurBouton couleurBouton)
        : tempsAffichage(tAffichage), tempsDepart(tDepart), duree(tdurree), couleur(couleurBouton) {
    }

    // Surcharge de l'op�rateur d'affectation
    Note& operator=(const Note& other) {
        if (this != &other) { // V�rification d'auto-affectation
            tempsAffichage = other.tempsAffichage;
            tempsDepart = other.tempsDepart;
            duree = other.duree;
            couleur = other.couleur;
            etat = other.etat;
            action = other.action;
        }
        return *this;
    }
};
