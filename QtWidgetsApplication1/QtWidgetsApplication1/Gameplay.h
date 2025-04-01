#pragma once
#include <iostream>
#include "ComBluetooth.h"
#include "ComFilaire.h"
#include "Joueur.h"
#include "GameStruct.h"
#include <vector>
#include <QLabel>
#include <QTimer>
//#include <QObject>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <iostream>

#include <windows.h>
#pragma comment(lib, "User32.lib")

class Gameplay : public QObject        //QT
{
    Q_OBJECT;        //QT

public:
    Gameplay(std::string comPort = "COM5", ComMode modeCommunication = FILAIRE, bool verbose = false, bool admin = false);
    explicit Gameplay(QObject* parent = nullptr);    //QT
    void afficherImage();
    void PrendreImage();
    void gotoxy(int x, int y);
    void affichageTitre();
    void affichageProgression();
    void loopGame();
    void demarrerPartie(QLabel* Label);
    void finPartie();
    void SelectionJoueur();
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
private slots:
    void updateGame();
};