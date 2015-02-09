#ifndef GLOBAL_H
#define GLOBAL_H

#define T_POC                   8.0
#define T_KON                   24.0*30

// kapacity v m3
#define POCET_SIL               10
#define KAPACITA_SILA           169.6
#define KAPACITA_PREDPENOVACKY  3.2
#define POCET_VAROK_NA_SILO     KAPACITA_SILA/KAPACITA_PREDPENOVACKY
#define KAPACITA_FORMY          5.3
#define KAPACITA_SKLAD_BLOKOV   3200
#define KAPACITA_SKLAD_HOTOVYCH 2300

// casy vyroby
#define T_PREDPENOVACKA         1.0/60/60*101       // 101 sekund
#define T_ZOTRVANIE_V_SILE      36.0                // 36 hodin
//#define T_FORMA                 1.0/60/60*380       // 380 sekund
#define T_FORMA                 1.0/60/60*260       // 260 sekund
#define T_SKLAD                 5.0*24              // 5 dni
#define T_REZACKA               3.0/60              // 3 minuty


// m3
extern double pocet_objednanych;
extern double pocet_na_vyrobu;

// sklady
extern double pocet_bloky_skladom;
extern double pocet_bloky_ready;
extern double pocet_hotovych;


#endif // GLOBAL_H
