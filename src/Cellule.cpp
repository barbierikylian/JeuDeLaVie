#include "Cellule.h"
#include <iostream>

// Initialise l'état actuel et le prochain état à faux
Cellule::Cellule(bool etatInitial) : vivante(etatInitial), prochainEtat(false) {}

// Définit le prochain état de la cellule
void Cellule::definirProchainEtat(bool etat) {
    prochainEtat = etat;
}


// Met à jour l'état actuel de la cellule avec son prochain état et compte les changements
void Cellule::actualiserEtat() {
    static int changements = 0; // Compteur global des changements d'état

    if (vivante != prochainEtat) { // Vérifie si l'état actuel diffère du prochain
        vivante = prochainEtat;   // Met à jour l'état actuel
        changements++;            
    }

    // Affiche le nombre de changements à la fin de chaque itération
    if (changements > 0) {
        // std::cout << "Changements dans l'itération courante : " << changements << " cellule.\n";
        changements = 0; // Réinitialise le compteur
    }
}

// Retourne vrai si la cellule est vivante, faux sinon
bool Cellule::estVivante() const {
    return vivante;
}

