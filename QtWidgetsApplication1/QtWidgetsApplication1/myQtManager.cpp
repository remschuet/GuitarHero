#include "myQtManager.h"
#include <QGraphicsOpacityEffect>
#include <QTextEdit>
#include <QListWidget>
#include <QFileDialog>
#include <QMenu>
#include <QString>
#include <QFileDialog>
#include <QPixmap>
#include <QMessageBox>
#include <iostream>
#include <Vector>

#include "MyQtPageMenu.h"
#include "MyQtPageAdmin.h"
#include "MyQtPageMenu.h"
#include "MyQtPageInfoJoueur.h"
#include "MyQtPageAccueil.h"
#include "MyQtPageMeilleurScore.h"

QVBoxLayout* myQtManager::GlobalLayout = nullptr;

#include "MyQtPageSettings.h"
#include "MyQtPageFinPartie.h"
#include "MyQtPageGameplay.h"

std::string myQtManager::nomChanson;


QLabel* myQtManager::getUnusedLabel() {
	for (QLabel* label : labels) {
		if (label->property("noteStatus") == "UNUSED" ){
			return label;
		}
	}
    return nullptr;
}

QWidget* myQtManager::getParentWidget() {
    return parentWidget;
}

QLabel* myQtManager::getLabelForNote(const Note& note) {
	for (QLabel* label : labels) {
		if (label->property("noteStatus") == "ACTIVE" && label->property("noteColor") == note.couleur) {
			return label;
		}
	}
	return nullptr;
}

void myQtManager::myQt_setFont(QLabel* q, int tailleFont) {
    QFont font = q->font();
    font.setPointSize(tailleFont);
    q->setFont(font);
}

void myQtManager::changerDePage(QStackedWidget* stack, fenetres page, Gameplay* G, myQtManager* manager)
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
        // MyQtAccueil::refresh(stack, G, manager);
        qtPageAccueil(nullptr, stack, G, manager);  // Ici, on passe `nullptr` en parent car c'est `qtPageAccueil` qui gère ça.
        nouvellePage = stack->widget(stack->count() - 1);
        break;
    case Menu:
        // MyQtPageMenu::refresh(stack, G, manager);
        qtPageMenu(nullptr, stack, G, manager);  // Ici, on passe `nullptr` en parent car c'est `qtPageAccueil` qui gère ça.
        nouvellePage = stack->widget(stack->count() - 1);
        break;
    case MeilleursScores:
        // MyQtPageMeilleurScore::refresh(stack, G, manager);
        qtPageMeilleurScore(nullptr, stack, G, manager);  // Ici, on passe `nullptr` en parent car c'est `qtPageAccueil` qui gère ça.
        nouvellePage = stack->widget(stack->count() - 1);
        break;
    case Informations:
        MyQtPageInfoJoueur::refresh(stack, G, manager);
        // qtPageInformations(nullptr, stack, G, manager);  // Ici, on passe `nullptr` en parent car c'est `qtPageAccueil` qui gère ça.
        nouvellePage = stack->widget(stack->count() - 1);
        break;
    case Parametre:
        MyQtPageSettings::refresh(stack, G, nullptr);
        // qtPageParametres(nullptr, stack, G, manager);
        nouvellePage = stack->widget(stack->count() - 1);
        break;
    case Game:
        // MyQtPageGameplay::refresh(stack, G, nullptr);
        qtPageGame(nullptr, stack, G, manager);
        nouvellePage = stack->widget(stack->count() - 1);
        break;
    case Admin:
        MyQtPageAdmin::refresh(stack, G, manager);
        nouvellePage = stack->widget(stack->count() - 1);
        break;
    }

    if (nouvellePage != nullptr) {
        stack->setCurrentIndex(stack->indexOf(nouvellePage));  // ✅ Afficher la nouvelle page
    };
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


void myQtManager::qtPageAccueil(QWidget* parent, QStackedWidget* stack, Gameplay* G, myQtManager* manager) {
    QWidget* page = new QWidget(parent);
    page->setStyleSheet("background-color: " + COULEUR_FOND + "; border-radius: 25px;");

    //// Image de fond
    QLabel* backgroundLabel = new QLabel(page);
    backgroundLabel->setGeometry(-275, -50, TAILLE_ECRAN_X, TAILLE_ECRAN_Y);
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

    // Champ de nom d'utilisateur centré
    QLineEdit* inputNom = new QLineEdit();
    inputNom->setPlaceholderText("Nom du joueur");
    inputNom->setStyleSheet(
        "background-color: white; "
        "color: black; "
        "border-radius: 25px; "
        "padding: 10px; "
        "font-size: 18px;"
    );
    inputNom->setFixedSize(300, 50);
    containerLayout->addWidget(inputNom, 0, Qt::AlignHCenter);
       //// Bouton de connexion stylé et centré
    QPushButton* btnLogin = new QPushButton("Se connecter");
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

       layout->addSpacing(-170);

    //// Connexion du bouton Login
    QObject::connect(inputNom, &QLineEdit::returnPressed, btnLogin, &QPushButton::click);
    QObject::connect(btnLogin, &QPushButton::clicked, [=]() {
        QString nomJoueur = inputNom->text().trimmed();
        if (nomJoueur.isEmpty()) {
            QMessageBox::warning(parent, "Erreur", "Veuillez entrer un nom d'utilisateur.");
            return;
        }
               // G->setJoueur(new Joueur(nomJoueur.toStdString()));

        // Enregistrement du joueur dans la base de données
        DAOSqlite* sqlite = DAOSqlite::getInstance();
        G->gameStruct.joueur = sqlite->getJoueur(nomJoueur.toStdString());
           //    // Aller au menu
        qtPageMenu(parent, stack, G, manager);
        stack->setCurrentIndex(Menu);
        });

    //// Ajout à la pile des widgets
    stack->addWidget(page);
}


