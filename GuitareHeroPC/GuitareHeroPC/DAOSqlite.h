#pragma once
// https://sqliteonline.com/

#include <iostream>
#include <sqlite3.h>
#include "Joueur.h"


class DAOSqlite
{
public:
    // Permet de récupérer l'objet DAOSqlite
    static DAOSqlite* getInstance();
    // Desctructeur
    ~DAOSqlite();

    // Permet de forcer la fermeture de connection
    void fermerConnection();
    // Permet d'ouvrir la connection
    void ouvrirConnection();

    // Permet de réinitialiser la base de donnée de manière forcé
    void reinitialiser();

    // Permet d'ajouter un nouveau joueur
    void ajouterJoueur(std::string nom, int score, std::string photoChemin);

    // Permet de récupérer ou créer un joueur
    Joueur* getJoueur(std::string nom);

    // Permet de renommer un joueur
    void updateJoueur(std::string nom, std::string nouveauNom);

    void updateImageJoueur(std::string nom, std::string imageChemin);
    
    void ajouterValeurAleatoire(); // permet de populer la base de donnee avec des valeurs aleatoire

    Joueur* getMeilleurScore(); // retourne un tableau de joueurs avec meilleurs scores

private:
    DAOSqlite();
    DAOSqlite(const DAOSqlite&) = delete;
    DAOSqlite& operator=(const DAOSqlite&) = delete;

    // permet de créer la table joueur
    void creationTableJoueur();

    sqlite3* db;
    static const char* nomFichier;
    static DAOSqlite* instance;
};