#include "MyQtPageMenu.h"

MyQtPageMenu::MyQtPageMenu(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent)
    : MyQtPage(stack, G, manager, parent) {
    // Créer un widget pour la page du menu
    QWidget* pageMenu = new QWidget();
    pageMenu->setStyleSheet("background-color: " + COULEUR_FOND + ";");

    // Image de fond
    QLabel* backgroundLabel = new QLabel(pageMenu);
    backgroundLabel->setGeometry(0, 0, TAILLE_ECRAN_X, TAILLE_ECRAN_Y);
    QPixmap resizedPixmap("./Images/placeholder_background_login.png");
    backgroundLabel->setPixmap(resizedPixmap);
    backgroundLabel->setScaledContents(true);
    backgroundLabel->lower();

    // Ajouter une couche semi-transparente au-dessus de l'image pour un effet d'assombrissement
    QWidget* overlay = new QWidget(pageMenu);
    overlay->setGeometry(0, 0, TAILLE_ECRAN_X, TAILLE_ECRAN_Y);
    overlay->setStyleSheet("background-color: rgba(0, 0, 0, 100);"); // Ajuster l'opacité si nécessaire
    overlay->lower();

    // Conteneur central pour le menu 
    QWidget* menuBox = new QWidget(pageMenu);
    menuBox->setStyleSheet("background-color: rgba(0, 0, 0, 150); border-radius: 25px; padding: 20px;");
    menuBox->setFixedSize(600, 400);

    QVBoxLayout* menuBoxLayout = new QVBoxLayout(menuBox);
    menuBoxLayout->setAlignment(Qt::AlignCenter);

    // Titre du menu
    QLabel* titre = new QLabel("Menu Principal", menuBox);
    myQt_setFont(titre, 40);
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet(
        "color: white; "
        "font-size: 40px; "
        "font-weight: bold; "
        "text-transform: uppercase; "
        "letter-spacing: 3px; "
        "text-shadow: 3px 3px 5px rgba(0, 0, 0, 0.8); "
        "border: none; "
        "padding: 10px; "
        "background: linear-gradient(to right, #ff0000, #ff6600, #ffff00, #33cc33, #0099ff, #9900cc); "
        "border-radius: 10px;");
    menuBoxLayout->addWidget(titre);

    // Liste des boutons
    QStringList buttonNames = { "Démarrer", "Voir meilleurs scores", "Informations joueur", "Paramètres", "Déconnexion" };
    QVector<QPushButton*> buttons;

    for (const QString& name : buttonNames) {
        QPushButton* button = new QPushButton(name, menuBox);
        button->setStyleSheet(
            "QPushButton { "
            "    background-color: " + COULEUR_BOUTON + "; "
            "    color: white; "
            "    font-size: 25px; "
            "    border-radius: 5px; "
            "    padding: 5px 10px; "
            "}"
            "QPushButton:hover { "
            "    background-color: gray; "
            "    color: white; "
            "}"
        );
        button->setFixedSize(250, 50);
        buttons.append(button);
        menuBoxLayout->addWidget(button, 0, Qt::AlignCenter);
    }

    // Ajouter la box centrée dans la page
    QVBoxLayout* mainLayout = new QVBoxLayout(pageMenu);
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addStretch();
    mainLayout->addWidget(menuBox, 0, Qt::AlignCenter);
    mainLayout->addStretch();
    pageMenu->setLayout(mainLayout);

    // Connexions des boutons
    QObject::connect(buttons[0], &QPushButton::clicked, [=]() {
        myQtManager::changerDePage(stack, Game, G, manager);
        });
    QObject::connect(buttons[1], &QPushButton::clicked, [=]() {
        myQtManager::changerDePage(stack, MeilleursScores, G, manager);
        });
    QObject::connect(buttons[2], &QPushButton::clicked, [=]() {
        myQtManager::changerDePage(stack, Informations, G, manager);
        });
    QObject::connect(buttons[3], &QPushButton::clicked, [=]() {
        myQtManager::changerDePage(stack, Parametre, G, manager);
        });
    QObject::connect(buttons[4], &QPushButton::clicked, [=]() {
        myQtManager::changerDePage(stack, Accueil, G, manager);
        });

    // Ajouter la page au QStackedWidget
    stack->addWidget(pageMenu);

}

