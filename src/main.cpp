#include <wx/wx.h>                   // Nécessaire pour wxWidgets de base
#include <wx/frame.h>                // Utilisé pour wxFrame (MaFrame)
#include <wx/menu.h>                 // Utilisé pour la barre de menu
#include <wx/grid.h>                 // Utilisé pour wxGrid
#include <wx/notebook.h>             // Utilisé pour wxNotebook
#include "Client/ClientEditDialog.h" // Vérifier si ce fichier est réellement utilisé
#include "Client/ClientAddDialog.cpp" // Inclure un .cpp directement n'est pas recommandé
#include "Client.h"                  // Nécessaire si des appels à ClientManager sont faits
#include "Trek.h"                    // Nécessaire si des appels à TrekManager sont faits
#include "Reservation.h"             // Nécessaire si des appels à ReservationManager sont faits
#include "db_setup.h"                // Nécessaire pour initialiser la base de données
#include "ButtonCellRenderer.h"      // Nécessaire pour les boutons personnalisés dans les grilles


class MonApp : public wxApp {
public:
    virtual bool OnInit();
};

class MaFrame : public wxFrame {
public:
    MaFrame(const wxString& title);

private:
    wxNotebook* m_notebook;

    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    void InitClientsTab();
    void InitTreksTab();
    void InitReservationsTab();
};

enum {
    ID_ABOUT = 1001,
    ID_EXIT = 1002
};

wxIMPLEMENT_APP(MonApp);

bool MonApp::OnInit() {
    // Initialiser wxWidgets pour UTF-8
    wxLocale locale;
    locale.Init(wxLANGUAGE_DEFAULT);

    // Initialize database
    DatabaseInitializer::initializeDatabase();

    // Create main frame
    SetAppName("Agence de Voyage");
    MaFrame* frame = new MaFrame("Gestion Agence de Voyage");
    frame->Show(true);
    return true;
}

// Resolution : 1280x1024
MaFrame::MaFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(1280, 1024)) {
    try {
        // Création de la barre de menu
        wxMenuBar* menuBar = new wxMenuBar();
        wxMenu* menuFile = new wxMenu();
        menuFile->Append(ID_ABOUT, "&A propos\tCtrl-A", "Voir à propos");
        menuFile->AppendSeparator();
        menuFile->Append(ID_EXIT, "&Quitter\tCtrl-Q", "Quitter");
        menuBar->Append(menuFile, "&Fichier");
        SetMenuBar(menuBar);

        // Ajout des événements
        Bind(wxEVT_MENU, &MaFrame::OnAbout, this, ID_ABOUT);
        Bind(wxEVT_MENU, &MaFrame::OnExit, this, ID_EXIT);

        // Création du notebook pour les onglets
        m_notebook = new wxNotebook(this, wxID_ANY);

        // Initialisation des onglets
        InitClientsTab();
        InitTreksTab();
        InitReservationsTab();
    }
    catch (const std::exception& e) {
        wxLogError("Exception: %s", e.what());
    }
}

void MaFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}

void MaFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("Application de gestion pour une agence de voyage specialisee dans les treks.",
                 "À propos", wxOK | wxICON_INFORMATION);
}

