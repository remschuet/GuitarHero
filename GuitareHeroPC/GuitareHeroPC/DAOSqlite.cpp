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
        "photo TEXT DEFAULT 'none');";

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

void DAOSqlite::updateJoueur(std::string nom, std::string nouveauNom) {
    std::string query = "UPDATE JOUEUR SET nom = '" + nouveauNom + "' WHERE nom = '" + nom + "';";
    sqlite3_exec(db, query.c_str(), nullptr, nullptr, nullptr);
}

void DAOSqlite::updateImageJoueur(std::string nom, std::string imageChemin)
{
}

void DAOSqlite::ajouterValeurAleatoire()
{
}

Joueur* DAOSqlite::getMeilleurScore()
{
    return nullptr;
}
