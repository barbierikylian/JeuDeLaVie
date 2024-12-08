#include "JeuDeLaVie.h"
#include <fstream>
#include <filesystem>

JeuDeLaVie::JeuDeLaVie(int nbLignes, int nbColonnes, int iterMax)
    : grille(nbLignes, nbColonnes), iterationsMax(iterMax) {}

JeuDeLaVie::~JeuDeLaVie() {}


bool JeuDeLaVie::EtatInitial(const std::string& cheminFichier) {
    std::ifstream fichier(cheminFichier);
    if (!fichier) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier.\n";
        return false;
    }

    int lignesFichier, colonnesFichier;
    fichier >> lignesFichier >> colonnesFichier;

    std::cout << "Chargement de l'état initial : " << lignesFichier << " x " << colonnesFichier << "\n";

    if (lignesFichier != grille.getLignes() || colonnesFichier != grille.getColonnes()) {
        std::cerr << "Erreur : Les dimensions du fichier ne correspondent pas à la grille.\n";
        return false;
    }

    for (int i = 0; i < lignesFichier; i++) {
        for (int j = 0; j < colonnesFichier; j++) {
            bool etat;
            fichier >> etat;

            if (i >= grille.getLignes() || j >= grille.getColonnes()) {
                std::cerr << "Erreur : Indice hors limites (" << i << ", " << j << ").\n";
                return false;
            }

            grille.getCellule(i, j).definirProchainEtat(etat);
        }
    }

    for (int i = 0; i < lignesFichier; i++) {
        for (int j = 0; j < colonnesFichier; j++) {
            grille.getCellule(i, j).actualiserEtat();
        }
    }

    return true;
}




void JeuDeLaVie::executer() {
    std::string fichierSauvegarde = "etat_iterations.txt"; 
    std::ofstream fichier(fichierSauvegarde, std::ios::trunc); // Nettoie le fichier au début
    fichier.close();

    for (int iter = 0; iter < iterationsMax+1; iter++) {
        std::cout << "Itération : " << iter << std::endl;
        grille.afficherGrille();

        sauvegarderEtat(fichierSauvegarde, iter + 1);
        grille.calculerProchainsEtats();
        grille.actualiserEtats();
    }
}


void JeuDeLaVie::afficher(){
    std::cout << "Voici votre grille "<<std::endl;
    grille.afficherGrille();
}
void JeuDeLaVie::sauvegarderEtat(const std::string& nomFichierEntree, int iteration) {
    // Construire le chemin du dossier de sortie
    std::string dossierSortie = nomFichierEntree + "_out";

    // Vérifier ou créer le dossier de sortie
    if (!std::filesystem::exists(dossierSortie)) {
        if (!std::filesystem::create_directory(dossierSortie)) {
            std::cerr << "Erreur : impossible de créer le dossier " << dossierSortie << ".\n";
            return;
        }
    }

    // Construire le chemin complet du fichier de sauvegarde
    std::string cheminFichier = dossierSortie + "/etat_" + std::to_string(iteration) + ".txt";

    // Ouvrir le fichier en mode écriture
    std::ofstream fichier(cheminFichier);
    if (!fichier) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier " << cheminFichier << " pour sauvegarde.\n";
        return;
    }

    // Écrire l'état de la grille pour l'itération spécifiée
    fichier << "Iteration " << iteration << ":\n";
    for (int i = 0; i < grille.getLignes(); i++) {
        for (int j = 0; j < grille.getColonnes(); j++) {
            fichier << (grille.getCellule(i, j).estVivante() ? "1 " : "0 ");
        }
        fichier << "\n";
    }
    fichier << "\n";

    std::cout << "État de l'itération " << iteration << " sauvegardé dans " << cheminFichier << "\n";
}
Grille& JeuDeLaVie::getGrille(){
        return grille;
    }

