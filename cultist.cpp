

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "cultist.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;


/*********************************************************************
 ** Function: Cultist()
 ** Description: calls base class constructor, then also sets additional value
 ** Parameters: none
 ** Pre-Conditions: subclass object created
 ** Post-Conditions: subclass member variables set
 *********************************************************************/
Cultist::Cultist(): Creature(5,10, "cultist"){
    
}


/*********************************************************************
 ** Function: attack
 ** Description: Virtual function, generates random attack value.  
 ** Parameters: none
 ** Pre-Conditions: subclass object created
 ** Post-Conditions: returns int value
 *********************************************************************/
int Cultist::attack(){
    
    return rand()%20+1 + 3;

    
}


/*********************************************************************
 ** Function: getName()
 ** Description: returns name of Cultist object
 ** Parameters: none
 ** Pre-Conditions: subclass object created
 ** Post-Conditions: string name returned
 *********************************************************************/
string Cultist::getName(){
    return this->name;
}

/*********************************************************************
 ** Function: getDesc()
 ** Description: returns description
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void Cultist::getDesc(){
    if(this->isDead(0)){
        cout << "The robes appear empty, as if the bearer faded to nothing...\n";
    }else{
        cout << "A humanoid shape shrouded in a dark blue cloak and hood.  A pendant hangs around their neck." << endl;
    }
    return;
}

/*********************************************************************
 ** Function: getRoomDesc()
 ** Description: returns description
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void Cultist::getRoomDesc(){
    if(this->isDead(0)){
        cout << "A dark blue cloak lies at your feet - empty."<< endl;
    } else{
        cout << "A cultist glares in your direction!" << endl;
    }
    return;
}

void Cultist::setBurned(){
    return;
}
int Cultist::getBurned(){
    return -1;
}
