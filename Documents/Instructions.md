Précédent
Non remis
Application c++
Échéance :31 janvier 2025 23:59
Instructions

Sujet d'évaluation : Création d'un programme C++ pour une agence de voyage spécialisée dans le trek

Objectif :

Développer une application en C++ pour une agence de voyage spécialisée dans l'organisation de treks. Le programme devra gérer les clients, les treks disponibles, les réservations, et intégrer une API météo pour fournir des informations sur les conditions climatiques des destinations. Une interface graphique permettra aux utilisateurs de gérer et de consulter les données facilement.

Contexte :

Vous êtes chargé de développer un programme pour une agence de trek. L'application doit permettre :

```
La gestion des clients et des treks (ajout, modification, suppression).
La gestion des réservations de treks par les clients.
La récupération des prévisions météo pour les lieux des treks via une API externe.
Une interface graphique ergonomique pour gérer ces fonctionnalités.

```

Exigences techniques :

1. Base de données MySQL :
    
    Concevoir une base de données avec les tables suivantes :
    Clients : (id, nom, prénom, email, numéro de téléphone, date d'inscription).
    Treks : (id, nom, lieu, durée (jours), prix, niveau de difficulté, description).
    Réservations : (id, client_id, trek_id, date de réservation, statut).
    
    Implémenter des fonctions pour :
    Ajouter, modifier et supprimer des clients, treks et réservations.
    Lister les clients, treks et réservations avec des filtres (par exemple, par lieu, niveau de difficulté, ou client).
    
2. Consommation d'une API :
    
    Intégrer une API météo pour obtenir les conditions climatiques des lieux de trek.
    Exemple d’API : OpenWeatherMap.
    Fonctionnalité : Lors de l'affichage des détails d'un trek, afficher la météo actuelle et les prévisions pour le lieu.
    
3. Interface graphique :
    
    Utiliser une bibliothèque graphique (Qt, wxWidgets ou FLTK) pour concevoir l'interface utilisateur.
    Écrans requis :
    Gestion des clients : formulaire pour ajouter/modifier les clients et liste des clients existants.
    Gestion des treks : formulaire pour ajouter/modifier les treks et liste des treks avec filtres par lieu ou difficulté.
    Gestion des réservations : formulaire pour ajouter une réservation, liste des réservations avec statut (confirmée, annulée).
    Détails du trek : affichage des informations du trek avec les prévisions météo intégrées.
    
    Ajouter des boutons pour les opérations CRUD et afficher des messages d'erreur en cas de problème (ex. connexion à la base de données).
    

Livrables :

```
Le code source complet du programme.
Le script SQL pour créer les tables et initialiser la base de données.
Un fichier README contenant les étapes pour installer et exécuter le programme, y compris les instructions pour configurer l'API météo.
Diagramme de cas d'usage
Diagramme de classe

```

Bonus :

```
Ajouter une fonctionnalité de recherche avancée pour les treks (par lieu, difficulté, prix).
Intégrer une carte interactive pour visualiser les lieux des treks.
Ajouter un système de notification par email pour confirmer les réservations.

```