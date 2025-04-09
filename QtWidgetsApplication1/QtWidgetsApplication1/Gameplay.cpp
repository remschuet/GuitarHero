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
#include <QProgressBar>
#include <stack>
#include <QPainter>

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
    timerTick = new QTimer(this);
    timerGameAffichage = new QTimer(this);
    timerBonusMuons = new QTimer(this);
    timerBtn = new QTimer(this);
}

void Gameplay::demarrerMusiqueJo(string pathMusique) {
    // Ouvrir le fichier MP3 en mode asynchrone

    std::string command = "open " + pathMusique + " type mpegvideo alias myMP3";
    mciSendStringA(command.c_str(), NULL, 0, NULL);

    // Jouer la musique en arrière-plan
    mciSendStringA("play myMP3", NULL, 0, NULL);
}

void Gameplay::arretMusiqueJo()
{
    // Arrêter et fermer la musique
    mciSendStringA("stop myMP3", NULL, 0, NULL);
    mciSendStringA("close myMP3", NULL, 0, NULL);
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
void Gameplay::rotateLabel(QLabel* label, int angle) {
    QPixmap pixmap(label->size());
    pixmap.fill(Qt::transparent); // Remplir d'un fond transparent

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.translate(label->width() / 2, label->height() / 2); // Translation au centre
    painter.rotate(angle); // Rotation de l'image
    painter.translate(-label->width() / 2, -label->height() / 2); // Revenir à l'origine

    QFont font("Arial", 16);
    painter.setFont(font);
    painter.setPen(Qt::black);
    painter.drawText(label->rect(), Qt::AlignCenter, label->text());

    label->setPixmap(pixmap); // Assigner l'image pivotée au QLabel
    label->setAlignment(Qt::AlignCenter);
    label->show();
}

void Gameplay::affichageTitre(QLabel* label, QVBoxLayout* layoutTitre) {
    label->clear();

	label->setText("Sherby Guitar");
    label->setStyleSheet(
        "color: white; "
        "font-size: 30px; "
        "font-weight: bold; "
        "text-transform: uppercase; "
        "letter-spacing: 3px; "
        "text-shadow: 3px 3px 5px rgba(0, 0, 0, 0.8); "
        "border: none; "
        "padding: 10px; "
        "background: linear-gradient(to right, #ff0000, #ff6600, #ffff00, #33cc33, #0099ff, #9900cc); "
        "border-radius: 10px;");
    label->setAlignment(Qt::AlignCenter | Qt::AlignTop);
    layoutTitre->addWidget(label, 0, Qt::AlignHCenter);  // Centre le titre horizontalement
    layoutTitre->setSpacing(0);  // Pas d'espace supplémentaire entre le titre et les éléments en dessous
    layoutTitre->setContentsMargins(0, 0, 0, 0); // Pas de marges

    // Ajoute le layout du titre au layout principal (layoutGame)

  //  QCoreApplication::processEvents();
    /*system("cls");
    gotoxy(10, 2);
    std::cout << "===========================";
    gotoxy(15, 3);
    std::cout << "!! GUITAR HERO !!";
    gotoxy(10, 4);
    std::cout << "===========================";*/
}

void Gameplay::affichageProgression(QLabel* label, QVBoxLayout* layout) {
    long long tempsEcoule = gameStruct.chansonEnCours->getChrono();
    //QCoreApplication::processEvents();
    long long dureeTotale = gameStruct.chansonEnCours->getDureeChanson();
    //QCoreApplication::processEvents();
    long long pourcentage = (tempsEcoule * 100 / dureeTotale);

    if (dureeTotale <= 0) return; // Évite la division par zéro

    int progression = (tempsEcoule * 20) / dureeTotale; // Calcul du nombre de blocs remplis
    progression = (progression > 20) ? 20 : progression;
    // Limite à 20 blocs
    
   // rotateLabel(label, 90);
    label->setText(QString("Progression : %1% (%2s / %3s)")
        .arg(pourcentage)
        .arg(tempsEcoule / 1000)
        .arg(dureeTotale / 1000));
    label->setStyleSheet("color : white");
    label->setFont(QFont("Arial", 17));

    layout->addWidget(label,10, Qt::AlignCenter);


    //QCoreApplication::processEvents();
    /*gotoxy(10, 29);
    std::cout << "[";
    for (int i = 0; i < 20; i++) {
        if (i < progression)
            std::cout << "X";  // Bloc plein
        else
            std::cout << "-";  // Bloc vide
    }
    std::cout << "] " << (tempsEcoule / 1000) << "s / " << (dureeTotale / 1000) << "s    " << pourcentage << "%" << endl;*/

}
void Gameplay::affichageScoreActuel(QLabel* label, QVBoxLayout* layout) {

    label->setText(QString("Score Actuel : %1").arg(gameStruct.score));
    label->setStyleSheet(
        "color: white; "
        "font-size: 17px; "
        "font-weight: bold; "
        "text-transform: uppercase; "
        "letter-spacing: 3px; "
        "text-shadow: 3px 3px 5px rgba(0, 0, 0, 0.8); "
        "border: none; "
        "padding: 10px; "
        "background: linear-gradient(to right, #ff0000, #ff6600, #ffff00, #33cc33, #0099ff, #9900cc); "
        "border-radius: 10px;");
    label->setAlignment(Qt::AlignCenter);
    if (!layout->children().contains(label)) layout->insertWidget(0, label);

    //label->show();
   // label->show();

}
void Gameplay::affichageMaxScore(QLabel* label, QVBoxLayout* layout) {

    int maxScore = gameStruct.joueur->getMeilleurScore();
    label->setText(QString("Meilleur Score : %1").arg(maxScore));
    label->setStyleSheet(
        "color: white; "
        "font-size: 17px; "
        "font-weight: bold; "
        "text-transform: uppercase; "
        "letter-spacing: 3px; "
        "text-shadow: 3px 3px 5px rgba(0, 0, 0, 0.8); "
        "border: none; "
        "padding: 10px; "
        "background: linear-gradient(to right, #ff0000, #ff6600, #ffff00, #33cc33, #0099ff, #9900cc); "
        "border-radius: 10px;");
    label->setAlignment(Qt::AlignCenter);
    if (!layout->children().contains(label)) layout->addWidget(label);
    //label->show();
  //  label->show();

}
void Gameplay::affichageNomJoueur(QLabel* label, QHBoxLayout* layout) {

    QString nomJoueur = QString::fromStdString(gameStruct.joueur->getNomJoueur());
    label->setText(QString("Joueur : %1").arg(nomJoueur));
    label->setFont(QFont("Arial", 17));
    label->setStyleSheet("color : white");
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
    //if (!layout->children().contains(label)) layout->addWidget(label);
    //label->show();
   // label->show();

}

void Gameplay::ajoutEffectLumineux(QLabel* bouton) {

    QPixmap pixmap(bouton->size()); // Create a pixmap with the same size as the label
    pixmap.fill(Qt::transparent);  // Transparent background

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    // Define the rectangle and radial gradient
    QRectF rect(0, 0, bouton->width(), bouton->height());
    QRadialGradient gradient(rect.center(), rect.width() / 2);
    gradient.setColorAt(0.0, QColor("lightgoldenrodyellow")); // Bright center
    gradient.setColorAt(0.6, QColor("lightgoldenrodyellow").lighter(150)); // Fading glow
    gradient.setColorAt(1.0, Qt::transparent); // Transparent edges

    painter.setBrush(gradient);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(rect); // Draw the glowing effect

    painter.end();

    // Apply the pixmap to the QLabel
    bouton->setPixmap(pixmap);
    bouton->update();

    QTimer::singleShot(250, [bouton]() {
        bouton->clear(); // Réinitialiser l'image du QLabel
        });


	// Ajout d'un effet lumineux sur le bouton
	//QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(bouton);
	//effect->setBlurRadius(15);
	//effect->setOffset(0, 0);
	//effect->setColor(QColor("lightgoldenrodyellow"));
	//bouton->setGraphicsEffect(effect);

 //   //effet plus lumineux
	//QGraphicsColorizeEffect* colorEffect = new QGraphicsColorizeEffect(bouton);
	//colorEffect->setColor(QColor("lightgoldenrodyellow"));
	//colorEffect->setStrength(1.0); // Ajuster la force de l'effet
	//bouton->setGraphicsEffect(colorEffect);
}

void Gameplay::loopGameQT(QLabel* titleLabel, QLabel* ProgressionLabel, myQtManager* manager, QVBoxLayout* layoutGame, QStackedWidget* stack, QWidget* boiteNotes) {
    int endY = 700; //position de la barre de la guitare (à changer)
    int noteWidth = 50; //largeur de la note
    int tailleNoteBase = 50; //hauteur de la note pour une note de 250 ms
    int noteHeight = 0;
    int startNote = 700; //hauteur de la zone de notes = 4000 ms

    vector<Note>* vecteur = gameStruct.chansonEnCours->getVecteurNotesEnCours();
    long long chrono = gameStruct.chansonEnCours->getChrono();

    for (auto& note : *vecteur) {
            if (note.tempsDepart <= chrono + delaiAffichage && note.tempsDepart + note.duree >= chrono) {

				// CREATION DE LA NOTE Si la note n'est pas déjà affichée
                if (!note.estQtAffiche && note.action != MORTE) {    //créer une note seulement si la note n'est pas morte pour éviter de move un pointeur nul
                    // Créer un QLabel pour afficher la note    

                    note.noteLabel = new QLabel(" ", boiteNotes);
                    note.noteLabel->setStyleSheet("background-color: red; color: white;");
                    note.noteLabel->show();
/*
                    QLabel* label = new QLabel("", boiteNotes);  // Mettre le label dans la boite
                    label->setStyleSheet("background-color: blue; color: white;");
                    label->setGeometry(10, 380, 50, 50);
                    label->show();

                    */
                    boiteNotes->setFixedSize(noteWidth * 9 + 15, 700);
                    note.noteLabel->setGeometry(50, 50, noteWidth, noteHeight);
					noteHeight = (note.duree * tailleNoteBase) / 250; // Calculer la hauteur de la note en fonction de sa durée

                    note.noteLabel->setFixedSize(noteWidth, noteHeight);
                    note.noteLabel->show();
                    note.estQtAffiche = true;
                    note.noteLabel->setVisible(true);
                    switch (note.couleur) {
                        case ROUGE: note.positionXQt = 7.5; note.noteLabel->setStyleSheet("background-color : #E83830; border-radius: 25px; border: 3px solid black;"); break;
                        case BLEU: note.positionXQt = noteWidth * 2 ; note.noteLabel->setStyleSheet("background-color : #056DE0 ; border-radius: 25px;border: 3px solid black;"); break;
                        case VERT: note.positionXQt = noteWidth * 4 + 7.5; note.noteLabel->setStyleSheet("background-color : #26CF13; border-radius: 25px;border: 3px solid black;"); break;
                        case JAUNE: note.positionXQt = noteWidth * 6 + 10;note.noteLabel->setStyleSheet("background-color : #FF6E00; border-radius: 25px;border: 3px solid black;"); break;
                        case MAUVE: note.positionXQt = noteWidth * 8 + 7.5;note.noteLabel->setStyleSheet("background-color : #9EB3C4; border-radius: 25px;border: 3px solid black;"); break;
                    }
                    note.noteLabel->setGeometry(100, 100, noteWidth, noteHeight);
                }
                
                if (note.estQtAffiche) {

                    int positionY = endY - ((((note.tempsDepart - chrono) * 50) / 250) + noteHeight);

                    note.noteLabel->move(note.positionXQt, positionY - (65 / 2));

                     if (positionY > endY) {

                         //if (noteHeight > 0) {
                         //    noteHeight -= 2;
                         //    note.noteLabel->setFixedSize(noteWidth, noteHeight);
                         //}

                         if (positionY <= -150) {
                             layoutGame->removeWidget(note.noteLabel);
                             delete note.noteLabel;
                             note.noteLabel = nullptr;
                             note.estQtAffiche = false;
                         }
                     }
                }
            }
        }

}
void clearLayout(QLayout* layout) {
    if (!layout)
        return;

    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            item->widget()->deleteLater();  // Supprime les widgets plus tard pour éviter les erreurs de segmentation
        }
        if (item->layout()) {
            clearLayout(item->layout()); // Nettoie récursivement les sous-layouts
            delete item->layout();       // Supprime le sous-layout
        }
        delete item; // Supprime l'élément lui-même
    }
}

