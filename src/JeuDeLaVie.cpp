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
    if (!fichier) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier " << cheminFichier << " pour sauvegarde.\n";
        return;
    }

    // Écrit les dimensions de la grille dans le fichier
    fichier << grille.getLignes() << " " << grille.getColonnes() << "\n";

    // Écrit l'état de la grille dans le fichier
    for (int i = 0; i < grille.getLignes(); i++) {
        for (int j = 0; j < grille.getColonnes(); j++) {
            fichier << (grille.getCellule(i, j).estVivante() ? "1 " : "0 "); // État des cellules
        }
        fichier << "\n"; // Passe à la ligne suivante après chaque rangée
    }

    // Message confirmant la sauvegarde
    std::cout << "État de l'itération " << iteration << " sauvegardé dans " << cheminFichier << "\n";
}


// Retourne une référence à la grille associée au jeu
Grille& JeuDeLaVie::getGrille() {
    return grille;
}
// Charge l'état depuis un fichier texte
bool JeuDeLaVie::chargerEtatDepuisFichier(const std::string& cheminFichier, std::vector<std::vector<bool>>& etatGrille) {
    std::ifstream fichier(cheminFichier); // Ouvre le fichier en mode lecture
    if (!fichier) { // Vérifie si le fichier est ouvert avec succès
        std::cerr << "Erreur : impossible d'ouvrir le fichier " << cheminFichier << ".\n";
        return false; // Retourne false en cas d'échec
    }

    int lignes, colonnes;
    fichier >> lignes >> colonnes; // Lit les dimensions de la grille
    std::cout << "Chargement des dimensions du fichier " << cheminFichier << " : " << lignes << " x " << colonnes << "\n";

    // Vérifie si les dimensions sont valides
    if (fichier.fail() || lignes <= 0 || colonnes <= 0) {
        std::cerr << "Erreur : dimensions invalides dans le fichier " << cheminFichier << ".\n";
        return false;
    }

    // Redimensionne la grille en fonction des dimensions lues
    etatGrille.resize(lignes, std::vector<bool>(colonnes));

    // Parcourt chaque cellule pour lire son état (0 ou 1)
    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            int val;
            fichier >> val; // Lit la valeur de la cellule
            // Vérifie si la valeur est valide (0 ou 1 uniquement)
            if (fichier.fail() || (val != 0 && val != 1)) {
                std::cerr << "Erreur : données invalides dans le fichier à la position (" << i << ", " << j << ").\n";
                return false;
            }
            // Convertit la valeur entière en booléen
            etatGrille[i][j] = (val == 1);
        }
    }

    // Si tout s'est bien passé, indique que le fichier a été chargé avec succès
    std::cout << "État chargé depuis le fichier : " << cheminFichier << "\n";
    return true;
}


// Compare l'état simulé et l'état attendu à partir de deux fichiers
void JeuDeLaVie::testerEtatAvecFichier(const std::string& fichierEtat, const std::string& fichierReference) {
    std::vector<std::vector<bool>> etatSimule;
    std::vector<std::vector<bool>> etatAttendu;

    // Charger l'état simulé
    std::cout << "Chargement de l'état simulé depuis : " << fichierEtat << "\n";
    if (!chargerEtatDepuisFichier(fichierEtat, etatSimule)) {
        std::cerr << "Erreur : impossible de charger le fichier d'état simulé.\n";
        return;
    }

    // Charger l'état attendu
    std::cout << "Chargement de l'état attendu depuis : " << fichierReference << "\n";
    if (!chargerEtatDepuisFichier(fichierReference, etatAttendu)) {
        std::cerr << "Erreur : impossible de charger le fichier de référence.\n";
        return;
    }

    // Afficher les dimensions des deux fichiers
    std::cout << "Dimensions de l'état simulé : " << etatSimule.size() << " x " << etatSimule[0].size() << "\n";
    std::cout << "Dimensions de l'état attendu : " << etatAttendu.size() << " x " << etatAttendu[0].size() << "\n";

    // Vérifier les dimensions
    if (etatSimule.size() != etatAttendu.size() || etatSimule[0].size() != etatAttendu[0].size()) {
        std::cerr << "Erreur : Les dimensions des fichiers ne correspondent pas.\n";
        return;
    }

    // Comparer les deux états
    bool identique = true;
    for (size_t i = 0; i < etatSimule.size(); ++i) {
        for (size_t j = 0; j < etatSimule[i].size(); ++j) {
            if (etatSimule[i][j] != etatAttendu[i][j]) {
                std::cout << "Différence détectée à la cellule (" << i << ", " << j << ").\n";
                identique = false;
            }
        }
    }

    // Afficher le résultat de la comparaison
    if (identique) {
        std::cout << "Les états sont identiques pour l'itération choisie.\n";
    } else {
        std::cout << "Les états sont différents pour l'itération choisie.\n";
    }
}



