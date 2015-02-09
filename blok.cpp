#include "blok.h"
#include "global.h"
#include "zariadenia.h"

Blok::Blok()
{
}

void Blok::Behavior()
{
///    std::cout << "PROCES: NOVY BLOK" << std::endl;

    // pridaj blok na sklad blokov
    pocet_bloky_skladom += KAPACITA_FORMY;

    // stabilizacia polystyrenoveho bloku v sklade blokov
    if (fronta_objednavok2.size() > 5)
        // ked je vela objednavok tak ciastocne zanedbavame stabilizaciu
        // 1 az 3 hodiny krat 1 az 24 hodin dna (min 1h, max 3dni)
        Wait(T_SKLAD - (random() % 3 + 1) * (random() % 24 + 1));
    else
        Wait(T_SKLAD);

    // cas prichodu bloku pred rezacku - blok je stabilizovany
    prichod_rezacka = Time;

    // logicky (nie fyzicky) presun bloku na sklad odlezanych blokov
    pocet_bloky_skladom -= KAPACITA_FORMY;
    pocet_bloky_ready   += KAPACITA_FORMY;

    // zisti kapacitu skladu hotovych vyrobkov, ak je plny cakaj
    WaitUntil(pocet_hotovych < KAPACITA_SKLAD_HOTOVYCH);

    // obsad rezacku
    if (!rezacka.Busy())      // ak je volna
        Seize(rezacka);       // obsad rezacku
    else {
        Into(fronta_rezacka); // cakaj na rezacku
        Passivate();
    }

    // presun blok do rezacky
    pocet_bloky_ready -= KAPACITA_FORMY;

    // procesy v rezacke:
    // rezanie pozdlzne, rezanie priecne
    Wait(T_REZACKA);

    // presun narezany blok na sklad hotovych vyrobkov
    pocet_hotovych    += KAPACITA_FORMY;

    // uvolni rezacku pre dalsi blok
    Release(rezacka);
}
