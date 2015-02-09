#ifndef ZARIADENIA_H
#define ZARIADENIA_H

#include "silo.h"
//#include "logger.h"
#include "output.h"

// OBJEDNAVKY
extern Facility spracovanie_objednavky;
extern Queue fronta_objednavok;

extern Facility dokoncenie_objednavky;
extern Queue fronta_objednavok2;
extern Histogram Tabulka_objednavok2;

// PREDPENOVACKA
extern Facility predpenovacka;
extern Queue fronta_predpenovacka;

// SILO
extern Silo *silo;
extern Queue fronta_silo;
extern Histogram Tabulka_silo;

// FORMA
extern Facility forma;
extern Queue fronta_forma;

// REZACKA
extern Facility rezacka;
extern Queue fronta_rezacka;

//extern logger *log;
extern Output *o;

#endif // ZARIADENIA_H
