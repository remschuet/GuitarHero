#include "Gameplay.h"
#include "ComBluetooth.h"
#include "ComFichierTexte.h"
#include "ComClavier.h"
#include "DAOSqlite.h"
#include <iostream>
#include <vector>
#include <CONST.h>
#include <conio.h> // Pour _getch()

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
    long long tempsEcoule = gameStruct.chansonEnCours->getChrono();
    long long dureeTotale = gameStruct.chansonEnCours->getDureeChanson();

    if (dureeTotale <= 0) return; // Évite la division par zéro

    int progression = (tempsEcoule * 20) / dureeTotale; // Calcul du nombre de blocs remplis
    progression = (progression > 20) ? 20 : progression; // Limite à 20 blocs

    gotoxy(10, 29);
    std::cout << "[";
    for (int i = 0; i < 20; i++) {
        if (i < progression)
            std::cout << "X";  // Bloc plein
        else
            std::cout << "-";  // Bloc vide
    }
    std::cout << "] " << (tempsEcoule / 1000) << "s / " << (dureeTotale / 1000) << "s" << std::endl;
}

void Gameplay::loopGame() {
    int delaiAffichage = 10000;
    affichageTitre();
    affichageProgression();
    tick++;

    gotoxy(40, 3);
    cout << "SCORE: " << gameStruct.score;

    // Barre en bas
    gotoxy(4, 25);
    std::cout << "------------------------------------";
    gotoxy(6, 26);
    std::cout << "ROUGE  BLEU  VERT  JAUNE  MAUVE";

    gameStruct.chansonEnCours->tick(delaiAffichage);

    vector<Note>* vecteur = gameStruct.chansonEnCours->getVecteurNotesEnCours();

    if (!vecteur) {
        Sleep(120);
        loopGame();
    }
    long long chrono = gameStruct.chansonEnCours->getChrono();

    for (auto& note : *vecteur) {
        if (note.tempsDepart <= chrono + delaiAffichage && note.tempsDepart + note.durree >= chrono) {

            int posX = 0;

            switch (note.couleur) {
                case ROUGE: posX = 8; break;
                case BLEU: posX = 15; break;
                case VERT: posX = 21; break;
                case JAUNE: posX = 27; break;
                case MAUVE: posX = 34; break;
            }

            int hauteurNote = note.durree / 250;
            int positionY = 25 - ((note.tempsDepart - chrono) / 250);

            for (int y = 0; y < hauteurNote; y++) {
                if (positionY - y <= 25) { // Empêcher d'afficher hors écran
                    gotoxy(posX, positionY - y);
                    std::cout << "X";
                }
            }
        }
    }

    CouleurBouton btn = choixBouton();

    // Appuyé sur une touche
    if (btn != UNKNOWN){
        bool aTouche = false;
        for (auto& note : *vecteur) {
            if (note.couleur == btn &&
                std::abs(note.tempsDepart - chrono) <= 450 && note.action == INITIALE) {
                note.action = APPUYE;
                aTouche = true;
                gameStruct.score++;
                break;
            }
        }
        if (!aTouche) {
            // Faire quelque chose !
            gameStruct.score--;
        }
    }

    for (auto& note : *vecteur) {
        if (chrono > note.tempsDepart + note.durree + 400 && 
            note.action == INITIALE) {
            note.action = MORTE;
            // Desendre le score a un max
            gameStruct.score--;
        }
    }

    Sleep(120);
    if (btn != QUITTER) {
        loopGame();
    }
    else {
        finPartie();
    }
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

void Gameplay::finPartie() {
    system("cls");
    std::cout << "\n=====================================\n";
    std::cout << "            FIN DE PARTIE            \n";
    std::cout << "=====================================\n\n";
    std::cout << gameStruct.joueur->getNomJoueur() << "  SCORE: " << gameStruct.score;

    if (gameStruct.joueur->ScoreMax < gameStruct.score) {
        // sauvegarder le score
        DAOSqlite* sqlite = DAOSqlite::getInstance();
        sqlite->updateScoreJoueur(gameStruct.joueur->getNomJoueur(), gameStruct.score);
    }
    gameStruct.chansonEnCours->arretMusique();
    
    CouleurBouton btn = UNKNOWN;
    while(btn == UNKNOWN) {
        btn = choixBouton();
        Sleep(50);
    }
    loopMenu();

}


void Gameplay::SelectionJoueur()
{
    string nomJoueur = "";

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
    loopMenu();
}

void Gameplay::loopMenu() {
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


    // Demander si l'utilisateur veut voir les meilleurs scores
    gotoxy(12, 6);
    std::cout << "Options: \n \t\tRouge:\tVoir les meilleurs scores\n\t\tBleu:\tmodifier le joueurs\n\t\tAutre:\tLancer une partie";
    choix = UNKNOWN;
    while (choix == UNKNOWN) {
        choix = choixBouton();
        Sleep(20);
    }
    if (choix == ROUGE){
        voirMeilleurScore();
        loopMenu();
        return;
    }
    else if (choix == BLEU) {
        modifierLeProfile();
        loopMenu();
        return;
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

    if (choix == ROUGE)     gameStruct.chansonEnCours = new Chanson(CHANSON_1_MP3);
    else if (choix == VERT) gameStruct.chansonEnCours = new Chanson(CHANSON_2_MP3);
    else                    gameStruct.chansonEnCours = new Chanson(CHANSON_3_MP3);

    choix = UNKNOWN;

    demarrerPartie();
}

void Gameplay::voirMeilleurScore() {        //Reste à tester après avoir obtenu des scores
    
    //int scores[10] = { 0 };
    std::pair < std::string, int> scores[10];
    DAOSqlite* sqlite = DAOSqlite::getInstance();
    sqlite->getMeilleurScore(scores);
    system("cls");
    gotoxy(10, 2);
    std::cout << "**************************************";
    gotoxy(10, 3);
    std::cout << "*        GUITAR HERO MENU           *";
    gotoxy(10, 4);
    std::cout << "**************************************";
    gotoxy(10, 7);
    std::cout << "             HIGH SCORE              ";
    gotoxy(10, 9);
    std::cout << "1er : " << scores[0].first << " - " << scores[0].second;      //afficher en très très gros et jaune/or?
    gotoxy(10, 11);
    std::cout << "2e  : " << scores[1].first << " - " << scores[1].second;        //afficher en très gros et argent/bleu?
    gotoxy(10, 13);
    std::cout << "3e  : " << scores[2].first << " - " << scores[2].second;        //afficher en gros et bronze/orange?

    int y = 15;

    for (int i = 3; i < 10; i++)
    {
        if (scores[i].first != "")
        {
            gotoxy(10, y);
            std::cout << i + 1 << "e : " << scores[i].first << " - " << scores[i].second;
            y += 2;
        }
    }

    CouleurBouton choix = UNKNOWN;
    while (choix == UNKNOWN) {
        choix = choixBouton();
        Sleep(20);
    }

    /*gotoxy(10, 15);
    std::cout << "4e  : " << scores[3].first << " - " << scores[3].second;
    gotoxy(10, 17);
    std::cout << "5e  : " << scores[4].first << " - " << scores[4].second;
    gotoxy(10, 19);
    std::cout << "6e  : " << scores[5].first << " - " << scores[5].second;
    gotoxy(10, 21);
    std::cout << "7e  : " << scores[6].first << " - " << scores[6].second;
    gotoxy(10, 23);
    std::cout << "8e  : " << scores[7].first << " - " << scores[7].second;
    gotoxy(10, 25);
    std::cout << "9e  : " << scores[8].first << " - " << scores[8].second;
    gotoxy(10, 27);
    std::cout << "10e : " << scores[9].first << " - " << scores[9].second;
    //std::string bob;
    //cin >> bob;*/
}

void Gameplay::modifierLeProfile() {
    system("cls");

    // Affichage du titre
    gotoxy(10, 2);
    std::cout << "**************************************";
    gotoxy(10, 3);
    std::cout << "*        GUITAR HERO MENU           *";
    gotoxy(10, 4);
    std::cout << "**************************************";

    // Affichage des informations du joueur
    gotoxy(5, 7);
    std::cout << "========= Parametres du joueur =========";

    gotoxy(5, 9);
    std::cout << "Nom           : " << gameStruct.joueur->getNomJoueur();

    gotoxy(5, 10);
    std::cout << "Meilleur Score: " << gameStruct.joueur->getMeilleurScore();

    gotoxy(5, 11);
    std::cout << "Image         : " << gameStruct.joueur->getImage();

    gotoxy(5, 13);
    std::cout << "========= Modification du joueur =========";

    gotoxy(5, 15);
    std::cout << "[1] Modifier le nom";

    gotoxy(5, 16);
    std::cout << "[2] Modifier l'image";

    gotoxy(5, 17);
    std::cout << "[3] Retour au menu principal";

    gotoxy(5, 18);
    std::cout << "Choix: ";

    CouleurBouton choix = UNKNOWN;
    while (choix == UNKNOWN) {
        choix = choixBouton();
        Sleep(20);
    }

    switch (choix) {
    case ROUGE: {
        gotoxy(5, 19);
        std::cout << "Nouveau nom: ";
        std::string nouveauNom;
        std::getline(std::cin, nouveauNom);
        gameStruct.joueur->setNouveauNomJoueur(nouveauNom);
        break;
    }
    case BLEU: {
        gotoxy(5, 19);
        std::cout << "Nouvelle image: ";
        std::string nouvelleImage;
        std::getline(std::cin, nouvelleImage);
        gameStruct.joueur->setNouvelleImage(nouvelleImage);
        break;
    }
    default:
        return;
    }

    modifierLeProfile();
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
        else if (it.key() == BTN_QUITTER && it.value() == BTN_RELACHE) {
            return CouleurBouton::QUITTER;
        }

        else {
            return CouleurBouton::UNKNOWN;
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
