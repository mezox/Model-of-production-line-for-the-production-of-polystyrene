#ifndef OBJEDNAVKA_H
#define OBJEDNAVKA_H

#include <simlib.h>
#include <fstream>


class Objednavka : public Process
{
    int _cislo_objednavky;
    double pocet;
    double prichod;


    public:
        Objednavka(int cislo_objednavky, int random_pocet, int random_priorita);

    private:
        void Behavior();

};

#endif // OBJEDNAVKA_H
