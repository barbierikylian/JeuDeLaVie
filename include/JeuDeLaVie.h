#ifndef JEUDELAVIE_H
#define JEUDELAVIE_H

#include "Grille.h"
#include <string>

class JeuDeLaVie  {
private:
    Grille grille;
    int iterationsMax;

public:
    JeuDeLaVie(int nbLignes, int nbColonnes, int iterMax);
    ~JeuDeLaVie();

    bool EtatInitial(const std::string& cheminFichier);
    void executer();
    void afficher();
    void sauvegarderEtat(const std::string& cheminFichier, int iteration); // Nouvelle méthode
    Grille& getGrille();
    bool chargerEtatDepuisFichier(const std::string& cheminFichier, std::vector<std::vector<bool>>& etatGrille);
    void testerEtatAvecFichier(const std::string& fichierEtat, const std::string& fichierReference); 
};

#endif
