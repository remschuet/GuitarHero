#include "Chanson.h"

void Chanson::setUpVecteur(vector<Note> vecteur)
{
}

vector<Note> Chanson::getVecteurNotesEnCours()
{
    return vecteurEnCours;  // Retourne les notes en cours d'affichage
}



Chanson::Chanson(string nom)
{
    nomChanson = nom;

}

void Chanson::tick()
{
    // Obtenir le temps actuel en millisecondes
    auto now = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count();

    for (auto& note : vecteurRouge) {
        if (now >= note.tempsDepart && note.etat == EN_ATTENTE) {
            // Changer l'état de la note
            note.etat = AFFICHER;
            vecteurEnCours.push_back(note);

            // Afficher un message de debug
            cout << "Note ROUGE activée à " << now << " ms\n";
        }
    }

    for (auto& note : vecteurVerte) {
        if (now >= note.tempsDepart && note.etat == EN_ATTENTE) {
            note.etat = AFFICHER;
            vecteurEnCours.push_back(note);
            cout << "Note VERTE activée à " << now << " ms\n";
        }
    }

    for (auto& note : vecteurBleu) {
        if (now >= note.tempsDepart && note.etat == EN_ATTENTE) {
            note.etat = AFFICHER;
            vecteurEnCours.push_back(note);
            cout << "Note BLEUE activée à " << now << " ms\n";
        }
    }
}

