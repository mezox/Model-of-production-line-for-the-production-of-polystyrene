#ifndef LOGGER_H
#define LOGGER_H

#include <simlib.h>
#include <fstream>
#include "zariadenia.h"

class logger
{
    std::ofstream objednavky;

    public:
        logger();
        void LogObjednavky(double prichod, double odchod);
};

#endif // LOGGER_H
