#include "Reservation.h"
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <stdexcept>
#include <memory>
#include <iostream>

// Liste toutes les réservations
std::vector<Reservation> ReservationManager::listReservations() {
    std::vector<Reservation> reservations;

    try {
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        auto con = std::unique_ptr<sql::Connection>(driver->connect("tcp://127.0.0.1:3310", "cppuser", "mycpp"));
        con->setSchema("agencesqlctn");

        auto stmt = std::unique_ptr<sql::Statement>(con->createStatement());
        auto res = std::unique_ptr<sql::ResultSet>(stmt->executeQuery(
            "SELECT r.id, r.client_id, r.trek_id, r.date_reservation, r.statut "
            "FROM Reservations r;"
        ));

        while (res->next()) {
            Reservation reservation;
            reservation.id = res->getInt("id");
            reservation.clientId = res->getInt("client_id");
            reservation.trekId = res->getInt("trek_id");
            reservation.dateReservation = res->getString("date_reservation");
            reservation.statut = res->getString("statut");
            reservations.push_back(reservation);
        }
    } catch (const sql::SQLException& e) {
        std::cerr << "Erreur SQL (listReservations): " << e.what() << std::endl;
    }

    return reservations;
}

// Ajoute une nouvelle réservation
void ReservationManager::addReservation(const Reservation& reservation) {
    try {
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        auto con = std::unique_ptr<sql::Connection>(driver->connect("tcp://127.0.0.1:3310", "cppuser", "mycpp"));
        con->setSchema("agencesqlctn");

        auto stmt = std::unique_ptr<sql::Statement>(con->createStatement());
        stmt->execute(
            "INSERT INTO Reservations (client_id, trek_id, date_reservation, statut) VALUES (" +
            std::to_string(reservation.clientId) + ", " +
            std::to_string(reservation.trekId) + ", '" +
            reservation.dateReservation + "', '" + reservation.statut + "');"
        );
    } catch (const sql::SQLException& e) {
        std::cerr << "Erreur SQL (addReservation): " << e.what() << std::endl;
    }
}

// Met à jour le statut d'une réservation
void ReservationManager::updateReservationStatus(int reservationId, const std::string& newStatus) {
    try {
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        auto con = std::unique_ptr<sql::Connection>(driver->connect("tcp://127.0.0.1:3310", "cppuser", "mycpp"));
        con->setSchema("agencesqlctn");

        auto pstmt = std::unique_ptr<sql::PreparedStatement>(
            con->prepareStatement("UPDATE Reservations SET statut = ? WHERE id = ?")
        );
        pstmt->setString(1, newStatus);
        pstmt->setInt(2, reservationId);

        pstmt->executeUpdate();
        std::cout << "Réservation ID " << reservationId << " mise à jour avec le statut : " << newStatus << std::endl;
    } catch (const sql::SQLException& e) {
        std::cerr << "Erreur SQL (updateReservationStatus): " << e.what() << std::endl;
        throw;
    }
}


// Supprime une réservation
void ReservationManager::deleteReservation(int reservationId) {
    try {
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        auto con = std::unique_ptr<sql::Connection>(driver->connect("tcp://127.0.0.1:3310", "cppuser", "mycpp"));
        con->setSchema("agencesqlctn");

        auto stmt = std::unique_ptr<sql::Statement>(con->createStatement());
        stmt->execute("DELETE FROM Reservations WHERE id = " + std::to_string(reservationId) + ";");
    } catch (const sql::SQLException& e) {
        std::cerr << "Erreur SQL (deleteReservation): " << e.what() << std::endl;
    }
}
