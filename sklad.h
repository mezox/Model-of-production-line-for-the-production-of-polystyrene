#ifndef SKLAD_H
#define SKLAD_H

#include <vector>
#include "blok.h"

class Sklad {
    public:
        Sklad();
        ~Sklad();
        std::vector<Blok> sklad_forma;
        std::vector<Blok> sklad_hotove;

    private:

};

#endif // SKLAD_H
