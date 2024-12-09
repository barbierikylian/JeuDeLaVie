#ifndef GRAPHIQUE_H
#define GRAPHIQUE_H

#include "JeuDeLaVie.h"
#include <SFML/Graphics.hpp>
#include <string>

class Graphique {
private:
    JeuDeLaVie& jeu;
    int maxIterations;
    void afficherGrille(sf::RenderWindow& fenetre, int tailleCellule);

public:
    Graphique(JeuDeLaVie& jeu, int maxIterations);
    bool chargerEtatInitial(const std::string& cheminFichier);
    void lancer();
};

#endif
