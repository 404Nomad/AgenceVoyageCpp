#ifndef TREK_H
#define TREK_H

#include <vector>
#include <string>

// Structure représentant un Trek
struct Trek {
    int id;
    std::string nom;
    std::string lieu;
    int duree;
    double prix;
    std::string niveau_difficulte;
    std::string description;
};

class TrekManager {
public:
    // Liste tous les treks disponibles
    static std::vector<Trek> listTreks();

    // Ajoute un nouveau trek
    static void addTrek(const Trek& trek);

    // Met à jour un trek existant
    static void updateTrek(const Trek& trek);

    // Supprime un trek par son ID
    static void deleteTrek(int trekId);

    // Recherche des treks par filtre
    static std::vector<Trek> searchTreks(const std::string& filter);

    static std::string getWeatherDetails(const std::string& location); // Nouvelle méthode
};

#endif // TREK_H
