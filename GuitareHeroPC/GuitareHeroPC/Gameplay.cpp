#include "Gameplay.h"
#include "ComBluetooth.h"
#include "ComFichierTexte.h"
#include "ComClavier.h"
#include <iostream>
#include <vector>

using namespace std;

Gameplay::Gameplay(string nomPort, ComMode modeCommunication, bool verbose, bool admin) {
    this->modeCommunication = modeCommunication;
    this->verbose = verbose;
    this->admin = admin;

    if (modeCommunication == BLUETOOTH) {
        configBluetooth(nomPort);
    }
    else if (modeCommunication == FILAIRE){
        configFilaire(nomPort);
    }
    else {
        comArduino = new ComClavier();
    }
}

void Gameplay::gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void Gameplay::loopGame() {
    vector<Note*> vecteur;
    vecteur.push_back(new Note(0, 5000, 1000, CouleurBouton::ROUGE));
    vecteur.push_back(new Note(0, 8000, 5000, CouleurBouton::ROUGE));
    vecteur.push_back(new Note(0, 5000, 1000, CouleurBouton::VERT));
    vecteur.push_back(new Note(0, 5000, 1000, CouleurBouton::MAUVE));
    vecteur.push_back(new Note(0, 6000, 3000, CouleurBouton::BLEU));
    vecteur.push_back(new Note(0, 5000, 2000, CouleurBouton::JAUNE));
    vecteur.push_back(new Note(0, 2000, 2000, CouleurBouton::ROUGE));
    vecteur.push_back(new Note(0, 8000, 3000, CouleurBouton::BLEU));

    int delaiAffichage = 6000;
    long long chrono = 5000;

    tick++;
    system("cls");
    // Titre du jeu
    gotoxy(10, 2);
    std::cout << "===========================";
    gotoxy(15, 3);
    std::cout << "!! GUITAR HERO !!";
    gotoxy(10, 4);
    std::cout << "===========================";

    // std::cout << "[";
    // int progression = gameStruct.chansonEnCours->getChrono();  // Simulation d'une progression
    // int tempsRestant = gameStruct.chansonEnCours->getTempsRestant();  // Simulation d'une progression
    /*
    for (int i = 0; i < 20; i++) {
        if (i <= progression)
            std::cout << "=";
        else
            std::cout << " ";
    }
    std::cout << "]";
    */

    // Barre en bas
    gotoxy(4, 25);
    std::cout << "------------------------------------";
    gotoxy(6, 26);
    std::cout << "ROUGE  BLEU  VERT  JAUNE  MAUVE";

    gameStruct.chansonEnCours->tick();

    for (auto& note : vecteur) {
        if (note->tempsDepart <= chrono + delaiAffichage && note->tempsDepart + note->durree >= chrono) {

            int posX = 0;

            switch (note->couleur) {
                case ROUGE: posX = 8; break;
                case BLEU: posX = 15; break;
                case VERT: posX =21; break;
                case JAUNE: posX = 27; break;
                case MAUVE: posX = 34; break;
            }

            int hauteurNote = note->durree / 1000;
            int positionY = 25 - ((note->tempsDepart - chrono) / 1000);

            for (int y = 0; y < hauteurNote; y++) {
                if (positionY - y <= 25) { // Emp�cher d'afficher hors �cran
                    gotoxy(posX, positionY - y);
                    std::cout << "X";
                }
            }
        }
    }
Sleep(1000);
    loopGame();
}

void Gameplay::demarrerPartie() {
    gotoxy(12, 18);
    std::cout << "D�part du jeu dans 3 secondes...";
    Sleep(1000);
    gotoxy(12, 18);
    std::cout << "D�part du jeu dans 2 secondes...";
    Sleep(1000);
    gotoxy(12, 18);
    std::cout << "D�part du jeu dans 1 secondes...";
    Sleep(1000);

    system("cls");
    tick = 0;
    gameStruct.chansonEnCours->startChrono();
    loopGame();
}

void Gameplay::loopMenu() {
    string nomJoueur = "";
    string numChanson = "-1";
    char voirScore;
    CouleurBouton choix = UNKNOWN;

    system("cls"); // Efface l'�cran avant d'afficher le menu

    // Affichage du cadre
    gotoxy(10, 2);
    std::cout << "**************************************";
    gotoxy(10, 3);
    std::cout << "*        GUITAR HERO MENU           *";
    gotoxy(10, 4);
    std::cout << "**************************************";

    // Demander le nom du joueur
    gotoxy(12, 6);
    std::cout << "Nom du joueur: ";
    cin >> nomJoueur;

    gameStruct.joueur = ComFichierTexte::setJoueur(nomJoueur);

    // Demander si l'utilisateur veut voir les meilleurs scores
    gotoxy(12, 8);
    std::cout << "Voulez-vous voir les meilleurs scores ? (O/N) ";
    choix == UNKNOWN;
    while (choix == UNKNOWN) {
        choix = choixBouton();
        Sleep(20);
    }
    if (choix == JAUNE){
        voirMeilleurScore();
    }

    // Choix de la musique
    gotoxy(12, 10);
    std::cout << "Choisir une chanson:";
    gotoxy(15, 12);
    std::cout << "Rouge - Beatles";
    gotoxy(15, 13);
    std::cout << "Vert - Integration";
    gotoxy(15, 14);
    std::cout << "Bleu - Autre";
    gotoxy(12, 16);

    std::cout << "Votre choix: ";
    choix = UNKNOWN;

    while (choix == UNKNOWN) {
        choix = choixBouton();
        Sleep(20);
    }

    if (choix == ROUGE)     gameStruct.chansonEnCours = new Chanson("Beatles");
    else if (choix == VERT) gameStruct.chansonEnCours = new Chanson("Integration");
    else                    gameStruct.chansonEnCours = new Chanson("Autre");

    choix = UNKNOWN;

    demarrerPartie();
}

void Gameplay::voirMeilleurScore() {
    string attente;
    std::cout << "Meilleur score: ";

    std::cin >> attente;
}

bool Gameplay::configFilaire(std::string nomPort) {
    comArduino = new ComFilaire(nomPort);
    return true;
}

void Gameplay::interpreterMsg(string msg) {
    json j = json::parse(msg);

    for (auto it = j.begin(); it != j.end(); ++it) {
        if (it.key() == "message") {
            std::cout << it.value() << std::endl;
        }
        if (it.key() == "btnBleu" && it.value() == "released") {
            std::cout << "note rouge appuy�" << std::endl;
        }
    }
}

CouleurBouton Gameplay::choixBouton(){
    std::string msg;
    if (!comArduino->recevoirMessage(msg)) {
        return CouleurBouton::UNKNOWN;
    }

    json j = json::parse(msg);
    if (verbose) {
        std::cout << j;
    }

    for (auto it = j.begin(); it != j.end(); ++it) {
        if (it.key() == "btlBleu" && it.value() == "released") {
            return CouleurBouton::BLEU;
        }
        else if (it.key() == "btnRouge" && it.value() == "released") {
            return CouleurBouton::ROUGE;
        }
        else if (it.key() == "btnVert" && it.value() == "released") {
            return CouleurBouton::VERT;
        }
    }

    return CouleurBouton();
}

bool Gameplay::configBluetooth(std::string nomPort) {
    
    comArduino = new ComBluetooth(nomPort);
    /*
    if (comArduino->ouvrirPort()) {
        bool isOk = comArduino->envoyerMessage("Hello HC-05!");
        if (isOk) {
            if (verbose)
                printf("message envoy�");
            return true;
        }
    }
    */
    return false;
}
