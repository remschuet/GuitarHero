#include "Gameplay.h"
#include "ComBluetooth.h"
#include <iostream>
#include "ComFichierTexte.h"

using namespace std;

Gameplay::Gameplay(string nomPort, bool bluetooth, bool verbose, bool admin) {
    this->estBluetooth = bluetooth;
    this->verbose = verbose;
    this->admin = admin;

    if (this->estBluetooth) {
        configBluetooth(nomPort);
    }
    else {
        configFilaire(nomPort);
    }
}

void Gameplay::gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void Gameplay::loopGame() {
    tick++;
    system("cls");
    gotoxy(10, 4);
    std::cout << "!! IN GAME !!";

    gameStruct.chansonEnCours->tick();

    // gameStruct.chansonEnCours.getVecteurCouleurs(); Recuperer les valeurs
    // boucler dessus et les afficher
    // get touches

    std::string message;
    if (comArduino->recevoirMessage(message)) {
        interpreterMsg(message);
    }

    Sleep(500);
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

    gameStruct.joueur = ComFichierTexte::setJoueur(nomJoueur);


    // Demander si l'utilisateur veut voir les meilleurs scores
    gotoxy(12, 8);
    std::cout << "Voulez-vous voir les meilleurs scores ? (O/N) ";
    while (choix == UNKNOWN) {
        choix = choixBouton();
        Sleep(20);
    }
    if (choix == ROUGE)
        voirMeilleurScore();

    choix = UNKNOWN;

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

    while (choix == UNKNOWN) {
        choix = choixBouton();
        Sleep(20);
    }
    if (choix == ROUGE)
        voirMeilleurScore();

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
                printf("message envoyé");
            return true;
        }
    }
    */
    return false;
}
