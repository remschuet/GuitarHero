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
    sqlite3_open(nomFichier, &db);
}

DAOSqlite::~DAOSqlite() {
    sqlite3_close(db);
}

void DAOSqlite::creationTableJoueur() {
    std::string createTableQuery = "CREATE TABLE IF NOT EXISTS JOUEUR(id INTEGER PRIMARY KEY AUTOINCREMENT, nom TEXT NOT NULL UNIQUE, score INTEGER DEFAULT 0, photo TEXT DEFAULT 'none');";
    sqlite3_exec(db, createTableQuery.c_str(), nullptr, nullptr, nullptr);
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
    std::string query = "SELECT id, nom, score, photo FROM JOUEUR WHERE nom = '" + nom + "';";
    sqlite3_stmt* stmt;
    Joueur* joueur = nullptr;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            joueur = new Joueur(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
                sqlite3_column_int(stmt, 2),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        }
        else {
            sqlite3_finalize(stmt);
            std::string insertQuery = "INSERT INTO JOUEUR (nom) VALUES ('" + nom + ");";
            sqlite3_exec(db, insertQuery.c_str(), nullptr, nullptr, nullptr);
            return getJoueur(nom);
        }
    }
    sqlite3_finalize(stmt);
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
