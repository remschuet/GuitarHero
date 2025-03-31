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
    case FinPartie:
        qtPageFinPartie(nullptr, stack, G);
        nouvellePage = stack->widget(stack->count() - 1);
        break;
    case Parametre:
        qtPageParametres(nullptr, stack, G);
        nouvellePage = stack->widget(stack->count() - 1);
        break;
    case Game:
        qtPageGameplay(nullptr, stack, G);
        nouvellePage = stack->widget(stack->count() - 1);
        break;
    }


    if (nouvellePage != nullptr) {
        stack->setCurrentIndex(stack->indexOf(nouvellePage));  // ✅ Afficher la nouvelle page
    }
}


void myQtManager::qtPageAccueil(QWidget* parent, QStackedWidget* stack, Gameplay* G) {

    QWidget* page = new QWidget(parent);
    page->setStyleSheet("background-color: " + COULEUR_FOND + ";");
    // Image de fond
    QLabel* backgroundLabel = new QLabel(page);
    backgroundLabel->setGeometry(0, 0, TAILLE_ECRAN_X, TAILLE_ECRAN_Y);
    QPixmap resizedPixmap("./images/placeholder_background_login.png");
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

void myQtManager::qtPageGameplay(QWidget* parent, QStackedWidget* stack, Gameplay* G)
{
    QWidget* pageGameplay = new QWidget();
    stack->addWidget(pageGameplay);
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
    backgroundLabel->setScaledContents(false);
    backgroundLabel->lower();

    QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect();
    opacityEffect->setOpacity(0.5);
    backgroundLabel->setGraphicsEffect(opacityEffect);

    // Conteneur blanc pour le menu (titre + boutons)
    QFrame* menuContainer = new QFrame();
    menuContainer->setStyleSheet("background-color: white; border-radius: 15px; padding: 15px;");
    menuContainer->setFixedSize(450, 500); // Ajuste la hauteur pour inclure le titre

    QVBoxLayout* menuLayout = new QVBoxLayout(menuContainer);
    menuLayout->setAlignment(Qt::AlignCenter);
    menuLayout->setSpacing(25); // Espacement entre les éléments

    // Titre du menu
    QLabel* titre = new QLabel("Menu Principal");
    myQt_setFont(titre, 20);
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet("color: green; border-radius: 5px; padding: 5px; font-size: 20px;");
    menuLayout->addWidget(titre);

    // Liste des boutons
    QStringList buttonNames = { "Demarrer", "Voir meilleurs scores", "Informations joueur","Paramètres" ,"Deconnexion" };
    QVector<QPushButton*> buttons;

    // Création des boutons avec un style uniforme
    // Création des boutons avec un style uniforme et ajout d'espacement
    for (const QString& name : buttonNames) {
        QPushButton* button = new QPushButton(name);
        button->setStyleSheet("background-color: " + COULEUR_BOUTON +
            "; color: " + COULEUR_TEXTE_BOUTON +
            "; font-size: 18px; border-radius: 5px; padding: 10px;");
        button->setFixedSize(250, 50);
        buttons.append(button);

        menuLayout->addWidget(button, 0, Qt::AlignHCenter);
    }


    // Ajouter le conteneur du menu au layout principal
    layout->addWidget(menuContainer, 0, Qt::AlignHCenter);

    // Gestion des connexions des boutons
    QObject::connect(buttons[0], &QPushButton::clicked, [=]() {
        fenetres QtFenetre = Parametre; // Page à changer
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




// Autres fonctions (à implémenter )
void myQtManager::qtPageInformations(QWidget* parent, QStackedWidget* stack, Gameplay* G)
{
    QWidget* window = new QWidget(parent);
    window->setStyleSheet(QString("background-color: %1;").arg(COULEUR_FOND));

    std::string nom = "Inconnu";
    int score = 0;
    

    if (G->getJoueur() != nullptr) {
        Joueur* joueurlog = G->getJoueur();
        nom = joueurlog->getNomJoueur();
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
    for (size_t i = 0; i < 10; ++i) {
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

