#include <wx/wx.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/grid.h>
#include <wx/notebook.h>
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
    wxMessageBox("Application de gestion pour une agence de voyage spécialisée dans les treks.",
                 "À propos", wxOK | wxICON_INFORMATION);
}

void MaFrame::InitClientsTab() {
    wxPanel* panel = new wxPanel(m_notebook, wxID_ANY);

    // Bouton pour ajouter un client
    wxButton* addButton = new wxButton(panel, wxID_ANY, "Ajouter Client", wxPoint(10, 10));
    wxButton* listButton = new wxButton(panel, wxID_ANY, "Lister Clients", wxPoint(150, 10));

    // Grille pour afficher les clients
    wxGrid* clientGrid = new wxGrid(panel, wxID_ANY, wxPoint(10, 50), wxSize(760, 400));
    clientGrid->CreateGrid(0, 5);
    clientGrid->SetColLabelValue(0, "ID");
    clientGrid->SetColLabelValue(1, "Nom");
    clientGrid->SetColLabelValue(2, "Prenom");
    clientGrid->SetColLabelValue(3, "Email");
    clientGrid->SetColLabelValue(4, "Telephone");

    // Lier les événements
    addButton->Bind(wxEVT_BUTTON, [=](wxCommandEvent&) {
        wxMessageBox("Fonction Ajouter Client appelée", "Info", wxOK | wxICON_INFORMATION);
    });

    listButton->Bind(wxEVT_BUTTON, [=](wxCommandEvent&) {
        // Exemple d'utilisation de `ClientManager` pour lister les clients
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
    });

    m_notebook->AddPage(panel, "Clients", true);
}

void MaFrame::InitTreksTab() {
    wxPanel* panel = new wxPanel(m_notebook, wxID_ANY);

    wxButton* addTrekButton = new wxButton(panel, wxID_ANY, "Ajouter Trek", wxPoint(10, 10));
    wxButton* listTreksButton = new wxButton(panel, wxID_ANY, "Lister Treks", wxPoint(150, 10));

    // Placeholder grid for treks
    wxGrid* trekGrid = new wxGrid(panel, wxID_ANY, wxPoint(10, 50), wxSize(760, 400));
    trekGrid->CreateGrid(0, 5);
    trekGrid->SetColLabelValue(0, "ID");
    trekGrid->SetColLabelValue(1, "Nom");
    trekGrid->SetColLabelValue(2, "Lieu");
    trekGrid->SetColLabelValue(3, "Duree");
    trekGrid->SetColLabelValue(4, "Prix");

    m_notebook->AddPage(panel, "Treks", false);
}

void MaFrame::InitReservationsTab() {
    wxPanel* panel = new wxPanel(m_notebook, wxID_ANY);

    wxButton* addReservationButton = new wxButton(panel, wxID_ANY, "Ajouter Réservation", wxPoint(10, 10));
    wxButton* listReservationsButton = new wxButton(panel, wxID_ANY, "Lister Réservations", wxPoint(150, 10));

    wxGrid* reservationGrid = new wxGrid(panel, wxID_ANY, wxPoint(10, 50), wxSize(760, 400));
    reservationGrid->CreateGrid(0, 5);
    reservationGrid->SetColLabelValue(0, "ID");
    reservationGrid->SetColLabelValue(1, "Client");
    reservationGrid->SetColLabelValue(2, "Trek");
    reservationGrid->SetColLabelValue(3, "Date");
    reservationGrid->SetColLabelValue(4, "Statut");

    m_notebook->AddPage(panel, "Réservations", false);
}
