#include "MyQtPageSettings.h"

MyQtPageSettings::MyQtPageSettings(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent)
    : MyQtPage(stack, G, manager, parent) {

}

void MyQtPageSettings::refresh(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent)
{
    QLabel* imageLabel = nullptr;
    // Créer un widget pour la page du menu
    QWidget* pageParametre = new QWidget();
    QGridLayout* layout = new QGridLayout(pageParametre);

    layout->setSpacing(5);  // Espacement entre les widgets dans la grille (réduit au minimum)
    layout->setContentsMargins(0, 0, 0, 0);  // Pas de marges autour du layout

    // Créer le bouton "Retour"
    QPushButton* btnRetour = new QPushButton("Retour");
    btnRetour->setStyleSheet(
        "QPushButton { "                       // Sélecteur pour QPushButton
        "    background-color: green; "          // Couleur de fond du bouton
        "    color: white; "                   // Couleur du texte
        "    font-size: 25px; "                // Taille de la police
        "    border-radius: 5px; "             // Coins arrondis
        "    padding: 5px 10px; "              // Espacement interne du bouton
        "}"
        "QPushButton:hover { "                 // Effet au survol
        "    background-color: gray; "       // Couleur de fond quand la souris survole le bouton
        "    color: white; "                 // Couleur du texte au survol
        "}"
    );
    //QFont font = btnRetour->font();
    //font.setPointSize(25);  // Définir la taille de la police ici
    //btnRetour->setFont(font);

    btnRetour->setFixedSize(500, 100);

    // Ajouter le bouton "Retour" en haut à gauche (cellule (0, 0))
    layout->addWidget(btnRetour, 0, 0, Qt::AlignLeft | Qt::AlignTop);

    // Titre du menu (centré dans la grille)
    QLabel* titre = new QLabel("");
    myQt_setFont(titre, 150);
    titre->setAlignment(Qt::AlignCenter);
    layout->addWidget(titre, 0, 0, 0, 0, Qt::AlignHCenter | Qt::AlignTop); // Centrer le titre

    // Image de fond (à l'arrière-plan)
    QLabel* backgroundLabel = new QLabel(pageParametre);
    backgroundLabel->setGeometry(0, 0, TAILLE_ECRAN_X, TAILLE_ECRAN_Y);
    backgroundLabel->setScaledContents(true);  // L'image de fond ne sera pas redimensionnée
    backgroundLabel->lower();

    // Ajouter un espacement entre le titre et les boutons
    QWidget* spacerTop = new QWidget();
    spacerTop->setFixedHeight(200);  // Espacement vertical
    layout->addWidget(spacerTop, 1, 0, 1, 3);  // Ajouter un widget vide comme espacement

    // Liste des boutons
    QStringList buttonNames = { "Difficulte", "Parametre de la manette", "Mode Admin" };
    QVector<QPushButton*> buttons;

    // Création des boutons avec un style uniforme
    for (int i = 0; i < buttonNames.size(); ++i) {
        QPushButton* button = new QPushButton(buttonNames[i]);
        //QFont fontButton = button->font();
        //fontButton.setPointSize(25);  // Définir la taille de la police ici
        //button->setFont(fontButton);

        button->setStyleSheet(
            "QPushButton { "                       // Sélecteur pour QPushButton
            "    background-color: green; "          // Couleur de fond du bouton
            "    color: white; "                   // Couleur du texte
            "    font-size: 25px; "                // Taille de la police
            "    border-radius: 5px; "             // Coins arrondis
            "    padding: 5px 10px; "              // Espacement interne du bouton
            "}"
            "QPushButton:hover { "                 // Effet au survol
            "    background-color: gray; "       // Couleur de fond quand la souris survole le bouton
            "    color: white; "                 // Couleur du texte au survol
            "}"
        );
        button->setFixedSize(500, 100);
        buttons.append(button);

        // Ajouter les boutons en ligne, un sous l'autre
        layout->addWidget(button, 2 + i, 1, Qt::AlignHCenter | Qt::AlignVCenter);
    }

    // Ajouter un espace après les boutons (espacement vers le bas)
    QWidget* spacerBottom = new QWidget();
    spacerBottom->setFixedHeight(600);  // Espacement vertical à la fin
    layout->addWidget(spacerBottom, 6, 0, 1, 3);  // Ajouter un widget vide comme espacement après les boutons

    // Connexion des boutons aux actions
    QObject::connect(buttons[0], &QPushButton::clicked, [=]() {
        fenetres QtFenetre = MeilleursScores;
        });

    QObject::connect(buttons[1], &QPushButton::clicked, [=]() {
        // Créer un widget qui contiendra l'image et le bouton
        QWidget* overlayWidget = new QWidget(pageParametre); // parent = pageParametre
        overlayWidget->setGeometry(0, 0, TAILLE_ECRAN_X, TAILLE_ECRAN_Y);  // Position et taille du widget

        // Créer un QLabel pour afficher l'image
        QLabel* paraManette = new QLabel(overlayWidget);  // Ajouter l'image au nouveau widget
        QPixmap ManettePixmap("./images/test.jpg");

        // Vérifier si l'image a été correctement chargée
        if (ManettePixmap.isNull()) {
            qDebug() << "Erreur de chargement de l'image!";
            return;
        }

        // Afficher l'image dans le QLabel
        paraManette->setPixmap(ManettePixmap);
        paraManette->setAlignment(Qt::AlignCenter);  // Centrer l'image dans le QLabel

        // Fixer la taille du QLabel à la taille de l'écran
        paraManette->setFixedSize(TAILLE_ECRAN_X, TAILLE_ECRAN_Y);  // S'assurer que le QLabel prend toute la taille de l'écran

        // S'assurer que l'image s'adapte à la taille du QLabel
        paraManette->setScaledContents(true);  // Redimensionner l'image pour s'adapter au QLabel

        // Créer un bouton "Retour aux Paramètres"
        QPushButton* btnRetourParametre = new QPushButton("Retour", overlayWidget);
        btnRetourParametre->setStyleSheet(
            "QPushButton { "
            "    background-color: green; "
            "    color: white; "
            "    font-size: 25px; "
            "    border-radius: 5px; "
            "    padding: 5px 10px; "
            "} "
            "QPushButton:hover { "
            "    background-color: gray; "
            "    color: white; "
            "} "
        );
        btnRetourParametre->setFixedSize(500, 100);
        btnRetourParametre->setGeometry(0, 0, 500, 100);  // Positionner le bouton

        // Ajouter l'overlayWidget à la pageParametre, au-dessus de tous les autres éléments
        layout->addWidget(overlayWidget, 0, 0, 0, 0);  // Assurez-vous qu'il couvre toute la page

        // Assurer que le bouton et l'image sont bien au-dessus des autres widgets
        overlayWidget->raise();  // Met l'overlayWidget (contenant l'image et le bouton) au-dessus des autres éléments

        // Connexion du bouton "Retour aux Paramètres"
        QObject::connect(btnRetourParametre, &QPushButton::clicked, [=]() {
            // Supprimer l'overlay (image et bouton) quand on clique sur "Retour"
            paraManette->deleteLater();  // Supprimer l'image
            btnRetourParametre->deleteLater();  // Supprimer le bouton
            overlayWidget->deleteLater();  // Supprimer l'overlayWidget complet
            });
        });


    QObject::connect(buttons[2], &QPushButton::clicked, [=]() {
        fenetres QtFenetre = Admin;
        myQtManager::changerDePage(stack, QtFenetre, G, manager);
        });

    QObject::connect(btnRetour, &QPushButton::clicked, [=]() {
        stack->setCurrentIndex(0); // Retour au menu principal
        });

    // Ajouter la page au QStackedWidget
    stack->addWidget(pageParametre);
}


void MyQtPageSettings::setBackground()
{
}
