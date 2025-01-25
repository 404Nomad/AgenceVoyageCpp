#ifndef CLIENTADDDIALOG_H
#define CLIENTADDDIALOG_H

#include <wx/dialog.h>
#include <wx/textctrl.h>   // Pour wxTextCtrl
#include <string>

// Déclare la fonction, si vous en avez besoin en dehors de ce .cpp
std::string getCurrentDate();

class ClientAddDialog : public wxDialog {
public:
    explicit ClientAddDialog(wxWindow* parent);

    std::string GetNom() const;
    std::string GetPrenom() const;
    std::string GetEmail() const;
    std::string GetTelephone() const;
    std::string GetDate() const;

private:
    wxTextCtrl* m_nomCtrl;
    wxTextCtrl* m_prenomCtrl;
    wxTextCtrl* m_emailCtrl;
    wxTextCtrl* m_telephoneCtrl;
    wxTextCtrl* m_dateCtrl;
};

#endif // CLIENTADDDIALOG_H
