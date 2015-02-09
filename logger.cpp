#include "logger.h"

logger::logger()
{
    objednavky.open("out/objednavky.txt");
    objednavky << "# 1(prichod) 2(odchod)\n";
}

void logger::LogObjednavky(double prichod, double odchod)
{
    objednavky << prichod << "\t" << odchod << "\n";
}

