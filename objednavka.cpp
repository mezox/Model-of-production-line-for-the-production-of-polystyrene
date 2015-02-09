#include "objednavka.h"
#include "varka.h"
#include "global.h"
#include "zariadenia.h"
#include <iostream>
#include <math.h>

Objednavka::Objednavka(int cislo_objednavky, int random_pocet, int random_priorita)
{
    _cislo_objednavky = cislo_objednavky;
    pocet = random_pocet;
    Priority = random_priorita;
}

void Objednavka::Behavior()
{
    prichod = Time;
    double d;
    int w;

    // ak objednavka prisla v noci, spracovanie zacne az rano
    if ( !((int)Time % 24 >= 8 && (int)ceil(Time) % 24 <= 18) ) {

        d = (int) prichod % 24;
        if (d >= 18)
            w = 24 - d + 8;
        else
            w = 8 - d;

        std::cout << " NOC  obj. c." << _cislo_objednavky << " cas " << Time <<std::endl;

        Wait((double) w - (prichod - floor(prichod)) );

        std::cout << " DEN  obj. c." << _cislo_objednavky << " cas " << Time << std::endl;
    }


    // obsad 'zariadenie' spracovavanie objednavky
    if (!spracovanie_objednavky.Busy())
        Seize(spracovanie_objednavky);
    else {
        Into(fronta_objednavok);
        Passivate();
    }

    // doba spracovania objednavky zamestnancom
    double sprac_zam = Normal(5.0/60, 1.0/60);
    Wait( sprac_zam );

    // premenna pocet2 sa bude menit, premennu pocet ponechame
    double pocet2 = pocet;

    // zisti zostatok po predoslych objednavkach a privlastni si ho
    if (pocet_na_vyrobu - pocet_objednanych > 0)
        pocet2 -= pocet_na_vyrobu - pocet_objednanych;

    if (pocet2 < 0)
        pocet2 = 0;

    std::cout <<
         "---------------------------------------------------- \n" <<
         "Objednavka c." << _cislo_objednavky << "  Priorita = " << (int)Priority << "\n" <<
         "  Prichod objednavky v case:    " << prichod << " (" << (int)prichod % 24 << "h)\n" <<
         "  Spracovanie objednvky v case: " << Time << " (" << (int)Time % 24 << "h)\n" <<
         "  Cas spracovania zamestnancom: " << sprac_zam * 60 << " minut\n" <<

         "  Pocet objednavanych (m3):     " << pocet << "\n" <<
         "  Zostatok z pred. objed. (m3): " << pocet_na_vyrobu - pocet_objednanych << "\n" <<
         "  Pocet na vyrobu (m3):         " << pocet2 << "\n";


    // vypocitaj pocet varok na vyrobu (vzdy min. na plne silo (53 varok) )
    double pocet_varok = 0;

    while ((pocet2 / KAPACITA_SILA) > 0) {
        pocet_varok += POCET_VAROK_NA_SILO;
        pocet2 -= KAPACITA_SILA;
    }

    // pripocitaj pocet objednanych m3 k celkovemu poctu objednanych m3
    pocet_objednanych += pocet;
    // pripocitaj pocet m3 na vyrobu k celkovu poctu m3 vydanych do vyroby
    pocet_na_vyrobu   += pocet_varok * KAPACITA_PREDPENOVACKY;


    std::cout << "\n" <<
         "  pocet objednanych celkom (m3): " << pocet_objednanych << std::endl <<
         "  pocet na vyrobu celkom (m3):   " << pocet_na_vyrobu << std::endl <<
         "  zostatok z tejto objed. (m3):  " << pocet_na_vyrobu - pocet_objednanych << std::endl <<
         "  potrebny pocet varok:          " << pocet_varok << std::endl <<
         "----------------------------------------------------" << std::endl;


    // vyrob potrebny pocet varok
    for (int i = 0; i < pocet_varok; i++ )
        (new Varka())->Activate();

    // uvolni spracovanie pre dalsiu objednavku
    Release(spracovanie_objednavky);


    // Obsad 'zariadenie' dokoncenie objednavky.
    // Objednavky s vyssou prioritou sa predbehnu
    if (!dokoncenie_objednavky.Busy())
        Seize(dokoncenie_objednavky);
    else {
        Into(fronta_objednavok2);
        Passivate();
    }

    // Objednavka tu caka na svoje objednane m3, ktore sa
    // maju objavit na sklade hotovych vyrobkov. Potom si ich vezme
    WaitUntil( pocet < pocet_hotovych );
    pocet_hotovych -= pocet;

    o->LogObjednavka(_cislo_objednavky, Time-prichod);
    std::cout << "--------- OBJEDNAVKA c." << _cislo_objednavky << " DOKONCENA --------\n";

    // zaznam o case, ako dlho objednavka cakala na dokoncenie
    Tabulka_objednavok2(Time - prichod);

    // uvolni dokoncenie objednavky pre dalsiu objednavku
    Release(dokoncenie_objednavky);
}
