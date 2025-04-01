#include "Gameplay.h"
#include "ComBluetooth.h"
#include "ComFichierTexte.h"
#include "ComClavier.h"
#include "DAOSqlite.h"
#include <iostream>
#include <vector>
#include <CONST.h>
#include <conio.h> // Pour _getch()
#include "CONST_QT.h"
#include <QThread>
#include <qcoreapplication.h>
#include <qstackedwidget>
#include <QVBoxLayout>
#include <QLabel>

using namespace std;

Gameplay::Gameplay(string nomPort, ComMode modeCommunication, bool verbose, bool admin) {
    this->modeCommunication = modeCommunication;
    this->verbose = verbose;
    this->admin = admin;

    if (modeCommunication == BLUETOOTH) {
        configBluetooth(nomPort);
    }
    else if (modeCommunication == FILAIRE) {
        configFilaire(nomPort);
    }
    else {
        comArduino = new ComClavier();
    }
}

void Gameplay::afficherImage() {
    //Montrer l'image àprès la capture
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);

    cv::Mat image = cv::imread(gameStruct.joueur->getImage());
    cv::namedWindow("Image", cv::WINDOW_NORMAL);

    cv::setWindowProperty("Image", cv::WND_PROP_TOPMOST, 1);
    HWND hwnd = FindWindowA(NULL, "Image");
    if (hwnd != NULL)
    {
        SetForegroundWindow(hwnd);
    }


    cv::imshow("Image", image);

    //CouleurBouton btn = UNKNOWN;
    //while (btn == UNKNOWN) {
    //    btn = choixBouton();
    //    Sleep(50);
    //}
    cv::waitKey(0);	//Attend qu'un touche soit pressé pour fermer la fenêtre
    cv::destroyWindow("Image");
    Sleep(200);
}

void Gameplay::PrendreImage() {
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);

    Sleep(1000);
    cv::VideoCapture cap(0);	//ouvre la caméra de base
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera" << std::endl;
    }

    cv::namedWindow("En direct", cv::WINDOW_AUTOSIZE);	//Crée la fenêtre pour la caméra

    cv::setWindowProperty("En direct", cv::WND_PROP_TOPMOST, 1);

    while (true) {
        cv::Mat frame;	//Matrice de frame pour le live feed
        cap >> frame;	//Capture une nouvelle frame

        if (frame.empty()) {
            std::cerr << "Error : Could not capture frame" << std::endl;
            break;
        }

        cv::flip(frame, frame, 1);

        cv::imshow("En direct", frame);	//Montre la vidéo

        if (cv::waitKey(30) >= 0) {	//Sauvegarde la frame choisi (bouton) dans un fichier avec le nom suivant 
            gameStruct.joueur->setNouvelleImage();

            cv::imwrite(gameStruct.joueur->getImage(), frame);	//changer la ligne, car ça change le nom de la frame. En faire pour chaque Joueur
            break;
        }
    }

    cap.release();	//ferme la caméra
    cv::destroyAllWindows();
}

void Gameplay::gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void Gameplay::affichageTitre(QLabel* label) {
    label->clear();

	label->setText("GUITAR HERO");
    label->setFont(QFont("Arial", 24, QFont::Bold));
    label->setAlignment(Qt::AlignCenter | Qt::AlignTop);
    /*system("cls");
    gotoxy(10, 2);
    std::cout << "===========================";
    gotoxy(15, 3);
    std::cout << "!! GUITAR HERO !!";
    gotoxy(10, 4);
    std::cout << "===========================";*/
}

void Gameplay::affichageProgression(QLabel* label) {
    long long tempsEcoule = gameStruct.chansonEnCours->getChrono();
    long long dureeTotale = gameStruct.chansonEnCours->getDureeChanson();
    long long pourcentage = (tempsEcoule * 100 / dureeTotale);

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
    std::cout << "] " << (tempsEcoule / 1000) << "s / " << (dureeTotale / 1000) << "s    " << pourcentage << "%" << endl;

}

