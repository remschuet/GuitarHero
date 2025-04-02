#include "MyQtPageAccueil.h"
#include "MyQtPageMenu.h"

MyQtAccueil::MyQtAccueil(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent)
    : MyQtPage(stack, G, manager, parent) {

}

void MyQtAccueil::refresh(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent)
{

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

    // Conteneur pour centrer les éléments avec fond semi-transparent
    QWidget* container = new QWidget();
    container->setStyleSheet(
        "background-color: rgba(0, 0, 0, 150); " // Semi-transparence
        "border-radius: 25px;"
        "padding: 20px;"
    );
    QVBoxLayout* containerLayout = new QVBoxLayout(container);
    containerLayout->setAlignment(Qt::AlignCenter);

    // Titre du jeu avec effet glow vert et sans contour gris
    QLabel* labelTitre = new QLabel("Welcome to Sherby Guitar!");
    labelTitre->setAlignment(Qt::AlignCenter);
    labelTitre->setStyleSheet(
        "font-size: 50px;"
        "font-family: Impact, Haettenschweiler, 'Arial Narrow Bold', sans-serif;"
        "color: " + COULEUR_BOUTON + ";"  // Vert flashy
        "font-weight: bold;"
        "letter-spacing: 2px;"
        "text-shadow: 3px 3px 10px rgba(0, 255, 0, 0.8), 5px 5px 15px rgba(0, 255, 0, 0.5);"
        "background: none;"
    );
    containerLayout->addWidget(labelTitre);

    // Champ de nom d'utilisateur centré
    QLineEdit* inputNom = new QLineEdit();
    inputNom->setPlaceholderText("USERNAME");
    inputNom->setStyleSheet(
        "background-color: white; "
        "color: black; "
        "border-radius: 25px; "
        "padding: 10px; "
        "font-size: 18px;"
    );
    inputNom->setFixedSize(300, 50);
    containerLayout->addWidget(inputNom, 0, Qt::AlignHCenter);

    // Bouton de connexion stylé et centré
    QPushButton* btnLogin = new QPushButton("LOGIN");
    btnLogin->setStyleSheet(
        "QPushButton { "
        "    background-color: " + COULEUR_BOUTON + "; "
        "    color: white; "
        "    font-size: 25px; "
        "    border-radius: 25px; "
        "    padding: 5px 10px; "
        "}"
        "QPushButton:hover { "
        "    background-color: gray; "
        "    color: white; "
        "}"
    );
    btnLogin->setFixedSize(250, 50);
    containerLayout->addWidget(btnLogin, 0, Qt::AlignHCenter);

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
        myQtManager::changerDePage(stack, Menu, G, manager);
        stack->setCurrentIndex(Menu);
        });

    // Ajout à la pile des widgets
    stack->addWidget(page);
}

void MyQtAccueil::setBackground()
{
}
