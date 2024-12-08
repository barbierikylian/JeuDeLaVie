#include "Console.h"
#include "GestionFichier.h"
#include "JeuDeLaVie.h"
#include "Graphique.h"
#include <iostream>
#include <fstream>
#include <filesystem> // Pour manipuler les chemins de fichiers

std::string cheminFichier;

int main() {
    // Demande à l'utilisateur le chemin du fichier contenant l'état initial
    std::cout << "Entrez le chemin du fichier contenant l'état initial : ";
    std::cin >> cheminFichier;

    // Vérifie si les dimensions de la grille peuvent être lues depuis le fichier
    int lignes = 0, colonnes = 0;

    if (!lireDimensions(cheminFichier, lignes, colonnes)) {
        std::cerr << "Erreur : impossible de lire les dimensions depuis " << cheminFichier << ".\n";
        return 1;
    }

    // Propose à l'utilisateur de choisir un mode
    std::cout << "Choisissez le mode :\n";
    std::cout << "1 pour le Mode Console\n";
    std::cout << "2 pour le Mode Graphique\n";

    int choix;
    std::cin >> choix;

    // Mode Console
    if (choix == 1) {
        // Demande le nombre d'itérations maximum
        int iterMax;
        std::cout << "Entrez le nombre maximum d'itérations : ";
        std::cin >> iterMax;

        if (iterMax <= 0) {
            std::cerr << "Erreur : le nombre d'itérations doit être supérieur à 0.\n";
            return 1;
        }

        // Crée une instance du jeu en mode console
        JeuDeLaVie jeu(lignes, colonnes, iterMax);

        // Charge l'état initial
        if (!jeu.EtatInitial(cheminFichier)) {
            std::cerr << "Erreur : impossible de charger l'état initial.\n";
            return 1;
        }

        // Lance l'exécution en mode console
        std::cout << "Simulation en mode console pour " << iterMax << " itérations maximum.\n";
        jeu.executer(); // Exécute le jeu et génère les fichiers de sortie
        std::cout << "Simulation terminée après " << iterMax << " itérations ou stabilisation.\n";

        // Comparaison facultative
        std::cout << "Voulez-vous comparer une itération spécifique avec un fichier de référence ? (1 = Oui, 0 = Non) : ";
        int comparer;
        std::cin >> comparer;

        if (comparer == 1) {
            std::string fichierReference;
            int iteration;

            // Demande l'itération à comparer
            std::cout << "Entrez le numéro de l'itération à comparer (entre 0 et " << iterMax  << ") : ";
            std::cin >> iteration;

            if (iteration < 0 || iteration >= iterMax + 1) {
                std::cerr << "Erreur : numéro d'itération invalide. Il doit être entre 0 et " << iterMax << ".\n";
                return 1;
            }

            // Demande le chemin du fichier de référence
            std::cout << "Entrez le chemin du fichier de référence : ";
            std::cin >> fichierReference;

            // Génère le chemin correct pour le fichier d'état simulé
            std::filesystem::path cheminInitial(cheminFichier);
            std::string dossierEtats = "etat_iterations.txt_out/"; // Nom fixe pour le dossier d'états
            std::string fichierEtat = dossierEtats + "etat_" + std::to_string(iteration) + ".txt";


            // Effectue la comparaison
            jeu.testerEtatAvecFichier(fichierEtat, fichierReference);
        }
    }
    // Mode Graphique
    else if (choix == 2) {
        // Crée une instance du jeu en mode graphique
        int iterMax = 100; // Une valeur par défaut pour le mode graphique
        JeuDeLaVie jeu(lignes, colonnes, iterMax);
        Graphique graphique(jeu);

        // Charge l'état initial
        if (!graphique.chargerEtatInitial(cheminFichier)) {
            std::cerr << "Erreur : impossible de charger l'état initial pour le mode graphique.\n";
            return 1;
        }

        // Lance l'exécution en mode graphique
        graphique.lancer();
    }
    // Choix invalide
    else {
        std::cerr << "Choix invalide.\n";
        return 1;
    }

    return 0;
}
