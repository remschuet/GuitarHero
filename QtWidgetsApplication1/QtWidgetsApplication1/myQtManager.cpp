#include "myQtManager.h"
#include <QGraphicsOpacityEffect>

void myQtManager::myQt_setFont(QLabel* q, int tailleFont) {
    QFont font = q->font();
    font.setPointSize(tailleFont);
    q->setFont(font);
}

void myQtManager::changerDePage(QStackedWidget* stack, fenetres page, Gameplay* G)
{
    // Supprimer l'ancienne page si elle existe
    QWidget* anciennePage = stack->widget(page);
    if (anciennePage != nullptr) {
        stack->removeWidget(anciennePage); // On le retire du stack
        delete anciennePage;               // On le supprime seulement après l'avoir retiré
    }

    QWidget* nouvellePage = nullptr;

    // Recréer la page demandée sans créer un QWidget vide !
    switch (page) {
    case Accueil:
        qtPageAccueil(nullptr, stack, G);  // Ici, on passe `nullptr` en parent car c'est `qtPageAccueil` qui gère ça.
        nouvellePage = stack->widget(stack->count() - 1);  // Récupère la dernière page ajoutée
        break;
    case Menu:
        qtPageMenu(nullptr, stack, G);
        nouvellePage = stack->widget(stack->count() - 1);
        break;
    case MeilleursScores:
        qtPageMeilleurScore(nullptr, stack, G);
        nouvellePage = stack->widget(stack->count() - 1);
        break;
    case Informations:
        qtPageInformations(nullptr, stack, G);
        nouvellePage = stack->widget(stack->count() - 1);
        break;
    case Parametre:
        qtPageParametres(nullptr, stack, G);
        nouvellePage = stack->widget(stack->count() - 1);
        break;
    case Game:
        qtPageGame(nullptr, stack, G);
        nouvellePage = stack->widget(stack->count() - 1);
        break;
    }
    if (nouvellePage != nullptr) {
        stack->setCurrentIndex(stack->indexOf(nouvellePage));  // ✅ Afficher la nouvelle page
    }
}

void myQtManager::afficherImage(QWidget* parentWidget, const QString& imagePath)
{
    // Créer un QLabel pour afficher l'image
    QLabel* imageLabel = new QLabel(parentWidget);

    // Charger l'image avec QPixmap
    QPixmap pixmap(imagePath);

    // Vérifier si l'image a été correctement chargée
    if (pixmap.isNull()) {
        qDebug() << "Erreur de chargement de l'image";
        return; // Si l'image ne peut pas être chargée, on arrête la fonction
    }

    // Définir l'image dans le QLabel
    imageLabel->setPixmap(pixmap);

    // Ajuster l'échelle de l'image à la taille du QLabel (facultatif)
    imageLabel->setScaledContents(true);

    // Définir la taille du QLabel pour qu'il soit adapté à l'image
    imageLabel->resize(pixmap.size());

    // Ajouter le QLabel à votre fenêtre (layout)
    imageLabel->show();
}


