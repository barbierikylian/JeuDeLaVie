#include "GestionFichier.h"
#include <fstream>
#include <iostream>

// Lit les dimensions (lignes et colonnes) depuis un fichier et vérifie leur validité
bool lireDimensions(const std::string& cheminFichier, int& lignes, int& colonnes) {
    std::ifstream fichier(cheminFichier);
    if (!fichier) { // Vérifie si le fichier s'ouvre correctement
        std::cerr << "Erreur : impossible d'ouvrir le fichier " << cheminFichier << ".\n";
        return false;
    }

    fichier >> lignes >> colonnes; // Lit les dimensions
    if (fichier.fail() || lignes <= 0 || colonnes <= 0) { // Vérifie la validité des dimensions
        std::cerr << "Erreur : dimensions invalides dans le fichier.\n";
        return false;
    }

    return true; // Dimensions valides
}

