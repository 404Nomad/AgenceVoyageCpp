#ifndef MAFRAME_H
#define MAFRAME_H

#include <wx/wx.h>
#include <wx/frame.h>
#include <wx/notebook.h>
#include <wx/menu.h>

class MaFrame : public wxFrame {
public:
    MaFrame(const wxString& title);

private:
    wxNotebook* m_notebook;

    void InitClientsTab( wxNotebook* notebook, wxWindow* parentWindow);       // <= on déclare la méthode membre
    void InitTreksTab(wxNotebook* notebook, wxWindow* parentWindow);
    void InitReservationsTab(wxNotebook* notebook, wxWindow* parentWindow);

    // Menu events
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    // Id pour le menu
    enum {
        ID_ABOUT = 1001,
        ID_EXIT = 1002
    };

    wxDECLARE_EVENT_TABLE();
};

#endif // MAFRAME_H
