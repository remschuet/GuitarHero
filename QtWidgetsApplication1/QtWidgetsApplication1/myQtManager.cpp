#include "myQtManager.h"

void myQtManager::myQt_setFont(QLabel* q, int tailleFont) {
    QFont font = q->font();
    font.setPointSize(tailleFont);
    q->setFont(font);
}

void myQtManager::qtPageAccueil(QWidget* parent, QStackedWidget* stack, Gameplay* G) {

    QWidget* page = new QWidget(parent);
    page->setStyleSheet("background-color: " + COULEUR_FOND + ";");
    // Image de fond
    QLabel* backgroundLabel = new QLabel(page);
    backgroundLabel->setGeometry(0, 0, TAILLE_ECRAN_X, TAILLE_ECRAN_Y);
    QPixmap resizedPixmap("placeholder_background_login.png");
    // QPixmap resizedPixmap = originalPixmap.scaled(TAILLE_ECRAN_X, TAILLE_ECRAN_Y, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    backgroundLabel->setPixmap(resizedPixmap);
    backgroundLabel->setScaledContents(false);
    backgroundLabel->lower();


    // Titre
    QLabel* labelTitre = new QLabel(page);
    labelTitre->setText("Welcome to Sherby Guitar !");
    labelTitre->setAlignment(Qt::AlignCenter);
    labelTitre->setStyleSheet("font-size: " + QString::number(QT_TITLE) + "px; color: " + COULEUR_TITRE + "; font-weight: bold;");
    labelTitre->setGeometry((TAILLE_ECRAN_X - 1750) / 2, 200, 1100, 100);

    // Sous-layout pour l'entrée du pseudo et mot de passe
    //QVBoxLayout* formLayout = new QVBoxLayout();

    //nom du joueur
    QLineEdit* inputNom = new QLineEdit(page);
    inputNom->setPlaceholderText("USERNAME");
    inputNom->setStyleSheet("background-color: white; color: black; border-radius: 5px; padding: 5px; font-size: 16px;");
    inputNom->setGeometry((TAILLE_ECRAN_X - 1100) / 2, 550, 400, 50);


    // formLayout->addWidget(inputNom);
// Bouton Login
    QPushButton* btnLogin = new QPushButton("LOGIN", page);
    btnLogin->setStyleSheet("background-color: " + COULEUR_BOUTON + "; color: " + COULEUR_TEXTE_BOUTON + "; font-size: 18px; border-radius: 5px; padding: 10px;");
    btnLogin->setGeometry((TAILLE_ECRAN_X - 900) / 2, 620, 200, 50);;

    // Associer le bouton login à la création du joueur
    QObject::connect(btnLogin, &QPushButton::clicked, [=]() {
        QString nomJoueur = inputNom->text().trimmed();
        if (nomJoueur.isEmpty()) {
            QMessageBox::warning(parent, "Erreur", "Veuillez entrer un nom d'utilisateur.");
            return;
        }

        G->setJoueur(new Joueur(nomJoueur.toStdString()));
        QMessageBox::information(parent, "Bienvenue", "Joueur " + nomJoueur);

        fenetres QtFenetre = Menu;


        // Configurer la page du menu et rediriger
        qtPageMenu(parent, stack, G);
        stack->setCurrentIndex(QtFenetre); // Aller à la dernière page ajoutée (menu)
        });

    // Définir la mise en page
    stack->addWidget(page);
}



void myQtManager::qtPageMenu(QWidget* parent, QStackedWidget* stack, Gameplay* G) {
    // Créer un widget pour la page du menu
    QWidget* pageMenu = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(pageMenu);
    layout->setAlignment(Qt::AlignCenter);

    // Titre du menu
    QLabel* titre = new QLabel("Menu Principal");
    myQt_setFont(titre, 20);
    layout->addWidget(titre, 0, Qt::AlignHCenter);

    // Espacement entre le titre et les boutons
    layout->addSpacing(30);

    // Liste des boutons
    QStringList buttonNames = { "Demarrer", "Voir meilleurs scores", "Informations joueur", "Deconnexion" };
    QVector<QPushButton*> buttons;

    // Création des boutons avec un style uniforme
    for (const QString& name : buttonNames) {
        QPushButton* button = new QPushButton(name);
        button->setStyleSheet("background-color: " + COULEUR_BOUTON +
            "; color: " + COULEUR_TEXTE_BOUTON +
            "; font-size: 18px; border-radius: 5px; padding: 10px;");
        button->setFixedSize(250, 50);
        buttons.append(button);
        layout->addWidget(button, 0, Qt::AlignHCenter);
    }

    // Gestion des connexions des boutons
    QObject::connect(buttons[0], &QPushButton::clicked, [=]() {
        fenetres QtFenetre = Parametre; // Page à changer
        stack->setCurrentIndex(QtFenetre);
        });

    QObject::connect(buttons[1], &QPushButton::clicked, [=]() {
        fenetres QtFenetre = MeilleursScores;
        stack->setCurrentIndex(QtFenetre);
        });

    QObject::connect(buttons[2], &QPushButton::clicked, [=]() {
        fenetres QtFenetre = Informations;
        stack->setCurrentIndex(QtFenetre);
        });

    QObject::connect(buttons[3], &QPushButton::clicked, [=]() {
        fenetres QtFenetre = Accueil;
        stack->setCurrentIndex(QtFenetre);
        });

    // Ajouter la page au QStackedWidget
    stack->addWidget(pageMenu);
}