// Resolution : 760x400 > 1024x768
void MaFrame::InitClientsTab() {
    wxPanel* panel = new wxPanel(m_notebook, wxID_ANY);

    wxButton* addButton = new wxButton(panel, wxID_ANY, "Ajouter Client", wxPoint(10, 10));
    wxButton* editButton = new wxButton(panel, wxID_ANY, "Modifier Client", wxPoint(150, 10));
    wxButton* deleteButton = new wxButton(panel, wxID_ANY, "Supprimer Client", wxPoint(300, 10));
    wxButton* listButton = new wxButton(panel, wxID_ANY, "Rafraichir Liste", wxPoint(460, 10));

    wxTextCtrl* searchCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(10, 50), wxSize(200, 35), wxTE_PROCESS_ENTER);
    searchCtrl->SetHint("Rechercher un client..."); // Ajouter un placeholder (grisé)
    wxButton* searchButton = new wxButton(panel, wxID_ANY, "Rechercher", wxPoint(220, 50));



    wxGrid* clientGrid = new wxGrid(panel, wxID_ANY, wxPoint(10, 90), wxSize(1260, 800));
    clientGrid->CreateGrid(0, 6);
    clientGrid->SetColLabelValue(0, "ID");
    clientGrid->SetColLabelValue(1, "Nom");
    clientGrid->SetColLabelValue(2, "Prenom");
    clientGrid->SetColLabelValue(3, "Email");
    clientGrid->SetColLabelValue(4, "Telephone");
    clientGrid->SetColLabelValue(5, "Date Inscription");


    // Ajuster la taille des colonnes
    clientGrid->SetColSize(0, 50);  // ID
    clientGrid->SetColSize(1, 150); // Nom
    clientGrid->SetColSize(2, 150); // Prenom
    clientGrid->SetColSize(3, 230); // Email
    clientGrid->SetColSize(4, 110); // Telephone
    clientGrid->SetColSize(5, 120); // Date Inscription

    // Ajuster la taille des lignes (optionnel)
    clientGrid->SetDefaultRowSize(30, true);

    // Fonction pour rafraîchir la grille des clients
    auto refreshClientGrid = [clientGrid](const std::string& filter = "") {
        std::vector<Client> clients;
        if (filter.empty()) {
            clients = ClientManager::listClients();
        } else {
            clients = ClientManager::searchClients(filter);
        }
        clientGrid->ClearGrid();
        if (clientGrid->GetNumberRows() > 0) {
            clientGrid->DeleteRows(0, clientGrid->GetNumberRows());
        }
        for (const auto& client : clients) {
            clientGrid->AppendRows(1);
            int lastRow = clientGrid->GetNumberRows() - 1;
            clientGrid->SetCellValue(lastRow, 0, std::to_string(client.id));
            clientGrid->SetCellValue(lastRow, 1, client.nom);
            clientGrid->SetCellValue(lastRow, 2, client.prenom);
            clientGrid->SetCellValue(lastRow, 3, client.email);
            clientGrid->SetCellValue(lastRow, 4, client.telephone);
            clientGrid->SetCellValue(lastRow, 5, client.date_inscription);
        }
    };

    // Lier le bouton de recherche
    searchButton->Bind(wxEVT_BUTTON, [searchCtrl, refreshClientGrid](wxCommandEvent&) {
        std::string filter = searchCtrl->GetValue().ToStdString();
        refreshClientGrid(filter);
    });

    // Lier la touche "Entrée" dans la barre de recherche
    searchCtrl->Bind(wxEVT_TEXT_ENTER, [searchCtrl, refreshClientGrid](wxCommandEvent&) {
        std::string filter = searchCtrl->GetValue().ToStdString();
        refreshClientGrid(filter);
    });

    // Charger les données au chargement de l'onglet
    refreshClientGrid();


    // Lier les événements
    addButton->Bind(wxEVT_BUTTON, [this, clientGrid, refreshClientGrid](wxCommandEvent&) {
        ClientAddDialog dlg(this);
        if (dlg.ShowModal() == wxID_OK) {
            Client newClient;
            newClient.nom = dlg.GetNom();
            newClient.prenom = dlg.GetPrenom();
            newClient.email = dlg.GetEmail();
            newClient.telephone = dlg.GetTelephone();
            newClient.date_inscription = dlg.GetDate();

            ClientManager::addClient(newClient);
            wxMessageBox("Client ajoute avec succes !", "Succès", wxOK | wxICON_INFORMATION);

            refreshClientGrid();
        }
    });

    editButton->Bind(wxEVT_BUTTON, [this, clientGrid, refreshClientGrid](wxCommandEvent&) {
        int selectedRow = clientGrid->GetGridCursorRow();
        if (selectedRow != wxNOT_FOUND) {
            // Récupérer les données du client sélectionné
            Client clientToEdit;
            clientToEdit.id = std::stoi(clientGrid->GetCellValue(selectedRow, 0).ToStdString());
            clientToEdit.nom = clientGrid->GetCellValue(selectedRow, 1).ToStdString();
            clientToEdit.prenom = clientGrid->GetCellValue(selectedRow, 2).ToStdString();
            clientToEdit.email = clientGrid->GetCellValue(selectedRow, 3).ToStdString();
            clientToEdit.telephone = clientGrid->GetCellValue(selectedRow, 4).ToStdString();

            // Ouvrir le formulaire de modification
            ClientEditDialog dialog(this, clientToEdit);
            if (dialog.ShowModal() == wxID_OK) {
                // Mettre à jour les données avec les nouvelles valeurs
                clientToEdit.nom = dialog.GetNom();
                clientToEdit.prenom = dialog.GetPrenom();
                clientToEdit.email = dialog.GetEmail();
                clientToEdit.telephone = dialog.GetTelephone();

                // Mettre à jour dans la base de données
                ClientManager::updateClient(clientToEdit);

                wxMessageBox("Client modifie avec succes !", "Succès", wxOK | wxICON_INFORMATION);

                refreshClientGrid();
            }
        } else {
            wxMessageBox("Veuillez sélectionner un client à modifier.", "Erreur", wxOK | wxICON_WARNING);
        }
    });

    deleteButton->Bind(wxEVT_BUTTON, [this, clientGrid, refreshClientGrid](wxCommandEvent&) {
        // Supprimer un client
        int selectedRow = clientGrid->GetGridCursorRow();
        if (selectedRow != wxNOT_FOUND) {
            int clientId = std::stoi(clientGrid->GetCellValue(selectedRow, 0).ToStdString());
            ClientManager::deleteClient(clientId);
            wxMessageBox("Client supprime avec succes !", "Succès", wxOK | wxICON_INFORMATION);

            refreshClientGrid();
        } else {
            wxMessageBox("Veuillez sélectionner un client à supprimer.", "Erreur", wxOK | wxICON_WARNING);
        }
    });

    listButton->Bind(wxEVT_BUTTON, [refreshClientGrid](wxCommandEvent&) {
        refreshClientGrid();
    });

    m_notebook->AddPage(panel, "Clients", true);
}

