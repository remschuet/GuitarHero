#pragma once
#include <iostream>
#include "ComBluetooth.h"
#include "ComFilaire.h"
#include "Joueur.h"
#include "GameStruct.h"
#include <vector>
#include <QLabel>
#include <QTimer>
#include "ComFichierTexte.h"
#include "ComClavier.h"
#include "DAOSqlite.h"
#include <CONST.h>
#include <conio.h> // Pour _getch()
#include "CONST_QT.h"
#include <QThread>
#include <qcoreapplication.h>
#include <qstackedwidget>
#include <QVBoxLayout>
#include <QObject>
#include "myQtManager.h"
#include <QProgressBar>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

#include <windows.h>
#pragma comment(lib, "User32.lib")

class myQtManager;

class Gameplay : public QObject        //QT
{
    Q_OBJECT;        //QT

public:
    Gameplay(std::string comPort = "COM5", ComMode modeCommunication = FILAIRE, bool verbose = false, bool admin = false);
    explicit Gameplay(QObject* parent = nullptr);    //QT
    void afficherImage();
    void PrendreImage();
    void gotoxy(int x, int y);
    void rotateLabel(QLabel* label, int angle);
    void affichageTitre(QLabel* Label, QVBoxLayout* layoutTitre);
    void affichageProgression(QLabel* Label, QVBoxLayout* layout);
    void affichageScoreActuel(QLabel* label, QVBoxLayout* layout);
    void affichageMaxScore(QLabel* label, QVBoxLayout* layout);
    void affichageNomJoueur(QLabel* label, QHBoxLayout* layout);
    void loopGame(QLabel* TitleLabel, QLabel* ProgressionLabel, myQtManager* manager, QVBoxLayout* layoutGame, QStackedWidget* stack);
    void demarrerPartie(QLabel* Label, QLabel* titleLabel, QLabel* ProgressionLabel, myQtManager* manager, QVBoxLayout* layoutGame, QStackedWidget* stack);
    void finPartie(myQtManager* manager, QStackedWidget* stack);
    void SelectionJoueur(QLabel* Label);
    void loopMenu();

    bool configBluetooth(std::string nomPort);
    bool configFilaire(std::string nomPort);
    void interpreterMsg(std::string);
    CouleurBouton choixBouton();
    GameStruct gameStruct;
    Joueur* getJoueur();
    void setJoueur(Joueur* nouveauJoueur);

private:
   
    Joueur* joueurActuel = nullptr;
    ComArduino* comArduino;
    ComMode modeCommunication;
    bool verbose;
    bool admin;
    int tick = 0;
    void modifierLeProfile();
    QTimer* gameTimer;
    QTimer* timerTick;
//private slots:
  //  void updateGame(QLabel* titleLabel, QLabel* ProgressionLabel, myQtManager* manager);
};