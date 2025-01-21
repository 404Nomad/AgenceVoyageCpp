#include <wx/wx.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/grid.h>
#include <wx/notebook.h>
#include "Client/ClientEditDialog.h"
#include "Client/ClientAddDialog.cpp"
#include "Client.h" // Inclure la gestion des clients
#include "Trek.h"   // Inclure la gestion des treks
#include "Reservation.h" // Inclure la gestion des reservations
#include "db_setup.h" // Inclure la gestion de la base de données

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

    // Initialize database
    DatabaseInitializer::initializeDatabase();

    // Create main frame
    SetAppName("Agence de Voyage");
    MaFrame* frame = new MaFrame("Gestion Agence de Voyage");
    frame->Show(true);
    return true;
}

MaFrame::MaFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)) {
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

void MaFrame::InitClientsTab() {
    wxPanel* panel = new wxPanel(m_notebook, wxID_ANY);

    wxButton* addButton = new wxButton(panel, wxID_ANY, "Ajouter Client", wxPoint(10, 10));
    wxButton* editButton = new wxButton(panel, wxID_ANY, "Modifier Client", wxPoint(150, 10));
    wxButton* deleteButton = new wxButton(panel, wxID_ANY, "Supprimer Client", wxPoint(300, 10));
    wxButton* listButton = new wxButton(panel, wxID_ANY, "Lister Clients", wxPoint(460, 10));

    wxGrid* clientGrid = new wxGrid(panel, wxID_ANY, wxPoint(10, 50), wxSize(760, 400));
    clientGrid->CreateGrid(0, 5);
    clientGrid->SetColLabelValue(0, "ID");
    clientGrid->SetColLabelValue(1, "Nom");
    clientGrid->SetColLabelValue(2, "Prenom");
    clientGrid->SetColLabelValue(3, "Email");
    clientGrid->SetColLabelValue(4, "Telephone");

    // Fonction pour rafraîchir la grille des clients
    auto refreshClientGrid = [clientGrid]() {
        std::vector<Client> clients = ClientManager::listClients();
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
        }
    };

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



void MaFrame::InitTreksTab() {
    wxPanel* panel = new wxPanel(m_notebook, wxID_ANY);

    wxButton* addTrekButton = new wxButton(panel, wxID_ANY, "Ajouter Trek", wxPoint(10, 10));
    wxButton* editTrekButton = new wxButton(panel, wxID_ANY, "Modifier Trek", wxPoint(150, 10));
    wxButton* listTreksButton = new wxButton(panel, wxID_ANY, "Lister Treks", wxPoint(300, 10));

    // Grille pour afficher les treks
    wxGrid* trekGrid = new wxGrid(panel, wxID_ANY, wxPoint(10, 50), wxSize(760, 400));
    trekGrid->CreateGrid(0, 5);
    trekGrid->SetColLabelValue(0, "ID");
    trekGrid->SetColLabelValue(1, "Nom");
    trekGrid->SetColLabelValue(2, "Lieu");
    trekGrid->SetColLabelValue(3, "Duree (Jours)");
    trekGrid->SetColLabelValue(4, "Prix");

    // Ajuster la taille des colonnes
    trekGrid->SetColSize(0, 50);  // ID
    trekGrid->SetColSize(1, 150); // Nom
    trekGrid->SetColSize(2, 150); // Lieu
    trekGrid->SetColSize(3, 100); // Durée
    trekGrid->SetColSize(4, 100); // Prix

    // Ajuster la taille des lignes (optionnel)
    trekGrid->SetDefaultRowSize(30, true);

    // Fonction pour rafraîchir la grille des treks
    auto refreshTrekGrid = [trekGrid]() {
        std::vector<Trek> treks = TrekManager::listTreks();
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
        }
    };

    // Charger les treks lors de l'ouverture de l'onglet
    refreshTrekGrid();

    // Lier les événements
    addTrekButton->Bind(wxEVT_BUTTON, [this, trekGrid, refreshTrekGrid](wxCommandEvent&) {
        Trek newTrek;
        newTrek.nom = "Nouveau Trek";
        newTrek.lieu = "Lieu Test";
        newTrek.duree = 5;
        newTrek.prix = 300.0;
        newTrek.niveau_difficulte = "Facile";
        newTrek.description = "Description test";

        TrekManager::addTrek(newTrek);
        wxMessageBox("Trek ajoute avec succes !", "Succès", wxOK | wxICON_INFORMATION);

        refreshTrekGrid();
    });

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

            // Afficher un formulaire pour modifier les informations du trek
            wxDialog editDialog(this, wxID_ANY, "Modifier Trek", wxDefaultPosition, wxSize(390, 400));

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

                // Mise à jour dans la base de données
                TrekManager::updateTrek(trekToEdit);
                wxMessageBox("Trek modifie avec succes !", "Succès", wxOK | wxICON_INFORMATION);

                refreshTrekGrid();
            }
        } else {
            wxMessageBox("Veuillez selectionner un trek a modifier.", "Erreur", wxOK | wxICON_WARNING);
        }
    });

    listTreksButton->Bind(wxEVT_BUTTON, [refreshTrekGrid](wxCommandEvent&) {
        refreshTrekGrid();
    });

    m_notebook->AddPage(panel, "Treks", false);
}


void MaFrame::InitReservationsTab() {
    wxPanel* panel = new wxPanel(m_notebook, wxID_ANY);

    wxButton* addReservationButton = new wxButton(panel, wxID_ANY, "Ajouter Reservation", wxPoint(10, 10));
    wxButton* listReservationsButton = new wxButton(panel, wxID_ANY, "Lister Reservations", wxPoint(150, 10));

    wxGrid* reservationGrid = new wxGrid(panel, wxID_ANY, wxPoint(10, 50), wxSize(760, 400));
    reservationGrid->CreateGrid(0, 5);
    reservationGrid->SetColLabelValue(0, "ID");
    reservationGrid->SetColLabelValue(1, "Client");
    reservationGrid->SetColLabelValue(2, "Trek");
    reservationGrid->SetColLabelValue(3, "Date");
    reservationGrid->SetColLabelValue(4, "Statut");

    m_notebook->AddPage(panel, "Reservations", false);
}
