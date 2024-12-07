#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <vector>

class Observateur;

class Observable {
private:
    std::vector<Observateur *> observateurs;

public:
    void ajouterObservateur(Observateur* observateur);
    void notifierTous();
    virtual ~Observable() {}
};

#endif
