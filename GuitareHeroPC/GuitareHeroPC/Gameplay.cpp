#include "Gameplay.h"
#include "ComBluetooth.h"
#include "ComFichierTexte.h"
#include "ComClavier.h"
#include "DAOSqlite.h"
#include <iostream>
#include <vector>
#include <CONST.h>

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

void Gameplay::affichageTitre() {
    system("cls");
    gotoxy(10, 2);
    std::cout << "===========================";
    gotoxy(15, 3);
    std::cout << "!! GUITAR HERO !!";
    gotoxy(10, 4);
    std::cout << "===========================";
}

void Gameplay::affichageProgression() {
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
}

void Gameplay::loopGame() {
    int delaiAffichage = 10000;
    affichageTitre();
    affichageProgression();
    tick++;

    // Barre en bas
    gotoxy(4, 25);
    std::cout << "------------------------------------";
    gotoxy(6, 26);
    std::cout << "ROUGE  BLEU  VERT  JAUNE  MAUVE";

    gameStruct.chansonEnCours->tick(delaiAffichage);

    vector<Note> vecteur = gameStruct.chansonEnCours->getVecteurNotesEnCours();

    long long chrono = gameStruct.chansonEnCours->getChrono();

    for (auto& note : vecteur) {
        if (note.tempsDepart <= chrono + delaiAffichage && note.tempsDepart + note.durree >= chrono) {

            int posX = 0;

            switch (note.couleur) {
                case ROUGE: posX = 8; break;
                case BLEU: posX = 15; break;
                case VERT: posX = 21; break;
                case JAUNE: posX = 27; break;
                case MAUVE: posX = 34; break;
            }

            int hauteurNote = note.durree / 1000;
            int positionY = 25 - ((note.tempsDepart - chrono) / 1000);

            for (int y = 0; y < hauteurNote; y++) {
                if (positionY - y <= 25) { // Empêcher d'afficher hors écran
                    gotoxy(posX, positionY - y);
                    std::cout << "X";
                }
            }
        }
    }

    CouleurBouton btn = choixBouton();

    switch (btn)
    {
    case ROUGE:
        exit(1);
        // if (qqch = rouge) note.appuyé
        break;
    case VERT:
        break;
    case BLEU:
        break;
    case JAUNE:
        break;
    case MAUVE:
        break;
    }

    Sleep(350);
    loopGame();
}

void Gameplay::demarrerPartie() {
    gotoxy(12, 18);
    std::cout << "Départ du jeu dans 3 secondes...";
    Sleep(1000);
    gotoxy(12, 18);
    std::cout << "Départ du jeu dans 2 secondes...";
    Sleep(1000);
    gotoxy(12, 18);
    std::cout << "Départ du jeu dans 1 secondes...";
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

    system("cls"); // Efface l'écran avant d'afficher le menu

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

    DAOSqlite* dao = DAOSqlite::getInstance();
    gameStruct.joueur = dao->getJoueur(nomJoueur);

    // Demander si l'utilisateur veut voir les meilleurs scores
    gotoxy(12, 8);
    std::cout << "Options: \n \t\tRouge:\tVoir les meilleurs scores\n\t\tBleu:\tmodifier le joueurs\n\t\tAutre:\tLancer une partie";
    choix == UNKNOWN;
    while (choix == UNKNOWN) {
        choix = choixBouton();
        Sleep(20);
    }
    if (choix == ROUGE){
        voirMeilleurScore();
    }
    else if (choix == BLEU) {
        modifierLeProfile();
    }

    system("cls"); // Efface l'écran avant d'afficher le menu

    // Affichage du cadre
    gotoxy(10, 2);
    std::cout << "**************************************";
    gotoxy(10, 3);
    std::cout << "*        GUITAR HERO MENU           *";
    gotoxy(10, 4);
    std::cout << "**************************************";

    // Choix de la musique
    gotoxy(12, 10);
    std::cout << "Choisir une chanson:";
    gotoxy(15, 12);
    std::cout << "Rouge - Beatles";
    gotoxy(15, 13);
    std::cout << "Vert - Integration";
    gotoxy(15, 14);
    std::cout << "Bleu - Pink floyd";
    gotoxy(12, 16);

    std::cout << "Votre choix: ";
    choix = UNKNOWN;

    while (choix == UNKNOWN) {
        choix = choixBouton();
        Sleep(20);
    }

    if (choix == ROUGE)     gameStruct.chansonEnCours = new Chanson("Beatles");
    else if (choix == VERT) gameStruct.chansonEnCours = new Chanson("Integration");
    else                    gameStruct.chansonEnCours = new Chanson("Pink floyd");

    choix = UNKNOWN;

    demarrerPartie();
}

void Gameplay::voirMeilleurScore() {
    system("cls");
    gotoxy(10, 2);
    std::cout << "**************************************";
    gotoxy(10, 3);
    std::cout << "*        GUITAR HERO MENU           *";
    gotoxy(10, 4);
    std::cout << "**************************************";
    gotoxy(5, 7);
    std::cout << "Fonctionnement à programmer...";

    std::string bob;
    cin >> bob;
}

void Gameplay::modifierLeProfile() {
    system("cls");
    gotoxy(10, 2);
    std::cout << "**************************************";
    gotoxy(10, 3);
    std::cout << "*        GUITAR HERO MENU           *";
    gotoxy(10, 4);
    std::cout << "**************************************";
    gotoxy(5, 7);
    std::cout << "Fonctionnement à programmer...";

    std::string bob;
    cin >> bob;
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
            std::cout << "note rouge appuyé" << std::endl;
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

        if (it.key() == BTN_BLEU && it.value() == BTN_RELACHE) {
            return CouleurBouton::BLEU;
        }
        else if (it.key() == BTN_ROUGE && it.value() == BTN_RELACHE) {
            return CouleurBouton::ROUGE;
        }
        else if (it.key() == BTN_VERT && it.value() == BTN_RELACHE) {
            return CouleurBouton::VERT;
        }
        else if (it.key() == BTN_JAUNE && it.value() == BTN_RELACHE) {
            return CouleurBouton::JAUNE;
        }
        else if (it.key() == BTN_MAUVE && it.value() == BTN_RELACHE) {
            return CouleurBouton::MAUVE;
        }
    }

    return CouleurBouton::UNKNOWN;
}

bool Gameplay::configBluetooth(std::string nomPort) {
    
    comArduino = new ComBluetooth(nomPort);
    /*
    if (comArduino->ouvrirPort()) {
        bool isOk = comArduino->envoyerMessage("Hello HC-05!");
        if (isOk) {
            if (verbose)
                printf("message envoyé");
            return true;
        }
    }
    */
    return false;
}