// Autres fonctions (à implémenter )
void myQtManager::qtPageInformations(QWidget* parent, QStackedWidget* stack, Gameplay* G)
{
    QWidget* pageInformations = new QWidget();
    stack->addWidget(pageInformations);
}

void myQtManager::qtPageFinPartie(QWidget* window, QStackedWidget* stack, Gameplay* G)
{
    QWidget* pageFinPartie= new QWidget();
    stack->addWidget(pageFinPartie);
}

void myQtManager::qtPageParametres(QWidget* window, QStackedWidget* stack, Gameplay* G)
{
    QWidget* pageParametres = new QWidget();
    stack->addWidget(pageParametres);

    QPushButton* btnRetour = new QPushButton("Retour");
    btnRetour->setStyleSheet("background-color: red; color: white; padding: 5px 10px;");
    btnRetour->setFixedSize(80, 30);

    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(btnRetour);

}

void myQtManager::qtPageMeilleurScore(QWidget* window, QStackedWidget* stack, Gameplay* G)
{
    QWidget* pageMeilleursScores = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout(pageMeilleursScores);

    // Titre "Meilleur Score"
    QLabel* titre = new QLabel("Meilleur Score");
    titre->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    QFont fontTitre("Arial", 16, QFont::Bold);
    titre->setFont(fontTitre);
    mainLayout->addWidget(titre);

    //debug
    qDebug() << "qtPageMeilleurScore appelée\n";

    // Récupération des meilleurs scores depuis Gameplay
    std::pair < std::string, int> scores[10];
    DAOSqlite* sqlite = DAOSqlite::getInstance();
    sqlite->getMeilleurScore(scores);

    // Affichage des scores
    for (size_t i = 0; i < 10 && i < 10; ++i) {
        if (scores[i].first != "")
        {
            QHBoxLayout* rowLayout = new QHBoxLayout();

            // Position
            QLabel* position = new QLabel(QString::number(i + 1) + ".");
            position->setFixedWidth(30);
            rowLayout->addWidget(position);

            // Nom du joueur
            QLabel* nomJoueur = new QLabel(QString::fromStdString(scores[i].first));
            nomJoueur->setFixedWidth(100);
            rowLayout->addWidget(nomJoueur);

            // Score
            QLabel* score = new QLabel(QString::number(scores[i].second));
            score->setFixedWidth(50);
            rowLayout->addWidget(score);

            /*// Icône du joueur (remplace l'ancien label par une image)
            QLabel* icone = new QLabel();
            QPixmap pixmap(QString::fromStdString(scores[i].first)); // Récupère le chemin de l'image
            pixmap = pixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation); // Redimensionne l'image
            icone->setPixmap(pixmap);
            rowLayout->addWidget(icone);

            mainLayout->addLayout(rowLayout);
            */
        }
    }

    // Bouton retour aligné à droite
    QPushButton* btnRetour = new QPushButton("Retour");
    btnRetour->setStyleSheet("background-color: red; color: white; padding: 5px 10px;");
    btnRetour->setFixedSize(80, 30);

    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(btnRetour);
    mainLayout->addLayout(btnLayout);

    // Action du bouton retour
    QObject::connect(btnRetour, &QPushButton::clicked, [stack]() {
        stack->setCurrentIndex(0); // Retour au menu principal
        });

    pageMeilleursScores->setLayout(mainLayout);
    stack->addWidget(pageMeilleursScores);
}