void Gameplay::loopGame(QLabel* titleLabel, QLabel* ProgressionLabel, myQtManager* manager, QVBoxLayout* layoutGame, QStackedWidget* stack) {
    clearLayout(layoutGame);
    int endY = 700; //position de la barre de la guitare (à changer)
    int noteWidth = 50; //largeur de la note
    int tailleNoteBase = 50; //hauteur de la note pour une note de 250 ms
    int noteHeight = 0;
    int startNote = 700; //hauteur de la zone de notes = 4000 ms
    bool inGame = true;

    long long dureeTotale = gameStruct.chansonEnCours->getDureeChanson();
    //double pixelsPerMs = static_cast<double>(startNote) / dureeTotale; // Calcul des pixels par milliseconde
    btnGame = UNKNOWN;

    QLabel* backgroudGame = new QLabel(stack);
    QString imageBackgroundPath = "./images/fondGame.png";

    backgroudGame->setStyleSheet(QString(
        "QLabel {"
        "background-image: url(%1);"
        "background-repeat: no-repeat;"
        "background-position: center;"
        "background-color: rgba(255, 255, 255, 150);" // Transparence de l'image (150 = environ 60% opaque)
        "}"
    ).arg(imageBackgroundPath));
    backgroudGame->setFixedSize(stack->width(), stack->height());
    backgroudGame->lower(); // Met l'image derrière tous les autres widgets
    backgroudGame->show();

    QVBoxLayout* layoutCentreNote = new QVBoxLayout();

    QWidget* boiteNotes = new QWidget();
    boiteNotes->setFixedSize((noteWidth * 9 + 15), 700);
  //  QString imagePath = "./images/grid vert 2.png";
    QLabel* imagesBoite = new QLabel(boiteNotes);
    
    QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect(imagesBoite);
    opacityEffect->setOpacity(0.7);
    imagesBoite->setGraphicsEffect(opacityEffect);

    imagesBoite->setFixedSize((noteWidth * 9 +15), 700);
    QString imagePath = "./images/grid final.png";
    

    imagesBoite->setStyleSheet(QString(
        "background-image: url(%1);"
        "background-repeat: no-repeat;"
        "background-position: center;"
      
    ).arg(imagePath));
    imagesBoite->lower();

    boiteNotes->show();
    //boiteNotes->move((TAILLE_ECRAN_X)-((noteWidth * 6) / 2), TAILLE_ECRAN_Y - (700 / 2)); does not work
    //boiteNotes->setGeometry((TAILLE_ECRAN_X ) - ((noteWidth * 6) / 2), TAILLE_ECRAN_Y - (700 / 2), (noteWidth * 6), 700);

    layoutCentreNote->addWidget(boiteNotes);

    //QGridLayout* layoutGridNotes = new QGridLayout();
    //layoutGridNotes->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

    //layouts pour les notes
    QVBoxLayout* RougeLayout = new QVBoxLayout();

    QVBoxLayout* BleuLayout = new QVBoxLayout();

    QVBoxLayout* VertLayout = new QVBoxLayout();

    QVBoxLayout* JauneLayout = new QVBoxLayout();

    QVBoxLayout* MauveLayout = new QVBoxLayout();

    QHBoxLayout* NotesLayout = new QHBoxLayout();
    //ajout des colonnes des notes à un layout horizontal
    NotesLayout->addLayout(RougeLayout);
    NotesLayout->addLayout(BleuLayout);
    NotesLayout->addLayout(VertLayout);
    NotesLayout->addLayout(JauneLayout);
    NotesLayout->addLayout(MauveLayout);

    boiteNotes->setLayout(NotesLayout);

    QLabel* invisible = new QLabel();
   // invisible->setVisible(false);

    invisible->setFixedSize(QT_BLOCINVISIBLE + 60, 100);
    invisible->setStyleSheet(QString(
        "background - color: transparent; "
  
    ));


    //Ajout de layout pour les autres items et ajout au layout principal
    QVBoxLayout* titleLayout = new QVBoxLayout();
   // titleLayout->addWidget(titleLabel);
   
	QLabel* titreChansonLabel = new QLabel(invisible);
	titreChansonLabel->setText(QString::fromStdString(gameStruct.chansonEnCours->getNomChanson()));
	titreChansonLabel->setFont(QFont("Arial", 17));
    titreChansonLabel->setStyleSheet("color : white; font-weight: bold;");
	titreChansonLabel->setAlignment(Qt::AlignCenter);
	titreChansonLabel->setGeometry(0, 0, invisible->width(), invisible->height());
    titreChansonLabel->show();


    affichageTitre(titleLabel,titleLayout);
    layoutGame->addLayout(titleLayout);

    layoutGame->addLayout(NotesLayout);
    
    //layoutGame->addWidget(boiteNotes);
    QHBoxLayout* noteBar = new QHBoxLayout();
    QVBoxLayout* progressLayout = new QVBoxLayout(layoutGame->parentWidget());
    noteBar->addWidget(invisible);
    noteBar->addLayout(layoutCentreNote);
    QLabel* invisible3 = new QLabel();
    // invisible->setVisible(false);

    invisible3->setFixedSize(100,10);
    invisible3->setStyleSheet(QString(
        "background - color: red; "

    ));
    noteBar->addWidget(invisible3);
    noteBar->addLayout(progressLayout);
    layoutGame->addLayout(noteBar);
    layoutCentreNote->setAlignment(Qt::AlignCenter);



 /*   QWidget* boitePrecision = new QWidget();
    boitePrecision->setFixedSize((noteWidth * 9), tailleNoteBase);
    boitePrecision->setStyleSheet("background-color: skyBlue");
    boitePrecision->show();

    layoutGame->addWidget(boitePrecision);*/

    //boutons de couleurs indiquant quand jouer la note
    QLabel* boutonRouge = new QLabel(boiteNotes);
    QLabel* boutonBleu = new QLabel(boiteNotes);
    QLabel* boutonVert = new QLabel(boiteNotes);
    QLabel* boutonJaune = new QLabel(boiteNotes);
    QLabel* boutonMauve = new QLabel(boiteNotes);


                                                           //rouge, bleu, vert orange, gris

    //note.positionXQt = 0; note.noteLabel->setStyleSheet("background-color : red; border-radius: 25px;");

    boutonRouge->setStyleSheet("background-color: #C93129; border-radius: 32px;");
    boutonRouge->show();
    boutonRouge->setGeometry(0, 700 - (tailleNoteBase + 15) / 2, noteWidth + 15, tailleNoteBase + 15);
    boutonRouge->setFixedSize(noteWidth + 15, tailleNoteBase + 15);
    boutonRouge->show();

    boutonBleu->setStyleSheet("background-color: #044EA1; border-radius: 32px;");
    boutonBleu->show();
    boutonBleu->setGeometry(noteWidth * 2 - 7.5, 700 - (tailleNoteBase + 15) / 2, noteWidth + 15, tailleNoteBase + 15);
    boutonBleu->setFixedSize(noteWidth + 15, tailleNoteBase + 15);
    boutonBleu->show();

    boutonVert->setStyleSheet("background-color: #21B311; border-radius: 32px;");
    boutonVert->show();
    boutonVert->setGeometry(noteWidth * 4, 700 - (tailleNoteBase + 15) / 2, noteWidth + 15, tailleNoteBase + 15);
    boutonVert->setFixedSize(noteWidth + 15, tailleNoteBase + 15);
    boutonVert->show();

    boutonJaune->setStyleSheet("background-color: #D65C00; border-radius: 32px;");
    boutonJaune->show();
    boutonJaune->setGeometry(noteWidth * 6 +2.5, 700 - (tailleNoteBase + 15) / 2, noteWidth + 15, tailleNoteBase + 15);
    boutonJaune->setFixedSize(noteWidth + 15, tailleNoteBase + 15);
    boutonJaune->show();

    boutonMauve->setStyleSheet("background-color: #8193A1; border-radius: 32px;");
    boutonMauve->show();
    boutonMauve->setGeometry(noteWidth * 8, 700 - (tailleNoteBase + 15) / 2, noteWidth + 15, tailleNoteBase + 15);
    boutonMauve->setFixedSize(noteWidth + 15, tailleNoteBase + 15);
    boutonMauve->show();

    QLabel* scoreLabel = new QLabel();
    QLabel* maxScoreLabel = new QLabel();
    QLabel* nomJoueurLabel = new QLabel();



    QProgressBar* barProgression = new QProgressBar(layoutGame->parentWidget());
    barProgression->setOrientation(Qt::Vertical);
    barProgression->setTextVisible(false);

    QHBoxLayout* infolayout = new QHBoxLayout(layoutGame->parentWidget());
    QVBoxLayout* scoreLayout = new QVBoxLayout(layoutGame->parentWidget());


    affichageMaxScore(maxScoreLabel, scoreLayout);
    scoreLayout->setAlignment(Qt::AlignTop);
    scoreLayout->setSpacing(0);  // Réduit l'espace entre les éléments à 2 pixels (au lieu de la valeur par défaut qui est souvent 6 ou 10)
    scoreLayout->setContentsMargins(0, 0, 0, 0);
    progressLayout->setSpacing(1);
    progressLayout->setContentsMargins(0, 0, 0, 0);
    QLabel* invisible4 = new QLabel();
    invisible4->setFixedSize(0,100);
    //invisible4->setStyleSheet();
  //  scoreLayout->addWidget(invisible4);
    //backbutton
    QPushButton* backButton = new QPushButton("Retour");
    backButton->setStyleSheet(QString(
        "background-color: red; "
        "color: white; "
        "border: 2px solid red; "
        "padding: 10px; "
        "border-radius: 10px; "
        "font-size: 18px; "
        "font-weight: bold;"
    ));

    disconnect(backButton, nullptr, nullptr, nullptr);
    QObject::connect(backButton, &QPushButton::clicked, [manager, this, stack, &inGame]() {
        inGame = false;
        // manager->qtPageFinPartie(this, nullptr, stack); // Retourne au menu principal
        });

    infolayout->addWidget(backButton, 0, Qt::AlignCenter);
    affichageNomJoueur(nomJoueurLabel, infolayout);
    //progress bar
    barProgression->setRange(0, 100);
    barProgression->setValue(0);
    barProgression->setFixedHeight(400);
   // progressLayout->setAlignment(Qt::AlignCenter);
    barProgression->setStyleSheet(
        "QProgressBar {"
        "    border: 2px solid #1a3c34;"
        "    border-radius: 10px;"
        "    background-color: #0f2a26;"
        "    width: 30px;"
        "}"
        "QProgressBar::chunk {"
        "    background: qlineargradient("
        "        x1: 0, y1: 0, x2: 0, y2: 1,"
        "        stop: 0 #00ffcc, stop: 1 #00b3b3);"
        "    border-radius: 8px;" // Coins arrondis
        "    box-shadow: 0 0 5px #00ffcc;"
        "    margin: 2px;"
        "}"
    );

    /******** LOGIQUE DES QTIMER *********/
    
    disconnect(timerTick, nullptr, nullptr, nullptr);
    disconnect(timerGameAffichage, nullptr, nullptr, nullptr);
    disconnect(timerBonusMuons, nullptr, nullptr, nullptr);
    disconnect(timerBtn, nullptr, nullptr, nullptr);

    connect(timerTick, &QTimer::timeout, this, [=]() {
        gameStruct.chansonEnCours->tick(delaiAffichage);
        });
    
    connect(timerBtn, &QTimer::timeout, this, [=]() {
        choixBoutonGame();
        });

	QLabel* bouton = nullptr;
    connect(glowNote, &QTimer::timeout, this, [=]() mutable {
        if (bouton != nullptr) {
            //bouton->setGraphicsEffect(nullptr);
            //bouton->clear();
        }
        // bouton->setGraphicsEffect(nullptr); // Retire l'effet de lueur
        });

    //glowNote->setSingleShot(true);


    connect(timerBonusMuons, &QTimer::timeout, this, [=]() mutable {
        multiplicateurPoint = 1; // revenir à la normale
        bonusActiveMuons = false;
        });

    connect(timerGameAffichage, &QTimer::timeout, this, [=]() {
        loopGameQT(titleLabel, ProgressionLabel, manager, layoutGame, stack, boiteNotes);
    });

    timerBonusMuons->setSingleShot(true);
    timerTick->start(100);
    timerBtn->start(40); // 25 fps
    timerGameAffichage->start(40);
    /******** FIN LOGIQUE DES QTIMER *********/

    QLabel* invisible2 = new QLabel();
    // invisible->setVisible(false);

    invisible2->setFixedSize(10, 200);
    invisible2->setStyleSheet(QString(
        "background - color: red; "

    ));
    
    // 60 fps
    progressLayout->addWidget(invisible2);

    while (inGame) {
        QCoreApplication::processEvents();
        long long tempsEcoule = gameStruct.chansonEnCours->getChrono();
        long long pourcentage = (tempsEcoule * 100 / dureeTotale);

        if (dureeTotale <= 0) return; // Évite la division par zéro

        int progression = (tempsEcoule * 20) / dureeTotale; // Calcul du nombre de blocs remplis
        progression = (progression > 20) ? 20 : progression;
        barProgression->setValue(pourcentage);

        //QCoreApplication::processEvents();
       
        //QCoreApplication::processEvents();
        progressLayout->addWidget(barProgression,0,Qt::AlignCenter);
        affichageProgression(ProgressionLabel, progressLayout);

        affichageScoreActuel(scoreLabel, scoreLayout);

        infolayout->insertLayout(0, scoreLayout);

        layoutGame->addLayout(infolayout);

        tick++;


        // Recuperer le vecteur
        vector<Note>* vecteur = gameStruct.chansonEnCours->getVecteurNotesEnCours();

        // si aucun vecteur (debut de partie)
        if (!vecteur) {
            //  Sleep(120);
            continue;
        }

        // chrono en fonction de la musique
        long long chrono = gameStruct.chansonEnCours->getChrono();

        // Affichage de toute les notes à l'ecran

        
        // btnGame = choixBouton();

        // Logique du joystick, si on appuis dessus et qu on a une note appuyer proche dans le temps on fait 3 points supplementaire
        if (btnGame == JOYSTICK) {
            for (auto& note : *vecteur) {
                // valeurs en milliseconde du chrono a modifier mais mettre plus grande que celui plus bas
                if (std::abs(note.tempsDepart - chrono) <= 600 && note.action == APPUYE) { // et si note n est pas terminé
                    gameStruct.score += P_BONUS_JOYSTICK * multiplicateurPoint;
                }
            }
        }
        else if (btnGame == MUONS_BONUS && !bonusActiveMuons) {
            bonusActiveMuons = true;
            multiplicateurPoint = P_MULTI_POINTS_BONUS_MUONS;
            timerBonusMuons->start(P_TEMPS_APPLICABLE_BONUS_MUONS);
        }
        // Appuyé sur une touche
        if (btnGame != UNKNOWN && btnGame != JOYSTICK && btnGame != QUITTER) {
            bool aTouche = false;

            //ajout l'effet de lueur au bouton presse
            switch (btnGame) {
            case ROUGE: bouton = boutonRouge; break;
            case BLEU: bouton = boutonBleu; break;
            case VERT: bouton = boutonVert; break;
            case JAUNE: bouton = boutonJaune; break;
            case MAUVE: bouton = boutonMauve; break;
            }

            for (auto& note : *vecteur) {
                // Si une touche est appuye et que le temps est proche d une note mettre note appuye
                if (note.couleur == btnGame &&
                    std::abs(note.tempsDepart - chrono) <= G_BUFFER_NOTE && note.action == INITIALE) {
                    note.action = APPUYE;
                    aTouche = true;
                    gameStruct.score += scoreAleatoire() * multiplicateurPoint;
                    break;
                }
            }
            if (bouton) {
                ajoutEffectLumineux(bouton);
                //             glowNote->start(250);

            }
            // Si une touche est appuye mais aucune note presente
            if (!aTouche) {
                gameStruct.score += P_MAUVAISE_TOUCHE;
            }
        }

        // Supprime les notes non appuyées devenues "mortes"
        for (auto it = vecteur->begin(); it != vecteur->end(); ) {
            Note& note = *it;

            // Vérifie si la note est expirée et toujours à l'état initial
            bool noteExpiree = (chrono > note.tempsDepart + note.duree + G_BUFFER_NOTE_MOURIR && note.action == INITIALE);

            if (noteExpiree) {
                // Si elle est affichée dans l'interface Qt, on la retire et libère la mémoire
                if (note.estQtAffiche && note.noteLabel != nullptr) {
                    layoutGame->removeWidget(note.noteLabel);
                    delete note.noteLabel;
                    note.noteLabel = nullptr;
                }

                note.action = MORTE;
                gameStruct.score += P_MANQUE_NOTE;

                // Supprimer la note du vecteur, erase retourne le prochain itérateur
                it = vecteur->erase(it);
            }
            else {
                ++it;
            }
        }

        if (btnGame != UNKNOWN) {
            btnGame = UNKNOWN;
        }
        if (gameStruct.score < 0) {
            gameStruct.score = 0;
        }

        // valeurs de fps en ms
        // Sleep(120);
        QCoreApplication::processEvents();
        if (tempsEcoule >= dureeTotale) {
            inGame = false;
        }
    }
    
    manager->qtPageFinPartie(this, layoutGame, stack); // Remplacez MenuPrincipal par votre enum réelle
}



