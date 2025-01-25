#include "Trek.h"
#include <cpprest/http_client.h>
#include <cpprest/uri.h>
#include <cpprest/json.h>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <stdexcept>
#include <memory>
#include <iostream>
#include <sstream>
#include "dotenv.h" // Inclure dotenv-cpp
#include <cstdlib>  // Pour std::getenv()


// Liste tous les treks 
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

// Ajouter un trek
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

// Mettre à jour un trek
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

        // Vérifier si des réservations existent pour ce trek
        auto res = std::unique_ptr<sql::ResultSet>(stmt->executeQuery(
            "SELECT COUNT(*) AS count FROM Reservations WHERE trek_id = " + std::to_string(trekId) + ";"
        ));

        res->next();
        int reservationCount = res->getInt("count");
        if (reservationCount > 0) {
            throw std::runtime_error("Des reservations existent pour ce trek. Suppression impossible.");
        }

        // Supprimer le trek
        stmt->execute("DELETE FROM Treks WHERE id = " + std::to_string(trekId) + ";");
    } catch (const sql::SQLException& e) {
        std::cerr << "Erreur SQL (deleteTrek): " << e.what() << std::endl;
        throw;
    } catch (const std::runtime_error& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
        throw;
    }
}

std::vector<Trek> TrekManager::searchTreks(const std::string& filter) {
    std::vector<Trek> treks;

    try {
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        auto con = std::unique_ptr<sql::Connection>(driver->connect("tcp://127.0.0.1:3310", "cppuser", "mycpp"));
        con->setSchema("agencesqlctn");

        auto stmt = std::unique_ptr<sql::Statement>(con->createStatement());
        auto res = std::unique_ptr<sql::ResultSet>(stmt->executeQuery(
            "SELECT * FROM Treks WHERE "
            "nom LIKE '%" + filter + "%' OR "
            "lieu LIKE '%" + filter + "%' OR "
            "prix LIKE '%" + filter + "%' OR "
            "niveau_difficulte LIKE '%" + filter + "%';"
        ));

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
        std::cerr << "Erreur SQL (searchTreks) : " << e.what() << std::endl;
    }

    return treks;
}

bool fileExists(const std::string& filepath) {
    struct stat buffer;
    return (stat(filepath.c_str(), &buffer) == 0);
}

std::string TrekManager::getWeatherDetails(const std::string& location) {
    try {
        // Vérifie si le fichier .env est accessible et charge les variables
        const std::string envPath = std::string(PROJECT_ROOT_DIR) + "/.env";
        if (!fileExists(envPath)) {
            throw std::runtime_error("Fichier .env introuvable ou inaccessible.");
        }

        //Dotenv::load(".env"); // Charge les variables depuis le fichier .env
        //Dotenv::load(std::string(PROJECT_ROOT_DIR) + "/.env");
        Dotenv::load(envPath);
        
        const char* apiKey = std::getenv("OPENWEATHER_API_KEY");
        if (!apiKey) {
            throw std::runtime_error("Clé API introuvable dans les variables d'environnement.");
        }

        web::http::client::http_client client(U("http://api.openweathermap.org/data/2.5/weather"));
        web::uri_builder builder;
        builder.append_query(U("q"), location);
        builder.append_query(U("appid"), apiKey);
        builder.append_query(U("units"), U("metric"));
        builder.append_query(U("lang"), U("fr"));

        auto response = client.request(web::http::methods::GET, builder.to_string()).get();
        if (response.status_code() == web::http::status_codes::OK) {
            auto json = response.extract_json().get();
            if (json.has_field(U("main")) && json.has_field(U("weather"))) {
                std::ostringstream weatherDetails;
                weatherDetails << "Température: " << json[U("main")][U("temp")].as_double() << "°C\n";
                weatherDetails << "Conditions: " << json[U("weather")][0][U("description")].as_string() << "\n";
                weatherDetails << "Humidité: " << json[U("main")][U("humidity")].as_integer() << "%\n";
                return weatherDetails.str();
            } else {
                return "Erreur : Réponse inattendue de l'API.";
            }
        } else {
            return "Erreur : Code HTTP " + std::to_string(response.status_code());
        }
    } catch (const std::exception& e) {
        return "Erreur récupération météo : " + std::string(e.what());
    }
}



