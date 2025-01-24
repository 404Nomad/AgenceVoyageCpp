#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>
#include <vector>

// Structure représentant une réservation
struct Reservation {
    int id;
    int clientId;
    int trekId;
    std::string dateReservation;
    std::string statut;
};

class ReservationManager {
public:
    // Liste toutes les réservations
    static std::vector<Reservation> listReservations();

    // Ajoute une nouvelle réservation
    static void addReservation(const Reservation& reservation);

    static void updateReservationStatus(int reservationId, const std::string& newStatus);

    // Supprime une réservation par son ID
    static void deleteReservation(int reservationId);

    // Recherche une réservation par son ID
    static std::vector<Reservation> searchReservationsByClientId(int ClientId);
};

#endif // RESERVATION_H