void Gameplay::demarrerPartie(QLabel* label, QLabel* titleLabel, QLabel* ProgressionLabel, myQtManager* manager, QVBoxLayout* layoutGame, QStackedWidget* stack) {

    //arret musique de menu et depart musique 3 2 1 
    arretMusiqueJo();
    //musique de fond
    demarrerMusiqueJo(MUSIQUEDEPARTPARTIE);

    QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect(label);

    if (label->graphicsEffect()) {
        delete label->graphicsEffect(); // ou delete si tu veux tout de suite
    }
    label->setGraphicsEffect(opacityEffect);

    gameStruct.score = 0;
    bonusActiveMuons = false;
    ////system("cls");
    label->clear();
    tick = 0;
    //gameTimer->start(120);
    //qDebug() << "Partie demarree";
   
    // affichageTitre(titleLabel,layoutGame);
    std::srand(static_cast<unsigned int>(time(nullptr)));
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("color: blac;");  // Tu peux personnaliser
    QFont baseFont("Arial", 60, QFont::Bold);  // Taille de base
    label->setFont(baseFont);



    QSequentialAnimationGroup* group = new QSequentialAnimationGroup();

    QStringList countdown = { "3", "2", "1"};
    for (const QString& number : countdown) {
        QParallelAnimationGroup* stepGroup = new QParallelAnimationGroup();

        // Animation de la taille du texte
        QVariantAnimation* fontAnim = new QVariantAnimation();
        fontAnim->setDuration(1333);
        fontAnim->setStartValue(60);  // Taille de départ
        fontAnim->setEndValue(120);   // Taille finale

        QObject::connect(fontAnim, &QVariantAnimation::valueChanged, [=](const QVariant& value) {
            QFont f = baseFont;
            f.setPointSize(value.toInt());
            label->setFont(f);
            });

        // Animation de l'opacité (disparition)
        QPropertyAnimation* opacityAnim = new QPropertyAnimation(opacityEffect, "opacity");
        opacityAnim->setDuration(1000);
        opacityAnim->setStartValue(1.0);
        opacityAnim->setEndValue(0.0);

        QObject::connect(stepGroup, &QParallelAnimationGroup::stateChanged, [=](QAbstractAnimation::State newState, QAbstractAnimation::State) {
            if (newState == QAbstractAnimation::Running) {
                label->setText(number);
                opacityEffect->setOpacity(1.0);
                label->setFont(baseFont);
            }
            });

        stepGroup->addAnimation(fontAnim);
        stepGroup->addAnimation(opacityAnim);
        group->addAnimation(stepGroup);
    }
    
    //arret musique 3 2 1 
    arretMusiqueJo();
    
    QObject::connect(group, &QSequentialAnimationGroup::finished, [=]() {
     
        gameStruct.score = 0;
        ////system("cls");
        label->clear();
        tick = 0;
        gameStruct.chansonEnCours->startChrono();
        //gameTimer->start(120);
        //qDebug() << "Partie demarree";

      //  affichageTitre(titleLabel, layoutGame);
        loopGame(titleLabel, ProgressionLabel, manager, layoutGame, stack);
        std::srand(static_cast<unsigned int>(time(nullptr)));
        });

    group->start(QAbstractAnimation::DeleteWhenStopped);
}

