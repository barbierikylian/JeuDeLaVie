#include "GestionFichier.h"
#include <fstream>
#include <iostream>

bool lireDimensions(const std::string& cheminFichier, int& lignes, int& colonnes) {
    std::ifstream fichier(cheminFichier);
    if (!fichier) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier " << cheminFichier << ".\n";
        return false;
    }

    fichier >> lignes >> colonnes;
    if (fichier.fail() || lignes <= 0 || colonnes <= 0) {
        std::cerr << "Erreur : dimensions invalides dans le fichier.\n";
        return false;
    }

    return true;
}
