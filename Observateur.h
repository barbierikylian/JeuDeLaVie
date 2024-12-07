#ifndef OBSERVATEUR_H
#define OBSERVATEUR_H

class Observateur {
public:
    virtual void notifier() = 0;
    virtual ~Observateur() {}
};

#endif
