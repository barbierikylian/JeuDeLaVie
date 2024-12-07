#include "Observable.h"
#include "Observateur.h"



void Observable::ajouterObservateur(Observateur* observateur) {
    observateurs.push_back(observateur);
}

void Observable::notifierTous() {
    for (size_t i = 0; i < observateurs.size(); i++) {
        observateurs[i]->notifier();
    }
}
