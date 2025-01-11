#ifndef CLIENT_EDIT_DIALOG_H
#define CLIENT_EDIT_DIALOG_H

#include <wx/wx.h>
#include "Client.h" // Inclure pour accéder à la structure Client

class ClientEditDialog : public wxDialog {
public:
    ClientEditDialog(wxWindow* parent, const Client& clientToEdit);

    // Méthodes pour récupérer les données modifiées
    std::string GetNom() const;
    std::string GetPrenom() const;
    std::string GetEmail() const;
    std::string GetTelephone() const;

private:
    wxTextCtrl* m_nomCtrl;
    wxTextCtrl* m_prenomCtrl;
    wxTextCtrl* m_emailCtrl;
    wxTextCtrl* m_telephoneCtrl;
};

#endif // CLIENT_EDIT_DIALOG_H