// Resolution : 760x400 > 973, 512
void MaFrame::InitTreksTab() {
    wxPanel* panel = new wxPanel(m_notebook, wxID_ANY);

    wxButton* addTrekButton = new wxButton(panel, wxID_ANY, "Ajouter Trek", wxPoint(10, 10));
    wxButton* editTrekButton = new wxButton(panel, wxID_ANY, "Modifier Trek", wxPoint(150, 10));
    wxButton* deleteTrekButton = new wxButton(panel, wxID_ANY, "Supprimer Trek", wxPoint(300, 10));
    wxButton* listTreksButton = new wxButton(panel, wxID_ANY, "Rafraichir Liste", wxPoint(460, 10));

    wxTextCtrl* searchCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(10, 50), wxSize(200, 35), wxTE_PROCESS_ENTER);
    searchCtrl->SetHint("Rechercher un trek..."); // Ajouter un placeholder (grisé)
    wxButton* searchButton = new wxButton(panel, wxID_ANY, "Rechercher", wxPoint(220, 50));


    // Grille pour afficher les treks
    wxGrid* trekGrid = new wxGrid(panel, wxID_ANY, wxPoint(10, 90), wxSize(1260, 800));
    trekGrid->CreateGrid(0, 8);
    trekGrid->SetColLabelValue(0, "ID");
    trekGrid->SetColLabelValue(1, "Nom");
    trekGrid->SetColLabelValue(2, "Lieu");
    trekGrid->SetColLabelValue(3, "Duree (J)");
    trekGrid->SetColLabelValue(4, "Prix (EUR)");
    trekGrid->SetColLabelValue(5, "Difficulte");
    trekGrid->SetColLabelValue(6, "Description");
    trekGrid->SetColLabelValue(7, "Details & Meteo"); // Colonne pour le bouton Détails

    // Ajuster la taille des colonnes
    trekGrid->SetColSize(0, 50);  // ID
    trekGrid->SetColSize(1, 150); // Nom
    trekGrid->SetColSize(2, 150); // Lieu
    trekGrid->SetColSize(3, 100); // Durée
    trekGrid->SetColSize(4, 110); // Prix
    trekGrid->SetColSize(5, 120); // Niveau Difficulté
    trekGrid->SetColSize(6, 250); // Description
    trekGrid->SetColSize(7, 150); // Détails

    // Ajuster la taille des lignes (optionnel)
    trekGrid->SetDefaultRowSize(30, true);

    trekGrid->SetDefaultCellOverflow(false);

    // Fonction pour rafraîchir la grille des treks
    auto refreshTrekGrid = [trekGrid](const std::string& filter = "") {
        std::vector<Trek> treks = TrekManager::listTreks();
        if (filter.empty()) {
            treks = TrekManager::listTreks();
        } else {
            treks = TrekManager::searchTreks(filter);
        }
        trekGrid->ClearGrid();
        if (trekGrid->GetNumberRows() > 0) {
            trekGrid->DeleteRows(0, trekGrid->GetNumberRows());
        }
        for (const auto& trek : treks) {
            trekGrid->AppendRows(1);
            int lastRow = trekGrid->GetNumberRows() - 1;
            trekGrid->SetCellValue(lastRow, 0, std::to_string(trek.id));
            trekGrid->SetCellValue(lastRow, 1, trek.nom);
            trekGrid->SetCellValue(lastRow, 2, trek.lieu);
            trekGrid->SetCellValue(lastRow, 3, std::to_string(trek.duree));
            trekGrid->SetCellValue(lastRow, 4, std::to_string(trek.prix));
            trekGrid->SetCellValue(lastRow, 5, trek.niveau_difficulte);
            trekGrid->SetCellValue(lastRow, 6, trek.description);
            trekGrid->SetCellRenderer(lastRow, 7, new ButtonCellRenderer());
            //trekGrid->SetCellValue(lastRow, 7, "Meteo"); // Texte fixe pour la colonne Détails

            // Appliquer le renderer personnalisé à la colonne Détails & Météo
        }
    };

    // Lier le bouton de recherche
    searchButton->Bind(wxEVT_BUTTON, [searchCtrl, refreshTrekGrid](wxCommandEvent&) {
        std::string filter = searchCtrl->GetValue().ToStdString();
        refreshTrekGrid(filter);
    });

    // Lier la touche "Entrée" dans la barre de recherche
    searchCtrl->Bind(wxEVT_TEXT_ENTER, [searchCtrl, refreshTrekGrid](wxCommandEvent&) {
        std::string filter = searchCtrl->GetValue().ToStdString();
        refreshTrekGrid(filter);
    });

    // Charger les treks lors de l'ouverture de l'onglet
    refreshTrekGrid();

   // Gestionnaire pour ouvrir une modale avec des données
    trekGrid->Bind(wxEVT_GRID_CELL_LEFT_CLICK, [trekGrid,this](wxGridEvent& event) {
        try {

            // Vérifiez simplement que la colonne cliquée est bien celle des Détails
            int col = event.GetCol();
            int row = event.GetRow();

            if (col == 7) { // Colonne Détails

                // Crée une boîte de dialogue pour tester l'affichage
                wxDialog* detailsDialog = new wxDialog(this, wxID_ANY, "Details du Trek", wxDefaultPosition, wxSize(600, 500));
                wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

                // Récupérer les données de la ligne
                std::string trekId = trekGrid->GetCellValue(row, 0).ToStdString();
                std::string nom = trekGrid->GetCellValue(row, 1).ToStdString();
                std::string lieu = trekGrid->GetCellValue(row, 2).ToStdString();
                std::string duree = trekGrid->GetCellValue(row, 3).ToStdString();
                std::string prix = trekGrid->GetCellValue(row, 4).ToStdString();
                std::string difficulte = trekGrid->GetCellValue(row, 5).ToStdString();
                std::string description = trekGrid->GetCellValue(row, 6).ToStdString();

                // Construire la localisation pour l'API météo
                std::string location = lieu;

                // Récupérer les détails météo
                std::string weatherDetails = TrekManager::getWeatherDetails(location);

                // Afficher les données dans la modale
                sizer->Add(new wxStaticText(detailsDialog, wxID_ANY, wxString::Format("ID: %s", trekId)), 0, wxALL, 10);
                sizer->Add(new wxStaticText(detailsDialog, wxID_ANY, wxString::Format("Nom: %s", nom)), 0, wxALL, 10);
                sizer->Add(new wxStaticText(detailsDialog, wxID_ANY, wxString::Format("Lieu: %s", lieu)), 0, wxALL, 10);
                sizer->Add(new wxStaticText(detailsDialog, wxID_ANY, wxString::Format("Duree: %s jours", duree)), 0, wxALL, 10);
                sizer->Add(new wxStaticText(detailsDialog, wxID_ANY, wxString::Format("Prix: %s EUR", prix)), 0, wxALL, 10);
                sizer->Add(new wxStaticText(detailsDialog, wxID_ANY, wxString::Format("Difficulte: %s", difficulte)), 0, wxALL, 10);
                sizer->Add(new wxStaticText(detailsDialog, wxID_ANY, wxString::Format("Description: %s", description)), 0, wxALL, 10);

                // Ajouter les données météo
                sizer->Add(new wxStaticText(detailsDialog, wxID_ANY, "Météo actuelle :"), 0, wxALL, 10);
                sizer->Add(new wxStaticText(detailsDialog, wxID_ANY, wxString::FromUTF8(weatherDetails)), 0, wxALL, 10);



                // Ajout de données temporaires pour le test
                // sizer->Add(new wxStaticText(detailsDialog, wxID_ANY, "ID: 1"), 0, wxALL, 10);
                // sizer->Add(new wxStaticText(detailsDialog, wxID_ANY, "Nom: Mont Blanc"), 0, wxALL, 10);
                // sizer->Add(new wxStaticText(detailsDialog, wxID_ANY, "Lieu: Alpes"), 0, wxALL, 10);
                // sizer->Add(new wxStaticText(detailsDialog, wxID_ANY, "Duree: 5 jours"), 0, wxALL, 10);
                // sizer->Add(new wxStaticText(detailsDialog, wxID_ANY, "Prix: 500 EUR"), 0, wxALL, 10);
                // sizer->Add(new wxStaticText(detailsDialog, wxID_ANY, "Difficulte: Moyen"), 0, wxALL, 10);
                // sizer->Add(new wxStaticText(detailsDialog, wxID_ANY, "Description: Une aventure alpine incroyable !"), 0, wxALL, 10);

                // Bouton pour fermer la boîte de dialogue
                wxButton* closeButton = new wxButton(detailsDialog, wxID_OK, "Fermer");
                sizer->Add(closeButton, 0, wxALIGN_CENTER | wxALL, 10);

                // Configurer et afficher la boîte de dialogue
                detailsDialog->SetSizer(sizer);
                detailsDialog->Layout();
                detailsDialog->ShowModal();

                // Nettoyer la boîte de dialogue après fermeture
                detailsDialog->Destroy();
            }
        } catch (const std::exception& e) {
            wxMessageBox(wxString::Format("Erreur : %s", e.what()), "Erreur", wxOK | wxICON_ERROR);
        } catch (...) {
            wxMessageBox("Une erreur inconnue est survenue.", "Erreur", wxOK | wxICON_ERROR);
        }
    });




    // Lier les événements
    addTrekButton->Bind(wxEVT_BUTTON, [this, trekGrid, refreshTrekGrid](wxCommandEvent&) {
        wxDialog addDialog(this, wxID_ANY, "Ajouter un Trek", wxDefaultPosition, wxSize(400, 500));

        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

        // Nom
        mainSizer->Add(new wxStaticText(&addDialog, wxID_ANY, "Nom:"), 0, wxALL, 5);
        wxTextCtrl* nomCtrl = new wxTextCtrl(&addDialog, wxID_ANY);
        mainSizer->Add(nomCtrl, 0, wxALL | wxEXPAND, 5);

        // Lieu
        mainSizer->Add(new wxStaticText(&addDialog, wxID_ANY, "Lieu:"), 0, wxALL, 5);
        wxTextCtrl* lieuCtrl = new wxTextCtrl(&addDialog, wxID_ANY);
        mainSizer->Add(lieuCtrl, 0, wxALL | wxEXPAND, 5);

        // Durée
        mainSizer->Add(new wxStaticText(&addDialog, wxID_ANY, "Duree (jours):"), 0, wxALL, 5);
        wxTextCtrl* dureeCtrl = new wxTextCtrl(&addDialog, wxID_ANY);
        mainSizer->Add(dureeCtrl, 0, wxALL | wxEXPAND, 5);

        // Prix
        mainSizer->Add(new wxStaticText(&addDialog, wxID_ANY, "Prix (EUR):"), 0, wxALL, 5);
        wxTextCtrl* prixCtrl = new wxTextCtrl(&addDialog, wxID_ANY);
        mainSizer->Add(prixCtrl, 0, wxALL | wxEXPAND, 5);

        // Niveau de difficulté
        mainSizer->Add(new wxStaticText(&addDialog, wxID_ANY, "Niveau de difficulte:"), 0, wxALL, 5);
        wxChoice* niveauCtrl = new wxChoice(&addDialog, wxID_ANY);
        niveauCtrl->Append("Facile");
        niveauCtrl->Append("Moyen");
        niveauCtrl->Append("Difficile");
        mainSizer->Add(niveauCtrl, 0, wxALL | wxEXPAND, 5);

        // Description
        mainSizer->Add(new wxStaticText(&addDialog, wxID_ANY, "Description:"), 0, wxALL, 5);
        wxTextCtrl* descriptionCtrl = new wxTextCtrl(&addDialog, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
        mainSizer->Add(descriptionCtrl, 1, wxALL | wxEXPAND, 5);

        // Boutons OK et Annuler
        wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
        wxButton* okButton = new wxButton(&addDialog, wxID_OK, "Ajouter");
        wxButton* cancelButton = new wxButton(&addDialog, wxID_CANCEL, "Annuler");
        buttonSizer->Add(okButton, 0, wxALL, 5);
        buttonSizer->Add(cancelButton, 0, wxALL, 5);
        mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER);

        addDialog.SetSizer(mainSizer);
        addDialog.Layout();

        if (addDialog.ShowModal() == wxID_OK) {
            Trek newTrek;
            newTrek.nom = nomCtrl->GetValue().ToStdString();
            newTrek.lieu = lieuCtrl->GetValue().ToStdString();

            try {
                newTrek.duree = std::stoi(dureeCtrl->GetValue().ToStdString());
            } catch (...) {
                wxMessageBox("Veuillez entrer une duree valide.", "Erreur", wxOK | wxICON_WARNING);
                return;
            }

            try {
                newTrek.prix = std::stod(prixCtrl->GetValue().ToStdString());
            } catch (...) {
                wxMessageBox("Veuillez entrer un prix valide.", "Erreur", wxOK | wxICON_WARNING);
                return;
            }

            newTrek.niveau_difficulte = niveauCtrl->GetStringSelection().ToStdString();
            newTrek.description = descriptionCtrl->GetValue().ToStdString();

            TrekManager::addTrek(newTrek);
            wxMessageBox("Trek ajoute avec succes !", "Succès", wxOK | wxICON_INFORMATION);

            refreshTrekGrid();
        }
    });

    // Modifier un trek
    editTrekButton->Bind(wxEVT_BUTTON, [this, trekGrid, refreshTrekGrid](wxCommandEvent&) {
        int selectedRow = trekGrid->GetGridCursorRow();
        if (selectedRow != wxNOT_FOUND) {
            // Récupérer les données du trek sélectionné
            Trek trekToEdit;
            trekToEdit.id = std::stoi(trekGrid->GetCellValue(selectedRow, 0).ToStdString());
            trekToEdit.nom = trekGrid->GetCellValue(selectedRow, 1).ToStdString();
            trekToEdit.lieu = trekGrid->GetCellValue(selectedRow, 2).ToStdString();
            trekToEdit.duree = std::stoi(trekGrid->GetCellValue(selectedRow, 3).ToStdString());
            trekToEdit.prix = std::stod(trekGrid->GetCellValue(selectedRow, 4).ToStdString());
            trekToEdit.niveau_difficulte = trekGrid->GetCellValue(selectedRow, 5).ToStdString();
            trekToEdit.description = trekGrid->GetCellValue(selectedRow, 6).ToStdString();

            // Afficher un formulaire pour modifier les informations du trek
            wxDialog editDialog(this, wxID_ANY, "Modifier Trek", wxDefaultPosition, wxSize(390, 500));

            wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

            // Nom
            mainSizer->Add(new wxStaticText(&editDialog, wxID_ANY, "Nom:"), 0, wxALL, 5);
            wxTextCtrl* nomCtrl = new wxTextCtrl(&editDialog, wxID_ANY, trekToEdit.nom);
            mainSizer->Add(nomCtrl, 0, wxALL | wxEXPAND, 5);

            // Lieu
            mainSizer->Add(new wxStaticText(&editDialog, wxID_ANY, "Lieu:"), 0, wxALL, 5);
            wxTextCtrl* lieuCtrl = new wxTextCtrl(&editDialog, wxID_ANY, trekToEdit.lieu);
            mainSizer->Add(lieuCtrl, 0, wxALL | wxEXPAND, 5);

            // Durée
            mainSizer->Add(new wxStaticText(&editDialog, wxID_ANY, "Duree (Jours):"), 0, wxALL, 5);
            wxTextCtrl* dureeCtrl = new wxTextCtrl(&editDialog, wxID_ANY, std::to_string(trekToEdit.duree));
            mainSizer->Add(dureeCtrl, 0, wxALL | wxEXPAND, 5);

            // Prix
            mainSizer->Add(new wxStaticText(&editDialog, wxID_ANY, "Prix (EUR):"), 0, wxALL, 5);
            wxTextCtrl* prixCtrl = new wxTextCtrl(&editDialog, wxID_ANY, std::to_string(trekToEdit.prix));
            mainSizer->Add(prixCtrl, 0, wxALL | wxEXPAND, 5);

            // Niveau de Difficulté
            mainSizer->Add(new wxStaticText(&editDialog, wxID_ANY, "Niveau Difficulte:"), 0, wxALL, 5);
            wxComboBox* niveauCtrl = new wxComboBox(&editDialog, wxID_ANY, trekToEdit.niveau_difficulte);
            niveauCtrl->Append("Facile");
            niveauCtrl->Append("Moyen");
            niveauCtrl->Append("Difficile");
            mainSizer->Add(niveauCtrl, 0, wxALL | wxEXPAND, 5);

            // Description
            mainSizer->Add(new wxStaticText(&editDialog, wxID_ANY, "Description:"), 0, wxALL, 5);
            wxTextCtrl* descriptionCtrl = new wxTextCtrl(&editDialog, wxID_ANY, trekToEdit.description);
            mainSizer->Add(descriptionCtrl, 0, wxALL | wxEXPAND, 5);

            // Boutons OK et Annuler
            wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
            wxButton* okButton = new wxButton(&editDialog, wxID_OK, "Enregistrer");
            wxButton* cancelButton = new wxButton(&editDialog, wxID_CANCEL, "Annuler");
            buttonSizer->Add(okButton, 0, wxALL, 5);
            buttonSizer->Add(cancelButton, 0, wxALL, 5);
            mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER);

            editDialog.SetSizer(mainSizer);
            editDialog.Layout();

            if (editDialog.ShowModal() == wxID_OK) {
                // Mettre à jour les données avec les nouvelles valeurs
                trekToEdit.nom = nomCtrl->GetValue().ToStdString();
                trekToEdit.lieu = lieuCtrl->GetValue().ToStdString();
                trekToEdit.duree = std::stoi(dureeCtrl->GetValue().ToStdString());
                trekToEdit.prix = std::stod(prixCtrl->GetValue().ToStdString());
                trekToEdit.niveau_difficulte = niveauCtrl->GetValue().ToStdString();
                trekToEdit.description = descriptionCtrl->GetValue().ToStdString();

                // Mise à jour dans la base de données
                TrekManager::updateTrek(trekToEdit);
                wxMessageBox("Trek modifie avec succes !", "Succès", wxOK | wxICON_INFORMATION);

                refreshTrekGrid();
            }
        } else {
            wxMessageBox("Veuillez selectionner un trek a modifier.", "Erreur", wxOK | wxICON_WARNING);
        }
    });

    // Supprimer un trek
    deleteTrekButton->Bind(wxEVT_BUTTON, [this, trekGrid, refreshTrekGrid](wxCommandEvent&) {
        int selectedRow = trekGrid->GetGridCursorRow();
        if (selectedRow != wxNOT_FOUND) {
            int trekId = std::stoi(trekGrid->GetCellValue(selectedRow, 0).ToStdString());
            try {
                TrekManager::deleteTrek(trekId);
                wxMessageBox("Trek supprime avec succes !", "Succès", wxOK | wxICON_INFORMATION);
                refreshTrekGrid();
            } catch (const std::runtime_error& e) {
                wxMessageBox(e.what(), "Erreur", wxOK | wxICON_ERROR);
            } catch (...) {
                wxMessageBox("Une erreur est survenue lors de la suppression du trek.", "Erreur", wxOK | wxICON_ERROR);
            }
        } else {
            wxMessageBox("Veuillez sélectionner un trek à supprimer.", "Erreur", wxOK | wxICON_WARNING);
        }
    });

    listTreksButton->Bind(wxEVT_BUTTON, [refreshTrekGrid](wxCommandEvent&) {
        refreshTrekGrid();
    });

    m_notebook->AddPage(panel, "Treks", false);
}

