#include "Console.h"
#include <iostream>
#include <fstream>



// Constructeur
Console::Console(JeuDeLaVie& jeu) : jeu(jeu) {}

// Méthode pour lancer le mode console
void Console::lancer() {
    std::string cheminFichier = "etat_initial.txt"; 

    int lignes, colonnes;
    if (!lireDimensions(cheminFichier, lignes, colonnes)) {
        return; 
    }

    int iterMax;
    std::cout << "Entrez le nombre d'itérations maximales : ";
    std::cin >> iterMax;

    if (iterMax <= 0) {
        std::cerr << "Erreur : le nombre d'itérations doit être supérieur à 0.\n";
        return;
    }

    // Reconfigurer JeuDeLaVie avec les nouvelles dimensions et itérations
    JeuDeLaVie nouveauJeu(lignes, colonnes, iterMax);
    jeu = nouveauJeu;

    if (!jeu.EtatInitial(cheminFichier)) {
        std::cerr << "Erreur : impossible de charger l'état initial.\n";
        return;
    }

    std::cout << "Grille initiale :\n";
    jeu.afficher();

    jeu.executer();
}
