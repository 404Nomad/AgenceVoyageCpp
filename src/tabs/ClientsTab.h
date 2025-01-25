#ifndef CLIENTSTAB_H
#define CLIENTSTAB_H

#include "../MaFrame.h"   // On inclut la classe complète

void InitClientsTab(wxNotebook* notebook, wxWindow* parentWindow);

// Dans MaFrame, on aura un prototype "void InitClientsTab();" qu’on peut mettre dedans
// Mais le plus propre est de déclarer la méthode directement dans MaFrame.h 
// et dans ClientsTab.cpp on fait la définition.

#endif // CLIENTSTAB_H
