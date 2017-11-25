
#ifndef cetus_creature
#define cetus_creature

#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "creature.hpp"


class Cetus: public Creature{
private:
    int burned;
    
public:
    Cetus();
    int attack();
    string getName();
    void getDesc();
    void getRoomDesc();
    void setBurned();
    int getBurned();
};

#endif 
