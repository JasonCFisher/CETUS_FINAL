

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "ghost.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;


/*********************************************************************
 ** Function: Ghost()
 ** Description: calls base class constructor, then also sets additional value
 ** Parameters: none
 ** Pre-Conditions: subclass object created
 ** Post-Conditions: subclass member variables set
 *********************************************************************/
Ghost::Ghost(): Creature(3,1, "ghost"){
    
}


/*********************************************************************
 ** Function: attack
 ** Description: Virtual function, generates random attack value.  
 ** Parameters: none
 ** Pre-Conditions: subclass object created
 ** Post-Conditions: returns int value
 *********************************************************************/
int Ghost::attack(){
    
    return rand()%20+1 + 2;

    
}


/*********************************************************************
 ** Function: getName()
 ** Description: returns name of Ghost object
 ** Parameters: none
 ** Pre-Conditions: subclass object created
 ** Post-Conditions: string name returned
 *********************************************************************/
string Ghost::getName(){
    return this->name;
}

/*********************************************************************
 ** Function: getDesc()
 ** Description: returns description
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void Ghost::getDesc(){
    if(this->isDead(0)){
        cout << "A pile of ectoplasmic goo lies at your feet." << endl;
    } else{
        cout << "A raging Ghost stares at you ready to strike!" << endl;
    }
    return;
}