/*void Gameplay::updateGame(QLabel* titleLabel, QLabel* ProgressionLabel, myQtManager* manager) {
    long long tempsEcoule = gameStruct.chansonEnCours->getChrono();
    long long dureeTotale = gameStruct.chansonEnCours->getDureeChanson();

    affichageTitre(titleLabel);
    affichageProgression(ProgressionLabel);
    tick++;

    if (tempsEcoule >= dureeTotale) {
        finPartie(manager);
    }
}*/

int Gameplay::scoreAleatoire() {
    return std::rand() % (P_BONNE_NOTE_MAX - P_BONNE_NOTE_MIN + 1) + P_BONNE_NOTE_MIN;
}

void Gameplay::finPartie(myQtManager* manager, QStackedWidget* stack) {
    // gameTimer->stop();
    timerTick->stop();
    timerBtn->stop();
    timerGameAffichage->stop();
    timerBonusMuons->stop();
    long long tempsEcoule = gameStruct.chansonEnCours->getChrono();
    long long dureeTotale = gameStruct.chansonEnCours->getDureeChanson();
    long long pourcentage = (tempsEcoule * 100 / dureeTotale);
    manager->qtPageFinPartie(this, nullptr, stack);

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
    try{
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
    catch (const std::exception& e) {
        msg = "";

        // Ignore l'erreur (tu peux aussi logguer si tu veux savoir ce qu’il s’est passé)
        // std::cerr << "Erreur JSON ignorée : " << e.what() << std::endl;
    }
}

void Gameplay::choixBoutonGame() {
    std::string msg;
    if (!comArduino->recevoirMessage(msg)) {
        // btnGame = CouleurBouton::UNKNOWN;
    }
    json j;
    try{
        j = json::parse(msg);
        if (verbose) {
            std::cout << j;
        }
    }
    catch (const std::exception& e) {
        // FIXME
        // btnGame = CouleurBouton::UNKNOWN;
        // Ignore l'erreur (tu peux aussi logguer si tu veux savoir ce qu’il s’est passé)
        // std::cerr << "Erreur JSON ignorée : " << e.what() << std::endl;
    }

    for (auto it = j.begin(); it != j.end(); ++it) {

        if (it.key() == BTN_BLEU && it.value() == BTN_APPUYE) {
            btnGame = CouleurBouton::BLEU;
        }
        else if (it.key() == BTN_ROUGE && it.value() == BTN_APPUYE) {
            btnGame = CouleurBouton::ROUGE;
        }
        else if (it.key() == BTN_VERT && it.value() == BTN_APPUYE) {
            btnGame = CouleurBouton::VERT;
        }
        else if (it.key() == BTN_JAUNE && it.value() == BTN_APPUYE) {
            btnGame = CouleurBouton::JAUNE;
        }
        else if (it.key() == BTN_MAUVE && it.value() == BTN_APPUYE) {
            btnGame = CouleurBouton::MAUVE;
        }
        else if (it.key() == BTN_QUITTER && it.value() == BTN_APPUYE) {
            btnGame = CouleurBouton::QUITTER;
        }
        else if (it.key() == BTN_JOYSTICK) {
            btnGame = CouleurBouton::JOYSTICK;
        }
        else if (it.key() == BTN_BONUS_MUONS) {
            btnGame = CouleurBouton::MUONS_BONUS;
        }

        else {
            // btnGame = CouleurBouton::UNKNOWN;
        }
    }

    // btnGame = CouleurBouton::UNKNOWN;
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

    if (gameStruct.joueur != nullptr) {
        delete joueurActuel;  // Supprime l'ancien joueur pour éviter les fuites mémoire
    }
    gameStruct.joueur = nouveauJoueur;
}

ComArduino* Gameplay::getCom()
{
    return comArduino;
}

Joueur* Gameplay::getJoueur() {
    return gameStruct.joueur;
}

bool Gameplay::configBluetooth(std::string nomPort) {
    comArduino = new ComBluetooth(nomPort);
    return true;
}