// Resolution : 760x400 > 973, 512
void MaFrame::InitReservationsTab() {
    wxPanel* panel = new wxPanel(m_notebook, wxID_ANY);

    wxButton* addReservationButton = new wxButton(panel, wxID_ANY, "Ajouter Reservation", wxPoint(10, 10));
    wxButton* listReservationsButton = new wxButton(panel, wxID_ANY, "Rafraichir Page", wxPoint(190, 10));
    wxButton* deleteReservationButton = new wxButton(panel, wxID_ANY, "Supprimer Reservation", wxPoint(340, 10));
    wxButton* cancelReservationButton = new wxButton(panel, wxID_ANY, "Annuler Reservation", wxPoint(540, 10));

    wxTextCtrl* searchCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(10, 50), wxSize(270, 35), wxTE_PROCESS_ENTER);
    searchCtrl->SetHint("Entrer l'id du Client pour rechercher..."); // Placeholder
    wxButton* searchButton = new wxButton(panel, wxID_ANY, "Rechercher", wxPoint(290, 50));


    wxGrid* reservationGrid = new wxGrid(panel, wxID_ANY, wxPoint(10, 90), wxSize(1260, 800));
    reservationGrid->CreateGrid(0, 5);
    reservationGrid->SetColLabelValue(0, "ID");
    reservationGrid->SetColLabelValue(1, "Client");
    reservationGrid->SetColLabelValue(2, "Trek");
    reservationGrid->SetColLabelValue(3, "Date");
    reservationGrid->SetColLabelValue(4, wxString::FromUTF8("Statut"));

    //reservationGrid->EnableEditing(true); // Activer l'édition des cellules

    // Ajuster la taille des colonnes
    reservationGrid->SetColSize(0, 50);  // ID
    reservationGrid->SetColSize(1, 100); // Client ID
    reservationGrid->SetColSize(2, 100); // Trek ID
    reservationGrid->SetColSize(3, 220); // Date Réservation
    reservationGrid->SetColSize(4, 150); // Statut

    reservationGrid->SetDefaultRowSize(30, true);

    // Fonction pour rafraîchir la grille des réservations
    auto refreshReservationGrid = [reservationGrid](int clientId = -1) {
        std::vector<Reservation> reservations;

        if (clientId == -1) {
            // Liste toutes les réservations
            reservations = ReservationManager::listReservations();
        } else {
            // Filtre par client_id
            reservations = ReservationManager::searchReservationsByClientId(clientId);
        }

        reservationGrid->ClearGrid();
        if (reservationGrid->GetNumberRows() > 0) {
            reservationGrid->DeleteRows(0, reservationGrid->GetNumberRows());
        }
        for (const auto& reservation : reservations) {
            reservationGrid->AppendRows(1);
            int lastRow = reservationGrid->GetNumberRows() - 1;
            reservationGrid->SetCellValue(lastRow, 0, std::to_string(reservation.id));
            reservationGrid->SetCellValue(lastRow, 1, std::to_string(reservation.clientId));
            reservationGrid->SetCellValue(lastRow, 2, std::to_string(reservation.trekId));
            reservationGrid->SetCellValue(lastRow, 3, reservation.dateReservation);
            reservationGrid->SetCellValue(lastRow, 4, reservation.statut);
        }
    };


    // Lier le bouton de recherche pour filtrer les réservations par client_id
    searchButton->Bind(wxEVT_BUTTON, [searchCtrl, refreshReservationGrid](wxCommandEvent&) {
        std::string input = searchCtrl->GetValue().ToStdString();
        try {
            int clientId = std::stoi(input); // Convertir l'entrée en entier
            refreshReservationGrid(clientId); // Appel avec un client_id spécifique
        } catch (const std::invalid_argument&) {
            wxMessageBox("Veuillez entrer un ID client valide.", "Erreur", wxOK | wxICON_ERROR);
        }
    });

    // Gérer l'événement pour la touche "Entrée" dans le champ de recherche
    searchCtrl->Bind(wxEVT_TEXT_ENTER, [searchCtrl, refreshReservationGrid](wxCommandEvent&) {
        std::string input = searchCtrl->GetValue().ToStdString();
        try {
            int clientId = std::stoi(input); // Convertir l'entrée en entier
            refreshReservationGrid(clientId); // Appel avec un client_id spécifique
        } catch (const std::invalid_argument&) {
            wxMessageBox("Veuillez entrer un ID client valide.", "Erreur", wxOK | wxICON_ERROR);
        }
    });

    // Automatisation du chargement des données
    refreshReservationGrid();

    // Ajout de réservations avec sélection via dropdown
    addReservationButton->Bind(wxEVT_BUTTON, [this, reservationGrid, refreshReservationGrid](wxCommandEvent&) {
        wxDialog addDialog(this, wxID_ANY, "Ajouter une Reservation", wxDefaultPosition, wxSize(400, 400));

        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

        // Client dropdown
        mainSizer->Add(new wxStaticText(&addDialog, wxID_ANY, "Client:"), 0, wxALL, 5);
        wxChoice* clientDropdown = new wxChoice(&addDialog, wxID_ANY);
        for (const auto& client : ClientManager::listClients()) {
            clientDropdown->Append(std::to_string(client.id) + " - " + client.nom + " " + client.prenom);
        }
        mainSizer->Add(clientDropdown, 0, wxALL | wxEXPAND, 5);

        // Trek dropdown
        mainSizer->Add(new wxStaticText(&addDialog, wxID_ANY, "Trek:"), 0, wxALL, 5);
        wxChoice* trekDropdown = new wxChoice(&addDialog, wxID_ANY);
        for (const auto& trek : TrekManager::listTreks()) {
            trekDropdown->Append(std::to_string(trek.id) + " - " + trek.nom);
        }
        mainSizer->Add(trekDropdown, 0, wxALL | wxEXPAND, 5);

        // Date de réservation
        mainSizer->Add(new wxStaticText(&addDialog, wxID_ANY, "Date de reservation (YYYY-MM-DD):"), 0, wxALL, 5);
        //wxTextCtrl* dateCtrl = new wxTextCtrl(&addDialog, wxID_ANY);
        wxTextCtrl* dateCtrl = new wxTextCtrl(&addDialog, wxID_ANY, getCurrentDate(), wxDefaultPosition, wxSize(350, -1));
        mainSizer->Add(dateCtrl, 0, wxALL | wxEXPAND, 5);

        // Statut
        mainSizer->Add(new wxStaticText(&addDialog, wxID_ANY, "Statut:"), 0, wxALL, 5);
        wxChoice* statutCtrl = new wxChoice(&addDialog, wxID_ANY);
        statutCtrl->Append("Confirmee");
        statutCtrl->Append("Annulee");
        mainSizer->Add(statutCtrl, 0, wxALL | wxEXPAND, 5);

        // Boutons OK et Annuler
        wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
        wxButton* okButton = new wxButton(&addDialog, wxID_OK, "Ajouter");
        wxButton* cancelButton = new wxButton(&addDialog, wxID_CANCEL, "Annuler");
        buttonSizer->Add(okButton, 0, wxALL, 5);
        buttonSizer->Add(cancelButton, 0, wxALL, 5);
        mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER);

        addDialog.SetSizer(mainSizer);
        addDialog.Layout();

        if (addDialog.ShowModal() == wxID_OK) {
            Reservation newReservation;

            // Récupérer les IDs sélectionnés dans les dropdowns
            try {
                int clientIndex = clientDropdown->GetSelection();
                int trekIndex = trekDropdown->GetSelection();
                if (clientIndex == wxNOT_FOUND || trekIndex == wxNOT_FOUND) {
                    throw std::runtime_error("Selection invalide");
                }

                std::string clientSelection = clientDropdown->GetString(clientIndex).ToStdString();
                newReservation.clientId = std::stoi(clientSelection.substr(0, clientSelection.find(" - ")));

                std::string trekSelection = trekDropdown->GetString(trekIndex).ToStdString();
                newReservation.trekId = std::stoi(trekSelection.substr(0, trekSelection.find(" - ")));
            } catch (...) {
                wxMessageBox("Veuillez selectionner des valeurs valides pour le client et le trek.", "Erreur", wxOK | wxICON_WARNING);
                return;
            }

            newReservation.dateReservation = dateCtrl->GetValue().ToStdString();
            newReservation.statut = statutCtrl->GetStringSelection().ToStdString();

            ReservationManager::addReservation(newReservation);
            wxMessageBox("Reservation ajoutee avec succes !", "Succès", wxOK | wxICON_INFORMATION);

            refreshReservationGrid();
        }
    });

    // Gestionnaire pour annuler une réservation
    cancelReservationButton->Bind(wxEVT_BUTTON, [this, reservationGrid, refreshReservationGrid](wxCommandEvent&) {
        int selectedRow = reservationGrid->GetGridCursorRow();
        if (selectedRow != wxNOT_FOUND) {
            int reservationId = std::stoi(reservationGrid->GetCellValue(selectedRow, 0).ToStdString());
            std::string currentStatus = reservationGrid->GetCellValue(selectedRow, 4).ToStdString();

            // Vérifier si la réservation est déjà annulée
            if (currentStatus == "Annulee") {
                wxMessageBox(wxString::FromUTF8("Cette réservation est déjà annulée."),
                             "Information", wxOK | wxICON_INFORMATION);
                return;
            }

            // Mise à jour du statut
            try {
                ReservationManager::updateReservationStatus(reservationId, "Annulee");
                wxMessageBox(wxString::FromUTF8("La réservation a été annulée avec succès."),
                             "Succès", wxOK | wxICON_INFORMATION);
                refreshReservationGrid();
            } catch (...) {
                wxMessageBox(wxString::FromUTF8("Erreur lors de l'annulation de la réservation."),
                             "Erreur", wxOK | wxICON_ERROR);
            }
        } else {
            wxMessageBox(wxString::FromUTF8("Veuillez sélectionner une réservation à annuler."),
                         "Erreur", wxOK | wxICON_WARNING);
        }
    });

    // Rafraîchir la grille des réservations avec bouton 
    listReservationsButton->Bind(wxEVT_BUTTON, [refreshReservationGrid](wxCommandEvent&) {
        refreshReservationGrid();
    });

    // Supprimer une reservation
    deleteReservationButton->Bind(wxEVT_BUTTON, [this, reservationGrid, refreshReservationGrid](wxCommandEvent&) {
        int selectedRow = reservationGrid->GetGridCursorRow();
        if (selectedRow != wxNOT_FOUND) {
            int reservationId = std::stoi(reservationGrid->GetCellValue(selectedRow, 0).ToStdString());

            int answer = wxMessageBox("Voulez-vous vraiment supprimer cette reservation ?", "Confirmation", wxYES_NO | wxICON_QUESTION);
            if (answer == wxYES) {
                ReservationManager::deleteReservation(reservationId);
                wxMessageBox("Reservation supprimee avec succes !", "Succès", wxOK | wxICON_INFORMATION);
                refreshReservationGrid();
            }
        } else {
            wxMessageBox("Veuillez selectionner une reservation valide.", "Erreur", wxOK | wxICON_WARNING);
        }
    });


    m_notebook->AddPage(panel, "Reservations", false);
}
