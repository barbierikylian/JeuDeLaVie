#include "Console.h"
#include "GestionFichier.h"
#include "JeuDeLaVie.h"
#include "Graphique.h"
#include <iostream>
#include <fstream>

std::string cheminFichier;

int main() {
    // Demande à l'utilisateur le chemin du fichier contenant l'état initial
    std::cout << "Entrez le chemin du fichier contenant l'état initial : ";
    std::cin >> cheminFichier;

    // Propose à l'utilisateur de choisir un mode (console ou graphique)
    std::cout << "Choisissez le mode :\n";
    std::cout << "1 pour entrer dans le Mode Console\n";
    std::cout << "2 pour entrer dans le Mode Graphique\n";

    int choix;
    std::cin >> choix;

    int lignes = 0, colonnes = 0, iterMax = 100;

    // Vérifie si les dimensions de la grille peuvent être lues depuis le fichier
    if (!lireDimensions(cheminFichier, lignes, colonnes)) {
        std::cerr << "Erreur : impossible de lire les dimensions depuis " << cheminFichier << ".\n";
        return 1;
    }

    // Mode Console
    if (choix == 1) {
        JeuDeLaVie jeu(lignes, colonnes, iterMax); // Initialise le jeu
        Console console(jeu); // Associe le jeu à l'interface console
        console.lancer(); // Lance le mode console
    } 
    // Mode Graphique
    else if (choix == 2) {
        JeuDeLaVie jeu(lignes, colonnes, iterMax); // Initialise le jeu
        Graphique graphique(jeu); // Associe le jeu à l'interface graphique

        // Charge l'état initial à partir du fichier
        if (!graphique.chargerEtatInitial(cheminFichier)) {
            std::cerr << "Erreur : impossible de charger l'état initial depuis " << cheminFichier << ".\n";
            return 1;
        }

        graphique.lancer(); // Lance le mode graphique
    } 
    // Choix invalide
    else {
        std::cerr << "Choix invalide.\n";
    }

    return 0;
}