void myQtManager::qtPageMenu(QWidget* parent, QStackedWidget* stack, Gameplay* G, myQtManager* manager) {
    // Créer un widget pour la page du menu
    QWidget* pageMenu = new QWidget();

    // Image de fond 
    QLabel* backgroundLabel = new QLabel(pageMenu);
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

    // Ajouter une couche semi-transparente au-dessus de l'image pour un effet d'assombrissement
    QWidget* overlay = new QWidget(pageMenu);
    overlay->setGeometry(-260, -50, TAILLE_ECRAN_X, TAILLE_ECRAN_Y);
    overlay->setStyleSheet("background-color: rgba(0, 0, 0, 100);"); // Ajuster l'opacité si nécessaire
    overlay->lower();

    // Conteneur central pour le menu 
    QWidget* menuBox = new QWidget(pageMenu);
    menuBox->setStyleSheet("background-color: rgba(0, 0, 0, 150); border-radius: 25px; padding: 20px;");
    menuBox->setFixedSize(600, 450);

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
    // Bouton Quitter le jeu
    QPushButton* quitterButton = new QPushButton("Quitter le jeu", menuBox);
    quitterButton->setStyleSheet(
        "QPushButton { "
        "    background-color: red; "
        "    color: white; "
        "    font-size: 25px; "
        "    border-radius: 5px; "
        "    padding: 5px 10px; "
        "} "
        "QPushButton:hover { "
        "    background-color: darkred; "
        "}"
    );
    quitterButton->setFixedSize(250, 50);
    menuBoxLayout->addWidget(quitterButton, 0, Qt::AlignCenter);

    // Connecter le bouton pour fermer l'application
    QObject::connect(quitterButton, &QPushButton::clicked, [G]() {
        delete G->gameStruct.chansonEnCours;
        delete G->gameStruct.joueur;
        delete G;

        QApplication::quit();
        });


    // Ajouter la box plus bas dans la page
    QVBoxLayout* mainLayout = new QVBoxLayout(pageMenu);
    mainLayout->setAlignment(Qt::AlignTop); // alignement global vers le haut

    mainLayout->addStretch(2); // plus d'espace en haut
    mainLayout->addWidget(menuBox, 0, Qt::AlignHCenter); // aligné horizontalement
    mainLayout->addStretch(1); // un peu d'espace en bas

    mainLayout->setContentsMargins(0, 50, 0, 50); // marges pour donner un peu de souffle
    pageMenu->setLayout(mainLayout);


    // Connexions des boutons
    QObject::connect(buttons[0], &QPushButton::clicked, [=]() {
        afficherPopupSelectionMusique(parent, stack, G, manager);
        //décommenter la ligne suivante et commenter la précédente pour éviter le choix de musique
        //changerDePage(stack, Game, G, manager);
        });
    QObject::connect(buttons[1], &QPushButton::clicked, [=]() {
        changerDePage(stack, MeilleursScores, G, manager);
        });
    QObject::connect(buttons[2], &QPushButton::clicked, [=]() {
        changerDePage(stack, Informations, G, manager);
        });
    QObject::connect(buttons[3], &QPushButton::clicked, [=]() {
        changerDePage(stack, Parametre, G, manager);
        });
    QObject::connect(buttons[4], &QPushButton::clicked, [=]() {
        changerDePage(stack, Accueil, G, manager);
        });

    // Ajouter la page au QStackedWidget
    stack->addWidget(pageMenu);
}

