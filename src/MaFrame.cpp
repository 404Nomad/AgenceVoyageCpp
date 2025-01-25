#include "MaFrame.h"
#include "tabs/ClientsTab.h"
#include "tabs/TreksTab.h"
#include "tabs/ReservationsTab.h"
#include <wx/msgdlg.h>
#include <exception>

wxBEGIN_EVENT_TABLE(MaFrame, wxFrame)
    // On associe les IDs de menu avec les handlers
    EVT_MENU(ID_ABOUT, MaFrame::OnAbout)
    EVT_MENU(ID_EXIT,  MaFrame::OnExit)
wxEND_EVENT_TABLE()

MaFrame::MaFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(1280, 1024))
{
    try {
        // Barre de menu
        wxMenuBar* menuBar = new wxMenuBar();
        wxMenu* menuFile = new wxMenu();
        menuFile->Append(ID_ABOUT, "&A propos\tCtrl-A", "Voir à propos");
        menuFile->AppendSeparator();
        menuFile->Append(ID_EXIT, "&Quitter\tCtrl-Q", "Quitter");
        menuBar->Append(menuFile, "&Fichier");
        SetMenuBar(menuBar);

        // Création du Notebook
        m_notebook = new wxNotebook(this, wxID_ANY);

        // On initialise chaque onglet via une fonction externe
        InitClientsTab(m_notebook, this);
        InitTreksTab(m_notebook, this);
        InitReservationsTab(m_notebook, this);

    } catch (const std::exception& e) {
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
