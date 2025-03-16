#include "myQtManager.h"
#include "CONST_QT.h"

void myQtManager::myQt_setFont(QLabel* q, int tailleFont) {
    // Créer un objet QFont et définir la taille de la police
    QFont font = q->font();
    font.setPointSize(tailleFont);

    // Appliquer la nouvelle police au QLabel
    q->setFont(font);
}

void myQtManager::qtPageInformations(QWidget* parent, QStackedWidget* stack) {
    QWidget* window = new QWidget();
    window->setStyleSheet("background-color: " + COULEUR_FOND + ";");  // Fond vert foncé

    std::string nom = "bob";
    int score = 1230;

    window->setWindowTitle("Informations");

    // Titre
    QLabel* title = new QLabel("Informations", window);
    myQt_setFont(title, QT_TITLE);
    title->setStyleSheet("color: " + COULEUR_TITRE + ";");  // Vert très foncé
    title->move(670, 30);

    // Espacement entre le titre et le texte
    int espaceVertical = 50;

    // Pseudo et Score
    QLabel* pseudoLabel = new QLabel("Pseudo", window);
    myQt_setFont(pseudoLabel, QT_SUBTITLE);
    pseudoLabel->setStyleSheet("color: " + COULEUR_TEXTE + ";");  // Vert clair
    pseudoLabel->move(150, 150);

    QLabel* pseudoValue = new QLabel(QString::fromStdString(nom), window);
    myQt_setFont(pseudoValue, QT_SUBTITLE);
    pseudoValue->setStyleSheet("color: " + COULEUR_TEXTE + ";");  // Blanc
    pseudoValue->move(350, 150);

    QLabel* scoreLabel = new QLabel("Score", window);
    myQt_setFont(scoreLabel, QT_SUBTITLE);
    scoreLabel->setStyleSheet("color: " + COULEUR_TEXTE + ";");  // Vert clair
    scoreLabel->move(150, 150 + pseudoLabel->height() + espaceVertical);  // Espacement vertical

    QLabel* scoreValue = new QLabel(QString::number(score, 10), window);
    myQt_setFont(scoreValue, QT_SUBTITLE);
    scoreValue->setStyleSheet("color: " + COULEUR_TEXTE + ";");  // Blanc
    scoreValue->move(350, 150 + pseudoLabel->height() + espaceVertical);  // Espacement vertical

    // Bouton Retour
    QPushButton* backButton = new QPushButton("Retour", window);
    backButton->setStyleSheet("background-color: " + COULEUR_BOUTON + "; color: " + COULEUR_TEXTE_BOUTON + "; "
        "border-radius: 10px; padding: 10px;");
    backButton->move(150, 400);

    // Ajouter une image à droite
    QLabel* imageLabel = new QLabel(window);
    QPixmap image("path_to_image.png"); // Remplacer par le chemin de ton image
    imageLabel->setPixmap(image.scaled(300, 300, Qt::KeepAspectRatio));
    imageLabel->setStyleSheet("border: 2px solid " + COULEUR_IMAGE_BORDURE + ";");  // Bordure verte
    imageLabel->move(TAILLE_ECRAN_X - 350, 150);

    // Changer de page au clic sur "Retour"
    QObject::connect(backButton, &QPushButton::clicked, [stack]() {
        stack->setCurrentIndex(0); // Retour au menu
        });

    stack->addWidget(window);
}

void myQtManager::qtPageMenu(QWidget* parent, QStackedWidget* stack, Gameplay* gameplay) {
    QWidget* window = new QWidget();
    window->setWindowTitle("Menu");

    //paramteres du joueur
    QPushButton* infoButton = new QPushButton("Parametres du joueur", window);
    infoButton->move(500, 300);
    

    //Titre du jeu
    QLabel* nomJeu = new QLabel("Guitar Hero UDS", window);
    myQt_setFont(nomJeu, QT_TITLE);
    nomJeu->setStyleSheet("color: " + COULEUR_TITRE + ";");  // Vert très foncé
    nomJeu->move(430, 30);

    //meilleur score
    QLabel* meilleurScore = new QLabel("Meilleur score: 1000", window);
    myQt_setFont(meilleurScore, QT_SUBTITLE);
    meilleurScore->setStyleSheet("color: " + COULEUR_TITRE + ";");  // Vert très foncé
    meilleurScore->move(430, 200);
    
    //image du joueur
    QLabel* imageLabel = new QLabel(window);
    QPixmap image("C:/Users/Jovan/Desktop/Git/GuitarHero/GuitareHeroPC/GuitareHeroPC/avatar.jpeg"); // Remplacer par le chemin de ton image
    imageLabel->setPixmap(image.scaled(100, 100, Qt::KeepAspectRatio));
    imageLabel->setStyleSheet("border: 2px solid " + COULEUR_IMAGE_BORDURE + ";");  // Bordure verte
    imageLabel->move(1000, 200);

    // Changer de page au clic
    QObject::connect(infoButton, &QPushButton::clicked, [stack]() {
        stack->setCurrentIndex(1); // Aller à la page d'informations
        });    

    stack->addWidget(window);
}
void myQtManager::qtPageAccueil(QWidget* parent, QStackedWidget* stack)
{
    QWidget* window = new QWidget();

    //image en background
    QLabel* imageLabel = new QLabel(window);
    QPixmap image("Path.png");
    imageLabel->setPixmap(image.scaled(1920, 1080, Qt::KeepAspectRatio));
    //pas de bordure (tous l'écran) et ne bouge pas par rapport à l'écran

    //login box

}

void myQtManager::qtPageFinPartie(QWidget* window)
{
}

void myQtManager::qtPageParametres(QWidget* window)
{
}

void myQtManager::qtPageMeilleurScore(QWidget* window)
{
}

