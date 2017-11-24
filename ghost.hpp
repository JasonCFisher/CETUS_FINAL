
#ifndef Ghost_creature
#define Ghost_creature

#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "creature.hpp"


class Ghost: public Creature{
private:
	
    
public:
    Ghost();
    int attack();
    string getName();
    void getDesc();
    
};

#endif 
