#include "Grille.h"



Grille::Grille(int nbLignes, int nbColonnes) : lignes(nbLignes), colonnes(nbColonnes) {
    // Vérification des dimensions de la grille
    // Si le nombre de lignes ou de colonnes est <= 0, la grille est invalide
    if (lignes <= 0 || colonnes <= 0) {
        std::cout << "Dimensions de la grille invalides.";
    }

    // Allocation dynamique d'un tableau de pointeurs pour les lignes
    cellules = new Cellule*[lignes];
    
    // Parcourir chaque ligne
    for (int i = 0; i < lignes; i++) {
        // Pour chaque ligne, créer un tableau de cellules
        cellules[i] = new Cellule[colonnes];
        
        // Parcourir chaque colonne dans la ligne
        for (int j = 0; j < colonnes; ++j) {
            // Initialisation de chaque cellule (si nécessaire avec `new`, cela dépend de l'implémentation)
            cellules[i][j] = new Cellule();
            
            // Ajout de la grille (this) comme observateur de chaque cellule
            // Cela permet à la grille de réagir aux changements dans les cellules
            cellules[i][j].ajouterObservateur(this);
        }
    }
}



Grille::~Grille() {
    for (int i = 0; i < lignes; ++i) {
        delete[] cellules[i]; // Supprime chaque ligne
    }
    delete[] cellules; // Supprime le tableau de lignes
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

        // Validation des indices
        if (nx >= 0 && nx < lignes && ny >= 0 && ny < colonnes) {
            if (cellules[nx][ny].estVivante()) {
                total++;
            }
        } else {
            // Indice hors limite
            // std::cerr << "Indice voisin hors limites (" << nx << ", " << ny << ").\n";
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

Cellule* Grille::getCellule(int i, int j) const{
    if (i >= 0 && i < lignes && j >= 0 && j < colonnes) {
        return &cellules[i][j];  
    }
    return nullptr;  
}
int Grille::getLignes() const{
    return lignes;
}
int Grille::getColonnes() const{
    return colonnes;
}
