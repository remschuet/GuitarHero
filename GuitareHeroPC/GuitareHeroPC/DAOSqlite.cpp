#include "DAOSqlite.h"
#include <cstdio>
#include <string>
#include <iostream>

DAOSqlite* DAOSqlite::instance = nullptr;  // Initialisation du pointeur d'instance
const char* DAOSqlite::nomFichier = "database.db";  // Initialisation de la variable statique

DAOSqlite* DAOSqlite::getInstance() {
    if (instance == nullptr) {
        // Crée une instance si elle n'existe pas encore
        instance = new DAOSqlite();
    }
    return instance;
}

DAOSqlite::DAOSqlite() {
    if (sqlite3_open(nomFichier, &db) != SQLITE_OK) {
        std::cerr << "Erreur SQLite (open) : " << sqlite3_errmsg(db) << std::endl;
    }
    else {
        creationTableJoueur();
    }
}

DAOSqlite::~DAOSqlite() {
    sqlite3_close(db);
}

void DAOSqlite::creationTableJoueur() {
    std::string createTableQuery =
        "CREATE TABLE IF NOT EXISTS JOUEUR("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "nom TEXT NOT NULL UNIQUE, "
        "score INTEGER DEFAULT 0, "
        "photo TEXT DEFAULT 'Icone.jpeg');";

    char* errMsg = nullptr;
    if (sqlite3_exec(db, createTableQuery.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Erreur SQLite (create table) : " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

void DAOSqlite::fermerConnection() {
    sqlite3_close(db);
}

void DAOSqlite::ouvrirConnection() {
    sqlite3_open(nomFichier, &db);
}

void DAOSqlite::reinitialiser() {
    fermerConnection();
    std::remove(nomFichier);
    ouvrirConnection();
    creationTableJoueur();
}

void DAOSqlite::ajouterJoueur(std::string nom, int score, std::string photoChemin) {
    std::string query = "INSERT INTO JOUEUR(nom, score, photo) VALUES('" + nom + "', " + std::to_string(score) + ", '" + photoChemin + "');";
    sqlite3_exec(db, query.c_str(), nullptr, nullptr, nullptr);
}

Joueur* DAOSqlite::getJoueur(std::string nom) {
    std::string query = "SELECT id, nom, score, photo FROM JOUEUR WHERE nom = ?;";
    sqlite3_stmt* stmt;
    Joueur* joueur = nullptr;

    // Préparer la requête pour éviter l'injection SQL
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erreur SQLite (prepare) : " << sqlite3_errmsg(db) << std::endl;
        return nullptr;
    }

    // Lier le paramètre 'nom' à la requête
    if (sqlite3_bind_text(stmt, 1, nom.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        std::cerr << "Erreur SQLite (bind) : " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return nullptr;
    }

    // Exécuter la requête
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* nomJoueur = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        int scoreJoueur = sqlite3_column_int(stmt, 2);
        const char* photoJoueur = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));

        joueur = new Joueur(nomJoueur ? nomJoueur : "", scoreJoueur, photoJoueur ? photoJoueur : "");
    }

    // Finaliser la requête
    sqlite3_finalize(stmt);

    // Si le joueur n'existe pas, l'insérer
    if (!joueur) {
        std::string insertQuery = "INSERT INTO JOUEUR (nom) VALUES (?);";
        sqlite3_stmt* insertStmt;

        if (sqlite3_prepare_v2(db, insertQuery.c_str(), -1, &insertStmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(insertStmt, 1, nom.c_str(), -1, SQLITE_STATIC);
            if (sqlite3_step(insertStmt) != SQLITE_DONE) {
                std::cerr << "Erreur SQLite (insert) : " << sqlite3_errmsg(db) << std::endl;
            }
        }
        else {
            std::cerr << "Erreur SQLite (prepare insert) : " << sqlite3_errmsg(db) << std::endl;
        }

        sqlite3_finalize(insertStmt);

        // Réessayer de récupérer le joueur après insertion
        return getJoueur(nom);
    }

    return joueur;
}

bool DAOSqlite::updateJoueur(std::string nom, std::string nouveauNom) {
    // Vérifier si le nouveau nom existe déjà
    std::string checkQuery = "SELECT COUNT(*) FROM JOUEUR WHERE nom = ?;";
    sqlite3_stmt* checkStmt;

    if (sqlite3_prepare_v2(db, checkQuery.c_str(), -1, &checkStmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erreur SQLite (prepare check) : " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(checkStmt, 1, nouveauNom.c_str(), -1, SQLITE_STATIC);

    bool exists = false;
    if (sqlite3_step(checkStmt) == SQLITE_ROW) {
        exists = (sqlite3_column_int(checkStmt, 0) > 0);
    }
    sqlite3_finalize(checkStmt);

    if (exists) {
        return false;  // 🔴 Nom déjà existant
    }

    // Effectuer la mise à jour
    std::string updateQuery = "UPDATE JOUEUR SET nom = ? WHERE nom = ?;";
    sqlite3_stmt* updateStmt;

    if (sqlite3_prepare_v2(db, updateQuery.c_str(), -1, &updateStmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erreur SQLite (prepare update) : " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(updateStmt, 1, nouveauNom.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(updateStmt, 2, nom.c_str(), -1, SQLITE_STATIC);

    bool success = (sqlite3_step(updateStmt) == SQLITE_DONE);
    sqlite3_finalize(updateStmt);

    return success;
}


bool DAOSqlite::updateImageJoueur(std::string nom, std::string imageChemin) {
    // Créer la requête SQL pour mettre à jour le chemin de l'image
    std::string updateQuery = "UPDATE JOUEUR SET photo = ? WHERE nom = ?;";
    sqlite3_stmt* stmt;

    // Préparer la requête
    if (sqlite3_prepare_v2(db, updateQuery.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erreur SQLite (prepare update image) : " << sqlite3_errmsg(db) << std::endl;
        return false;  // Erreur de préparation
    }

    // Lier les paramètres à la requête
    sqlite3_bind_text(stmt, 1, imageChemin.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, nom.c_str(), -1, SQLITE_STATIC);

    // Exécuter la requête
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);

    // Finaliser la requête
    sqlite3_finalize(stmt);

    return success;
}

bool DAOSqlite::updateScoreJoueur(std::string nom, int meilleurScore) {
    // Créer la requête SQL pour mettre à jour le chemin de l'image
    std::string updateQuery = "UPDATE JOUEUR SET score = ? WHERE nom = ?;";
    sqlite3_stmt* stmt;

    // Préparer la requête
    if (sqlite3_prepare_v2(db, updateQuery.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erreur SQLite (prepare update image) : " << sqlite3_errmsg(db) << std::endl;
        return false;  // Erreur de préparation
    }

    // Lier les paramètres à la requête
    sqlite3_bind_int(stmt, 1, meilleurScore);
    sqlite3_bind_text(stmt, 2, nom.c_str(), -1, SQLITE_STATIC);

    // Exécuter la requête
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);

    // Finaliser la requête
    sqlite3_finalize(stmt);

    return success;
}

void DAOSqlite::ajouterValeurAleatoire()
{
}

Joueur* DAOSqlite::getMeilleurScore(std::pair < std::string,int>(&scores)[10])
{
    const char* sql = "SELECT nom, score FROM JOUEUR ORDER BY score DESC LIMIT 10;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
    {
        int index = 0;
        while (sqlite3_step(stmt) == SQLITE_ROW && index < 10)
        {
            scores[index].first = reinterpret_cast <const char*> (sqlite3_column_text(stmt, 0));
            scores[index].second = sqlite3_column_int(stmt, 1);
            index++;
        }
        sqlite3_finalize(stmt);
    }
    else
    {
        std::cerr << "Error, impossible d'executer le statement (getMeilleurScore) : " << sqlite3_errmsg(db) << std::endl;
    }

    return nullptr;
}
