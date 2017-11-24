
#ifndef cultist_creature
#define cultist_creature

#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "creature.hpp"


class Cultist: public Creature{
private:
	
    
public:
    Cultist();
    int attack();
    string getName();
    void getDesc();
    void getRoomDesc();
};

#endif 
