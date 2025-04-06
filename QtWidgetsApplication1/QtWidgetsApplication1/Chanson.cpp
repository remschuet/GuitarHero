#include "Chanson.h"
#include "ComFichierTexte.h"
#include "CONST.h"
#pragma comment(lib, "winmm.lib")

Chanson::Chanson(string nom) {
    nomChansonMp3 = "chanson/" + enleverCrochets(nom) + ".mp3";
    nomChansonTxt = "chanson/" + nom + ".txt";
    setUpVecteur(nomChansonTxt);
}

Chanson::~Chanson() {
    resetChrono();

}

void Chanson::setUpVecteur(string nomTxt) {
    ComFichierTexte::setListeNotes(nomTxt, vecteurRouge, vecteurVerte, vecteurJaune, vecteurBleu, vecteurMauve);

}

vector<Note>* Chanson::getVecteurNotesEnCours() {
    return &vecteurEnCours; // ERREUR ! temp est détruit en sortie de fonction
}

std::string Chanson::enleverCrochets(const std::string& input) {
    std::string output = input;
    size_t debut = output.find('[');
    size_t fin = output.find(']');

    if (debut != std::string::npos && fin != std::string::npos && fin > debut) {
        output.erase(debut, fin - debut + 1);
    }

    return output;
}


long long Chanson::getTempsRestantChanson() {
    // A FAIRE
    return 0;
}



void Chanson::startChrono() {
    // Obtenir le temps actuel en millisecondes
    chronoDemarrage = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count();
    departMusique();
}

void Chanson::departMusique() {
    // Ouvrir le fichier MP3 en mode asynchrone


    std::string command = "open \"" + nomChansonMp3 + "\" type mpegvideo alias myMP3";
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
    return nomChansonMp3;
}

long long Chanson::getDureeChanson() {
    char buffer[128];
    mciSendStringA("status myMP3 length", buffer, sizeof(buffer), NULL);

    // Vérifier que la chaîne n'est pas vide ou corrompue
    if (strlen(buffer) > 0 && isdigit(buffer[0])) {
        durreeBackup = atoll(buffer);
        return durreeBackup; // Convertir et renvoyer la durée en millisecondes
    }
    else {
        std::cerr << "Erreur lors de la récupération de la durée de la chanson." << std::endl;
        return durreeBackup; // Retourner 0 en cas d'erreur
    }
}


// Chrono de la chanson et non du chrono
long long Chanson::getChrono() {
    char buffer[128];
    mciSendStringA("status myMP3 position", buffer, sizeof(buffer), NULL);
    return atoll(buffer);
}

void Chanson::resetChrono() {  // 🔥 Nouvelle méthode pour réinitialiser le chrono
    arretMusique(); // Arrête la musique si elle est en cours

  //  chronoDemarrage = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count();
    vecteurEnCours.clear();  // Remet à zéro les notes en cours
    setUpVecteur(nomChansonTxt);  // Recharge les notes depuis les fichiers texte
}

//long long Chanson::getChrono() {
  //  return duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count() - chronoDemarrage;
//}

void Chanson::tick(int delaiAffichage) {
    long long tempsActuel = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count();

    // Utilisation d'itérateurs pour supprimer les éléments tout en les parcourant
    for (auto it = vecteurRouge.begin(); it != vecteurRouge.end(); ) {
        if (tempsActuel >= (chronoDemarrage + it->tempsDepart - delaiAffichage) && it->etat == EN_ATTENTE) {
            it->etat = AFFICHER;
            vecteurEnCours.push_back(*it);
            it = vecteurRouge.erase(it); // Supprime l'élément et met à jour l'itérateur
        }
        else
        {
            ++it;
        }
    }

    for (auto it = vecteurVerte.begin(); it != vecteurVerte.end(); ) {
        if (tempsActuel >= (chronoDemarrage + it->tempsDepart - delaiAffichage) && it->etat == EN_ATTENTE) {
            it->etat = AFFICHER;
            vecteurEnCours.push_back(*it);
            it = vecteurVerte.erase(it);
        }
        else
        {
            ++it;
        }
    }

    for (auto it = vecteurBleu.begin(); it != vecteurBleu.end(); ) {
        if (tempsActuel >= (chronoDemarrage + it->tempsDepart - delaiAffichage) && it->etat == EN_ATTENTE) {
            it->etat = AFFICHER;
            vecteurEnCours.push_back(*it);
            it = vecteurBleu.erase(it);
        }
        else
        {
            ++it;
        }
    }

    for (auto it = vecteurJaune.begin(); it != vecteurJaune.end(); ) {
        if (tempsActuel >= (chronoDemarrage + it->tempsDepart - delaiAffichage) && it->etat == EN_ATTENTE) {
            it->etat = AFFICHER;
            vecteurEnCours.push_back(*it);
            it = vecteurJaune.erase(it);
        }
        else
        {
            ++it;
        }
    }

    for (auto it = vecteurMauve.begin(); it != vecteurMauve.end(); ) {
        if (tempsActuel >= (chronoDemarrage + it->tempsDepart - delaiAffichage) && it->etat == EN_ATTENTE) {
            it->etat = AFFICHER;
            vecteurEnCours.push_back(*it);
            it = vecteurMauve.erase(it);
        }
        else
        {
            ++it;
        }
    }
}