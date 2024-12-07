#include "Cellule.h"
#include <iostream>

Cellule::Cellule(bool etatInitial) : vivante(etatInitial), prochainEtat(false) {}

void Cellule::definirProchainEtat(bool etat) {
    prochainEtat = etat;
}

void Cellule::actualiserEtat() {
    static int changements = 0; // Compteur de changements d'état

    if (vivante != prochainEtat) {
        vivante = prochainEtat;
        changements++;
    }

    // Afficher le nombre de changements après chaque itération (à appeler après les boucles principales)
    if (changements > 0) {
        // std::cout << "Changements dans l'itération courante : " << changements << " cellule.\n";
        changements = 0; // Réinitialiser le compteur
    }
}


bool Cellule::estVivante() const {
    return vivante;
}
