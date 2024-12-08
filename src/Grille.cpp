#include "Grille.h"



// Constructeur : initialise une grille avec le nombre de lignes et de colonnes spécifié
Grille::Grille(int nbLignes, int nbColonnes)
    : lignes(nbLignes), colonnes(nbColonnes) {
    // Vérifie que les dimensions de la grille sont valides
    if (lignes <= 0 || colonnes <= 0) {
        std::cerr << "Dimensions de la grille invalides.\n";
        return;
    }

    // Crée une grille 2D de cellules avec les dimensions spécifiées
    cellules = std::vector<std::vector<Cellule>>(lignes, std::vector<Cellule>(colonnes));

    // Associe chaque cellule à la grille.
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            cellules[i][j].ajouterObservateur(this);
        }
    }
}



// Destructeur : libère les ressources de la grille
Grille::~Grille() {
    cellules.clear(); // Vide le tableau 2D des cellules
}


// Informe du changement d'une cellule
void Grille::notifier() {
    std::cout << "Une cellule a changé d'état.\n";
}

// Calcule les prochains états de toutes les cellules de la grille en fonction des règles du jeu
void Grille::calculerProchainsEtats() {
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            // Compte les voisins vivants de la cellule (i, j)
            int voisinsVivants = compterVoisinsVivants(i, j);
            bool etatActuel = cellules[i][j].estVivante();

            // Application des règles du jeu de la vie
            if (etatActuel) {
                // Une cellule vivante survit si elle a 2 ou 3 voisins vivants
                cellules[i][j].definirProchainEtat(voisinsVivants == 2 || voisinsVivants == 3);
            } else {
                // Une cellule morte devient vivante si elle a exactement 3 voisins vivants
                cellules[i][j].definirProchainEtat(voisinsVivants == 3);
            }
        }
    }
}


// Met à jour l'état de toutes les cellules de la grille
void Grille::actualiserEtats() {
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            cellules[i][j].actualiserEtat();
        }
    }
}

// Compte les voisins vivants autour de la cellule située aux coordonnées (x, y)
int Grille::compterVoisinsVivants(int x, int y) const {
    // Directions des 8 voisins
    int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        { 0, -1},          { 0, 1},
        { 1, -1}, { 1, 0}, { 1, 1}
    };

    int total = 0;

    // Parcourt les 8 directions pour vérifier les voisins
    for (int i = 0; i < 8; i++) {
        int nx = x + directions[i][0];
        int ny = y + directions[i][1];

        // Vérifie si le voisin est dans les limites de la grille et s'il est vivant
        if (nx >= 0 && nx < lignes && ny >= 0 && ny < colonnes && cellules[nx][ny].estVivante()) {
            total++;
        }
    }

    return total;
}



// Affiche la grille avec "1" pour les cellules vivantes et "0" pour les cellules mortes
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


// Retourne une référence à la cellule située aux coordonnées (i, j)
Cellule& Grille::getCellule(int i, int j) {
    if (i < 0 || i >= lignes || j < 0 || j >= colonnes) {
        // `throw` interrompt l'exécution et envoie une exception pour signaler l'erreur d'indice
        throw std::out_of_range("Indices hors limites dans Grille::getCellule.");
    }
    return cellules[i][j];
}

// Renvoie le nombre de lignes dans la grille
int Grille::getLignes() const {
    return lignes;
}

// Renvoie le nombre de colonnes dans la grille
int Grille::getColonnes() const {
    return colonnes;
}

