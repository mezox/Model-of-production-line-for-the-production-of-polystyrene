#include "silo.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "zariadenia.h"
#include "plnesilo.h"

Silo::Silo()
{
    _attribs = new siloAttrib[POCET_SIL];
    _active_silo_ID = -1;
}

Silo::~Silo(){
}

int Silo::getFulls(){
    int p = 0;
    for (int i = 0; i < POCET_SIL; i++)
        if (_attribs[i]._is_full)
            p++;
    return p;
}

bool Silo::getStateIsEmpty(unsigned int i) {
    return _attribs[i]._is_empty;
}

bool Silo::getStateIsFull(unsigned int i) {
    return _attribs[i]._is_full;
}

void Silo::setStateFull(unsigned int i) {
    _attribs[i]._is_full = true;
    _attribs[i]._is_empty = false;
    _attribs[i]._can_be_filled = false;
}

void Silo::setStateEmpty(unsigned int i) {
    _attribs[i]._is_empty = true;
    _attribs[i]._is_full = false;
    _attribs[i]._can_be_filled = true;
}

void Silo::setStateInUse(unsigned int i){
    _attribs[i]._in_use = true;
}

void Silo::setStateNotInUse(unsigned int i){
    _attribs[i]._in_use = false;
}

bool Silo::getStateInUse(unsigned int i){
    return _attribs[i]._in_use;
}

void Silo::setSiloCapacityTotal(double cap, unsigned int i){
    _attribs[i]._capacity_total = cap;
}

double Silo::getSiloCapacityTotal(unsigned int i){
    return _attribs[i]._capacity_total;
}

unsigned int Silo::getSiloID(unsigned int i){
    return _attribs[i]._id;
}

 void Silo::setSiloID(unsigned int id, unsigned int i){
     _attribs[i]._id = id;
}

void Silo::setCapacityUsed(double used,unsigned int i){
    _attribs[i]._capacity_used = used;
}

double Silo::getCapacityUsed(unsigned int i){
    return _attribs[i]._capacity_used;
}

void Silo::initSilo(){

    siloHandle.SetQueue(fronta_silo);

    for(unsigned int i = 0; i < POCET_SIL; i++){

            siloAttrib &attr = _attribs[i];

            attr._silo_fac = new Facility();

            attr._silo_fac->SetName("silo");

            attr._id = i;
            attr._can_be_filled = true;
            attr._capacity_total = KAPACITA_SILA;
            attr._capacity_used = 0.0;
            attr._in_use = false;
            attr._is_empty = true;
            attr._is_full = false;

            _attribs[i] = attr;
        }
    _active_silo_ID = 0;
    _attribs[_active_silo_ID]._in_use = true;
}

Facility * Silo::getSiloFacility(unsigned int i){
    return _attribs[i]._silo_fac;
}

/*string Silo::getSiloName(unsigned int i){
    return _attribs->_silo_fac->Name();
}*/


/* Najdi volne silo
 * - pokial je aktivne silo plne, vyhlada prve volne silo
 **************************************************************/
bool Silo::checkOtherSiloCap(bool set){

    unsigned int i = _active_silo_ID;

    if (!_attribs[_active_silo_ID]._is_full)
        return true;

    //ak je aktivne posledne silo, hladaj od prveho (id = 0)
    if(_active_silo_ID == (POCET_SIL - 1))
        i = 0;

    for(; i < POCET_SIL; i++){

        //hladaj silo ktore moze byt naplnene (neobsahuje neodstate gulicky),
        //nie je aktivne pouzivane a nie je plne
        if(_attribs[i]._can_be_filled && !_attribs[i]._in_use && !_attribs[i]._is_full){



            if (set) {
                _attribs[_active_silo_ID]._can_be_filled = false;
                _attribs[_active_silo_ID]._in_use = false;
                _attribs[_active_silo_ID]._is_full = true;
                _attribs[_active_silo_ID]._is_empty = false;

                printf("**naslo sa volne silo -> id:%d\n",i);

                _active_silo_ID = i;
                _attribs[_active_silo_ID]._in_use = true;
            }

            return true;
        }
    }

    return false;
}

/*
 *Pridaj do sila jednu varku z predpenovacky (3.2 m3)
 ******************************************************/
bool Silo::addToSilo(){

    //aktivne silo nie je plne
    if(_attribs[_active_silo_ID]._in_use && !_attribs[_active_silo_ID]._is_full){

        if(_attribs[_active_silo_ID]._capacity_used + KAPACITA_PREDPENOVACKY < _attribs[_active_silo_ID]._capacity_total -1){

            _attribs[_active_silo_ID]._capacity_used += KAPACITA_PREDPENOVACKY;

///            std::cout<<"                        SILO " << _attribs[_active_silo_ID]._capacity_used << std::endl;
            return true;

        }
        //po pridani aktualnej varky bude aktivne silo plne
        else {

            _attribs[_active_silo_ID]._can_be_filled = false;
            _attribs[_active_silo_ID]._in_use = false;
            _attribs[_active_silo_ID]._is_full = true;
            _attribs[_active_silo_ID]._is_empty = false;


            //pridaj varku uz do noveho sila
            _attribs[_active_silo_ID]._capacity_used += KAPACITA_PREDPENOVACKY;

///            std::cout<<"                        SILO " << _attribs[_active_silo_ID]._capacity_used << std::endl;

            //vytvor proces plne silo v ktorom bude ako prve cakanie na stabilizaciu (36h)
            (new PlneSilo(_active_silo_ID))->Activate();

            //nastav aktivne silo na dalsie prazdne
            checkOtherSiloCap(true);



            return true;
        }
    }
    else{        

        if(checkOtherSiloCap(true)){

            printf("**pridavam do najdeneho sila");
            _attribs[_active_silo_ID]._capacity_used += 3.2;

            return true;
        }
        else {
            //vsetky sila su plne
            printf("nemam kam");
            return false;
        }
    }

    return false;
}

/*
 *Vybere naplnene a odstate zrna zo sila,
 *pokracuje do formy
 ********************************************/
bool Silo::pullFromSilo(){

    /*treba zaistit aby po odobrati nenastala situacia, ze predplnovacka
     *bude chciet doplnit do sila z ktoreho odoberame, ostatne sila mozu byt plne
     *a tymto sa jedno uvolni*/

    /*if(!__in_use && !_is_empty && !_can_be_filled){
        _capacity_used -= 5.3;
    }*/

    return false;
}

unsigned int Silo::getActiveSilo() {
    return _active_silo_ID;
}

/*
 *Nastav silo na prazdne a oznac ho
 *ako aktivne silo
 ********************************************/
void Silo::setAttrib(unsigned id) {
    _attribs[id]._can_be_filled = true;
    _attribs[id]._is_full = false;
    _attribs[id]._is_empty = true;
    _attribs[id]._capacity_used = 0;

 //  _active_silo_ID = id;
}
