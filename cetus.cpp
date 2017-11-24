

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "cetus.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;


/*********************************************************************
 ** Function: Cetus()
 ** Description: calls base class constructor, then also sets additional value
 ** Parameters: none
 ** Pre-Conditions: subclass object created
 ** Post-Conditions: subclass member variables set
 *********************************************************************/
Cetus::Cetus(): Creature(5,1, "cetus"){
    
}


/*********************************************************************
 ** Function: attack
 ** Description: Virtual function, generates random attack value.  
 ** Parameters: none
 ** Pre-Conditions: subclass object created
 ** Post-Conditions: returns int value
 *********************************************************************/
int Cetus::attack(){
    
    return rand()%20+1 + 3;

    
}


/*********************************************************************
 ** Function: getName()
 ** Description: returns name of Cetus object
 ** Parameters: none
 ** Pre-Conditions: subclass object created
 ** Post-Conditions: string name returned
 *********************************************************************/
string Cetus::getName(){
    return this->name;
}

/*********************************************************************
 ** Function: getDesc()
 ** Description: returns description
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void Cetus::getDesc(){
    if(this->isDead(0)){
        cout << "No trace of the monster exists."<< endl;
    } else{
        cout << "This beast towers over you.  Tentacles emerge from its face, its big toothy maw grinding and snarling.  Spines and scales cover its body.  Quite a nasty piece of work." << endl;
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
void Cetus::getRoomDesc(){
    if(this->isDead(0)){
        cout << "No trace of the monster is found."<< endl;
    } else{
        cout << "A mythical sea beast with tentacles towers over you, making horrid noises." << endl;
    }
    return;
}


