

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "merman.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;


/*********************************************************************
 ** Function: Merman()
 ** Description: calls base class constructor, then also sets additional value
 ** Parameters: none
 ** Pre-Conditions: subclass object created
 ** Post-Conditions: subclass member variables set
 *********************************************************************/
Merman::Merman(): Creature(10,10, "merman"){
    
}


/*********************************************************************
 ** Function: attack
 ** Description: Virtual function, generates random attack value.  
 ** Parameters: none
 ** Pre-Conditions: subclass object created
 ** Post-Conditions: returns int value
 *********************************************************************/
int Merman::attack(){
    
    return rand()%20+1 + 3;

    
}


/*********************************************************************
 ** Function: getName()
 ** Description: returns name of Merman object
 ** Parameters: none
 ** Pre-Conditions: subclass object created
 ** Post-Conditions: string name returned
 *********************************************************************/
string Merman::getName(){
    return this->name;
}

/*********************************************************************
 ** Function: getDesc()
 ** Description: returns description
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void Merman::getDesc(){
    if(this->isDead(0)){
        cout << "Other than stagnant water, you see no sign of the creature."<< endl;
    } else{
        cout << "A man from the waist up, serpent otherwise.  Red eyes, and nasty claws." << endl;
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
void Merman::getRoomDesc(){
    if(this->isDead(0)){
        cout << "A puddle of water sits stagnant on the ground."<< endl;
    } else{
        cout << "A Merman stares at you, hissing, with claws out!" << endl;
    }
    return;
}

void Merman::setBurned(){
    return;
}
int Merman::getBurned(){
    return -1;
}