void myQtManager::afficherPopupSelectionMusique(QWidget* parent, QStackedWidget* stack, Gameplay* G, myQtManager* manager) {
    QDialog dialog(parent);
    dialog.setWindowTitle("Sélectionner une musique");
    dialog.setModal(true);  // Bloque les interactions avec la fenêtre principale

    // Layout principal
    QVBoxLayout* layout = new QVBoxLayout(&dialog);

    // Liste déroulante pour choisir la difficulté
    QComboBox* comboBox = new QComboBox();
    comboBox->addItem("Facile");
    comboBox->addItem("Intermédiaire");
    comboBox->addItem("Difficile");
    comboBox->addItem("Expert");

    layout->addWidget(new QLabel("Choisissez la difficulté :"));
    layout->addWidget(comboBox);

    // Liste de chansons
    QListWidget* listWidget = new QListWidget();
    layout->addWidget(new QLabel("Sélectionnez une musique :"));
    layout->addWidget(listWidget);

    // Bouton pour valider
    QPushButton* btnValider = new QPushButton("Sélectionner");
    layout->addWidget(btnValider);

    // Bouton random
    QPushButton* randomMusic = new QPushButton("Musique Aleatoire");
    layout->addWidget(randomMusic);

    // Remplissage des listes selon la difficulté 
    //****- A modifier pour avoir les constantes des chansons en fonction des dificultés-****
    // Remplissage des listes selon la difficulté
    QMap<QString, QStringList> chansons = {
        {"Facile", CHANSON_FACILE},
        {"Intermédiaire", CHANSON_INTERMEDIAIRE},
        {"Difficile", CHANSON_DIFFICILE},
        {"Expert", CHANSON_EXPERT}
    };

    // Remplir la liste des chansons au début
    QObject::connect(comboBox, &QComboBox::currentTextChanged, [&](const QString& niveau) {
        listWidget->clear();
        listWidget->addItems(chansons[niveau]);
        });

    // Charger la liste par défaut (Facile)
    listWidget->addItems(chansons["Facile"]);

    // Gestion du bouton sélection
    QObject::connect(btnValider, &QPushButton::clicked, [&]() {
        QListWidgetItem* selectedItem = listWidget->currentItem();
        QString niveauChoisi = comboBox->currentText(); // Récupérer le niveau sélectionné
        if (selectedItem) {
            QString chansonChoisie = selectedItem->text();


            if (niveauChoisi == "Facile") {
                myQtManager::nomChanson = chansonChoisie.toStdString() + "[EasySingle]";
            }
			else if (niveauChoisi == "Intermédiaire") {
                myQtManager::nomChanson = chansonChoisie.toStdString() + "[MediumSingle]";
            }
			else if (niveauChoisi == "Difficile") {
                myQtManager::nomChanson = chansonChoisie.toStdString() + "[HardSingle]";
            }
			else if (niveauChoisi == "Expert") {
                myQtManager::nomChanson = chansonChoisie.toStdString() + "[ExpertSingle]";
            }
            
            G->gameStruct.chansonEnCours = new Chanson(myQtManager::nomChanson);

            qDebug() << "Niveau sélectionné :" << niveauChoisi; // Ajouter le niveau au print
            qDebug() << "Musique sélectionnée :" << chansonChoisie;

            // Fermer le popup
            dialog.accept();

            // Changer de page vers Game
            changerDePage(stack, Game, G, manager);
        }
        });

    QObject::connect(randomMusic, &QPushButton::clicked, [&]() {
        QString niveauChoisi = comboBox->currentText();

        if (!chansons.contains(niveauChoisi) || chansons[niveauChoisi].isEmpty()) {
            qDebug() << "Aucune chanson disponible pour le niveau :" << niveauChoisi;
            return;
        }

        const QStringList& listeChansons = chansons[niveauChoisi];
        QString chansonChoisie = listeChansons[rand() % listeChansons.size()];

        // Format du nom de chanson utilisé dans le backend
        QString suffix;
        if (niveauChoisi == "Facile") suffix = "[EasySingle]";
        else if (niveauChoisi == "Intermédiaire") suffix = "[MediumSingle]";
        else if (niveauChoisi == "Difficile") suffix = "[HardSingle]";
        else if (niveauChoisi == "Expert") suffix = "[ExpertSingle]";

        myQtManager::nomChanson = chansonChoisie.toStdString() + suffix.toStdString();

        G->gameStruct.chansonEnCours = new Chanson(myQtManager::nomChanson);

        qDebug() << "Niveau sélectionné :" << niveauChoisi;
        qDebug() << "Musique sélectionnée :" << chansonChoisie;

        dialog.accept(); // Fermer le popup
        changerDePage(stack, Game, G, manager); // Aller au jeu
        });


    // Affichage de la boîte de dialogue
    dialog.exec();
}


