#include "varka.h"
#include "zariadenia.h"
#include "global.h"

#include <iostream>

Varka::Varka()
{    
}

void Varka::Behavior()
{
    // cas prichodu varky pred silo
    prichod_silo = Time;


    // obsad zariadenie na naplnanie sila
    if (! silo->siloHandle.Busy() )
        Seize( *silo->siloHandle );
    else {
        Into(fronta_silo);
        Passivate();
    }

    // cakaj na uvolnenie sila
    WaitUntil(silo->checkOtherSiloCap(true));

///    std::cout << "                                          VARKA: " << prichod_silo << "  MAM SILO: " << Time << std::endl;

    // zaznam o case, ako dlho varka cakala na silo
    Tabulka_silo(Time - prichod_silo);

    // nastav aktualne silo na pouzivane silo (resp. vratene silo)
    silo->setStateInUse( silo->getActiveSilo() );


    // cas prichodu varky pred predpenovacku
    prichod_predpenovacka = Time;

    // obsad predpenovacku
    if (!predpenovacka.Busy())      // ak je volna
        Seize(predpenovacka);       // obsad predpenovacku
    else {
        Into(fronta_predpenovacka); // cakaj na predpenovacku
        Passivate();
    }
    
    // procesy v predpenovacke:
    // naplnovanie, napenovanie, stabilizacia, vysypanie
    Wait(T_PREDPENOVACKA);
    
    // napln silo
    silo->addToSilo();

    //std::cout << silo->getCapacityUsed( silo->getActiveSilo() ) << std::endl;


    // uvolni predpenovacku
    Release(predpenovacka);

    // uvolni zariadenie pre naplnanie sila
    Release( *silo->siloHandle );
}
