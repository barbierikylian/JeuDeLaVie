#ifndef GRAPHIQUE_H
#define GRAPHIQUE_H

#include "JeuDeLaVie.h"
#include <SFML/Graphics.hpp>
#include <string>

class Graphique {
private:
    JeuDeLaVie& jeu;

    void afficherGrille(sf::RenderWindow& fenetre, int tailleCellule);

public:
    Graphique(JeuDeLaVie& jeu);
    bool chargerEtatInitial(const std::string& cheminFichier);
    void lancer();
};

#endif
