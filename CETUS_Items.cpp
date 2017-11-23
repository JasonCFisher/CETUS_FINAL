#include <string>
#include "CETUS_Items.hpp"

using std::string;

Item::Item(){
	
	this->Name = ' ';
	this->Description = ' ';
	this->roomDescription = ' ';
	this->Power = 0;
	this->Healing = 0;
	this->weapon = false;
	this->roomFeature = false;
	this->collectible = false;
	return;	
		
}

Item::Item(string newID, string newName, string newDesc, string roomDesc, int newPower, int newHealing, bool newWeapon, bool feature, bool collect){
	
	this->ID = newID;
	this->Name = newName;
	this->Description = newDesc;
	this->roomDescription = roomDesc;
	this->Power = newPower;
	this->Healing = newHealing;
	this->weapon = newWeapon;
	this->roomFeature = feature;
	this->collectible = collect;
	return;	
	
}


string Item::getID(){
	return this->ID;
}


string Item::getName(){
	
	return this->Name;
	
}

string Item::getDescription(){
	
	return this->Description;
	
}

string Item::getRoomDescription(){
	
	return this->roomDescription;
	
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

void Item::damageItem(int damage){
	
	this->Power -= damage;
	if (this->Power < 0){
		
		this->Power = 0; 
		
	}
	
}

void Item::setName(string current){
	
	this->Name = current;
	return;
	
}
void Item::setDescription(string current){
	
	this->Description = current;
	return;
	
}
void Item::setRoomDescription(string current){
	
	this->roomDescription = current;
	return;
	
}
void Item::setPower(int current){
	
	this->Power = current;
	return;
	
}
void Item::setHealing(int current){
	
	this->Healing = current;
	return;
	
}
void Item::setWeapon(bool current){
	
	this->weapon = current;
	return;
	
}
void Item::setRoomFeature(bool current){
	
	this->roomFeature = current;
	return;
	
}
void Item::setCollectible(bool current){
	
	this->collectible = current;
	return;
	
}
