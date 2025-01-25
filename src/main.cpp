#include <wx/wx.h>
#include "MaFrame.h"
#include "db_setup.h"

class MonApp : public wxApp {
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MonApp);

bool MonApp::OnInit() {
    // Initialiser wxWidgets pour UTF-8
    wxLocale locale;
    locale.Init(wxLANGUAGE_DEFAULT);

    // Initialize database 
    DatabaseInitializer::initializeDatabase();

    // Crée la fenêtre principale
    SetAppName("Agence de Voyage");
    MaFrame* frame = new MaFrame("Gestion Agence de Voyage");
    frame->Show(true);

    return true;
}
