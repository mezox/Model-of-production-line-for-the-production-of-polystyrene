#ifndef VARKA_H
#define VARKA_H

#include <simlib.h>

class Varka : public Process
{
    double prichod_silo;
    int prichod_predpenovacka;

    public:
        Varka();

    private:
        void Behavior();
};

#endif // VARKA_H
