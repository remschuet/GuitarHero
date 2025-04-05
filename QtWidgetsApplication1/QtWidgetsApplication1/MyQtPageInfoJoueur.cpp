#include "MyQtPageInfoJoueur.h"

MyQtPageInfoJoueur::MyQtPageInfoJoueur(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent)
    : MyQtPage(stack, G, manager, parent) {

}

void MyQtPageInfoJoueur::refresh(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent)
{
    QWidget* window = new QWidget();

    // Image de fond (comme dans qtPageMenu)
    QLabel* backgroundLabel = new QLabel(window);
    backgroundLabel->setGeometry(-275, -50, TAILLE_ECRAN_X, TAILLE_ECRAN_Y);
    QPixmap pixmap("./Images/placeholder_background_login.png");
    backgroundLabel->setPixmap(pixmap);
    backgroundLabel->setAlignment(Qt::AlignCenter);

    // Appliquer un effet de flou
    QGraphicsBlurEffect* blurEffect = new QGraphicsBlurEffect();
    blurEffect->setBlurRadius(10); // Ajustez le rayon de flou (5-20 pour un effet léger à fort)

    // Appliquer une opacité
    QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect();
    opacityEffect->setOpacity(0.7); // Opacité de 0 (transparent) à 1 (opaque), ici 70% d'opacité

    // Combiner les effets : d'abord l'opacité, puis le flou
    backgroundLabel->setGraphicsEffect(opacityEffect);
    blurEffect->setParent(backgroundLabel); // Nécessaire pour que l'effet soit appliqué après l'opacité
    backgroundLabel->setGraphicsEffect(blurEffect);

    backgroundLabel->lower();

    QWidget* infoContainer = new QWidget(window);
    infoContainer->setGeometry(0, 0, TAILLE_ECRAN_X, TAILLE_ECRAN_Y);
    infoContainer->setStyleSheet("background-color: rgba(0, 0, 0, 100);");
    infoContainer->lower();

    QWidget* Box = new QWidget(window);
    Box->setStyleSheet("background-color: rgba(0, 0, 0, 150); border-radius: 25px; padding: 20px;");
    Box->setFixedSize(600, 400);

    QVBoxLayout* BoxLayout = new QVBoxLayout(Box);
    BoxLayout->setAlignment(Qt::AlignCenter);
    BoxLayout->setSpacing(15);

    std::string nom = "Inconnu";
    int score = 0;
    QString imagePath = "./images/avatar.jpg";
    Joueur* joueurlog = G->getJoueur();

    if (joueurlog != nullptr) {
        nom = joueurlog->getNomJoueur();
        QString tempImagePath = QString::fromStdString(joueurlog->getImage());
        if (!tempImagePath.isEmpty() && QFile::exists(tempImagePath)) {
            imagePath = tempImagePath;
        }
        score = joueurlog->getMeilleurScore();
    }

    QLabel* titre = new QLabel("INFORMATIONS", infoContainer);
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

    QHBoxLayout* topContentLayout = new QHBoxLayout();

    // Layout gauche : Pseudo/Nom et Score Max/Valeur
    QVBoxLayout* leftLayout = new QVBoxLayout();
    leftLayout->setAlignment(Qt::AlignCenter);

    // Pseudo et Nom dans une même ligne avec ":"
    QHBoxLayout* nameLayout = new QHBoxLayout();
    QLabel* pseudoLabel = new QLabel("Pseudo: ", infoContainer);
    myQt_setFont(pseudoLabel, QT_SUBTITLE);
    pseudoLabel->setStyleSheet(QString("color: %1;").arg(COULEUR_TEXTE));

    QLabel* pseudoValue = new QLabel(QString::fromStdString(nom), infoContainer);
    myQt_setFont(pseudoValue, QT_SUBTITLE);
    pseudoValue->setStyleSheet(QString("color: %1; font-weight: bold;").arg(COULEUR_TEXTE));

    QPushButton* modiferNomJoueur = new QPushButton("✏️", infoContainer);
    modiferNomJoueur->setStyleSheet(QString(
        "background-color: %1; "
        "color: %2; "
        "border: 2px solid %3; "
        "padding: 5px; "
        "border-radius: 5px; "
        "font-size: 16px;"
    ).arg(COULEUR_BOUTON).arg(COULEUR_TEXTE_BOUTON).arg(COULEUR_PSEUDO_SCORE));
    modiferNomJoueur->setFixedSize(30, 30);

    QObject::connect(modiferNomJoueur, &QPushButton::clicked, [=]() {
        bool ok;
        QString nouveauNom = QInputDialog::getText(window, "Modifier le nom du joueur",
            "Entrez le nouveau nom du joueur :", QLineEdit::Normal, "", &ok);
        if (ok && !nouveauNom.isEmpty()) {
            if (joueurlog != nullptr) {
                joueurlog->setNouveauNomJoueur(nouveauNom.toStdString());
                pseudoValue->setText(nouveauNom);
                QMessageBox::information(window, "Nom modifié", "Le nom du joueur a été modifié avec succès.");
            }
        }
        else {
            QMessageBox::warning(window, "Nom invalide", "Le nom entré est invalide ou vide.");
        }
        });

    nameLayout->addWidget(pseudoLabel);
    nameLayout->addWidget(pseudoValue);
    nameLayout->addWidget(modiferNomJoueur);

    // Score Max et Valeur dans une même ligne avec ":"
    QHBoxLayout* scoreLayout = new QHBoxLayout();
    QLabel* scoreLabel = new QLabel("Score Max: ", infoContainer);
    myQt_setFont(scoreLabel, QT_SUBTITLE);
    scoreLabel->setStyleSheet(QString("color: %1;").arg(COULEUR_TEXTE));

    QLabel* scoreValue = new QLabel(QString::number(score), infoContainer);
    myQt_setFont(scoreValue, QT_SUBTITLE);
    scoreValue->setStyleSheet(QString("color: %1; font-weight: bold;").arg(COULEUR_TEXTE));

    scoreLayout->addWidget(scoreLabel);
    scoreLayout->addWidget(scoreValue);

    leftLayout->addLayout(nameLayout);
    leftLayout->addLayout(scoreLayout);

    // Layout droit : Photo et Bouton
    QVBoxLayout* rightLayout = new QVBoxLayout();
    rightLayout->setAlignment(Qt::AlignCenter);

    QLabel* imageLabel = new QLabel(infoContainer);
    QPixmap pixmap_profil(imagePath);
    if (!pixmap_profil.isNull()) {
        imageLabel->setPixmap(pixmap_profil.scaled(150, 150, Qt::KeepAspectRatio));
    }
    else {
        imageLabel->setText("Image non disponible");
    }
    // Obtenir la hauteur totale du bloc contenant le nom et le score
    int heightReference = leftLayout->sizeHint().height();

    // Ajuster la taille de l'image pour correspondre à la hauteur du bloc de texte
    imageLabel->setPixmap(pixmap_profil.scaledToHeight(heightReference, Qt::SmoothTransformation));


    QPushButton* modifyButton = new QPushButton("✏️", infoContainer);
    modifyButton->setStyleSheet(QString(
        "background-color: %1; "
        "color: %2; "
        "border: 2px solid %3; "
        "padding: 5px; "
        "border-radius: 5px; "
        "font-size: 16px;"
    ).arg(COULEUR_BOUTON).arg(COULEUR_TEXTE_BOUTON).arg(COULEUR_PSEUDO_SCORE));
    modifyButton->setFixedSize(30, 30);

    QMenu* menu = new QMenu(modifyButton);
    menu->setStyleSheet(R"(
        QMenu {
            background-color: #333333;
            border: 2px solid #0078D7;
            padding: 5px;
        }
        QMenu::item {
            background-color: #444444;
            color: white;
            padding: 8px 20px;
            border-radius: 4px;
        }
        QMenu::item:selected {
            background-color: #00A759;
            color: white;
        }
    )");

    QAction* actionDefaultImage = new QAction("Mettre image par défaut", menu);
    QAction* actionTakePhoto = new QAction("Prendre une photo", menu);
    menu->addAction(actionDefaultImage);
    menu->addAction(actionTakePhoto);
    menu->setFixedWidth(500);

    QObject::connect(modifyButton, &QPushButton::clicked, [menu, modifyButton]() {
        QPoint globalPos = modifyButton->mapToGlobal(QPoint(0, modifyButton->height()));
        menu->exec(globalPos);
        });

    QObject::connect(actionDefaultImage, &QAction::triggered, [G, imageLabel]() {
        if (G != nullptr && G->getJoueur() != nullptr) {
            std::string defaultImagePath = "./images/avatar.jpeg";
            G->getJoueur()->setNouvelleImage();
            QPixmap newPixmap(QString::fromStdString(defaultImagePath));
            if (!newPixmap.isNull()) {
                imageLabel->setPixmap(newPixmap.scaled(150, 150, Qt::KeepAspectRatio));
            }
            else {
                std::cerr << "Erreur : Impossible de charger l'image par défaut." << std::endl;
            }
        }
        });

    QObject::connect(actionTakePhoto, &QAction::triggered, [G, imageLabel]() {
        if (G != nullptr) {
            G->PrendreImage();
            if (G->getJoueur() != nullptr) {
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

    rightLayout->addWidget(imageLabel);
    rightLayout->addWidget(modifyButton, 0, Qt::AlignCenter);

    topContentLayout->addLayout(leftLayout);
    topContentLayout->addSpacing(20);
    topContentLayout->addLayout(rightLayout);

    BoxLayout->addLayout(topContentLayout);

    BoxLayout->addSpacing(40);

    QPushButton* backButton = new QPushButton("Retour", infoContainer);
    backButton->setStyleSheet(QString(
        "background-color: red; "
        "color: white; "
        "border: 2px solid red; "
        "padding: 10px; "
        "border-radius: 10px; "
        "font-size: 18px; "
        "font-weight: bold;"
    ));
    QObject::connect(backButton, &QPushButton::clicked, [stack]() {
        stack->setCurrentIndex(Menu);
        });
    BoxLayout->addWidget(backButton, 0, Qt::AlignCenter);

    QVBoxLayout* windowLayout = new QVBoxLayout(window);
    windowLayout->addStretch();  // Espace flexible en haut
    windowLayout->addWidget(Box, 0, Qt::AlignCenter); // Centre la Box
    windowLayout->addStretch();  // Espace flexible en bas


    stack->addWidget(window);
}

void MyQtPageInfoJoueur::setBackground()
{
}
