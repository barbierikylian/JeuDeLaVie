#include "Grille.h"



Grille::Grille(int nbLignes, int nbColonnes)
    : lignes(nbLignes), colonnes(nbColonnes) {
    // Vérification des dimensions de la grille
    if (lignes <= 0 || colonnes <= 0) {
        std::cerr << "Dimensions de la grille invalides.\n";
        return;
    }

    // Initialisation du tableau 2D avec std::vector
    cellules = std::vector<std::vector<Cellule>>(lignes, std::vector<Cellule>(colonnes));

    // Ajout de la grille comme observateur à chaque cellule (si nécessaire)
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            cellules[i][j].ajouterObservateur(this); // Ajoute `this` comme observateur
        }
    }
}



Grille::~Grille() {
    cellules.clear(); 
}


void Grille::notifier() {
    std::cout << "Une cellule a changé d'état.\n";
}

void Grille::calculerProchainsEtats() {
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            // Compter les voisins vivants
            int voisinsVivants = compterVoisinsVivants(i, j);
            bool etatActuel = cellules[i][j].estVivante();

            // Vérification des indices
            if (i < 0 || i >= lignes || j < 0 || j >= colonnes) {
                // std::cerr << "Erreur : Indice hors limites détecté (" << i << ", " << j << ").\n";
                continue;
            }

            // Application des règles du jeu
            if (etatActuel) {
                cellules[i][j].definirProchainEtat(voisinsVivants == 2 || voisinsVivants == 3);
            } else {
                cellules[i][j].definirProchainEtat(voisinsVivants == 3);
            }
        }
    }
}


void Grille::actualiserEtats() {
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            cellules[i][j].actualiserEtat();
        }
    }
}

int Grille::compterVoisinsVivants(int x, int y) const {
    int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        { 0, -1},          { 0, 1},
        { 1, -1}, { 1, 0}, { 1, 1}
    };

    int total = 0;

    for (int i = 0; i < 8; i++) {
        int nx = x + directions[i][0];
        int ny = y + directions[i][1];

        // Validation stricte des indices
        if (nx >= 0 && nx < lignes && ny >= 0 && ny < colonnes) {
            if (cellules[nx][ny].estVivante()) {
                total++;
            }
        }
    }

    return total;
}



void Grille::afficherGrille() const {
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            if (cellules[i][j].estVivante()) {
                std::cout << "1 ";
            } else {
                std::cout << "0 ";
            }
        }
        std::cout << "\n";
    }
}

Cellule& Grille::getCellule(int i, int j) {
    if (i < 0 || i >= lignes || j < 0 || j >= colonnes) {
        throw std::out_of_range("Indices hors limites dans Grille::getCellule.");
    }
    return cellules[i][j];
}

const Cellule& Grille::getCellule(int i, int j) const {
    if (i < 0 || i >= lignes || j < 0 || j >= colonnes) {
        throw std::out_of_range("Indices hors limites dans Grille::getCellule.");
    }
    return cellules[i][j];
}

int Grille::getLignes() const{
    return lignes;
}
int Grille::getColonnes() const{
    return colonnes;
}
