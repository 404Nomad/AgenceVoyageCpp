#include "Client/ClientEditDialog.h"

ClientEditDialog::ClientEditDialog(wxWindow* parent, const Client& clientToEdit)
    : wxDialog(parent, wxID_ANY, "Modifier Client", wxDefaultPosition, wxSize(400, 400)) {
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    // Nom
    sizer->Add(new wxStaticText(this, wxID_ANY, "Nom"), 0, wxALL, 5);
    m_nomCtrl = new wxTextCtrl(this, wxID_ANY, clientToEdit.nom, wxDefaultPosition, wxSize(300, -1));
    sizer->Add(m_nomCtrl, 0, wxALL, 5);

    // Prénom
    sizer->Add(new wxStaticText(this, wxID_ANY, "Prenom"), 0, wxALL, 5);
    m_prenomCtrl = new wxTextCtrl(this, wxID_ANY, clientToEdit.prenom, wxDefaultPosition, wxSize(300, -1));
    sizer->Add(m_prenomCtrl, 0, wxALL, 5);

    // Email
    sizer->Add(new wxStaticText(this, wxID_ANY, "Email"), 0, wxALL, 5);
    m_emailCtrl = new wxTextCtrl(this, wxID_ANY, clientToEdit.email, wxDefaultPosition, wxSize(300, -1));
    sizer->Add(m_emailCtrl, 0, wxALL, 5);

    // Téléphone
    sizer->Add(new wxStaticText(this, wxID_ANY, "Telephone"), 0, wxALL, 5);
    m_telephoneCtrl = new wxTextCtrl(this, wxID_ANY, clientToEdit.telephone, wxDefaultPosition, wxSize(300, -1));
    sizer->Add(m_telephoneCtrl, 0, wxALL, 5);

    // Boutons OK et Annuler
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton* okButton = new wxButton(this, wxID_OK, "Enregistrer"); // Bouton Valider
    wxButton* cancelButton = new wxButton(this, wxID_CANCEL, "Annuler");

    buttonSizer->Add(okButton, 0, wxALL, 5);
    buttonSizer->Add(cancelButton, 0, wxALL, 5);

    sizer->Add(buttonSizer, 0, wxALIGN_LEFT);

    SetSizer(sizer);
    Layout();
}

std::string ClientEditDialog::GetNom() const { return m_nomCtrl->GetValue().ToStdString(); }
std::string ClientEditDialog::GetPrenom() const { return m_prenomCtrl->GetValue().ToStdString(); }
std::string ClientEditDialog::GetEmail() const { return m_emailCtrl->GetValue().ToStdString(); }
std::string ClientEditDialog::GetTelephone() const { return m_telephoneCtrl->GetValue().ToStdString(); }
