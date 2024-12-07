#ifndef GRILLE_H
#define GRILLE_H

#include "Cellule.h"
#include "Observateur.h"
#include <iostream>

class Grille : public Observateur {
private:
    int lignes, colonnes;
    Cellule** cellules;

public:
    Grille(int nbLignes, int nbColonnes);
    ~Grille();

    void notifier() override;
    void calculerProchainsEtats();
    void actualiserEtats();
    int compterVoisinsVivants(int x, int y) const;
    void afficherGrille() const;
    Cellule* getCellule(int i, int j) const;
    int getLignes() const;
    int getColonnes() const;
};

#endif
