#include "plnesilo.h"
#include "global.h"
#include "zariadenia.h"
#include "blok.h"
#include "iostream"

PlneSilo::PlneSilo(unsigned int id)
{
    _id = id;
    _capacity_used = KAPACITA_SILA;
}

void PlneSilo::Behavior()
{
    std::cout << "                               PROCES: PLNE SILO" << _id << " NE stabilizovane " << Time << std::endl;

    // stabilizacia polystyrenu v sile
    Wait(T_ZOTRVANIE_V_SILE);

    // cas prichodu sila pred formu
    prichod_forma = Time;

    std::cout << "                               PROCES: PLNE SILO " << _id << " stabilizovane " << Time << std::endl;

    // obsad formu
    if (!forma.Busy())          // ak je volna
        Seize(forma);           // obsad formu
    else {
        Into(fronta_forma);     // cakaj na formu
        Passivate();
    }

    // pocet vyrobenych blokov
    int pocet_blokov = 0;

    // vyprazdnuj silo => naplnaj formu
    while (_capacity_used - KAPACITA_FORMY >= 0) {

        // zisti ci nie je plna kapacita skladu, ak je tak cakaj
        WaitUntil(pocet_bloky_skladom + pocet_bloky_ready < KAPACITA_SKLAD_BLOKOV);

        // procesy vo forme:
        // zatvaranie, naplnanie, cistenie,
        // naparovanie, stabilizacia, otvorenie + vysunutie
        Wait(T_FORMA);

        // napln formu (vyprazdni cast sila)
        _capacity_used -= KAPACITA_FORMY;

        // vytvor novy blok, ktory bude pridany na sklad blokov
        (new Blok)->Activate();
        pocet_blokov++;
    }

    // oznac silo ako prazdne
    silo->setAttrib(_id);

    std::cout << "VRACIAM SILO c." << _id << "  Pocet vyrobenych blokov: " << pocet_blokov << std::endl;

    // uvolni formu pre dalsie silo
    Release(forma);
}
