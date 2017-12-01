#include <string>


#ifndef CETUS_ITEMS_HPP
#define CETUS_ITEMS_HPP

using std::string;

class Item {
	
	private:
	
		string ID;
		string	Name;
		string	Description;
		string 	roomDescription;
		int		Power;
		int		Healing;
		bool	weapon;
		bool	roomFeature;
		bool	collectible;
		
	public:
	
		Item();
		Item(string ID, string Name, string Description, string roomDesc, int Power, int Healing, bool weapon, bool feature, bool collect);
		~Item();
		void damageItem(int damage);
		string getID();
		string getName();
		string getDescription();
		string getRoomDescription();
		int getPower();
		int getHealing();
		bool getWeapon();
		bool getRoomFeature();
		bool getCollectible();
		void setName(string current);
		void setID(string current);
		void setDescription(string current);
		void setRoomDescription(string current);
		void setPower(int current);
		void setHealing(int current);
		void setWeapon(bool current);
		void setRoomFeature(bool current);
		void setCollectible(bool current);
	
};
#endif
