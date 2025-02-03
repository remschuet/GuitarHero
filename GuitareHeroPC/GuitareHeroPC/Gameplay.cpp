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
    if (estBluetooth) {
        std::string message;
        if (comBluetooth->lireMessage(message)) {
            std::cout << "Message reçu : " << message << std::endl;
        }
    }
    else {
        std::string message;
        if (comFilaire->recevoirMessage(message)) {
            interpreterMsg(message);
        }
    }
    Sleep(500);
    loopGame();
}

void Gameplay::loopMenu() {
    string nomJoueur = "";
    char voirScore;
    char choixMusique = '0';

    system("cls"); // Efface l'écran avant d'afficher le menu

    // Affichage du cadre
    gotoxy(10, 2);
    cout << "**************************************";
    gotoxy(10, 3);
    cout << "*        GUITAR HERO MENU           *";
    gotoxy(10, 4);
    cout << "**************************************";

    // Demander le nom du joueur
    gotoxy(12, 6);
    cout << "Nom du joueur: ";
    cin >> nomJoueur;

    joueur = ComFichierTexte::setJoueur(nomJoueur);

    // Demander si l'utilisateur veut voir les meilleurs scores
    gotoxy(12, 8);
    cout << "Voulez-vous voir les meilleurs scores ? (O/N) ";
    cin >> voirScore;

    if (voirScore == 'O' || voirScore == 'o') {
        voirMeilleurScore();
    }

    // Choix de la musique
    gotoxy(12, 10);
    cout << "Choisir une chanson:";
    gotoxy(15, 12);
    cout << "1) Beatles";
    gotoxy(15, 13);
    cout << "2) Intégration";
    gotoxy(15, 14);
    cout << "3) Autre";



    do {
        gotoxy(12, 16);
        cout << "Votre choix: ";
        cin >> choixMusique;
    } while (choixMusique != '1' && choixMusique != '2' && choixMusique != '3');

    // Démarrage du jeu
    gotoxy(12, 18);
    cout << "Départ du jeu dans 3 secondes...";
    Sleep(1000);
    gotoxy(12, 18);
    cout << "Départ du jeu dans 2 secondes...";
    Sleep(1000);
    gotoxy(12, 18);
    cout << "Départ du jeu dans 1 secondes...";
    Sleep(1000);
    system("cls"); // Nettoyage de l'écran avant de lancer le jeu
    loopGame();
}

void Gameplay::voirMeilleurScore() {
    string attente;
    cout << "Meilleur score: ";

    cin >> attente;
}

bool Gameplay::configFilaire(std::string nomPort) {
    comFilaire = new ComFilaire(nomPort);
    return true;
}

void Gameplay::interpreterMsg(string msg) {
    json j = json::parse(msg);

    for (auto it = j.begin(); it != j.end(); ++it) {
        if (it.key() == "message") {
            std::cout << it.value() << std::endl;
        }
        if (it.key() == "bouton1" && it.value() == "released") {
            std::cout << "note rouge appuyé" << std::endl;
        }
    }
}

bool Gameplay::configBluetooth(std::string nomPort) {
    comBluetooth = new ComBluetooth(nomPort);

    if (comBluetooth->ouvrirPort()) {
        bool isOk = comBluetooth->envoyerMessage("Hello HC-05!");
        if (isOk) {
            if (verbose)
                printf("message envoyé");
            return true;
        }
    }
    return false;
}
