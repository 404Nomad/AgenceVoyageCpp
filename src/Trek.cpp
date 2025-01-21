#include "Trek.h"
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <stdexcept>
#include <memory>
#include <iostream>

std::vector<Trek> TrekManager::listTreks() {
    std::vector<Trek> treks;

    try {
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        auto con = std::unique_ptr<sql::Connection>(driver->connect("tcp://127.0.0.1:3310", "cppuser", "mycpp"));
        con->setSchema("agencesqlctn");

        auto stmt = std::unique_ptr<sql::Statement>(con->createStatement());
        auto res = std::unique_ptr<sql::ResultSet>(stmt->executeQuery("SELECT * FROM Treks;"));

        while (res->next()) {
            Trek trek;
            trek.id = res->getInt("id");
            trek.nom = res->getString("nom");
            trek.lieu = res->getString("lieu");
            trek.duree = res->getInt("duree");
            trek.prix = res->getDouble("prix");
            trek.niveau_difficulte = res->getString("niveau_difficulte");
            trek.description = res->getString("description");
            treks.push_back(trek);
        }
    } catch (const sql::SQLException& e) {
        std::cerr << "Erreur SQL (listTreks): " << e.what() << std::endl;
    }

    return treks;
}

void TrekManager::addTrek(const Trek& trek) {
    try {
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        auto con = std::unique_ptr<sql::Connection>(driver->connect("tcp://127.0.0.1:3310", "cppuser", "mycpp"));
        con->setSchema("agencesqlctn");

        auto stmt = std::unique_ptr<sql::Statement>(con->createStatement());
        stmt->execute(
            "INSERT INTO Treks (nom, lieu, duree, prix, niveau_difficulte, description) VALUES ('" +
            trek.nom + "', '" + trek.lieu + "', " + std::to_string(trek.duree) + ", " +
            std::to_string(trek.prix) + ", '" + trek.niveau_difficulte + "', '" + trek.description + "');"
        );
    } catch (const sql::SQLException& e) {
        std::cerr << "Erreur SQL (addTrek): " << e.what() << std::endl;
    }
}

void TrekManager::updateTrek(const Trek& trek) {
    try {
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        auto con = std::unique_ptr<sql::Connection>(driver->connect("tcp://127.0.0.1:3310", "cppuser", "mycpp"));
        con->setSchema("agencesqlctn");

        auto stmt = std::unique_ptr<sql::Statement>(con->createStatement());
        stmt->execute(
            "UPDATE Treks SET nom='" + trek.nom + "', lieu='" + trek.lieu +
            "', duree=" + std::to_string(trek.duree) + ", prix=" + std::to_string(trek.prix) +
            ", niveau_difficulte='" + trek.niveau_difficulte + "', description='" + trek.description +
            "' WHERE id=" + std::to_string(trek.id) + ";"
        );
    } catch (const sql::SQLException& e) {
        std::cerr << "Erreur SQL (updateTrek): " << e.what() << std::endl;
    }
}

void TrekManager::deleteTrek(int trekId) {
    try {
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        auto con = std::unique_ptr<sql::Connection>(driver->connect("tcp://127.0.0.1:3310", "cppuser", "mycpp"));
        con->setSchema("agencesqlctn");

        auto stmt = std::unique_ptr<sql::Statement>(con->createStatement());
        stmt->execute("DELETE FROM Treks WHERE id=" + std::to_string(trekId) + ";");
    } catch (const sql::SQLException& e) {
        std::cerr << "Erreur SQL (deleteTrek): " << e.what() << std::endl;
    }
}
