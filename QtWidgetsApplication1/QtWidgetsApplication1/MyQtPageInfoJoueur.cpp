#include "MyQtPageInfoJoueur.h"

MyQtPageInfoJoueur::MyQtPageInfoJoueur(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent)
    : MyQtPage(stack, G, manager, parent) {

    QWidget* window = new QWidget(parent);
    window->setStyleSheet(QString("background-color: %1;").arg(COULEUR_FOND));

    std::string nom = "Inconnu";
    int score = 0;
    QString imagePath = "";

    if (G->getJoueur() != nullptr) {
        Joueur* joueurlog = G->getJoueur();
        nom = joueurlog->getNomJoueur();
        imagePath = QString::fromStdString("./images/avatar.jpeg"); // Chemin de l'image
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

    // Layout pour afficher l'image, le texte et le bouton côte à côte
    QHBoxLayout* imageLayout = new QHBoxLayout();

    // Charger l'image
    QLabel* imageLabel = new QLabel(window);
    QPixmap pixmap(imagePath);  // Charger l'image de l'avatar
    if (!pixmap.isNull()) {
        imageLabel->setPixmap(pixmap.scaled(150, 150, Qt::KeepAspectRatio)); // Ajuster la taille de l'image
    }
    else {
        imageLabel->setText("Image non disponible");
    }

    // Ajouter un texte à côté de l'image
    QLabel* textLabel = new QLabel("Avatar utilisé", window);
    myQt_setFont(textLabel, QT_SUBTITLE);
    textLabel->setStyleSheet(QString("color: %1; font-weight: bold;").arg(COULEUR_TEXTE));

    // Ajouter le bouton "Modifier l'image"
    QPushButton* modifyButton = new QPushButton("Modifier l'image", window);
    modifyButton->setStyleSheet(QString(
        "background-color: %1; color: %2; border: 2px solid %3; padding: 10px; border-radius: 10px; font-size: 14px; font-weight: bold;"
    ).arg(COULEUR_BOUTON)
        .arg(COULEUR_TEXTE_BOUTON)
        .arg(COULEUR_PSEUDO_SCORE));

    // Création du menu déroulant

// Création du menu déroulant
    QMenu* menu = new QMenu(modifyButton);

    // Appliquer un style personnalisé au QMenu
    menu->setStyleSheet(R"(
    QMenu {
        background-color: #333333;  /* Couleur de fond du menu */
        border: 2px solid #0078D7;  /* Bordure de couleur */
        padding: 5px;
        width: 200px; /* Largeur fixe du menu (doit correspondre au bouton) */
    }

    QMenu::item {
        background-color: #444444; /* Couleur de fond des items */
        color: white;
        padding: 8px 20px;
        border-radius: 4px;
    }

    QMenu::item:selected {
        background-color: #0078D7; /* Couleur de fond lors du survol */
        color: white;
    }
)");

    // Création des actions du menu
    QAction* actionDefaultImage = new QAction("Mettre image par défaut", menu);
    QAction* actionTakePhoto = new QAction("Prendre une photo", menu);

    // Ajouter les actions au menu
    menu->addAction(actionDefaultImage);
    menu->addAction(actionTakePhoto);

    // Appliquer la taille du bouton au menu
    menu->setFixedWidth(modifyButton->width());

    // Associer le menu au bouton
    modifyButton->setMenu(menu);

    // Connecter l'action "Mettre image par défaut"
    QObject::connect(actionDefaultImage, &QAction::triggered, [G, imageLabel]() {
        if (G != nullptr && G->getJoueur() != nullptr) {
            std::string defaultImagePath = "./images/avatar.jpeg";  // Chemin de l'image par défaut
            G->getJoueur()->setNouvelleImage();  // Met à jour l'image par défaut

            QPixmap newPixmap(QString::fromStdString(defaultImagePath));  // Charge l'image par défaut
            if (!newPixmap.isNull()) {
                imageLabel->setPixmap(newPixmap.scaled(150, 150, Qt::KeepAspectRatio));
            }
            else {
                std::cerr << "Erreur : Impossible de charger l'image par défaut." << std::endl;
            }
        }
        });

    // Connecter l'action "Prendre une photo"
    QObject::connect(actionTakePhoto, &QAction::triggered, [G, imageLabel]() {
        if (G != nullptr) {  // Vérifie que Gameplay existe
            G->PrendreImage();  // Capture l'image avec OpenCV

            if (G->getJoueur() != nullptr) {  // Vérifie que le joueur existe
                QString newImagePath = QString::fromStdString(G->getJoueur()->getImage());
                QPixmap newPixmap(newImagePath);
                if (!newPixmap.isNull()) {
                    imageLabel->setPixmap(newPixmap.scaled(150, 150, Qt::KeepAspectRatio));
                }
                else {
                    std::cerr << "Erreur : Impossible de charger l'image prise." << std::endl;
                }
            }
        }
        });
    // Connecter le bouton à l'affichage du menu
    QObject::connect(modifyButton, &QPushButton::clicked, [menu]() {
        menu->exec(QCursor::pos());  // Afficher le menu contextuel
        });

    // Ajouter l'image, le texte et le bouton dans le layout horizontal
    imageLayout->addWidget(imageLabel);
    imageLayout->addWidget(textLabel);
    imageLayout->addWidget(modifyButton);

    // Ajouter le layout de l'image, du texte et du bouton au layout principal
    mainLayout->addLayout(imageLayout);

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

void MyQtPageInfoJoueur::setBackground()
{
}
