#include <string>
#include "CETUS_Items.hpp"

using std::string;

Item::Item(){
	
	this->Name = "";
	this->Description = "";
	this->Power = 0;
	this->Healing = 0;
	this->weapon = false;
	this->roomFeature = false;
	this->collectible = false;
	return;	
		
}

Item::Item(string newName, string newDesc, int newPower, int newHealing, bool newWeapon, bool feature, bool collect){
	
	this->Name = newName;
	this->Description = newDesc;
	this->Power = newPower;
	this->Healing = newHealing;
	this->weapon = newWeapon;
	this->roomFeature = feature;
	this->collectible = collect;
	return;	
	
}


string Item::getName(){
	
	return this->Name;
	
}

string Item::getDescription(){
	
    return this->Description;
	
}

int Item::getPower(){
	
	return this->Power;	
	
}

int Item::getHealing(){
	
	return this->Healing;
	
}

bool Item::getWeapon(){
	
	return this->weapon;
	
}

bool Item::getRoomFeature(){
	
	return this->roomFeature;
	
	
}

bool Item::getCollectible(){
	
	return this->collectible;	
	
}

int Item::damageItem(int damage){
	
	this->Power -= damage;
	if (this->Power < 0){
		
		this->Power = 0; 
		
	}
    return 0;
}
