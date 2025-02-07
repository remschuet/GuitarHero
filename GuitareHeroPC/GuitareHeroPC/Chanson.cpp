#include "Chanson.h"
#pragma comment(lib, "winmm.lib")

void Chanson::setUpVecteur(vector<Note> vecteur) {
}

vector<Note> Chanson::getVecteurNotesEnCours() {
    return vecteurEnCours;
}

long long Chanson::getTempsRestantChanson() {
    // A FAIRE
    return 0;
}

Chanson::Chanson(string nom) {
    nomChanson = nom;
}

void Chanson::startChrono() {
    // Obtenir le temps actuel en millisecondes
    chronoDemarrage = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count();
    departMusique();
}

void Chanson::departMusique() {
    // Ouvrir le fichier MP3 en mode asynchrone
    std::string command = "open \"" + std::string(chanson1Nom) + "\" type mpegvideo alias myMP3";
    mciSendStringA(command.c_str(), NULL, 0, NULL);

    // Jouer la musique en arrière-plan
    mciSendStringA("play myMP3", NULL, 0, NULL);
}

void Chanson::arretMusique() {
    // Arrêter et fermer la musique
    mciSendStringA("stop myMP3", NULL, 0, NULL);
    mciSendStringA("close myMP3", NULL, 0, NULL);
}

string Chanson::getNomChanson()
{
    return nomChanson;
}

long long Chanson::getChrono()
{
    return duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count() - chronoDemarrage;
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

/*
void Chanson::tick()
{
    // Obtenir le temps actuel une seule fois
    long long tempsActuel = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count();

    // Traitement des notes rouges
    for (auto it = vecteurRouge.begin(); it != vecteurRouge.end(); ) {
        if (tempsActuel >= chronoDemarrage + it->tempsDepart && it->etat == EN_ATTENTE) {
            it->etat = AFFICHER;
            vecteurEnCours.push_back(it);
            it = vecteurRouge.erase(it); // Erase et obtient le nouvel itérateur
            cout << "Note ROUGE activée à " << tempsActuel << " ms\n";
        } else {
            ++it;
        }
    }

    // Traitement des notes vertes
    for (auto it = vecteurVerte.begin(); it != vecteurVerte.end(); ) {
        if (tempsActuel >= chronoDemarrage + it->tempsDepart && it->etat == EN_ATTENTE) {
            it->etat = AFFICHER;
            vecteurEnCours.push_back(it);
            it = vecteurVerte.erase(it); // Erase et obtient le nouvel itérateur
            cout << "Note VERTE activée à " << tempsActuel << " ms\n";
        } else {
            ++it;
        }
    }

    // Traitement des notes bleues
    for (auto it = vecteurBleu.begin(); it != vecteurBleu.end(); ) {
        if (tempsActuel >= chronoDemarrage + it->tempsDepart && it->etat == EN_ATTENTE) {
            it->etat = AFFICHER;
            vecteurEnCours.push_back(*it);
            it = vecteurBleu.erase(it); // Erase et obtient le nouvel itérateur
            cout << "Note BLEUE activée à " << tempsActuel << " ms\n";
        } else {
            ++it;
        }
    }
}
*/