static void refresh(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent = nullptr)
{
    // Créer un widget pour la page du menu
    QWidget* pageMenu = new QWidget();
    pageMenu->setStyleSheet("background-color: " + COULEUR_FOND + ";");

    // Image de fond
    QLabel* backgroundLabel = new QLabel(pageMenu);
    backgroundLabel->setGeometry(0, 0, TAILLE_ECRAN_X, TAILLE_ECRAN_Y);
    QPixmap resizedPixmap("./Images/placeholder_background_login.png");
    backgroundLabel->setPixmap(resizedPixmap);
    backgroundLabel->setScaledContents(true);
    backgroundLabel->lower();

    // Ajouter une couche semi-transparente au-dessus de l'image pour un effet d'assombrissement
    QWidget* overlay = new QWidget(pageMenu);
    overlay->setGeometry(0, 0, TAILLE_ECRAN_X, TAILLE_ECRAN_Y);
    overlay->setStyleSheet("background-color: rgba(0, 0, 0, 100);"); // Ajuster l'opacité si nécessaire
    overlay->lower();

    // Conteneur central pour le menu 
    QWidget* menuBox = new QWidget(pageMenu);
    menuBox->setStyleSheet("background-color: rgba(0, 0, 0, 150); border-radius: 25px; padding: 20px;");
    menuBox->setFixedSize(600, 400);

    QVBoxLayout* menuBoxLayout = new QVBoxLayout(menuBox);
    menuBoxLayout->setAlignment(Qt::AlignCenter);

    // Titre du menu
    QLabel* titre = new QLabel("Menu Principal", menuBox);
    myQt_setFont(titre, 40);
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet(
        "color: white; "
        "font-size: 40px; "
        "font-weight: bold; "
        "text-transform: uppercase; "
        "letter-spacing: 3px; "
        "text-shadow: 3px 3px 5px rgba(0, 0, 0, 0.8); "
        "border: none; "
        "padding: 10px; "
        "background: linear-gradient(to right, #ff0000, #ff6600, #ffff00, #33cc33, #0099ff, #9900cc); "
        "border-radius: 10px;");
    menuBoxLayout->addWidget(titre);

    // Liste des boutons
    QStringList buttonNames = { "Démarrer", "Voir meilleurs scores", "Informations joueur", "Paramètres", "Déconnexion" };
    QVector<QPushButton*> buttons;

    for (const QString& name : buttonNames) {
        QPushButton* button = new QPushButton(name, menuBox);
        button->setStyleSheet(
            "QPushButton { "
            "    background-color: " + COULEUR_BOUTON + "; "
            "    color: white; "
            "    font-size: 25px; "
            "    border-radius: 5px; "
            "    padding: 5px 10px; "
            "}"
            "QPushButton:hover { "
            "    background-color: gray; "
            "    color: white; "
            "}"
        );
        button->setFixedSize(250, 50);
        buttons.append(button);
        menuBoxLayout->addWidget(button, 0, Qt::AlignCenter);
    }

    // Ajouter la box centrée dans la page
    QVBoxLayout* mainLayout = new QVBoxLayout(pageMenu);
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addStretch();
    mainLayout->addWidget(menuBox, 0, Qt::AlignCenter);
    mainLayout->addStretch();
    pageMenu->setLayout(mainLayout);

    // Connexions des boutons
    QObject::connect(buttons[0], &QPushButton::clicked, [=]() {
        myQtManager::changerDePage(stack, Game, G, manager);
        });
    QObject::connect(buttons[1], &QPushButton::clicked, [=]() {
        myQtManager::changerDePage(stack, MeilleursScores, G, manager);
        });
    QObject::connect(buttons[2], &QPushButton::clicked, [=]() {
        myQtManager::changerDePage(stack, Informations, G, manager);
        });
    QObject::connect(buttons[3], &QPushButton::clicked, [=]() {
        myQtManager::changerDePage(stack, Parametre, G, manager);
        });
    QObject::connect(buttons[4], &QPushButton::clicked, [=]() {
        myQtManager::changerDePage(stack, Accueil, G, manager);
        });

    // Ajouter la page au QStackedWidget
    stack->addWidget(pageMenu);

}


void MyQtPageMenu::setBackground()
{
}
