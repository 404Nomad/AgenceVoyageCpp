#include "ButtonCellRenderer.h"

// Méthode pour dessiner un bouton visuel dans une cellule
void ButtonCellRenderer::Draw(wxGrid& grid, wxGridCellAttr& attr, wxDC& dc,
                              const wxRect& rect, int row, int col, bool isSelected) {
    // Dessiner le fond de la cellule
    wxColour bg = isSelected ? wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT) : attr.GetBackgroundColour();
    dc.SetBrush(wxBrush(bg));
    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.DrawRectangle(rect);

    // Dessiner un bouton visuel
    wxRect buttonRect(rect.x + 2, rect.y + 2, rect.width - 4, rect.height - 4);
    dc.SetBrush(wxBrush(wxColour(30, 144, 255))); // Couleur bleue
    dc.SetPen(wxPen(wxColour(0, 0, 139)));        // Bordure foncée
    dc.DrawRectangle(buttonRect);

    // Dessiner le texte "Meteo" au centre du bouton
    dc.SetTextForeground(*wxWHITE);
    dc.DrawLabel("Meteo", buttonRect, wxALIGN_CENTER);
}

// Retourne la taille optimale pour le contenu de la cellule
wxSize ButtonCellRenderer::GetBestSize(wxGrid& grid, wxGridCellAttr& attr, wxDC& dc,
                                       int row, int col) {
    return wxSize(100, 30); // Largeur et hauteur par défaut pour un bouton
}

// Clone l'instance du renderer
wxGridCellRenderer* ButtonCellRenderer::Clone() const {
    return new ButtonCellRenderer(*this);
}