void myQtManager::qtPageInformations(QWidget* parent, QStackedWidget* stack, Gameplay* G, myQtManager* manager)
{
    //QWidget* window = new QWidget(parent);

    //// Utiliser un QLabel pour l'image de fond
    //QLabel* backgroundLabel = new QLabel(window);
    //QPixmap backgroundPixmap("./Images/placeholder_background_login.png");
    //if (!backgroundPixmap.isNull()) {
    //    backgroundLabel->setPixmap(backgroundPixmap.scaled(window->size(), Qt::KeepAspectRatioByExpanding));
    //    backgroundLabel->setScaledContents(true);
    //}
    //else {
    //    backgroundLabel->setText("Image de fond non disponible");
    //}
    //backgroundLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //QVBoxLayout* windowLayout = new QVBoxLayout(window);
    //windowLayout->addWidget(backgroundLabel);
    //backgroundLabel->lower();

    //std::string nom = "Inconnu";
    //int score = 0;
    //QString imagePath = "./images/avatar.jpg";
    //Joueur* joueurlog = G->getJoueur();

    //if (joueurlog != nullptr) {
    //    nom = joueurlog->getNomJoueur();
    //    QString tempImagePath = QString::fromStdString(joueurlog->getImage());
    //    if (!tempImagePath.isEmpty() && QFile::exists(tempImagePath)) {
    //        imagePath = tempImagePath;
    //    }
    //    score = joueurlog->getMeilleurScore();
    //}

    //QVBoxLayout* mainLayout = new QVBoxLayout(backgroundLabel);
    //mainLayout->setAlignment(Qt::AlignCenter);

    //QWidget* infoContainer = new QWidget(window);
    //infoContainer->setStyleSheet(
    //    "background-color: rgba(255, 255, 255, 180); "
    //    "border: 2px solid #333333; "
    //    "border-radius: 10px; "
    //    "padding: 20px;"
    //);
    //QVBoxLayout* containerLayout = new QVBoxLayout(infoContainer);
    //containerLayout->setAlignment(Qt::AlignCenter);

    //QLabel* title = new QLabel("INFORMATIONS", infoContainer);
    //myQt_setFont(title, QT_TITLE);
    //title->setStyleSheet(QString("color: %1; padding: 20px;").arg(COULEUR_TITRE));
    //title->setAlignment(Qt::AlignCenter);
    //containerLayout->addWidget(title);

    //QHBoxLayout* topContentLayout = new QHBoxLayout();

    //// Layout gauche : Pseudo/Nom et Score Max/Valeur
    //QVBoxLayout* leftLayout = new QVBoxLayout();
    //leftLayout->setAlignment(Qt::AlignCenter);

    //// Pseudo et Nom dans une même ligne avec ":"
    //QHBoxLayout* nameLayout = new QHBoxLayout();
    //QLabel* pseudoLabel = new QLabel("Pseudo: ", infoContainer);
    //myQt_setFont(pseudoLabel, QT_SUBTITLE);
    //pseudoLabel->setStyleSheet(QString("color: %1;").arg(COULEUR_TEXTE));

    //QLabel* pseudoValue = new QLabel(QString::fromStdString(nom), infoContainer);
    //myQt_setFont(pseudoValue, QT_SUBTITLE);
    //pseudoValue->setStyleSheet(QString("color: %1; font-weight: bold;").arg(COULEUR_TEXTE));

    //QPushButton* modiferNomJoueur = new QPushButton("✏️", infoContainer);
    //modiferNomJoueur->setStyleSheet(QString(
    //    "background-color: %1; "
    //    "color: %2; "
    //    "border: 2px solid %3; "
    //    "padding: 5px; "
    //    "border-radius: 5px; "
    //    "font-size: 16px;"
    //).arg(COULEUR_BOUTON).arg(COULEUR_TEXTE_BOUTON).arg(COULEUR_PSEUDO_SCORE));
    //modiferNomJoueur->setFixedSize(30, 30);

    //QObject::connect(modiferNomJoueur, &QPushButton::clicked, [=]() {
    //    bool ok;
    //    QString nouveauNom = QInputDialog::getText(window, "Modifier le nom du joueur",
    //        "Entrez le nouveau nom du joueur :", QLineEdit::Normal, "", &ok);
    //    if (ok && !nouveauNom.isEmpty()) {
    //        if (joueurlog != nullptr) {
    //            joueurlog->setNouveauNomJoueur(nouveauNom.toStdString());
    //            pseudoValue->setText(nouveauNom);
    //            QMessageBox::information(window, "Nom modifié", "Le nom du joueur a été modifié avec succès.");
    //        }
    //    }
    //    else {
    //        QMessageBox::warning(window, "Nom invalide", "Le nom entré est invalide ou vide.");
    //    }
    //    });

    //nameLayout->addWidget(pseudoLabel);
    //nameLayout->addWidget(pseudoValue);
    //nameLayout->addWidget(modiferNomJoueur);

    //// Score Max et Valeur dans une même ligne avec ":"
    //QHBoxLayout* scoreLayout = new QHBoxLayout();
    //QLabel* scoreLabel = new QLabel("Score Max: ", infoContainer);
    //myQt_setFont(scoreLabel, QT_SUBTITLE);
    //scoreLabel->setStyleSheet(QString("color: %1;").arg(COULEUR_TEXTE));

    //QLabel* scoreValue = new QLabel(QString::number(score), infoContainer);
    //myQt_setFont(scoreValue, QT_SUBTITLE);
    //scoreValue->setStyleSheet(QString("color: %1; font-weight: bold;").arg(COULEUR_TEXTE));

    //scoreLayout->addWidget(scoreLabel);
    //scoreLayout->addWidget(scoreValue);

    //leftLayout->addLayout(nameLayout);
    //leftLayout->addLayout(scoreLayout);

    //// Layout droit : Photo et Bouton
    //QVBoxLayout* rightLayout = new QVBoxLayout();
    //rightLayout->setAlignment(Qt::AlignCenter);

    //QLabel* imageLabel = new QLabel(infoContainer);
    //QPixmap pixmap(imagePath);
    //if (!pixmap.isNull()) {
    //    imageLabel->setPixmap(pixmap.scaled(150, 150, Qt::KeepAspectRatio));
    //}
    //else {
    //    imageLabel->setText("Image non disponible");
    //}
    //// Obtenir la hauteur totale du bloc contenant le nom et le score
    //int heightReference = leftLayout->sizeHint().height();

    //// Ajuster la taille de l'image pour correspondre à la hauteur du bloc de texte
    //imageLabel->setPixmap(pixmap.scaledToHeight(heightReference, Qt::SmoothTransformation));


    //QPushButton* modifyButton = new QPushButton("✏️", infoContainer);
    //modifyButton->setStyleSheet(QString(
    //    "background-color: %1; "
    //    "color: %2; "
    //    "border: 2px solid %3; "
    //    "padding: 5px; "
    //    "border-radius: 5px; "
    //    "font-size: 16px;"
    //).arg(COULEUR_BOUTON).arg(COULEUR_TEXTE_BOUTON).arg(COULEUR_PSEUDO_SCORE));
    //modifyButton->setFixedSize(30, 30);

    //QMenu* menu = new QMenu(modifyButton);
    //menu->setStyleSheet(R"(
    //    QMenu {
    //        background-color: #333333;
    //        border: 2px solid #0078D7;
    //        padding: 5px;
    //    }
    //    QMenu::item {
    //        background-color: #444444;
    //        color: white;
    //        padding: 8px 20px;
    //        border-radius: 4px;
    //    }
    //    QMenu::item:selected {
    //        background-color: #00A759;
    //        color: white;
    //    }
    //)");

    //QAction* actionDefaultImage = new QAction("Mettre image par défaut", menu);
    //QAction* actionTakePhoto = new QAction("Prendre une photo", menu);
    //menu->addAction(actionDefaultImage);
    //menu->addAction(actionTakePhoto);
    //menu->setFixedWidth(500);

    //QObject::connect(modifyButton, &QPushButton::clicked, [menu, modifyButton]() {
    //    QPoint globalPos = modifyButton->mapToGlobal(QPoint(0, modifyButton->height()));
    //    menu->exec(globalPos);
    //    });

    //QObject::connect(actionDefaultImage, &QAction::triggered, [G, imageLabel]() {
    //    if (G != nullptr && G->getJoueur() != nullptr) {
    //        std::string defaultImagePath = "./images/avatar.jpeg";
    //        G->getJoueur()->setNouvelleImage();
    //        QPixmap newPixmap(QString::fromStdString(defaultImagePath));
    //        if (!newPixmap.isNull()) {
    //            imageLabel->setPixmap(newPixmap.scaled(150, 150, Qt::KeepAspectRatio));
    //        }
    //        else {
    //            std::cerr << "Erreur : Impossible de charger l'image par défaut." << std::endl;
    //        }
    //    }
    //    });

    //QObject::connect(actionTakePhoto, &QAction::triggered, [G, imageLabel]() {
    //    if (G != nullptr) {
    //        G->PrendreImage();
    //        if (G->getJoueur() != nullptr) {
    //            QString newImagePath = QString::fromStdString(G->getJoueur()->getImage());
    //            QPixmap newPixmap(newImagePath);
    //            if (!newPixmap.isNull()) {
    //                imageLabel->setPixmap(newPixmap.scaled(150, 150, Qt::KeepAspectRatio));
    //            }
    //            else {
    //                std::cerr << "Erreur : Impossible de charger l'image prise." << std::endl;
    //            }
    //        }
    //    }
    //    });

    //rightLayout->addWidget(imageLabel);
    //rightLayout->addWidget(modifyButton, 0, Qt::AlignCenter);

    //topContentLayout->addLayout(leftLayout);
    //topContentLayout->addSpacing(20);
    //topContentLayout->addLayout(rightLayout);

    //containerLayout->addLayout(topContentLayout);

    //containerLayout->addSpacing(40);

    //QPushButton* backButton = new QPushButton("Retour", infoContainer);
    //backButton->setStyleSheet(QString(
    //    "background-color: red; "
    //    "color: white; "
    //    "border: 2px solid red; "
    //    "padding: 10px; "
    //    "border-radius: 10px; "
    //    "font-size: 18px; "
    //    "font-weight: bold;"
    //));
    //QObject::connect(backButton, &QPushButton::clicked, [stack]() {
    //    stack->setCurrentIndex(Menu);
    //    });
    //containerLayout->addWidget(backButton, 0, Qt::AlignCenter);

    //mainLayout->addStretch();  // Ajoute un espace flexible au-dessus
    //mainLayout->addWidget(infoContainer, 0, Qt::AlignCenter);
    //mainLayout->addStretch();  // Ajoute un espace flexible en dessous    mainLayout->addStretch();

    //stack->addWidget(window);
}


