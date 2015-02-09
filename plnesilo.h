#ifndef PLNESILO_H
#define PLNESILO_H

#include <simlib.h>

class PlneSilo : public Process
{
    unsigned int _id;
    int prichod_forma;
    double _capacity_used;

    public:
        PlneSilo(unsigned int id);

    private:
        void Behavior();
};

#endif // PLNESILO_H
