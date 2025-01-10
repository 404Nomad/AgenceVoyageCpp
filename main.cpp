#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <variant>
#include <exception>
#include <wx/wx.h>
#include <wx/grid.h>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class MonApp : public wxApp {
    public:
        virtual bool OnInit();
};

class MaFrame : public wxFrame {
    public:
        MaFrame(const wxString& title);
        void OnExit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
    private:
        wxPanel* m_panel;
        wxButton* btn1;
        wxGrid* m_grid;
};

wxIMPLEMENT_APP(MonApp);

enum {
    ID_ABOUT = 1001,
    ID_EXIT = 1002
};

bool MonApp::OnInit() {
    SetAppName("Mon app");
    MaFrame* frame = new MaFrame("Ma première fenêtre");
    frame->Show(true);
    return true;
};

MaFrame::MaFrame(const wxString &title) 
        : wxFrame((wxFrame*) NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800,600)){
            try
            {

                wxMenuBar* menuBar = new wxMenuBar();
                wxMenu* menuFile = new wxMenu();
                menuFile->Append(ID_ABOUT, "&A propos\tCtrl-A","Voir à propos");
                menuFile->AppendSeparator();
                menuFile->Append(ID_EXIT, "&Quitter\tCtrl-Q","Quitter");
                menuBar->Append(menuFile, "&Fichier");
                SetMenuBar(menuBar);

                // creation du panel
                m_panel = new wxPanel(this, wxID_ANY);

                // creation de la grille
                m_grid = new wxGrid(m_panel, wxID_ANY, wxDefaultPosition, wxSize(400,500));
                // initié une table de 5 colonnes et 10 lignes
                m_grid->CreateGrid(10, 5);
                m_grid->SetColLabelValue(0, "col 1");
                m_grid->SetColLabelValue(1, "col 2");
                m_grid->SetColLabelValue(2, "col 3");
                m_grid->SetColLabelValue(3, "col 4");
                m_grid->SetColLabelValue(4, "col 5");

                // remplir la grille avec des données
                for(int row = 0; row < 10; row++){
                    for(int col = 0; col < 5; col++){
                        m_grid->SetCellValue(row, col, wxString::Format("R%dC%d", row + 1, col +1));
                    }
                }

                // désactivation de l'édition des cellules
                m_grid->EnableEditing(false);

                btn1 = new wxButton(m_panel, wxID_ANY, wxT("ok"), wxPoint(10,500));
                
                Bind(wxEVT_MENU, &MaFrame::OnAbout, this, ID_ABOUT);
                Bind(wxEVT_MENU, &MaFrame::OnExit, this, ID_EXIT);

            }
            catch(const std::exception& e)
            {
                std::cerr << "Exception => " << e.what() << '\n';
            }
            
        }

void MaFrame::OnExit(wxCommandEvent& event){
    Close(true);
}

void MaFrame::OnAbout(wxCommandEvent& event){
    wxMessageBox("C'est le widget exemple de menu",
        "about du menubar"
        , wxOK | wxICON_INFORMATION);
}