#ifndef OUTPUT_H
#define OUTPUT_H

#include <simlib.h>
#include <fstream>


class Output : public Event
{
    std::ofstream f;
    std::ofstream sklad;
    std::ofstream objednavky;
    std::ofstream plotfile;

    public:
        Output();
        void CloseAll();
        void LogObjednavka(double prichod, double odchod);
        void LogObjednavka2(double prichod);

    private:
        void Behavior();
};

#endif // OUTPUT_H