void myQtManager::qtPageAccueil(QWidget* parent, QStackedWidget* stack, Gameplay* G) {
    QWidget* page = new QWidget(parent);
    page->setStyleSheet("background-color: " + COULEUR_FOND + "; border-radius: 25px;");

    // Image de fond
    QLabel* backgroundLabel = new QLabel(page);
    backgroundLabel->setGeometry(0, 0, TAILLE_ECRAN_X, TAILLE_ECRAN_Y);
    QPixmap resizedPixmap("./images/placeholder_background_login.png");
    backgroundLabel->setPixmap(resizedPixmap);
    backgroundLabel->setScaledContents(true);
    backgroundLabel->lower();

    // Layout principal centré
    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->setAlignment(Qt::AlignCenter);

    // Conteneur pour centrer les éléments
    QWidget* container = new QWidget();
    QVBoxLayout* containerLayout = new QVBoxLayout(container);
    containerLayout->setAlignment(Qt::AlignCenter);

    // Titre du jeu avec effet glow vert et sans contour gris
    QLabel* labelTitre = new QLabel("Welcome to Sherby Guitar!");
    labelTitre->setAlignment(Qt::AlignCenter);
    labelTitre->setStyleSheet(
        "font-size: 50px;"
        "font-family: Impact, Haettenschweiler, 'Arial Narrow Bold', sans-serif;"
        "color: "+COULEUR_BOUTON+";"  // Vert flashy
        "font-weight: bold;"
        "letter-spacing: 2px;"
        "border-radius: 25px;"  // Arrondi du titre
        "padding: 10px;"
        "text-shadow: 3px 3px 10px rgba(0, 255, 0, 0.8), 5px 5px 15px rgba(0, 255, 0, 0.5);"
        "background: none;"  // Supprime le fond gris
    );
    containerLayout->addWidget(labelTitre);

    // Champ de nom d'utilisateur centré
    QLineEdit* inputNom = new QLineEdit();
    inputNom->setPlaceholderText("USERNAME");
    inputNom->setStyleSheet(
        "background-color: white; "
        "color: black; "
        "border-radius: 25px;"  // Arrondi du champ
        "padding: 10px; "
        "font-size: 18px;"
    );
    inputNom->setFixedSize(300, 50);
    containerLayout->addWidget(inputNom, 0, Qt::AlignHCenter);  // Centré horizontalement

    // Bouton de connexion stylé et centré
    QPushButton* btnLogin = new QPushButton("LOGIN");
    btnLogin->setStyleSheet(
        "background-color: " + COULEUR_BOUTON + "; "
        "color: " + COULEUR_TEXTE_BOUTON + "; "
        "font-size: 20px; "
        "border-radius: 25px;"  // Arrondi du bouton
        "padding: 10px;"
        "border: 2px solid white;"
    );
    btnLogin->setFixedSize(250, 50);
    containerLayout->addWidget(btnLogin, 0, Qt::AlignHCenter);  // Centré horizontalement

    layout->addWidget(container);

    // Connexion du bouton Login
    QObject::connect(inputNom, &QLineEdit::returnPressed, btnLogin, &QPushButton::click);
    QObject::connect(btnLogin, &QPushButton::clicked, [=]() {
        QString nomJoueur = inputNom->text().trimmed();
        if (nomJoueur.isEmpty()) {
            QMessageBox::warning(parent, "Erreur", "Veuillez entrer un nom d'utilisateur.");
            return;
        }

        G->setJoueur(new Joueur(nomJoueur.toStdString()));

        // Enregistrement du joueur dans la base de données
        DAOSqlite* sqlite = DAOSqlite::getInstance();
        sqlite->ajouterJoueur(nomJoueur.toStdString(), 0, "");

        // Aller au menu
        qtPageMenu(parent, stack, G);
        stack->setCurrentIndex(Menu);
        });

    // Ajout à la pile des widgets
    stack->addWidget(page);
}