void myQtManager::qtPageAdmin(QWidget* parent, QStackedWidget* stack, Gameplay* G, myQtManager* manager)
{
    QWidget* window = new QWidget(parent);
    // window->setStyleSheet(QString("background-color: %1;").arg(COULEUR_FOND));
    QVBoxLayout* layout = new QVBoxLayout(window);
    // pageAdmin->setStyleSheet("background-color: #222; color: white;");


    // Zone de texte pour logs
    QTextEdit* logArea = new QTextEdit(window);
    logArea->setStyleSheet(
        "background-color: black; "
        "color: green; "
        "font-size: 18px; "
        "padding: 10px; "
        "border-radius: 10px;"
    );
    logArea->setReadOnly(true);
    logArea->setFixedHeight(200);
    layout->addWidget(logArea);

    // Entrées pour Key et Value
    QHBoxLayout* inputLayout = new QHBoxLayout();

    QLineEdit* keyInput = new QLineEdit(window);
    keyInput->setPlaceholderText("Key");
    keyInput->setStyleSheet(
        "QLineEdit { "
        "    background-color: #333; "
        "    color: white; "
        "    border-radius: 5px; "
        "    padding: 5px; "
        "    font-size: 18px; "
        "} "
    );

    QLineEdit* valueInput = new QLineEdit(window);
    valueInput->setPlaceholderText("Value");
    valueInput->setStyleSheet(
        "QLineEdit { "
        "    background-color: #333; "
        "    color: white; "
        "    border-radius: 5px; "
        "    padding: 5px; "
        "    font-size: 18px; "
        "} "
    );

    QPushButton* sendButton = new QPushButton("Envoyer", window);
    sendButton->setStyleSheet(
        "QPushButton { "
        "    background-color: blue; "
        "    color: white; "
        "    font-size: 18px; "
        "    border-radius: 5px; "
        "    padding: 5px 10px; "
        "} "
        "QPushButton:hover { "
        "    background-color: lightblue; "
        "    color: white; "
        "}"
    );

    inputLayout->addWidget(keyInput);
    inputLayout->addWidget(valueInput);
    inputLayout->addWidget(sendButton);
    layout->addLayout(inputLayout);

    // Bouton Retour
    QPushButton* btnRetour = new QPushButton("Retour", window);
    btnRetour->setFixedSize(120, 40);
    btnRetour->setStyleSheet(
        "QPushButton { "
        "    background-color: green; "
        "    color: white; "
        "    font-size: 20px; "
        "    border-radius: 5px; "
        "    padding: 5px 10px; "
        "    width: 50px;} "
        "QPushButton:hover { "
        "    background-color: gray; "
        "    color: white; "
        "}"
    );
    layout->addWidget(btnRetour);



    // Connexion du bouton "Envoyer" pour vider les entrées
    QObject::connect(sendButton, &QPushButton::clicked, [=]() {
        keyInput->clear();
        valueInput->clear();
        });

    // Connexion du bouton "Retour" pour revenir à la page précédente
    QObject::connect(btnRetour, &QPushButton::clicked, [=]() {
        stack->setCurrentIndex(0); // Exemple : revenir à la première page du stack
        });

    stack->addWidget(window);
}

void myQtManager::crashAvecMessage(const QString& message) {
    QString programme = QCoreApplication::applicationFilePath();
    QStringList arguments;
    arguments << message;
    QProcess::startDetached(programme, arguments);
    QCoreApplication::exit(-1); // Fin du programme actuel (code d'erreur)
}

