#include <string>
//#include "CETUS_Room.hpp"
//#include "CETUS_World.hpp"

#ifndef CETUS_ITEM_HPP
#define CETUS_ITEM_HPP
using std::string;
class Item {
	
	private:
	
    string	Name;
    string	Description;
		int		Power;
		int		Healing;
		bool	weapon;
		bool	roomFeature;
		bool	collectible;
		
	public:
	
		Item();
		Item(string Name, string Description, int Power, int Healing, bool newWeapon, bool feature, bool collect);
		~Item();
		int damageItem(int damage);
		string getName();
		string getDescription();
		int getPower();
		int getHealing();
		bool getWeapon();
		bool getRoomFeature();
		bool getCollectible();
	
};
#endif
