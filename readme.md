TODO: changer les "je", "on" , "nous" par un verbe conjugée:
   ex : Nous créons le .env > Création du .env.
# Documentation

## Énoncé

Développer une application en C++ pour une agence de voyage spécialisée dans l'organisation de treks. Le programme devra gérer les clients, les treks disponibles, les réservations, et intégrer une API météo pour fournir des informations sur les conditions climatiques des destinations. Une interface graphique permettra aux utilisateurs de gérer et de consulter les données facilement.

---

## Pré-requis

Avant de pouvoir lancer ou modifier l'application, assurez-vous que les outils et bibliothèques nécessaires sont correctement installés.

### 1. Installer les bibliothèques nécessaires (**libs**)
L'application nécessite plusieurs bibliothèques et outils pour fonctionner correctement :

- **Clang** (compilateur C++) :
  ```bash
  sudo apt install clang
  clang --version
  ```
  Exemple de sortie :
  ```
  Ubuntu clang version 14.0.0-1ubuntu1.1
  ```

- **CMake** (générateur de build) :
  ```bash
  sudo apt install cmake
  cmake --version
  ```
  Exemple de sortie :
  ```
  cmake version 3.22.1
  ```

- **Connecteur MySQL pour C++** :
  ```bash
  sudo apt-get install libmysqlcppconn-dev
  ```

- **Bibliothèque Curl** (pour les requêtes HTTP et FTP) :
  ```bash
  sudo apt-get install libcurl4-openssl-dev
  ```

- **wxWidgets** (pour l'interface graphique) :
  ```bash
  sudo add-apt-repository ppa:hrzhu/wxwidgets3.2-backport
  sudo apt update
  sudo apt install libwxgtk3.2-dev
  ```

### 2. Installer les extensions pour Visual Studio Code
Ouvrez Visual Studio Code et installez les extensions suivantes pour une meilleure gestion des projets C++ :

- **C/C++ by Microsoft** (analyse de code et débogage)
- **C/C++ Themes by Microsoft**
- **C/C++ Extension Pack**
- **CMake Tools by Microsoft** (intégration CMake dans VSCode)
- **CMake by twxs** (coloration syntaxique pour les fichiers `CMakeLists.txt`)
- **Better C++ Syntax** (amélioration de la coloration syntaxique)
- **MakeFile Tools** (support des projets Makefile)

### 3. Configuration de Docker pour MySQL
#### Vérifiez si Docker et Docker Compose sont installés :
Assurez-vous que Docker et Docker Compose sont disponibles sur votre machine :
```bash
docker --version
docker-compose --version
```

#### Démarrez le conteneur MySQL :
Lancez le conteneur Docker avec la commande suivante :
```bash
docker-compose up --build -d
```

#### Vérifiez que le conteneur est opérationnel :
```bash
docker ps
```

---

## Lancer l'application
Une fois tous les prérequis installés et configurés, vous pouvez compiler et exécuter l'application.

1. **Compiler le projet avec CMake :**
   ```bash
   cd build
   cmake ..
   make
   ./wxApp
   ```

2. **Vérifier la connexion à la base de données :**
   Assurez-vous que l'application peut se connecter au conteneur MySQL. Par défaut :
   - Hôte : `localhost`
   - Port : `3310`
   - Utilisateur et mot de passe : configurés dans le fichier `docker-compose.yml`.



## Structure du projet


# Conception

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

On choisit d'utiliser un orchestrateur pour notre base de donnée comme Docker.
On utilise une bibliothèque comme MySQL Connector/C++ pour interagir avec la base de données.
On utilise wxWidgets pour L'interface Utilisateur

### Base de donnée
   On crée notre .env
   On crée notre orchestrateur docker-compose.yml 
      $ docker compose up --build -d
      On se connecte avec un outil externe :
         mysql -h 127.0.0.1 -P 3310 -u cppuser -p
            show databases;
            use agencesqslctn
      Maintenant nos identifiants sont dans le cache du container docker on peut se connecter via un terminal bash ou executer notre fichier  mysqlbase.cpp qui va automatiquement se connecter et charger/créer les tables.
   On crée notre fichier qui servira a load la base mysqlbase.cpp
      Dans ce fichier nous créons la connexion a la base de donnée, créons les tables si elles n'existent pas et insérons des données fictives "fixtures". on finit par montrer le resultat de l'insertion dans le terminal.
      On execute la commande suivnte :  g++ mysqlbase.cpp -o mysqlbase -lmysqlcppconn
      Puis ./mysqlbase
      On a un résultat : ![screenshot](Documents/BaseDeDonnée/bddimport.png)
   On refactor notre fichier mysqlbase.cpp en db_setup.cpp et db_setup.h avec une Fonction void DatabaseInitializer::initializeDatabase() 

### CMake et wxWidgets

   On installe CMake et wxWidgets
   On ajoute un CMakeLists.txt
   On crée un dossier build
   On ajoute le json.hpp de la librairie nlohmann/json: JSON for Modern C++ a notre main.cpp

   On ouvre un terminal et on execute :
   - cmake ..
   - make
   - ./wxApp
   - Notre simple fenetre s'ouvre.
  
  On se rend compte que notre script pour la creation de la base de donnée utilise un int main() ce qui leve une erreur lors de la compilation avec CMake.
  On corrige cette erreur, on compile et ça fonctionne, on peut maintenant lister les clients depuis notre application



---
Database Initialization:

    Tables are created or updated automatically when the application is run.
    This ensures a seamless setup process for your application.

Application Functionality:

    The main window opens correctly.
    The "List Clients" feature works, pulling data from the database and displaying it.
    The "Add Clients" button is functional with placeholder behavior.