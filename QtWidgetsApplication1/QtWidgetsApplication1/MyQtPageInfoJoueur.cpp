#include "MyQtPageInfoJoueur.h"

MyQtPageInfoJoueur::MyQtPageInfoJoueur(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent)
    : MyQtPage(stack, G, manager, parent) {

}

void MyQtPageInfoJoueur::refresh(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent)
{
    QWidget* window = new QWidget(parent);

    // Utiliser un QLabel pour l'image de fond
    QLabel* backgroundLabel = new QLabel(window);
    QPixmap backgroundPixmap("./Images/placeholder_background_login.png");
    if (!backgroundPixmap.isNull()) {
        backgroundLabel->setPixmap(backgroundPixmap.scaled(window->size(), Qt::KeepAspectRatioByExpanding));
        backgroundLabel->setScaledContents(true);
    }
    else {
        backgroundLabel->setText("Image de fond non disponible");
    }
    backgroundLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout* windowLayout = new QVBoxLayout(window);
    windowLayout->addWidget(backgroundLabel);
    backgroundLabel->lower();

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

    QVBoxLayout* mainLayout = new QVBoxLayout(backgroundLabel);
    mainLayout->setAlignment(Qt::AlignCenter);

    QWidget* infoContainer = new QWidget(window);
    infoContainer->setStyleSheet(
        "background-color: rgba(255, 255, 255, 180); "
        "border: 2px solid #333333; "
        "border-radius: 10px; "
        "padding: 20px;"
    );
    QVBoxLayout* containerLayout = new QVBoxLayout(infoContainer);
    containerLayout->setAlignment(Qt::AlignCenter);

    QLabel* title = new QLabel("INFORMATIONS", infoContainer);
    myQt_setFont(title, QT_TITLE);
    title->setStyleSheet(QString("color: %1; padding: 20px;").arg(COULEUR_TITRE));
    title->setAlignment(Qt::AlignCenter);
    containerLayout->addWidget(title);

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
    QPixmap pixmap(imagePath);
    if (!pixmap.isNull()) {
        imageLabel->setPixmap(pixmap.scaled(150, 150, Qt::KeepAspectRatio));
    }
    else {
        imageLabel->setText("Image non disponible");
    }
    // Obtenir la hauteur totale du bloc contenant le nom et le score
    int heightReference = leftLayout->sizeHint().height();

    // Ajuster la taille de l'image pour correspondre à la hauteur du bloc de texte
    imageLabel->setPixmap(pixmap.scaledToHeight(heightReference, Qt::SmoothTransformation));


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

    containerLayout->addLayout(topContentLayout);

    containerLayout->addSpacing(40);

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
    containerLayout->addWidget(backButton, 0, Qt::AlignCenter);

    mainLayout->addStretch();  // Ajoute un espace flexible au-dessus
    mainLayout->addWidget(infoContainer, 0, Qt::AlignCenter);
    mainLayout->addStretch();  // Ajoute un espace flexible en dessous    mainLayout->addStretch();

    stack->addWidget(window);
}

void MyQtPageInfoJoueur::setBackground()
{
}
