
#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>
#include "creature.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;

/*********************************************************************
 ** Function: Creature()
 ** Description: constructor for base and all subclasses
 ** Parameters: ints for all values and a string for the name
 ** Pre-Conditions: subclass object created
 ** Post-Conditions: subclass member variables set
 *********************************************************************/

Creature::Creature(int arm, int str, string word){
    
    this->armor = arm;
    this->health = str;
    this->name = word;
    
}

/*********************************************************************
 ** Function: ~Creature
 ** Description: virtual Destructor
 ** Parameters: N/A
 ** Pre-Conditions: None
 ** Post-Conditions: Object destroyed
 *********************************************************************/
Creature::~Creature(){
    
}


/*********************************************************************
 ** Function: attack
 ** Description: Virtual function, generates random attack value.  
 **              
 ** Parameters: None
 ** Pre-Conditions: subclass object created
 ** Post-Conditions: returns int value
 *********************************************************************/
int Creature::attack(){
    
    return rand()%20+1;
    
}

/*********************************************************************
 ** Function: defense
 ** Description: Virtual function, if attack higher than armor, loses 1 HP
 ** Parameters: int value (opposing creatures attack roll)
 ** Pre-Conditions: opponent made attack
 ** Post-Conditions: creature obtains damage or dodges
 *********************************************************************/
void Creature::defense(int incoming){
        
    
    //If damage is 0 or less, creature "dodged"
    if(incoming < armor){
        cout << this->name << " dodged the attack!"<< endl;
        return;
    }
    
    //If not dodged, apply damage to creature
    cout << this->name << " took damage!" << endl;
    this->health -= 1;
    return;
    
}

/*********************************************************************
 ** Function: isDead()
 ** Description: Virtual function, determines if creatures has 0 or less str
 ** Parameters: none
 ** Pre-Conditions: None
 ** Post-Conditions: returns bool value of true if dead
 *********************************************************************/
bool Creature::isDead(int check = 1){
    
    //Checks if creature is dead.  Shows total health left
    if(check != 0){
        cout << this->name << " : " << this->health << " life." << endl;
    }
    if(this->health <= 0){
        return true;
    } else{
        return false;
    }
}

/*********************************************************************
 ** Function: adjName
 ** Description: Virtual function, adds to name, used when two same creatures
 **              fight
 ** Parameters: string value to add to name
 ** Pre-Conditions: None
 ** Post-Conditions: creature name altered
 *********************************************************************/
void Creature::adjName(string add){
    this->name = add;
}

/*********************************************************************
 ** Function: Overloaded == function
 ** Description: compares two creature types
 ** Parameters: two creature addresses
 ** Pre-Conditions: two creature objects created
 ** Post-Conditions: returns true or false
 *********************************************************************/
bool operator==(Creature& left, Creature& right){
    
    return (left.name == right.name);
}

/*********************************************************************
 ** Function: healme
 ** Description: adds to health
 ** Parameters: integer val
 ** Pre-Conditions: none
 ** Post-Conditions: health increased
 *********************************************************************/
void Creature::healme(int val){
    this->health += val;
}

/*********************************************************************
 ** Function: getHP
 ** Description: returns value of health
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
int Creature::getHP(){
    return health;
}
