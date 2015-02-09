#include <iostream>
#include <simlib.h>
#include "objednavka.h"
#include "silo.h"
#include "sklad.h"
#include <time.h>

#include "output.h"
#include "logger.h"
#include <fstream>


/** ********** GLOBALNE PREMENNE *************** **
 ** ******************************************** **/
// OBJEDNAVKY
Facility spracovanie_objednavky;
Queue fronta_objednavok("Objednavky na spracovanie");

Facility dokoncenie_objednavky;
Queue fronta_objednavok2("Cakajuce objednavky");
Histogram Tabulka_objednavok2("Cakacie doby na dokoncenie objednavky",24*6,5.0,100);

// PREDPENOVACKA
Facility predpenovacka;
Queue fronta_predpenovacka("Varky pred predpenovackou");

// SILO
Silo *silo = new Silo();
Queue fronta_silo("Varky pred silom");
Histogram Tabulka_silo("Varky pred silom",0,1.0,10);

// FORMA
Facility forma;
Queue fronta_forma("Varky pred formou");

// REZACKA
Facility rezacka;
Queue fronta_rezacka("Varky pred rezackou");

Output *o = new Output();

double pocet_objednanych = 0;
double pocet_na_vyrobu   = 0;

double pocet_bloky_skladom = 0;
double pocet_bloky_ready   = 0;
double pocet_hotovych      = 0;

int cislo_objednavky = 1;


/** ********** GENERATOR OBJEDNAVOK ************ **
 ** ******************************************** **/
class Generator : public Event
{
    void Behavior() {

        // nova objednavka
        (new Objednavka( cislo_objednavky, random() % 150 + 50, random() % 3 + 1 ))->Activate();

        cislo_objednavky++;

        // generuj novu objednavku o ..
        Activate(Time + Exponential(4.0));
    }
};


/** ****************** MAIN ******************** **
 ** ******************************************** **/
int main()
{
    Init(T_POC, T_KON); // zaciatok a koniec simulacie
    srand(time(NULL));  // semienko nahodnosti


    // NASTAVENIE ZARIADENI
    spracovanie_objednavky.Clear();
    spracovanie_objednavky.SetName("Spracovanie objednavky");
    spracovanie_objednavky.SetQueue(fronta_objednavok);
    dokoncenie_objednavky.Clear();
    dokoncenie_objednavky.SetName("Dokoncenie objednavok");
    dokoncenie_objednavky.SetQueue(fronta_objednavok2);

    predpenovacka.Clear();
    predpenovacka.SetName("Predpenovacka");
    predpenovacka.SetQueue(fronta_predpenovacka);

    silo->initSilo();

    forma.Clear();
    forma.SetName("Forma");
    forma.SetQueue(fronta_forma);

    rezacka.Clear();
    rezacka.SetName("Rezacka");
    rezacka.SetQueue(fronta_rezacka);


    // NASTAVENIE HISTOGRAMOV
    Tabulka_objednavok2.Clear();
    Tabulka_silo.Clear();


    /* ------------------- *
     * SPUSTENIE SIMULACIE *
     * --------------------*/
    std::cout << " -- SIMULACIA VYROBY POLYSTYRENU --" << std::endl;

    // spustenie generatora objednavok
    (new Generator)->Activate();

    o->Activate();

    Run();
    /* ------------------- *
     *  KONIEC SIMULACIE   *
     * --------------------*/


    // VYSLEDKY SIMULACIE:

//    SetOutput("out/aa.txt");

    // doby cakania objednavky vo fronte na dokoncenie
    fronta_objednavok2.Output();

    // doby cakania objednavok na ich dokoncenie
    Tabulka_objednavok2.Output();

    // doby cakania variek na silo
    Tabulka_silo.Output();

    fronta_silo.Output();

    // doby cakania vo fronte pred predpenovackou
    fronta_predpenovacka.Output();

    // doby cakania vo fronte pred formou
    fronta_forma.Output();

    // doby cakania vo fronte pred rezackou
    fronta_rezacka.Output();


    return 0;
}

