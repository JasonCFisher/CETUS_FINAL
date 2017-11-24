
#ifndef merman_creature
#define merman_creature

#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "creature.hpp"


class Merman: public Creature{
private:
	
    
public:
    Merman();
    int attack();
    string getName();
    void getDesc();
    void getRoomDesc();
};

#endif 
