#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <iostream>

// Commande pour compiler : g++ mysqlbase.cpp -o mysqlbase -lmysqlcppconn
// Exécution : ./mysqlbase

int main() {
    try {
        // Création de la connexion
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        std::unique_ptr<sql::Connection> con(driver->connect("tcp://127.0.0.1:3310", "cppuser", "mycpp"));

        // Connexion à la base de données
        con->setSchema("agencesqlctn");

        // Création des tables
        std::unique_ptr<sql::Statement> stmt(con->createStatement());

        // Table Clients
        stmt->execute(
            "CREATE TABLE IF NOT EXISTS Clients ("
            "id INT AUTO_INCREMENT PRIMARY KEY, "
            "nom VARCHAR(100) NOT NULL, "
            "prenom VARCHAR(100) NOT NULL, "
            "email VARCHAR(150) NOT NULL UNIQUE, "
            "telephone VARCHAR(20) NOT NULL, "
            "date_inscription DATE NOT NULL);"
        );

        // Table Treks
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

        // Table Reservations
        stmt->execute(
            "CREATE TABLE IF NOT EXISTS Reservations ("
            "id INT AUTO_INCREMENT PRIMARY KEY, "
            "client_id INT NOT NULL, "
            "trek_id INT NOT NULL, "
            "date_reservation DATE NOT NULL, "
            "statut ENUM('Confirmée', 'Annulée', 'En attente') NOT NULL, "
            "FOREIGN KEY (client_id) REFERENCES Clients(id) ON DELETE CASCADE ON UPDATE CASCADE, "
            "FOREIGN KEY (trek_id) REFERENCES Treks(id) ON DELETE CASCADE ON UPDATE CASCADE);"
        );

        // Insertion de données dans Clients
        stmt->execute(
            "INSERT INTO Clients(nom, prenom, email, telephone, date_inscription) VALUES "
            "('Dupont', 'Jean', 'jean.dupont@example.com', '0123456789', '2023-01-01'),"
            "('Durand', 'Marie', 'marie.durand@example.com', '0987654321', '2023-02-01');"
        );

        // Insertion de données dans Treks
        stmt->execute(
            "INSERT INTO Treks(nom, lieu, duree, prix, niveau_difficulte, description) VALUES "
            "('Mont Blanc', 'Alpes', 5, 500.00, 'Difficile', 'Une randonnée exigeante mais gratifiante.'),"
            "('Sentier des douaniers', 'Bretagne', 3, 300.00, 'Facile', 'Un trek le long des côtes bretonnes.');"
        );

        // Insertion de données dans Reservations
        stmt->execute(
            "INSERT INTO Reservations(client_id, trek_id, date_reservation, statut) VALUES "
            "(1, 1, '2023-03-01', 'Confirmée'),"
            "(2, 2, '2023-03-05', 'En attente');"
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

    } catch (sql::SQLException& e) {
        std::cerr << "Erreur SQL : " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
