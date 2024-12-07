#ifndef CELLULE_H
#define CELLULE_H

#include "Observable.h"

class Cellule : public Observable {
private:
    bool vivante;
    bool prochainEtat;

public:
    Cellule(bool etatInitial = false);

    void definirProchainEtat(bool etat);
    void actualiserEtat();
    bool estVivante() const;
};

#endif