void myQtManager::qtPageMenu(QWidget* parent, QStackedWidget* stack, Gameplay* G) {
    // Créer un widget pour la page du menu
    QWidget* pageMenu = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(pageMenu);
    layout->setAlignment(Qt::AlignCenter);

    // Image de fond
    QLabel* backgroundLabel = new QLabel(pageMenu);
    backgroundLabel->setGeometry(0, 0, TAILLE_ECRAN_X, TAILLE_ECRAN_Y);
    QPixmap resizedPixmap("./Images/placeholder_background_login.png");
    backgroundLabel->setPixmap(resizedPixmap);
    backgroundLabel->setScaledContents(true); // Correction pour assurer que l'image prend bien tout l'espace
    backgroundLabel->lower();

    QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect();
    opacityEffect->setOpacity(0.5);
    backgroundLabel->setGraphicsEffect(opacityEffect);

    QVBoxLayout* menuLayout = new QVBoxLayout;
    menuLayout->setAlignment(Qt::AlignCenter);
    menuLayout->setSpacing(25); // Espacement entre les éléments

    // Titre du menu avec un style inspiré de Guitar Hero
    QLabel* titre = new QLabel("Menu Principal");
    myQt_setFont(titre, 40);
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet(
        "color: white; "
        "font-size: 40px; "
        "font-weight: bold; "
        "text-transform: uppercase; "
        "letter-spacing: 3px; "
        "text-shadow: 3px 3px 5px rgba(0, 0, 0, 0.8); "
        "border: 2px solid white; "
        "padding: 10px; "
        "background: linear-gradient(to right, #ff0000, #ff6600, #ffff00, #33cc33, #0099ff, #9900cc); "
        "border-radius: 10px; "
    );
    menuLayout->addWidget(titre);

    // Liste des boutons
    QStringList buttonNames = { "Demarrer", "Voir meilleurs scores", "Informations joueur", "Paramètres" ,"Deconnexion" };
    QVector<QPushButton*> buttons;

    // Création des boutons avec un style uniforme
    for (const QString& name : buttonNames) {
        QPushButton* button = new QPushButton(name);
        button->setStyleSheet(
            "QPushButton { "
            "    background-color: green; "
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
        menuLayout->addWidget(button, 0, Qt::AlignHCenter);
    }

    // S'assurer que menuLayout est bien ajouté au layout principal
    layout->addLayout(menuLayout);

    // Gestion des connexions des boutons
    QObject::connect(buttons[0], &QPushButton::clicked, [=]() {
        fenetres QtFenetre = Game;
        changerDePage(stack, QtFenetre, G);
        });

    QObject::connect(buttons[1], &QPushButton::clicked, [=]() {
        fenetres QtFenetre = MeilleursScores;
        changerDePage(stack, QtFenetre, G);
        });

    QObject::connect(buttons[2], &QPushButton::clicked, [=]() {
        fenetres QtFenetre = Informations;
        changerDePage(stack, QtFenetre, G);
        });

    QObject::connect(buttons[3], &QPushButton::clicked, [=]() {
        fenetres QtFenetre = Parametre;
        changerDePage(stack, QtFenetre, G);
        });

    QObject::connect(buttons[4], &QPushButton::clicked, [=]() {
        fenetres QtFenetre = Accueil;
        changerDePage(stack, QtFenetre, G);
        });

    // Ajouter la page au QStackedWidget
    stack->addWidget(pageMenu);
}


void myQtManager::qtPageInformations(QWidget* parent, QStackedWidget* stack, Gameplay* G)
{
    QWidget* window = new QWidget(parent);
    window->setStyleSheet(QString("background-color: %1;").arg(COULEUR_FOND));

    std::string nom = "Inconnu";
    int score = 0;
    QString imagePath = "";

    if (G->getJoueur() != nullptr) {
        Joueur* joueurlog = G->getJoueur();
        nom = joueurlog->getNomJoueur();
     
        imagePath = QString::fromStdString("./images/avatar.jpeg");
    }

    // Layout principal
    QVBoxLayout* mainLayout = new QVBoxLayout(window);
    mainLayout->setAlignment(Qt::AlignTop);

    QLabel* title = new QLabel("INFORMATIONS", window);
    myQt_setFont(title, QT_TITLE);
    title->setStyleSheet(QString("color: %1; border: 3px solid %1; padding: 10px;").arg(COULEUR_TITRE));
    title->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(title);

    // Cadre infos
    QFrame* infoFrame = new QFrame(window);
    infoFrame->setStyleSheet(QString("border: 3px solid %1; background-color: %2; padding: 15px; border-radius: 15px;")
        .arg(COULEUR_TITRE));
    QVBoxLayout* infoLayout = new QVBoxLayout(infoFrame);

    // Infos texte
    QHBoxLayout* pseudoLayout = new QHBoxLayout();
    QLabel* pseudoLabel = new QLabel("Pseudo :", window);
    myQt_setFont(pseudoLabel, QT_SUBTITLE);
    pseudoLabel->setStyleSheet(QString("color: %1;").arg(COULEUR_TEXTE));
    QLabel* pseudoValue = new QLabel(QString::fromStdString(nom), window);
    myQt_setFont(pseudoValue, QT_SUBTITLE);
    pseudoValue->setStyleSheet(QString("color: %1; font-weight: bold;").arg(COULEUR_TEXTE));
    pseudoLayout->addWidget(pseudoLabel);
    pseudoLayout->addWidget(pseudoValue);

    QHBoxLayout* scoreLayout = new QHBoxLayout();
    QLabel* scoreLabel = new QLabel("Score :", window);
    myQt_setFont(scoreLabel, QT_SUBTITLE);
    scoreLabel->setStyleSheet(QString("color: %1;").arg(COULEUR_TEXTE));
    QLabel* scoreValue = new QLabel(QString::number(score), window);
    myQt_setFont(scoreValue, QT_SUBTITLE);
    scoreValue->setStyleSheet(QString("color: %1; font-weight: bold;").arg(COULEUR_TEXTE));
    scoreLayout->addWidget(scoreLabel);
    scoreLayout->addWidget(scoreValue);

    QVBoxLayout* detailsLayout = new QVBoxLayout();
    detailsLayout->addLayout(pseudoLayout);
    detailsLayout->addLayout(scoreLayout);
    infoLayout->addLayout(detailsLayout);
    infoFrame->setLayout(infoLayout);
    mainLayout->addWidget(infoFrame);

    // Image
    QLabel* imageLabel = new QLabel(window);
    QPixmap pixmap(imagePath);  // Charger l'image
    if (!pixmap.isNull()) {
        imageLabel->setPixmap(pixmap.scaled(150, 150, Qt::KeepAspectRatio)); // Ajuster la taille de l'image si nécessaire
    }
    else {
        imageLabel->setText("Image non disponible");
    }

    mainLayout->addWidget(imageLabel); // Ajouter l'image au layout

    // Retour
    QPushButton* backButton = new QPushButton("Retour", window);
    backButton->setStyleSheet(QString(
        "background-color: %1; color: %2; border: 2px solid %3; padding: 10px; border-radius: 10px; font-size: 18px; font-weight: bold;"
    ).arg(COULEUR_BOUTON)
        .arg(COULEUR_TEXTE_BOUTON)
        .arg(COULEUR_BOUTON));
    QObject::connect(backButton, &QPushButton::clicked, [stack]() {
        stack->setCurrentIndex(Menu); // ou l'index du menu
        });
    mainLayout->addWidget(backButton, 0, Qt::AlignLeft);

    stack->addWidget(window);
}


void myQtManager::qtPageFinPartie(QWidget* window, QStackedWidget* stack, Gameplay* G)
{
    QDialog* finPartieDialog = new QDialog(window);
    finPartieDialog->setWindowTitle("Fin de Partie");
    finPartieDialog->setModal(true); // Pour s'assurer qu'on ne peut pas interagir avec le gameplay
    finPartieDialog->setFixedSize(300, 200);

    QVBoxLayout* layout = new QVBoxLayout(finPartieDialog);
    QLabel* message = new QLabel("La partie est terminée !", finPartieDialog);
    message->setAlignment(Qt::AlignCenter);

    QPushButton* restartButton = new QPushButton("Rejouer", finPartieDialog);
    QPushButton* quitButton = new QPushButton("Retourner au menu", finPartieDialog);

    layout->addWidget(message);
    layout->addWidget(restartButton);
    layout->addWidget(quitButton);

    // Connexions des boutons
    QObject::connect(restartButton, &QPushButton::clicked, [stack, finPartieDialog]() {
        stack->setCurrentIndex(Game); // Supposons que l'index 0 soit celui du gameplay
        finPartieDialog->accept();
        });

    QObject::connect(quitButton, &QPushButton::clicked, [stack, finPartieDialog]() {
        stack->setCurrentIndex(Menu);
        finPartieDialog->accept();
        });

    // Affichage de la boîte de dialogue
    finPartieDialog->exec();
}

void myQtManager::qtPageParametres(QWidget* window, QStackedWidget* stack, Gameplay* G)
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
    QPixmap resizedPixmap("./images/Setting.png");
    backgroundLabel->setPixmap(resizedPixmap);
    backgroundLabel->setScaledContents(true);  // L'image de fond ne sera pas redimensionnée
    backgroundLabel->lower();
    QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect();
    opacityEffect->setOpacity(0.5);  // Appliquer un effet de transparence
    backgroundLabel->setGraphicsEffect(opacityEffect);

    // Ajouter un espacement entre le titre et les boutons
    QWidget* spacerTop = new QWidget();
    spacerTop->setFixedHeight(200);  // Espacement vertical
    layout->addWidget(spacerTop, 1, 0, 1, 3);  // Ajouter un widget vide comme espacement

    // Liste des boutons
    QStringList buttonNames = { "Difficulté", "Paramètre de la manette", "Mode Admin" };
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
        fenetres QtFenetre = Accueil;
        changerDePage(stack, QtFenetre, G);
        });

    QObject::connect(btnRetour, &QPushButton::clicked, [=]() {
        stack->setCurrentIndex(0); // Retour au menu principal
        });

    // Ajouter la page au QStackedWidget
    stack->addWidget(pageParametre);
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
    titre->setStyleSheet(COULEUR_FOND);
    mainLayout->addWidget(titre);

    //debug
    qDebug() << "qtPageMeilleurScore appelée\n";

    // Récupération des meilleurs scores depuis Gameplay
    std::pair < std::string, int> scores[10];
    DAOSqlite* sqlite = DAOSqlite::getInstance();
    sqlite->getMeilleurScore(scores);
    // Affichage des scores
    for (size_t i = 0; i < 10; ++i) {
        if (scores[i].first != "") {
            // Définition des couleurs et des médailles
            QString bgColor = "rgba(128, 128, 128, 0.5)"; // Fond général vert pour toutes les cartes
            QString textColor = COULEUR_TEXTE_BOUTON; // Blanc pour contraste
            QString medal;
            QString borderColor = COULEUR_IMAGE_BORDURE; // Bordure verte par défaut
            QString nameBgColor; // Couleur de fond pour le nom du joueur
            QString positionTextColor; // Couleur pour le texte de la position

            // Couleurs spécifiques pour les noms et positions du top 3, gris transparent pour les autres
            if (i == 0) {
                medal = "🥇";
                borderColor = "#FFD700"; // Or pour la bordure
                nameBgColor = "#FFD700"; // Fond or pour le nom
                positionTextColor = "#FFD700"; // Or pour la position
                textColor = "#FFD700";
            }
            else if (i == 1) {
                medal = "🥈";
                borderColor = "#C0C0C0"; // Argent pour la bordure
                nameBgColor = "#C0C0C0"; // Fond argent pour le nom
                positionTextColor = "#C0C0C0"; // Argent pour la position
                textColor = "#C0C0C0";
            }
            else if (i == 2) {
                medal = "🥉";
                borderColor = "#CD7F32"; // Bronze pour la bordure
                nameBgColor = "#CD7F32"; // Fond bronze pour le nom
                positionTextColor = "#CD7F32"; // Bronze pour la position
                textColor = "#CD7F32";


            }
            else {
                nameBgColor = COULEUR_TEXTE_BOUTON; // Gris semi-transparent pour les autres
                positionTextColor = "#0000"; // Vert clair pour les positions hors top 3
            }

            // Conteneur principal du score (Style carte)
            QFrame* scoreCard = new QFrame();
            scoreCard->setStyleSheet("background-color: " + bgColor + "; "
                "border: 2px solid " + borderColor + "; "
                "border-radius: 10px; "
                "padding: 10px;");

            QHBoxLayout* rowLayout = new QHBoxLayout(scoreCard);

            // Position + Médaille
            QLabel* position = new QLabel(QString::number(i + 1) + ". " + medal);
            position->setFixedWidth(60);
            position->setFixedHeight(40);
            position->setStyleSheet("font-weight: bold; color: " + positionTextColor + ";"); // Couleur ajustée pour la position
            rowLayout->addWidget(position);

            // Nom du joueur avec fond spécifique
            QLabel* nomJoueur = new QLabel(QString::fromStdString(scores[i].first));
            nomJoueur->setFixedWidth(120);
            nomJoueur->setStyleSheet("font-weight: bold; color: #000000;" // Noir sur or/argent/bronze, vert foncé sur gris
                "background-color: " + nameBgColor + "; "
                "border-radius: 5px; "
                "padding: 2px;");
            nomJoueur->setFixedHeight(35);

            rowLayout->addWidget(nomJoueur);

            // Score
            QLabel* score = new QLabel(QString::number(scores[i].second));
            score->setFixedWidth(60);
            score->setStyleSheet("font-weight: bold; color: " + textColor + ";"); // Blanc
            score->setFixedHeight(35);
            rowLayout->addWidget(score);

            // Ajouter le cadre au layout principal
            mainLayout->addWidget(scoreCard);

            // Debug
            qDebug() << "Score[" << i << "] : " << QString::fromStdString(scores[i].first) << " - " << scores[i].second;
        }
    }    // Bouton retour aligné à droite
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

void myQtManager::qtPageGame(QWidget* window, QStackedWidget* stack, Gameplay* G)
{
    QWidget* pageGame = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(pageGame);

    QLabel* gameLabel = new QLabel(pageGame);
    gameLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(gameLabel);

    int pageIndex = stack->addWidget(pageGame); // Add the page and get its index
    qDebug() << "PageGame ajouté à l'index :" << pageIndex;

    QObject::connect(stack, &QStackedWidget::currentChanged, [stack, pageGame, G, gameLabel](int index) {
        qDebug() << "Index actuel changé à :" << index;
        if (stack->widget(index) == pageGame) {
            qDebug() << "PageGame est affichée!";
            G->demarrerPartie(gameLabel);
        }
        });
    stack->addWidget(pageGame);
}