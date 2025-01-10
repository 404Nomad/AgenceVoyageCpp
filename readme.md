# Documentation

## Énoncé

Développer une application en C++ pour une agence de voyage spécialisée dans l'organisation de treks. Le programme devra gérer les clients, les treks disponibles, les réservations, et intégrer une API météo pour fournir des informations sur les conditions climatiques des destinations. Une interface graphique permettra aux utilisateurs de gérer et de consulter les données facilement.

---

## Lancer l'application


## Conception

### Analyse des besoins :
Nous utilisons **Draw.io** pour créer les diagrammes suivants :

TODO: corriger les diagrammes
ex: use case ajouter api meteo
ex: verifier cardinalités et include exclude
ex: ...

- **Diagramme des cas d'utilisation** : Représente les interactions principales.
![screenshot](Documents/DiagrammeCasUtilisations/DUse.png)
- **Diagramme de classe** : Modélise les relations entre les entités.
![screenshot](Documents/DiagrammeDeClasse/DClasse.png)

### Conception de la base de donnée :
    Clients : (id, nom, prénom, email, numéro de téléphone, date d'inscription).
    Treks : (id, nom, lieu, durée (jours), prix, niveau de difficulté, description).
    Réservations : (id, client_id, trek_id, date de réservation, statut).
---

## Développement

### Pré-requis

1. Installer les bibliothèques nécessaires (**libs**) :
   - (Liste des bibliothèques à ajouter ici)

### Structure du projet

1. Créer le dossier principal : `AgenceVoyageIHM`.
2. Créer le premier fichier : `main.cpp`.
3. Créer le dossier pour stocker les documents : `Documents`

---
