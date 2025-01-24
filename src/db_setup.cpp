#include "db_setup.h"
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <iostream>
#include <memory>

void DatabaseInitializer::initializeDatabase() {
    try {
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        std::unique_ptr<sql::Connection> con(driver->connect("tcp://127.0.0.1:3310", "cppuser", "mycpp"));

        con->setSchema("agencesqlctn");
        std::unique_ptr<sql::Statement> stmt(con->createStatement());

        // Create Clients table
        stmt->execute(
            "CREATE TABLE IF NOT EXISTS Clients ("
            "id INT AUTO_INCREMENT PRIMARY KEY, "
            "nom VARCHAR(100) NOT NULL, "
            "prenom VARCHAR(100) NOT NULL, "
            "email VARCHAR(150) NOT NULL UNIQUE, "
            "telephone VARCHAR(20) NOT NULL, "
            "date_inscription DATE NOT NULL);"
        );

        // Create Treks table
        stmt->execute(
            "CREATE TABLE IF NOT EXISTS Treks ("
            "id INT AUTO_INCREMENT PRIMARY KEY, "
            "nom VARCHAR(150) NOT NULL, "
            "lieu VARCHAR(150) NOT NULL, "
            "duree INT NOT NULL, "
            "prix DECIMAL(10, 2) NOT NULL, "
            "niveau_difficulte VARCHAR(50) NOT NULL, "
            "description TEXT NOT NULL);"
        );

        // Create Reservations table
        stmt->execute(
            "CREATE TABLE IF NOT EXISTS Reservations ("
            "id INT AUTO_INCREMENT PRIMARY KEY, "
            "client_id INT NOT NULL, "
            "trek_id INT NOT NULL, "
            "date_reservation DATE NOT NULL, "
            "statut ENUM('Confirmee', 'Annulee') NOT NULL, "
            "FOREIGN KEY (client_id) REFERENCES Clients(id) ON DELETE CASCADE ON UPDATE CASCADE, "
            "FOREIGN KEY (trek_id) REFERENCES Treks(id) ON DELETE CASCADE ON UPDATE CASCADE);"
        );

        // Insert fixtures for Clients
        stmt->execute(
            "INSERT IGNORE INTO Clients(nom, prenom, email, telephone, date_inscription) VALUES "
            "('Dupont', 'Jean', 'jean.dupont@example.com', '0123456789', '2023-01-01'),"
            "('Durand', 'Marie', 'marie.durand@example.com', '0987654321', '2023-02-01');"
        );

        // Insert fixtures for Treks
        stmt->execute(
            "INSERT IGNORE INTO Treks(nom, lieu, duree, prix, niveau_difficulte, description) VALUES "
            "('Mont Blanc', 'Alpes', 5, 500.00, 'Difficile', 'Une randonnee exigeante mais gratifiante.'),"
            "('Sentier des douaniers', 'Bretagne', 3, 300.00, 'Facile', 'Un trek le long des cotes bretonnes.');"
        );

        // Insert fixtures for Reservations
        stmt->execute(
            "INSERT IGNORE INTO Reservations(client_id, trek_id, date_reservation, statut) VALUES "
            "(1, 1, '2023-03-01', 'Confirmee'),"
            "(2, 2, '2023-03-05', 'Annulee');"
        );

        // Affichage des données de la table Clients
        std::cout << "Table Clients:" << std::endl;
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM Clients;"));
        while (res->next()) {
            std::cout << "ID : " << res->getInt("id") << " | "
                      << "Nom : " << res->getString("nom") << " | "
                      << "Prénom : " << res->getString("prenom") << " | "
                      << "Email : " << res->getString("email") << " | "
                      << "Téléphone : " << res->getString("telephone") << " | "
                      << "Date d'inscription : " << res->getString("date_inscription") << std::endl;
        }

        // Affichage des données de la table Treks
        std::cout << "\nTable Treks:" << std::endl;
        res.reset(stmt->executeQuery("SELECT * FROM Treks;"));
        while (res->next()) {
            std::cout << "ID : " << res->getInt("id") << " | "
                      << "Nom : " << res->getString("nom") << " | "
                      << "Lieu : " << res->getString("lieu") << " | "
                      << "Durée : " << res->getInt("duree") << " jours | "
                      << "Prix : " << res->getDouble("prix") << "€ | "
                      << "Niveau : " << res->getString("niveau_difficulte") << " | "
                      << "Description : " << res->getString("description") << std::endl;
        }

        // Affichage des données de la table Reservations
        std::cout << "\nTable Reservations:" << std::endl;
        // une jointure SQL est utilisée pour inclure les noms des clients et des treks associés.
        res.reset(stmt->executeQuery(
            "SELECT r.id, c.nom AS client_nom, t.nom AS trek_nom, r.date_reservation, r.statut "
            "FROM Reservations r "
            "JOIN Clients c ON r.client_id = c.id "
            "JOIN Treks t ON r.trek_id = t.id;"
        ));
        while (res->next()) {
            std::cout << "ID : " << res->getInt("id") << " | "
                      << "Client : " << res->getString("client_nom") << " | "
                      << "Trek : " << res->getString("trek_nom") << " | "
                      << "Date : " << res->getString("date_reservation") << " | "
                      << "Statut : " << res->getString("statut") << std::endl;
        }

        std::cout << "Database initialized successfully with fixtures!" << std::endl;
    } catch (const sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
    }
}
