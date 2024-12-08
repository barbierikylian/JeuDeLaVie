#include "Console.h"
#include "GestionFichier.h"

#include "JeuDeLaVie.h"
#include <iostream>
#include "Graphique.h"
#include <fstream>



int main() {

    std::string cheminFichier;
    std::cout << "Entrez le chemin du fichier contenant l'état initial : ";
    std::cin >> cheminFichier;
    
    std::cout << "Choisissez le mode :\n";
    std::cout << "1. Mode Console\n";
    std::cout << "2. Mode Graphique\n";

    int choix;
    std::cin >> choix; 

    int lignes = 0, colonnes = 0, iterMax = 100;

    if (!lireDimensions(cheminFichier, lignes, colonnes)) {
        std::cerr << "Erreur : impossible de lire les dimensions depuis " << cheminFichier << ".\n";
        return 1;
    }

    if (choix == 1) {
        JeuDeLaVie jeu(lignes, colonnes, iterMax);
        Console console(jeu);
        console.lancer();
    } else if (choix == 2) {
        JeuDeLaVie jeu(lignes, colonnes, iterMax);
        Graphique graphique(jeu);

        if (!graphique.chargerEtatInitial(cheminFichier)) {
            std::cerr << "Erreur : impossible de charger l'état initial depuis " << cheminFichier << ".\n";
            return 1;
        }

        graphique.lancer();
    } else {
        std::cerr << "Choix invalide.\n";
    }

    return 0;
}
