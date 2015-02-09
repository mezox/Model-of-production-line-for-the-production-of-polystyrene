#ifndef BLOK_H
#define BLOK_H

#include <simlib.h>

class Blok : public Process
{
    int prichod_rezacka;

    public:
        Blok();

    private:
        void Behavior();
};

#endif // BLOK_H
