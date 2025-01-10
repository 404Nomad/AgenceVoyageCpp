-- Création de la table Clients
CREATE TABLE Clients (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nom VARCHAR(100) NOT NULL,
    prenom VARCHAR(100) NOT NULL,
    email VARCHAR(150) NOT NULL UNIQUE,
    telephone VARCHAR(20) NOT NULL,
    date_inscription DATE NOT NULL
);

-- Création de la table Treks
CREATE TABLE Treks (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nom VARCHAR(150) NOT NULL,
    lieu VARCHAR(150) NOT NULL,
    duree INT NOT NULL,
    prix DECIMAL(10, 2) NOT NULL,
    niveau_difficulte VARCHAR(50) NOT NULL,
    description TEXT NOT NULL
);

-- Création de la table Réservations
CREATE TABLE Reservations (
    id INT AUTO_INCREMENT PRIMARY KEY,
    client_id INT NOT NULL,
    trek_id INT NOT NULL,
    date_reservation DATE NOT NULL,
    statut ENUM('Confirmée', 'Annulée', 'En attente') NOT NULL,
    FOREIGN KEY (client_id) REFERENCES Clients(id) ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (trek_id) REFERENCES Treks(id) ON DELETE CASCADE ON UPDATE CASCADE
);
œ