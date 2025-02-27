#include "ClientAddDialog.h"
#include <wx/wx.h>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "Client.h"
#include <wx/textctrl.h>

// Fonction pour obtenir la date actuelle sous forme de chaîne (YYYY-MM-DD)
std::string getCurrentDate() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d");
    return oss.str();
}


ClientAddDialog::ClientAddDialog(wxWindow* parent)
    : wxDialog(parent, wxID_ANY, "Ajouter un Client", wxDefaultPosition, wxSize(420, 460))
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Nom
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Nom:"), 0, wxALL, 5);
    m_nomCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString,
                               wxDefaultPosition, wxSize(350, -1));
    mainSizer->Add(m_nomCtrl, 0, wxALL | wxEXPAND, 5);

    // Prénom
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Prenom:"), 0, wxALL, 5);
    m_prenomCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString,
                                  wxDefaultPosition, wxSize(350, -1));
    mainSizer->Add(m_prenomCtrl, 0, wxALL | wxEXPAND, 5);

    // Email
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Email:"), 0, wxALL, 5);
    m_emailCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString,
                                 wxDefaultPosition, wxSize(350, -1));
    mainSizer->Add(m_emailCtrl, 0, wxALL | wxEXPAND, 5);

    // Téléphone
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Telephone:"), 0, wxALL, 5);
    m_telephoneCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString,
                                     wxDefaultPosition, wxSize(350, -1));
    mainSizer->Add(m_telephoneCtrl, 0, wxALL | wxEXPAND, 5);

    // Date d'inscription
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Date d'inscription:"), 0, wxALL, 5);
    m_dateCtrl = new wxTextCtrl(this, wxID_ANY, getCurrentDate(),
                                wxDefaultPosition, wxSize(350, -1));
    m_dateCtrl->SetEditable(false); // La date est en lecture seule
    mainSizer->Add(m_dateCtrl, 0, wxALL | wxEXPAND, 5);

    // Boutons OK et Annuler
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton* okButton = new wxButton(this, wxID_OK, "Ajouter");
    wxButton* cancelButton = new wxButton(this, wxID_CANCEL, "Annuler");

    buttonSizer->Add(okButton, 0, wxALL, 10);
    buttonSizer->Add(cancelButton, 0, wxALL, 10);
    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER);

    // Ajout du padding global
    wxSizer* paddingSizer = new wxBoxSizer(wxVERTICAL);
    paddingSizer->Add(mainSizer, 1, wxALL | wxEXPAND, 20);
    SetSizer(paddingSizer);

    Layout();
}

// std::string GetNom() const { return m_nomCtrl->GetValue().ToStdString(); }
// std::string GetPrenom() const { return m_prenomCtrl->GetValue().ToStdString(); }
// std::string GetEmail() const { return m_emailCtrl->GetValue().ToStdString(); }
// std::string GetTelephone() const { return m_telephoneCtrl->GetValue().ToStdString(); }
// std::string GetDate() const { return m_dateCtrl->GetValue().ToStdString(); }

// Getters
std::string ClientAddDialog::GetNom() const {
    return m_nomCtrl->GetValue().ToStdString();
}

std::string ClientAddDialog::GetPrenom() const {
    return m_prenomCtrl->GetValue().ToStdString();
}

std::string ClientAddDialog::GetEmail() const {
    return m_emailCtrl->GetValue().ToStdString();
}

std::string ClientAddDialog::GetTelephone() const {
    return m_telephoneCtrl->GetValue().ToStdString();
}

std::string ClientAddDialog::GetDate() const {
    return m_dateCtrl->GetValue().ToStdString();
}

