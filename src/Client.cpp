#include "Client.h"
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <stdexcept>
#include <memory>
#include <iostream>

// `MySQLBase` contient la logique de connexion
#include "db_setup.h"

// Liste tous les clients
std::vector<Client> ClientManager::listClients() {
    std::vector<Client> clients;

    try {
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        auto con = std::unique_ptr<sql::Connection>(driver->connect("tcp://127.0.0.1:3310", "cppuser", "mycpp"));
        con->setSchema("agencesqlctn");

        auto stmt = std::unique_ptr<sql::Statement>(con->createStatement());
        auto res = std::unique_ptr<sql::ResultSet>(stmt->executeQuery("SELECT * FROM Clients;"));

        while (res->next()) {
            Client client;
            client.id = res->getInt("id");
            client.nom = res->getString("nom");
            client.prenom = res->getString("prenom");
            client.email = res->getString("email");
            client.telephone = res->getString("telephone");
            client.date_inscription = res->getString("date_inscription");
            clients.push_back(client);
        }
    } catch (const sql::SQLException& e) {
        std::cerr << "Erreur SQL (listClients) : " << e.what() << std::endl;
    }

    return clients;
}

// Ajoute un client
void ClientManager::addClient(const Client& client) {
    try {
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        auto con = std::unique_ptr<sql::Connection>(driver->connect("tcp://127.0.0.1:3310", "cppuser", "mycpp"));
        con->setSchema("agencesqlctn");

        auto stmt = std::unique_ptr<sql::Statement>(con->createStatement());
        stmt->execute(
            "INSERT INTO Clients (nom, prenom, email, telephone, date_inscription) VALUES ('" +
            client.nom + "', '" + client.prenom + "', '" + client.email + "', '" + client.telephone + "', '" +
            client.date_inscription + "');"
        );
    } catch (const sql::SQLException& e) {
        std::cerr << "Erreur SQL (addClient) : " << e.what() << std::endl;
    }
}

// Mettre à jour un client
void ClientManager::updateClient(const Client& client) {
    try {
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        auto con = std::unique_ptr<sql::Connection>(driver->connect("tcp://127.0.0.1:3310", "cppuser", "mycpp"));
        con->setSchema("agencesqlctn");

        auto stmt = std::unique_ptr<sql::Statement>(con->createStatement());
        stmt->execute(
            "UPDATE Clients SET nom='" + client.nom + "', prenom='" + client.prenom + "', email='" + client.email +
            "', telephone='" + client.telephone + "' WHERE id=" + std::to_string(client.id) + ";"
        );
    } catch (const sql::SQLException& e) {
        std::cerr << "Erreur SQL (updateClient) : " << e.what() << std::endl;
    }
}

// Supprime un client
void ClientManager::deleteClient(int clientId) {
    try {
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        auto con = std::unique_ptr<sql::Connection>(driver->connect("tcp://127.0.0.1:3310", "cppuser", "mycpp"));
        con->setSchema("agencesqlctn");

        auto stmt = std::unique_ptr<sql::Statement>(con->createStatement());
        stmt->execute("DELETE FROM Clients WHERE id=" + std::to_string(clientId) + ";");
    } catch (const sql::SQLException& e) {
        std::cerr << "Erreur SQL (deleteClient) : " << e.what() << std::endl;
    }
}

std::vector<Client> ClientManager::searchClients(const std::string& filter) {
    std::vector<Client> clients;

    try {
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        auto con = std::unique_ptr<sql::Connection>(driver->connect("tcp://127.0.0.1:3310", "cppuser", "mycpp"));
        con->setSchema("agencesqlctn");

        auto stmt = std::unique_ptr<sql::Statement>(con->createStatement());
        auto res = std::unique_ptr<sql::ResultSet>(stmt->executeQuery(
            "SELECT * FROM Clients WHERE nom LIKE '%" + filter + 
            "%' OR prenom LIKE '%" + filter + 
            "%' OR email LIKE '%" + filter + 
            "%' OR telephone LIKE '%" + filter + "%';"
        ));

        while (res->next()) {
            Client client;
            client.id = res->getInt("id");
            client.nom = res->getString("nom");
            client.prenom = res->getString("prenom");
            client.email = res->getString("email");
            client.telephone = res->getString("telephone");
            client.date_inscription = res->getString("date_inscription");
            clients.push_back(client);
        }
    } catch (const sql::SQLException& e) {
        std::cerr << "Erreur SQL (searchClients) : " << e.what() << std::endl;
    }

    return clients;
}

