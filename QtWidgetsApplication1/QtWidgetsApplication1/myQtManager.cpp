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

    QLabel* titre = new QLabel("Menu Principal");
    myQt_setFont(titre, 20);
    layout->addWidget(titre);
    layout->setAlignment(titre, Qt::AlignHCenter | Qt::AlignTop);

    //QPushButton* btnStart = new QPushButton("Démarrer");
    //layout->addWidget(btnStart);

    // Bouton Meilleurs Scores
    QPushButton* btnMeilleursScores = new QPushButton("Voir meilleurs scores", pageMenu);
    btnMeilleursScores->setStyleSheet("background-color: " + COULEUR_BOUTON + "; color: " + COULEUR_TEXTE_BOUTON + "; font-size: 18px; border-radius: 5px; padding: 10px;");
    layout->addWidget(btnMeilleursScores);
    layout->setAlignment(btnMeilleursScores, Qt::AlignHCenter | Qt::AlignTop);
    layout->setSpacing(20);
    //btnMeilleursScores->setGeometry((TAILLE_ECRAN_X - 900) / 2, 620, 200, 50);;
    QObject::connect(btnMeilleursScores, &QPushButton::clicked, [=]() {
        fenetres QtFenetre = MeilleursScores;
        // Configurer la page du menu et rediriger
        qtPageMenu(parent, stack, G);
        qDebug() << "index actuel : " << QtFenetre;
        stack->setCurrentIndex(QtFenetre); 
        });

    //Bouton Informations joueur
    QPushButton* btnInfosJoueur = new QPushButton("Informations joueur", pageMenu);
    btnInfosJoueur->setStyleSheet("background-color: " + COULEUR_BOUTON + "; color: " + COULEUR_TEXTE_BOUTON + "; font-size: 18px; border-radius: 5px; padding: 10px;");
    btnInfosJoueur->setGeometry((TAILLE_ECRAN_X - 900) / 2, 520, 200, 50);;
    QObject::connect(btnInfosJoueur, &QPushButton::clicked, [=]() {
        fenetres QtFenetre = Informations;
        // Configurer la page du menu et rediriger
        qtPageMenu(parent, stack, G);
        qDebug() << "index actuel : " << QtFenetre;
        stack->setCurrentIndex(QtFenetre); 
        });


    //bouton Commencer Partie
    QPushButton* btnCommencerPartie = new QPushButton("Demarrer ", pageMenu);
    btnCommencerPartie->setStyleSheet("background-color: " + COULEUR_BOUTON + "; color: " + COULEUR_TEXTE_BOUTON + "; font-size: 18px; border-radius: 5px; padding: 10px;");
    btnCommencerPartie->setGeometry((TAILLE_ECRAN_X - 900) / 2, 320, 200, 50);;
    QObject::connect(btnCommencerPartie, &QPushButton::clicked, [=]() {
        fenetres QtFenetre = Parametre; //La page partie n'existe pas encore                 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                                                                                                           // À changer!!!
        // Configurer la page du menu et rediriger
        qtPageMenu(parent, stack, G);
        qDebug() << "index actuel : " << QtFenetre;
        stack->setCurrentIndex(QtFenetre);
        });

    //bouton Déconnexion (changement de joueur)
    QPushButton* btnDeconnexion = new QPushButton("Deconnexion", pageMenu);
    btnDeconnexion->setStyleSheet("background-color: " + COULEUR_BOUTON + "; color: " + COULEUR_TEXTE_BOUTON + "; font-size: 18px; border-radius: 5px; padding: 10px;");
    btnDeconnexion->setGeometry((TAILLE_ECRAN_X ) / 2, 620, 200, 50);;
    QObject::connect(btnDeconnexion, &QPushButton::clicked, [=]() {
        fenetres QtFenetre = Accueil;
        // Configurer la page du menu et rediriger
        qtPageMenu(parent, stack, G);
        qDebug() << "index actuel : " << QtFenetre;
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
}

void myQtManager::qtPageMeilleurScore(QWidget* window, QStackedWidget* stack, Gameplay* G)
{
    QWidget* pageMeilleursScores = new QWidget();
    stack->addWidget(pageMeilleursScores);
}


