#ifndef BUTTON_CELL_RENDERER_H
#define BUTTON_CELL_RENDERER_H

#include <wx/grid.h>
#include <wx/dc.h>
#include <wx/settings.h>
#include <wx/colour.h>

// Classe pour dessiner un bouton visuel dans une cellule
class ButtonCellRenderer : public wxGridCellRenderer {
public:
    // Dessine un bouton visuel
    void Draw(wxGrid& grid, wxGridCellAttr& attr, wxDC& dc,
              const wxRect& rect, int row, int col, bool isSelected) override;

    // Retourne la meilleure taille pour le contenu
    wxSize GetBestSize(wxGrid& grid, wxGridCellAttr& attr, wxDC& dc,
                       int row, int col) override;

    // Clone l'instance du renderer
    wxGridCellRenderer* Clone() const override;
};

#endif // BUTTON_CELL_RENDERER_H