void Gameplay::loopGame(QLabel* titleLabel, QLabel* ProgressionLabel) {
    while (true) {
        long long tempsEcoule = gameStruct.chansonEnCours->getChrono();
        long long dureeTotale = gameStruct.chansonEnCours->getDureeChanson();

        affichageTitre(titleLabel);
        affichageProgression(ProgressionLabel);
        tick++;

        //Barre d'infos du joueur
        gotoxy(40, 3);
        cout << "SCORE: " << gameStruct.score;
        gotoxy(40, 2);
        cout << "MAX_SCORE: " << gameStruct.joueur->getMeilleurScore();
        gotoxy(40, 1);
        cout << "PLAYER: " << gameStruct.joueur->getNomJoueur();
        // Barre en bas
        gotoxy(4, 25);
        std::cout << "------------------------------------";
        gotoxy(6, 26);
        std::cout << "ROUGE  BLEU  VERT  JAUNE  MAUVE";

        // mettre à jours les vecteurs
        gameStruct.chansonEnCours->tick(delaiAffichage);

        vector<Note>* vecteur = gameStruct.chansonEnCours->getVecteurNotesEnCours();

        // si aucun vecteur (debut de partie)
        if (!vecteur) {
            Sleep(120);
            //loopGame();
        }

        // chrono en fonction de la musique
        long long chrono = gameStruct.chansonEnCours->getChrono();

        // Affichage de toute les notes à l'ecran
        for (auto& note : *vecteur) {
            if (note.tempsDepart <= chrono + delaiAffichage && note.tempsDepart + note.duree >= chrono) {

                int posX = 0;

                switch (note.couleur) {
                case ROUGE: posX = 8; break;
                case BLEU: posX = 15; break;
                case VERT: posX = 21; break;
                case JAUNE: posX = 27; break;
                case MAUVE: posX = 34; break;
                }

                int hauteurNote = note.duree / 250;
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

        // Logique du joystick, si on appuis dessus et qu on a une note appuyer proche dans le temps on fait 3 points supplementaire
        if (btn == JOYSTICK) {
            for (auto& note : *vecteur) {
                // valeurs en milliseconde du chrono a modifier mais mettre plus grande que celui plus bas
                if (std::abs(note.tempsDepart - chrono) <= 600 && note.action == APPUYE) { // et si note n est pas terminé
                    gameStruct.score += 3;
                }
            }
        }
        // Appuyé sur une touche
        if (btn != UNKNOWN && btn != JOYSTICK && btn != QUITTER) {
            bool aTouche = false;
            for (auto& note : *vecteur) {
                // Si une touche est appuye et que le temps est proche d une note mettre note appuye
                if (note.couleur == btn &&
                    std::abs(note.tempsDepart - chrono) <= 450 && note.action == INITIALE) {
                    note.action = APPUYE;
                    aTouche = true;
                    gameStruct.score++;
                    break;
                }
            }
            // Si une touche est appuye mais aucune note presente
            if (!aTouche) {
                gameStruct.score--;
            }
        }


        // Si une note n'a pas ete appuye, la mettre morte
        for (auto& note : *vecteur) {
            if (chrono > note.tempsDepart + note.duree + 400 &&
                note.action == INITIALE) {
                note.action = MORTE;
                gameStruct.score--;
            }
        }

        // valeurs de fps en ms
        Sleep(120);
        if (btn == QUITTER || tempsEcoule >= dureeTotale) {
            finPartie();
        }
    }
}

void Gameplay::demarrerPartie(QLabel* label) {
    qDebug() << "Demarrage de la partie";
    gameStruct.score = 0;
    label->setGeometry((TAILLE_ECRAN_X / 2) - 100, (TAILLE_ECRAN_Y / 2), 0, 0);
    label->setText("Depart du jeu dans 3 secondes...");
    QCoreApplication::processEvents();
    Sleep(1000);                                            //Si ça ne marche pas, essayer QThread::sleep(1); ou QThread::sleep(1000);
    //QThread::sleep(1);
    label->setText("Depart du jeu dans 2 secondes...");
    QCoreApplication::processEvents();
    //QThread::sleep(1);
    Sleep(1000);
    label->setText("Depart du jeu dans 1 secondes...");
    QCoreApplication::processEvents();
    //QThread::sleep(1);
    Sleep(1000);

    ////system("cls");
    label->clear();
    tick = 0;
    gameStruct.chansonEnCours->startChrono();
    gameTimer->start(120);
    qDebug() << "Partie demarree";
    //loopGame();
}

void Gameplay::updateGame(QLabel* titleLabel, QLabel* ProgressionLabel) {
    long long tempsEcoule = gameStruct.chansonEnCours->getChrono();
    long long dureeTotale = gameStruct.chansonEnCours->getDureeChanson();

    affichageTitre(titleLabel);
    affichageProgression(ProgressionLabel);
    tick++;

    if (tempsEcoule >= dureeTotale) {
        finPartie();
    }
}

void Gameplay::finPartie() {
    gameTimer->stop();
    long long tempsEcoule = gameStruct.chansonEnCours->getChrono();
    long long dureeTotale = gameStruct.chansonEnCours->getDureeChanson();
    long long pourcentage = (tempsEcoule * 100 / dureeTotale);

    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //la fonction pour afficher la page de fin de partie doit être dans myQtManager pour que la fct soit accepté...
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


   /* system("cls");
    std::cout << "\n=====================================\n";
    std::cout << "            FIN DE PARTIE            \n";
    std::cout << "=====================================\n\n";

    if (gameStruct.joueur->getMeilleurScore() < gameStruct.score) {
        cout << "Felicitations vous avez battu votre meilleur score !!! \n\n";
    }
    std::cout << "Name:  " << gameStruct.joueur->getNomJoueur() << "           SCORE: " << gameStruct.score << "\n\n";

    std::cout << "Vous avez completer :  " << pourcentage << "% de la chanson";

     gameStruct.chansonEnCours->arretMusique();


     if (gameStruct.joueur->ScoreMax < gameStruct.score) {
         // sauvegarder le score
         DAOSqlite* sqlite = DAOSqlite::getInstance();
         sqlite->updateScoreJoueur(gameStruct.joueur->getNomJoueur(), gameStruct.score);
         gameStruct.joueur->ScoreMax = gameStruct.score;
     }

     CouleurBouton btn = UNKNOWN;
     while(btn == UNKNOWN) {
         btn = choixBouton();
         Sleep(50);
     }
     loopMenu();*/

}

void Gameplay::SelectionJoueur(QLabel* label)                    //cout à enlever
{
    string nomJoueur = "";

   //system("cls"); // Efface l'écran avant d'afficher le menu
    label->clear();
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
    if (choix == ROUGE) {
        //myQtmanager->getMeilleursScores(); À revoir
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
    std::cout << "Bleu - Pink floyd";
    gotoxy(15, 14);
    std::cout << "Vert - Integration";
    gotoxy(12, 16);

    std::cout << "Votre choix: ";
    choix = UNKNOWN;

    while (choix == UNKNOWN) {
        choix = choixBouton();
        Sleep(20);
    }

    if (choix == ROUGE)     gameStruct.chansonEnCours = new Chanson(CHANSON_1_MP3);
    else if (choix == BLEU) gameStruct.chansonEnCours = new Chanson(CHANSON_2_MP3);
    else                    gameStruct.chansonEnCours = new Chanson(CHANSON_3_MP3);

    choix = UNKNOWN;

    //demarrerPartie();
}


void Gameplay::modifierLeProfile() {
    Sleep(1000);
    afficherImage();
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

        PrendreImage();

        // std::string nouvelleImage;
        // std::getline(std::cin, nouvelleImage);
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

CouleurBouton Gameplay::choixBouton() {
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
        else if (it.key() == BTN_JOYSTICK && it.value() == BTN_RELACHE) {
            return CouleurBouton::JOYSTICK;
        }

        else {
            return CouleurBouton::UNKNOWN;
        }
    }

    return CouleurBouton::UNKNOWN;
}

void Gameplay::setJoueur(Joueur* nouveauJoueur) {

    if (joueurActuel != nullptr) {
        delete joueurActuel;  // Supprime l'ancien joueur pour éviter les fuites mémoire
    }
    joueurActuel = nouveauJoueur;
}

Joueur* Gameplay::getJoueur() {
    return joueurActuel;
}

bool Gameplay::configBluetooth(std::string nomPort) {
    comArduino = new ComBluetooth(nomPort);
    return true;
}
