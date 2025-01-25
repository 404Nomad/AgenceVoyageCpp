#include "ClientsTab.h"
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/msgdlg.h>
#include <wx/grid.h>
#include "../Client/ClientAddDialog.h"
#include "../Client/ClientEditDialog.h"
#include "../Client.h"  // Pour ClientManager
#include "../ButtonCellRenderer.h"   
#include <vector>
#include <string>
#include <exception>
#include <algorithm>

// Si vous avez une classe parentFrame, on la déclare en forward ou on inclut "MaFrame.h"
#include "../MaFrame.h"

void MaFrame::InitClientsTab(wxNotebook* notebook, wxWindow* parentWindow)
{
    wxPanel* panel = new wxPanel(notebook, wxID_ANY);

    wxButton* addButton = new wxButton(panel, wxID_ANY, "Ajouter Client", wxPoint(10, 10));
    wxButton* editButton = new wxButton(panel, wxID_ANY, "Modifier Client", wxPoint(150, 10));
    wxButton* deleteButton = new wxButton(panel, wxID_ANY, "Supprimer Client", wxPoint(300, 10));
    wxButton* listButton = new wxButton(panel, wxID_ANY, "Rafraichir Liste", wxPoint(460, 10));

    wxTextCtrl* searchCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(10, 50), wxSize(200, 35), wxTE_PROCESS_ENTER);
    searchCtrl->SetHint("Rechercher un client...");
    wxButton* searchButton = new wxButton(panel, wxID_ANY, "Rechercher", wxPoint(220, 50));

    wxGrid* clientGrid = new wxGrid(panel, wxID_ANY, wxPoint(10, 90), wxSize(1260, 800));
    clientGrid->CreateGrid(0, 6);
    clientGrid->SetColLabelValue(0, "ID");
    clientGrid->SetColLabelValue(1, "Nom");
    clientGrid->SetColLabelValue(2, "Prenom");
    clientGrid->SetColLabelValue(3, "Email");
    clientGrid->SetColLabelValue(4, "Telephone");
    clientGrid->SetColLabelValue(5, "Date Inscription");

    // Ajustement des tailles de colonnes
    clientGrid->SetColSize(0, 50);
    clientGrid->SetColSize(1, 150);
    clientGrid->SetColSize(2, 150);
    clientGrid->SetColSize(3, 230);
    clientGrid->SetColSize(4, 110);
    clientGrid->SetColSize(5, 120);

    clientGrid->SetDefaultRowSize(30, true);

    // Lambda pour rafraîchir la grille
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

    // Bind du bouton de recherche
    searchButton->Bind(wxEVT_BUTTON, [searchCtrl, refreshClientGrid](wxCommandEvent&) {
        std::string filter = searchCtrl->GetValue().ToStdString();
        refreshClientGrid(filter);
    });

    // Bind sur Enter
    searchCtrl->Bind(wxEVT_TEXT_ENTER, [searchCtrl, refreshClientGrid](wxCommandEvent&) {
        std::string filter = searchCtrl->GetValue().ToStdString();
        refreshClientGrid(filter);
    });

    // Charger la liste au départ
    refreshClientGrid();

    // Ajouter un client
    addButton->Bind(wxEVT_BUTTON, [parentWindow, refreshClientGrid](wxCommandEvent&) {
        ClientAddDialog dlg(parentWindow);
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

    // Modifier un client
    editButton->Bind(wxEVT_BUTTON, [parentWindow, clientGrid, refreshClientGrid](wxCommandEvent&) {
        int selectedRow = clientGrid->GetGridCursorRow();
        if (selectedRow != wxNOT_FOUND) {
            Client clientToEdit;
            clientToEdit.id = std::stoi(clientGrid->GetCellValue(selectedRow, 0).ToStdString());
            clientToEdit.nom = clientGrid->GetCellValue(selectedRow, 1).ToStdString();
            clientToEdit.prenom = clientGrid->GetCellValue(selectedRow, 2).ToStdString();
            clientToEdit.email = clientGrid->GetCellValue(selectedRow, 3).ToStdString();
            clientToEdit.telephone = clientGrid->GetCellValue(selectedRow, 4).ToStdString();

            ClientEditDialog dialog(parentWindow, clientToEdit);
            if (dialog.ShowModal() == wxID_OK) {
                clientToEdit.nom = dialog.GetNom();
                clientToEdit.prenom = dialog.GetPrenom();
                clientToEdit.email = dialog.GetEmail();
                clientToEdit.telephone = dialog.GetTelephone();

                ClientManager::updateClient(clientToEdit);
                wxMessageBox("Client modifie avec succes !", "Succès", wxOK | wxICON_INFORMATION);
                refreshClientGrid();
            }
        } else {
            wxMessageBox("Veuillez sélectionner un client à modifier.", "Erreur", wxOK | wxICON_WARNING);
        }
    });

    // Supprimer un client
    deleteButton->Bind(wxEVT_BUTTON, [clientGrid, refreshClientGrid](wxCommandEvent&) {
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

    // Rafraîchir
    listButton->Bind(wxEVT_BUTTON, [refreshClientGrid](wxCommandEvent&) {
        refreshClientGrid();
    });

    // On ajoute le panel dans l'onglet
    notebook->AddPage(panel, "Clients", true);
}
