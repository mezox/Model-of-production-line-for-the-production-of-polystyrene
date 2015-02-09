#include <iostream>
#include <simlib.h>
#include "global.h"
#include <string>

#ifndef Silo_H
#define Silo_H

class siloAttrib {

    public:
        Facility * _silo_fac;

        unsigned int _id;
        double _capacity_total;
        double _capacity_used;
        bool _in_use;
        bool _is_empty;
        bool _is_full;
        bool _can_be_filled;
};

class Silo
{
    public:
        Silo();
        ~Silo();

        void initSilo();

        int getFulls();

        //sets / gets state of current silo
        void setStateFull(unsigned int i);
        void setStateEmpty(unsigned int i);
        void setStateInUse(unsigned int i);
        void setStateNotInUse(unsigned int i);
        bool getStateIsFull(unsigned int i);
        bool getStateIsEmpty(unsigned int i);
        bool getStateInUse(unsigned int i);

        void setSiloCapacityTotal(double cap,unsigned int i);
        double getSiloCapacityTotal(unsigned int i);
        unsigned int getSiloID(unsigned int i);
        void setSiloID(unsigned int id,unsigned int i);

        void setCapacityUsed(double used,unsigned int i);
        double getCapacityUsed(unsigned int i);

        //string getSiloName(unsigned int i);

        bool checkOtherSiloCap(bool set);
        bool addToSilo();
        bool pullFromSilo();
        unsigned int getActiveSilo();

        Facility * getSiloFacility(unsigned int i);
        Facility siloHandle;

        void setAttrib(unsigned id);

    private:
        siloAttrib * _attribs;
        unsigned int _active_silo_ID;

};

#endif // Silo_H