void myQtManager::qtPageFinPartie(Gameplay* game, QVBoxLayout* layoutGame, QStackedWidget* stack)
{
    game->gameStruct.chansonEnCours->resetChrono();

    // Créer une boîte de dialogue
    QMessageBox msgBox;
    msgBox.setWindowTitle("Fin de la partie");
    QString message = QString("La partie est terminée !\nScore : %1\nVoulez-vous rejouer ou retourner au menu ?").arg(game->gameStruct.score);
    msgBox.setText(message);
    QPushButton* replayButton = msgBox.addButton("Rejouer", QMessageBox::AcceptRole);
    QPushButton* menuButton = msgBox.addButton("Retour au menu", QMessageBox::RejectRole);
    QPushButton* cancelButton = msgBox.addButton("Annuler", QMessageBox::RejectRole); // Bouton personnalisé pour Cancel

    if (game->gameStruct.joueur->ScoreMax < game->gameStruct.score) {
        // sauvegarder le score
        DAOSqlite* sqlite = DAOSqlite::getInstance();
        sqlite->updateScoreJoueur(game->gameStruct.joueur->getNomJoueur(), game->gameStruct.score);
        game->gameStruct.joueur->ScoreMax = game->gameStruct.score;
    }

    // Exécuter la boîte de dialogue
    msgBox.exec();

    if (msgBox.clickedButton() == replayButton) {

        QMessageBox::information(nullptr, "Sérieux ?", "T'abuses");
    }
    
    else if (msgBox.clickedButton() == menuButton) {
        // Nettoyer le layout avant de retourner au menu pour éviter les résidus
        if (layoutGame) {
            QLayoutItem* item;
            while ((item = layoutGame->takeAt(0)) != nullptr) {
                delete item->widget();
                delete item;
            }
        }
        game->gameStruct.chansonEnCours->resetChrono();
        // Retourner au menu principal avec changerDePage
        crashAvecMessage(QString::fromStdString(game->gameStruct.joueur->getNomJoueur()));
        changerDePage(stack, Menu, game, this);
    }
    else if (msgBox.clickedButton() == cancelButton) {
        // Afficher "T'abuses" si Cancel est cliqué
        QMessageBox::information(nullptr, "Sérieux ?", "T'abuses");
    }
}

void myQtManager::qtPageParametres(QWidget* window, QStackedWidget* stack, Gameplay* G, myQtManager* manager)
{
    //QLabel* imageLabel = nullptr;
    //// Créer un widget pour la page du menu
    //QWidget* pageParametre = new QWidget();
    //QGridLayout* layout = new QGridLayout(pageParametre);

    //layout->setSpacing(5);  // Espacement entre les widgets dans la grille (réduit au minimum)
    //layout->setContentsMargins(0, 0, 0, 0);  // Pas de marges autour du layout

    //// Créer le bouton "Retour"
    //QPushButton* btnRetour = new QPushButton("Retour");
    //btnRetour->setStyleSheet(
    //    "QPushButton { "                       // Sélecteur pour QPushButton
    //    "    background-color: green; "          // Couleur de fond du bouton
    //    "    color: white; "                   // Couleur du texte
    //    "    font-size: 25px; "                // Taille de la police
    //    "    border-radius: 5px; "             // Coins arrondis
    //    "    padding: 5px 10px; "              // Espacement interne du bouton
    //    "}"
    //    "QPushButton:hover { "                 // Effet au survol
    //    "    background-color: gray; "       // Couleur de fond quand la souris survole le bouton
    //    "    color: white; "                 // Couleur du texte au survol
    //    "}"
    //);
    ////QFont font = btnRetour->font();
    ////font.setPointSize(25);  // Définir la taille de la police ici
    ////btnRetour->setFont(font);

    //btnRetour->setFixedSize(500, 100);

    //// Ajouter le bouton "Retour" en haut à gauche (cellule (0, 0))
    //layout->addWidget(btnRetour, 0, 0, Qt::AlignLeft | Qt::AlignTop);

    //// Titre du menu (centré dans la grille)
    //QLabel* titre = new QLabel("");
    //myQt_setFont(titre, 150);
    //titre->setAlignment(Qt::AlignCenter);
    //layout->addWidget(titre, 0, 0, 0, 0, Qt::AlignHCenter | Qt::AlignTop); // Centrer le titre

    //// Image de fond (à l'arrière-plan)
    //QLabel* backgroundLabel = new QLabel(pageParametre);
    //backgroundLabel->setGeometry(0, 0, TAILLE_ECRAN_X, TAILLE_ECRAN_Y);
    //backgroundLabel->setScaledContents(true);  // L'image de fond ne sera pas redimensionnée
    //backgroundLabel->lower();

    //// Ajouter un espacement entre le titre et les boutons
    //QWidget* spacerTop = new QWidget();
    //spacerTop->setFixedHeight(200);  // Espacement vertical
    //layout->addWidget(spacerTop, 1, 0, 1, 3);  // Ajouter un widget vide comme espacement

    //// Liste des boutons
    //QStringList buttonNames = { "Difficulté", "Paramètre de la manette", "Mode Admin" };
    //QVector<QPushButton*> buttons;

    //// Création des boutons avec un style uniforme
    //for (int i = 0; i < buttonNames.size(); ++i) {
    //    QPushButton* button = new QPushButton(buttonNames[i]);
    //    //QFont fontButton = button->font();
    //    //fontButton.setPointSize(25);  // Définir la taille de la police ici
    //    //button->setFont(fontButton);

    //    button->setStyleSheet(
    //            "QPushButton { "                       // Sélecteur pour QPushButton
    //            "    background-color: green; "          // Couleur de fond du bouton
    //            "    color: white; "                   // Couleur du texte
    //            "    font-size: 25px; "                // Taille de la police
    //            "    border-radius: 5px; "             // Coins arrondis
    //            "    padding: 5px 10px; "              // Espacement interne du bouton
    //            "}"
    //            "QPushButton:hover { "                 // Effet au survol
    //            "    background-color: gray; "       // Couleur de fond quand la souris survole le bouton
    //            "    color: white; "                 // Couleur du texte au survol
    //            "}"
    //        );
    //    button->setFixedSize(500, 100);
    //    buttons.append(button);

    //    // Ajouter les boutons en ligne, un sous l'autre
    //    layout->addWidget(button, 2 + i, 1, Qt::AlignHCenter | Qt::AlignVCenter);
    //}

    //// Ajouter un espace après les boutons (espacement vers le bas)
    //QWidget* spacerBottom = new QWidget();
    //spacerBottom->setFixedHeight(600);  // Espacement vertical à la fin
    //layout->addWidget(spacerBottom, 6, 0, 1, 3);  // Ajouter un widget vide comme espacement après les boutons

    //// Connexion des boutons aux actions
    //QObject::connect(buttons[0], &QPushButton::clicked, [=]() {
    //    fenetres QtFenetre = MeilleursScores;
    //    });

    //QObject::connect(buttons[1], &QPushButton::clicked, [=]() {
    //    // Créer un widget qui contiendra l'image et le bouton
    //    QWidget* overlayWidget = new QWidget(pageParametre); // parent = pageParametre
    //    overlayWidget->setGeometry(0, 0, TAILLE_ECRAN_X, TAILLE_ECRAN_Y);  // Position et taille du widget

    //    // Créer un QLabel pour afficher l'image
    //    QLabel* paraManette = new QLabel(overlayWidget);  // Ajouter l'image au nouveau widget
    //    QPixmap ManettePixmap("./images/test.jpg");

    //    // Vérifier si l'image a été correctement chargée
    //    if (ManettePixmap.isNull()) {
    //        qDebug() << "Erreur de chargement de l'image!";
    //        return;
    //    }

    //    // Afficher l'image dans le QLabel
    //    paraManette->setPixmap(ManettePixmap);
    //    paraManette->setAlignment(Qt::AlignCenter);  // Centrer l'image dans le QLabel

    //    // Fixer la taille du QLabel à la taille de l'écran
    //    paraManette->setFixedSize(TAILLE_ECRAN_X, TAILLE_ECRAN_Y);  // S'assurer que le QLabel prend toute la taille de l'écran

    //    // S'assurer que l'image s'adapte à la taille du QLabel
    //    paraManette->setScaledContents(true);  // Redimensionner l'image pour s'adapter au QLabel

    //    // Créer un bouton "Retour aux Paramètres"
    //    QPushButton* btnRetourParametre = new QPushButton("Retour", overlayWidget);
    //    btnRetourParametre->setStyleSheet(
    //        "QPushButton { "
    //        "    background-color: green; "
    //        "    color: white; "
    //        "    font-size: 25px; "
    //        "    border-radius: 5px; "
    //        "    padding: 5px 10px; "
    //        "} "
    //        "QPushButton:hover { "
    //        "    background-color: gray; "
    //        "    color: white; "
    //        "} "
    //    );
    //    btnRetourParametre->setFixedSize(500, 100);
    //    btnRetourParametre->setGeometry(0, 0, 500, 100);  // Positionner le bouton

    //    // Ajouter l'overlayWidget à la pageParametre, au-dessus de tous les autres éléments
    //    layout->addWidget(overlayWidget, 0, 0, 0, 0);  // Assurez-vous qu'il couvre toute la page

    //    // Assurer que le bouton et l'image sont bien au-dessus des autres widgets
    //    overlayWidget->raise();  // Met l'overlayWidget (contenant l'image et le bouton) au-dessus des autres éléments

    //    // Connexion du bouton "Retour aux Paramètres"
    //    QObject::connect(btnRetourParametre, &QPushButton::clicked, [=]() {
    //        // Supprimer l'overlay (image et bouton) quand on clique sur "Retour"
    //        paraManette->deleteLater();  // Supprimer l'image
    //        btnRetourParametre->deleteLater();  // Supprimer le bouton
    //        overlayWidget->deleteLater();  // Supprimer l'overlayWidget complet
    //        });
    //    });


    //QObject::connect(buttons[2], &QPushButton::clicked, [=]() {
    //    fenetres QtFenetre = Admin;
    //    changerDePage(stack, QtFenetre, G, manager);
    //});

    //QObject::connect(btnRetour, &QPushButton::clicked, [=]() {
    //    stack->setCurrentIndex(0); // Retour au menu principal
    //    });

    //// Ajouter la page au QStackedWidget
    //stack->addWidget(pageParametre);
}



