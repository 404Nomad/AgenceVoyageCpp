#include "Client/ClientEditDialog.h"

ClientEditDialog::ClientEditDialog(wxWindow* parent, const Client& clientToEdit)
    : wxDialog(parent, wxID_ANY, "Modifier Client", wxDefaultPosition, wxSize(400, 420)) {
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Titre
    wxStaticText* title = new wxStaticText(this, wxID_ANY, "Modifier les informations du client", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    title->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    mainSizer->Add(title, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);

    // Nom
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Nom:"), 0, wxALL, 5);
    m_nomCtrl = new wxTextCtrl(this, wxID_ANY, clientToEdit.nom, wxDefaultPosition, wxSize(350, -1));
    mainSizer->Add(m_nomCtrl, 0, wxALL | wxEXPAND, 5);

    // Prénom
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Prenom:"), 0, wxALL, 5);
    m_prenomCtrl = new wxTextCtrl(this, wxID_ANY, clientToEdit.prenom, wxDefaultPosition, wxSize(350, -1));
    mainSizer->Add(m_prenomCtrl, 0, wxALL | wxEXPAND, 5);

    // Email
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Email:"), 0, wxALL, 5);
    m_emailCtrl = new wxTextCtrl(this, wxID_ANY, clientToEdit.email, wxDefaultPosition, wxSize(350, -1));
    mainSizer->Add(m_emailCtrl, 0, wxALL | wxEXPAND, 5);

    // Téléphone
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Telehone:"), 0, wxALL, 5);
    m_telephoneCtrl = new wxTextCtrl(this, wxID_ANY, clientToEdit.telephone, wxDefaultPosition, wxSize(350, -1));
    mainSizer->Add(m_telephoneCtrl, 0, wxALL | wxEXPAND, 5);

    // Boutons OK et Annuler
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton* okButton = new wxButton(this, wxID_OK, "Enregistrer"); // Bouton Valider
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

std::string ClientEditDialog::GetNom() const { return m_nomCtrl->GetValue().ToStdString(); }
std::string ClientEditDialog::GetPrenom() const { return m_prenomCtrl->GetValue().ToStdString(); }
std::string ClientEditDialog::GetEmail() const { return m_emailCtrl->GetValue().ToStdString(); }
std::string ClientEditDialog::GetTelephone() const { return m_telephoneCtrl->GetValue().ToStdString(); }
