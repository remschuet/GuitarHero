#include "Chanson.h"

void Chanson::setUpVecteur(vector<Note> vecteur)
{
}

vector<Note> Chanson::getVecteurNotesEnCours()
{
    return vecteurEnCours;  // Retourne les notes en cours d'affichage
}



Chanson::Chanson(string nom) {
    nomChanson = nom;
}

void Chanson::startChrono() {
    // Obtenir le temps actuel en millisecondes
    chronoDemarrage = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count();
}

long long Chanson::getChrono()
{
    return duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count();
}


void Chanson::tick()
{
    // Obtenir le temps actuel une seule fois
    long long tempsActuel = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count();

    // REMI -> NE PAS OUBLIER DE SUPPRIMER la note de la listes actuelle
    for (auto& note : vecteurRouge) {
        if (tempsActuel >= chronoDemarrage + note.tempsDepart && note.etat == EN_ATTENTE) {
            note.etat = AFFICHER;
            vecteurEnCours.push_back(note);
            cout << "Note ROUGE activée à " << tempsActuel << " ms\n";
        }
    }

    for (auto& note : vecteurVerte) {
        if (tempsActuel >= chronoDemarrage + note.tempsDepart && note.etat == EN_ATTENTE) {
            note.etat = AFFICHER;
            vecteurEnCours.push_back(note);
            cout << "Note VERTE activée à " << tempsActuel << " ms\n";
        }
    }

    for (auto& note : vecteurBleu) {
        if (tempsActuel >= chronoDemarrage + note.tempsDepart && note.etat == EN_ATTENTE) {
            note.etat = AFFICHER;
            vecteurEnCours.push_back(note);
            cout << "Note BLEUE activée à " << tempsActuel << " ms\n";
        }
    }
}

