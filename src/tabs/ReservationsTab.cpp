#include "ReservationsTab.h"
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/msgdlg.h>
#include <wx/grid.h>
#include <vector>
#include <string>
#include "../Reservation.h"
#include "../Client.h" // Pour lister les clients
#include "../Trek.h"   // Pour lister les treks
#include "../MaFrame.h"

// Suppose que vous avez une fonction getCurrentDate() quelque part 
// ou vous pouvez la retirer si elle n'est pas nécessaire
extern std::string getCurrentDate();

// Resolution : 760x400 > 973, 512
void MaFrame::InitReservationsTab(wxNotebook* notebook, wxWindow* parentWindow) {
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
