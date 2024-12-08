#include "JeuDeLaVie.h"
#include <fstream>
#include <filesystem>

// Constructeur : initialise une grille avec les dimensions et fixe le nombre maximal d'itérations
JeuDeLaVie::JeuDeLaVie(int nbLignes, int nbColonnes, int iterMax)
    : grille(nbLignes, nbColonnes), iterationsMax(iterMax) {}

// Destructeur par défaut
JeuDeLaVie::~JeuDeLaVie() {}

// Charge l'état initial de la grille à partir d'un fichier et vérifie sa validité
bool JeuDeLaVie::EtatInitial(const std::string& cheminFichier) {
    std::ifstream fichier(cheminFichier);
    if (!fichier) { // Vérifie si le fichier peut être ouvert
        std::cerr << "Erreur : Impossible d'ouvrir le fichier.\n";
        return false;
    }

    int lignesFichier, colonnesFichier;
    fichier >> lignesFichier >> colonnesFichier;

    std::cout << "Chargement de l'état initial : " << lignesFichier << " x " << colonnesFichier << "\n";

    // Vérifie si les dimensions du fichier correspondent à celles de la grille
    if (lignesFichier != grille.getLignes() || colonnesFichier != grille.getColonnes()) {
        std::cerr << "Erreur : Les dimensions du fichier ne correspondent pas à la grille.\n";
        return false;
    }

    // Lecture des états des cellules depuis le fichier
    for (int i = 0; i < lignesFichier; i++) {
        for (int j = 0; j < colonnesFichier; j++) {
            bool etat;
            fichier >> etat;

            // Vérifie que les indices sont valides (bien que déjà couvert par les dimensions)
            if (i >= grille.getLignes() || j >= grille.getColonnes()) {
                std::cerr << "Erreur : Indice hors limites (" << i << ", " << j << ").\n";
                return false;
            }

            grille.getCellule(i, j).definirProchainEtat(etat); // Définit le prochain état de la cellule
        }
    }

    // Met à jour l'état actuel de toutes les cellules après lecture
    for (int i = 0; i < lignesFichier; i++) {
        for (int j = 0; j < colonnesFichier; j++) {
            grille.getCellule(i, j).actualiserEtat();
        }
    }

    return true; // État initial chargé avec succès
}





// Exécute le jeu sur un nombre d'itérations défini, sauvegarde les états et met à jour la grille
void JeuDeLaVie::executer() {
    std::string fichierSauvegarde = "etat_iterations.txt"; 
    std::ofstream fichier(fichierSauvegarde, std::ios::trunc); // Initialise le fichier en le vidant
    fichier.close();

    for (int iter = 0; iter < iterationsMax + 1; iter++) {
        std::cout << "Itération : " << iter << std::endl;
        grille.afficherGrille(); // Affiche l'état actuel de la grille

        sauvegarderEtat(fichierSauvegarde, iter); // Sauvegarde l'état actuel
        grille.calculerProchainsEtats(); // Calcule les prochains états des cellules
        grille.actualiserEtats();       // Met à jour la grille avec les nouveaux états
    }
}

// Affiche la grille actuelle avec un message descriptif
void JeuDeLaVie::afficher() {
    std::cout << "Voici votre grille " << std::endl;
    grille.afficherGrille();
}

// Sauvegarde l'état actuel de la grille pour une itération donnée dans un fichier spécifique.
void JeuDeLaVie::sauvegarderEtat(const std::string& nomFichierEntree, int iteration) {
    // Nom du dossier où les états seront sauvegardés
    std::string dossierSortie = nomFichierEntree + "_out";

    // Crée le dossier de sortie s'il n'existe pas
    if (!std::filesystem::exists(dossierSortie)) {
        if (!std::filesystem::create_directory(dossierSortie)) {
            std::cerr << "Erreur : impossible de créer le dossier " << dossierSortie << ".\n";
            return;
        }
    }

    // Chemin complet du fichier pour l'itération actuelle
    std::string cheminFichier = dossierSortie + "/etat_" + std::to_string(iteration) + ".txt";

    // Ouvre le fichier pour écrire l'état de la grille
    std::ofstream fichier(cheminFichier);
    if (!fichier) { // Vérifie si l'ouverture du fichier a échoué
        std::cerr << "Erreur : impossible d'ouvrir le fichier " << cheminFichier << " pour sauvegarde.\n";
        return;
    }

    // Écrit l'état de la grille dans le fichier
    fichier << "Iteration " << iteration << ":\n";
    for (int i = 0; i < grille.getLignes(); i++) {
        for (int j = 0; j < grille.getColonnes(); j++) {
            fichier << (grille.getCellule(i, j).estVivante() ? "1 " : "0 "); // État des cellules
        }
        fichier << "\n"; // Passe à la ligne suivante après chaque rangée
    }
    fichier << "\n"; // Ajoute une ligne vide après la grille

    // Message confirmant la sauvegarde
    std::cout << "État de l'itération " << iteration << " sauvegardé dans " << cheminFichier << "\n";
}

// Retourne une référence à la grille associée au jeu
Grille& JeuDeLaVie::getGrille() {
    return grille;
}

