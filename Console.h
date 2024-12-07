#ifndef CONSOLE_H
#define CONSOLE_H

#include "JeuDeLaVie.h"
#include "GestionFichier.h"
#include <string>

class Console {
private:
    JeuDeLaVie& jeu; 

public:
    Console(JeuDeLaVie& jeu);
    void lancer(); 
};

#endif
