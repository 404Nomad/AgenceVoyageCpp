#include <wx/wx.h>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "Client.h"
#include "Client.h"

// Fonction pour obtenir la date actuelle sous forme de chaîne (YYYY-MM-DD)
std::string getCurrentDate() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d");
    return oss.str();
}

class ClientAddDialog : public wxDialog {
public:
    ClientAddDialog(wxWindow* parent)
        : wxDialog(parent, wxID_ANY, "Ajouter un Client", wxDefaultPosition, wxSize(400, 400)) {
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

        // Champs d'entrée
        wxFlexGridSizer* gridSizer = new wxFlexGridSizer(2, 10, 10);
        gridSizer->Add(new wxStaticText(this, wxID_ANY, "Nom:"));
        m_nomCtrl = new wxTextCtrl(this, wxID_ANY);
        gridSizer->Add(m_nomCtrl);

        gridSizer->Add(new wxStaticText(this, wxID_ANY, "Prenom:"));
        m_prenomCtrl = new wxTextCtrl(this, wxID_ANY);
        gridSizer->Add(m_prenomCtrl);

        gridSizer->Add(new wxStaticText(this, wxID_ANY, "Email:"));
        m_emailCtrl = new wxTextCtrl(this, wxID_ANY);
        gridSizer->Add(m_emailCtrl);

        gridSizer->Add(new wxStaticText(this, wxID_ANY, "Telephone:"));
        m_telephoneCtrl = new wxTextCtrl(this, wxID_ANY);
        gridSizer->Add(m_telephoneCtrl);

        gridSizer->Add(new wxStaticText(this, wxID_ANY, "Date d'inscription:"));
        m_dateCtrl = new wxTextCtrl(this, wxID_ANY, getCurrentDate());
        m_dateCtrl->SetEditable(false); // La date est en lecture seule
        gridSizer->Add(m_dateCtrl);

        sizer->Add(gridSizer, 1, wxALL | wxEXPAND, 10);

        // Boutons
        wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
        buttonSizer->Add(new wxButton(this, wxID_OK, "Ajouter"), 0, wxALL, 5);
        buttonSizer->Add(new wxButton(this, wxID_CANCEL, "Annuler"), 0, wxALL, 5);
        sizer->Add(buttonSizer, 0, wxALIGN_CENTER);

        SetSizer(sizer);
    }

    std::string GetNom() const { return m_nomCtrl->GetValue().ToStdString(); }
    std::string GetPrenom() const { return m_prenomCtrl->GetValue().ToStdString(); }
    std::string GetEmail() const { return m_emailCtrl->GetValue().ToStdString(); }
    std::string GetTelephone() const { return m_telephoneCtrl->GetValue().ToStdString(); }
    std::string GetDate() const { return m_dateCtrl->GetValue().ToStdString(); }

private:
    wxTextCtrl *m_nomCtrl, *m_prenomCtrl, *m_emailCtrl, *m_telephoneCtrl, *m_dateCtrl;
};