void myQtManager::qtPageMeilleurScore(QWidget* window, QStackedWidget* stack, Gameplay* G, myQtManager* manager)
{
    QWidget* pageMeilleursScores = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout(pageMeilleursScores);
    mainLayout->setContentsMargins(20, 10, 20, 10); // Marges réduites

    // Image de fond 
    QLabel* backgroundLabel = new QLabel(pageMeilleursScores);
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

    // Titre
    QLabel* titre = new QLabel("Meilleurs Scores");
    titre->setAlignment(Qt::AlignHCenter);
    QFont fontTitre("Arial", 18, QFont::Bold); // Taille réduite
    titre->setFont(fontTitre);
    titre->setStyleSheet(COULEUR_FOND);
    mainLayout->addWidget(titre);

    // Conteneur avec défilement
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setStyleSheet("QScrollArea { border: none; background: transparent; }");

    QWidget* scoreContainer = new QWidget();
    QVBoxLayout* scoreLayout = new QVBoxLayout(scoreContainer);
    scoreLayout->setContentsMargins(0, 5, 0, 5); // Marges réduites
    scoreLayout->setSpacing(6); // Espacement réduit entre les lignes

    // Récupération des meilleurs scores
    std::pair<std::string, int> scores[10];
    DAOSqlite* sqlite = DAOSqlite::getInstance();
    sqlite->getMeilleurScore(scores);

    for (size_t i = 0; i < 10; ++i) {
        QFrame* scoreCard = new QFrame();
        scoreCard->setStyleSheet("background-color: rgba(128, 128, 128, 0.5); "
            "border: 2px solid transparent; "
            "border-radius: 8px; padding: 3px;"); // Bordures et padding réduits
        scoreCard->setFixedHeight(70); // Hauteur réduite

        QHBoxLayout* rowLayout = new QHBoxLayout(scoreCard);
        rowLayout->setContentsMargins(10, 0, 10, 0); // Marges réduites

        if (i < 10 && scores[i].first != "") {
            QString medal, borderColor, nameBgColor, positionTextColor, textColor = COULEUR_TEXTE_BOUTON;

            if (i == 0) {
                medal = "🥇"; borderColor = "#FFD700"; nameBgColor = "#FFD700"; positionTextColor = "#FFD700"; textColor = "#FFD700";
            }
            else if (i == 1) {
                medal = "🥈"; borderColor = "#C0C0C0"; nameBgColor = "#C0C0C0"; positionTextColor = "#C0C0C0"; textColor = "#C0C0C0";
            }
            else if (i == 2) {
                medal = "🥉"; borderColor = "#CD7F32"; nameBgColor = "#CD7F32"; positionTextColor = "#CD7F32"; textColor = "#CD7F32";
            }
            else {
                nameBgColor = COULEUR_TEXTE_BOUTON; positionTextColor = "#000000";
            }

            scoreCard->setStyleSheet("background-color: rgba(128, 128, 128, 0.5); "
                "border: 2px solid " + borderColor + "; "
                "border-radius: 8px; padding: 3px;");

            // Image du joueur (taille réduite)
            QLabel* imageLabel = new QLabel();
            QString imagePath = (G && G->getJoueur() && scores[i].first == G->getJoueur()->getNomJoueur())
                ? QString::fromStdString(G->getJoueur()->getImage())
                : "./images/avatar.jpg";

            QPixmap pixmap(imagePath);
            if (!pixmap.isNull()) {
                imageLabel->setPixmap(pixmap.scaled(60, 60, Qt::KeepAspectRatio));
            }
            imageLabel->setScaledContents(true);
            imageLabel->setFixedSize(60, 60);
            rowLayout->addWidget(imageLabel, 0, Qt::AlignVCenter);

            // Position + Médaille
            QLabel* position = new QLabel(QString::number(i + 1) + ". " + medal);
            position->setFixedWidth(60); // Largeur réduite
            position->setStyleSheet("font-weight: bold; color: " + positionTextColor + "; font-size: 16px;");
            rowLayout->addWidget(position, 0, Qt::AlignVCenter);

            // Nom du joueur
            QLabel* nomJoueur = new QLabel(QString::fromStdString(scores[i].first));
            nomJoueur->setFixedWidth(180); // Largeur réduite
            nomJoueur->setFixedHeight(40); // Hauteur réduite
            nomJoueur->setStyleSheet("font-weight: bold; color: #000000; "
                "background-color: " + nameBgColor + "; "
                "border-radius: 5px; padding: 3px; font-size: 14px;"); // Taille de police réduite
            rowLayout->addWidget(nomJoueur, 0, Qt::AlignVCenter);

            // Score
            QLabel* score = new QLabel(QString::number(scores[i].second));
            score->setFixedWidth(60); // Largeur réduite
            score->setStyleSheet("font-weight: bold; color: " + textColor + "; font-size: 16px;");
            rowLayout->addWidget(score, 0, Qt::AlignVCenter);
        }
        else {
            // Lignes vides avec des placeholders invisibles
            QLabel* imageLabel = new QLabel();
            imageLabel->setFixedSize(60, 60);
            rowLayout->addWidget(imageLabel);

            QLabel* position = new QLabel("");
            position->setFixedWidth(60);
            rowLayout->addWidget(position);

            QLabel* nomJoueur = new QLabel("");
            nomJoueur->setFixedWidth(180);
            nomJoueur->setFixedHeight(40);
            rowLayout->addWidget(nomJoueur);

            QLabel* score = new QLabel("");
            score->setFixedWidth(60);
            rowLayout->addWidget(score);
        }

        scoreLayout->addWidget(scoreCard);
    }

    scrollArea->setWidget(scoreContainer);
    mainLayout->addWidget(scrollArea);

    // Bouton retour
    QPushButton* btnRetour = new QPushButton("Retour");
    btnRetour->setStyleSheet("background-color: red; color: white; padding: 3px 8px; font-size: 14px;");
    btnRetour->setFixedSize(90, 35); // Taille réduite

    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(btnRetour);
    mainLayout->addLayout(btnLayout);

    QObject::connect(btnRetour, &QPushButton::clicked, [stack]() {
        stack->setCurrentIndex(Menu);
        });

    pageMeilleursScores->setLayout(mainLayout);
    stack->addWidget(pageMeilleursScores);
}

void myQtManager::qtPageGame(QWidget* window, QStackedWidget* stack, Gameplay* G, myQtManager* manager)
{
    QWidget* pageGame = new QWidget();
    QVBoxLayout* layoutGame = new QVBoxLayout(pageGame);

    QLabel* gameLabel = new QLabel(pageGame);
    gameLabel->setAlignment(Qt::AlignCenter);
    layoutGame->addWidget(gameLabel);

    QLabel* titleLabel = new QLabel(pageGame);

    QLabel* ProgressionLabel = new QLabel(pageGame);

    int pageIndex = stack->addWidget(pageGame); // Add the page and get its index

    QObject::connect(stack, &QStackedWidget::currentChanged, [stack, pageGame, G, gameLabel, titleLabel, ProgressionLabel, manager, layoutGame](int index) {
        if (stack->widget(index) == pageGame) {
            qDebug() << "PageGame est affichée!";
            // Creation de la chanson
            // Lancement de la partie
            G->demarrerPartie(gameLabel, titleLabel, ProgressionLabel, manager, layoutGame, stack);
        }
        });
    stack->addWidget(pageGame);
}                                   //il manque changer dans ChangerDePage, ajouter QtManager* manager à l'appel de fct
                                    // et manager à QtPageGame