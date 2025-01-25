#include "TreksTab.h"
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/msgdlg.h>
#include <wx/grid.h>
#include <vector>
#include <string>
#include "../Trek.h"
#include "../ButtonCellRenderer.h"
#include "../MaFrame.h"
#include <sstream>

// Resolution : 760x400 > 973, 512
void MaFrame::InitTreksTab(wxNotebook* notebook, wxWindow* parentWindow) {
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
                std::istringstream weatherStream(weatherDetails);
                std::string weatherLine;
                while (std::getline(weatherStream, weatherLine)) {
                    sizer->Add(new wxStaticText(detailsDialog, wxID_ANY, wxString::FromUTF8(weatherLine)), 0, wxALL, 5);
                }



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
