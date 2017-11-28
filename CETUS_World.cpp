#include <iostream>
#include <string>
#include "CETUS_Player.hpp"
#include "CETUS_Room.hpp"
#include "CETUS_List.hpp"
#include "CETUS_Items.hpp"
#include "CETUS_World.hpp"



#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3
#define UP 4
#define DOWN 5
#define LINESIZE 80

const std::string red("\033[0;31m");
const std::string green("\033[1;32m");
const std::string yellow("\033[1;33m");
const std::string cyan("\033[0;36m");
const std::string magenta("\033[0;35m");
const std::string reset("\033[0m");


using std::endl;
using std::cout;
using std::string;

	World::World(){


		this->Name = ' ';
		this->Description = ' ';
		this->currentPlayer = NULL;
		this->realWorld = true;
        this->act = 1;
		//this->currentPlayer->setCurrentRoom(NULL);
		//this->currentPlayer->setNeighbors(NULL);

	}

	World::World(Room* current, int currentHealth, int currentMoves, int currentSpecialCount, int currentAct){

		Player temp = Player(current, currentHealth, currentMoves, currentSpecialCount);
		this->currentPlayer = &temp;
		this->realWorld = true;
        this->act=currentAct;

	}


	string World::getName(){

		return this->Name;

	}

	string World::getDescription(){

		return this->Description;

	}

	Player* World::getPlayer(){

		return this->currentPlayer;

	}


	bool World::getRealWorld(){

		return this->realWorld;

	}

	Room* World::getCurrentRoom(){

		return this->currentPlayer->getCurrentRoom();

	}


	void World::setName(string current){

		this->Name = current;
		return;

	}

	void World::setDescription(string current){

		this->Description = current;
		return;

	}

	void World::setPlayer(Player* current){

		this->currentPlayer = current;
		return;


	}

	void World::setRealWorld(bool current){

		this->realWorld = current;
		return;

	}

	void World::setCurrentRoom(Room* current){

		this->currentPlayer->setCurrentRoom(current);
		return;

	}

	void World::dropItems(){}

	void World::addItem(Item* current){

		this->currentPlayer->inventory.push_back(current);
		return;

	}
	void World::dropItem(string current){

		Item* temp = findItem(current, true);
		if (temp != NULL){
			this->currentPlayer->currentRoom->addItem(temp);
		}

		return;
	}

	Item* World::findItem(string current){

		for (int i = 0; i < this->currentPlayer->inventory.size(); i++){

			if (!this->currentPlayer->inventory[i]->getName().compare(current)){

				return this->currentPlayer->inventory[i];
			}

		}

		return NULL;

	}


	Item* World::findItem(string current, bool drop){

			string tempString;
			std::transform(current.begin(), current.end(), current.begin(), ::tolower);

			Player* temp = this->currentPlayer;

			for (int i = 0; i < temp->inventory.size(); i++){

				tempString = temp->inventory[i]->getName();
				std::transform(tempString.begin(), tempString.end(), tempString.begin(), ::tolower);

				if (!tempString.compare(current)){

					Item* currentItem = temp->inventory[i];

					if(drop == true){
						temp->inventory.erase(temp->inventory.begin()+i);
					}

					return currentItem;
				}

			}

			return NULL;

	}

	Item* World::findRoomItem(string current, bool drop){

        std::string tempString;
        std::transform(current.begin(), current.end(), current.begin(), ::tolower);
        for (int i = 0; i < this->currentPlayer->currentRoom->roomItems.size(); i++){
            if(this->currentPlayer->currentRoom->roomItems[i] != NULL){
                tempString = this->currentPlayer->currentRoom->roomItems[i]->getName();
                std::transform(tempString.begin(), tempString.end(), tempString.begin(), ::tolower);
                if (!tempString.compare(current)){

                    Item* temp = this->currentPlayer->currentRoom->roomItems[i];

                    if(drop == true){
                        this->currentPlayer->currentRoom->roomItems.erase(this->currentPlayer->currentRoom->roomItems.begin()+i);
                    }
                    return temp;
                }
            }
        }



		return NULL;

	}
	void World::printAllAdjacent(){

		Player* temp = this->currentPlayer;

		if (temp->currentRoom->neighbors->north != NULL){

            cout << "North: "<< temp->currentRoom->neighbors->north->Name << endl;

		}

		if (temp->currentRoom->neighbors->south != NULL){

			cout << "South: "<< temp->currentRoom->neighbors->south->Name << endl;

		}

		if (temp->currentRoom->neighbors->east != NULL){

			cout <<  "East: "<<temp->currentRoom->neighbors->east->Name << endl;

		}

		if (temp->currentRoom->neighbors->west != NULL){

			cout << "West: "<< temp->currentRoom->neighbors->west->Name << endl;

		}


		if (temp->currentRoom->neighbors->up != NULL){

			cout << "Up: "<< temp->currentRoom->neighbors->up->Name << endl;

		}

		if (temp->currentRoom->neighbors->down != NULL){

			cout << "Down: "<< temp->currentRoom->neighbors->down->Name << endl;

		}

		return;
	}

    void World::printInventory(){
        Player* temp = this->currentPlayer;
        if (temp->inventory.size() == 0) {

            cout << "Player has no items in inventory." << endl;
            return;
        }

        cout << "\nInventory\n" << "---------\n";
        for (int i = 0; i < temp->inventory.size(); i++){

            if (temp->inventory[i] != NULL){
                cout << temp->inventory[i]->getName() << "\n";
            }
        }

        return;

    }
	void World::printRoomInventory(){
		Player* temp = this->currentPlayer;
		if (temp->currentRoom->roomItems.size() == 0) {

			//cout << "Player has no items in inventory." << endl;
			return;
		}

		for (int i = 0; i < temp->currentRoom->roomItems.size(); i++){

			if (temp->currentRoom->roomItems[i] != NULL){
				cout << "  " << temp->currentRoom->roomItems[i]->getRoomDescription();
			}
		}

		return;

	}
	void World::printAdjacent(int direction){

		Player* temp = this->currentPlayer;
		switch(direction){

			case NORTH:
				cout << temp->currentRoom->neighbors->north->Name << endl;
				break;

			case SOUTH:
				cout << temp->currentRoom->neighbors->south->Name << endl;
				break;

			case EAST:
				cout << temp->currentRoom->neighbors->east->Name << endl;
				break;

			case WEST:
				cout << temp->currentRoom->neighbors->west->Name << endl;
				break;

			case UP:
				cout << temp->currentRoom->neighbors->up->Name << endl;
				break;

			case DOWN:
				cout << temp->currentRoom->neighbors->down->Name << endl;
				break;

			default:
				break;

		}
		return;

	}

	int World::move(int direction){
        int moveFlag=0;
		Player* temp = this->currentPlayer;

		switch(direction){

			case NORTH:
                if(temp->currentRoom->neighbors->north != NULL){
                    temp->setCurrentRoom(temp->currentRoom->neighbors->north);
                    temp->setNeighbors(temp->currentRoom->getNeighbors());
                    moveFlag=1;
                    this->getPlayer()->incrementMoves();
                } else {
                    printf("\nThere is no apparent exit in that direction.\n");
                }
				break;

			case SOUTH:
                if(temp->currentRoom->neighbors->south != NULL){
                    temp->setCurrentRoom(temp->currentRoom->neighbors->south);
                    temp->setNeighbors(temp->currentRoom->getNeighbors());
                    moveFlag=1;
                    this->getPlayer()->incrementMoves();
                } else {
                    printf("\nThere is no apparent exit in that direction.\n");
                }
				break;

			case EAST:
                if(temp->currentRoom->neighbors->east != NULL){
                    temp->setCurrentRoom(temp->currentRoom->neighbors->east);
                    temp->setNeighbors(temp->currentRoom->getNeighbors());
                    moveFlag=1;
                    this->getPlayer()->incrementMoves();
                } else {
                    printf("\nThere is no apparent exit in that direction.\n");
                }
				break;

			case WEST:
                if(temp->currentRoom->neighbors->west != NULL){
                    temp->setCurrentRoom(temp->currentRoom->neighbors->west);
                    temp->setNeighbors(temp->currentRoom->getNeighbors());
                    moveFlag=1;
                    this->getPlayer()->incrementMoves();
                } else {
                    printf("\nThere is no apparent exit in that direction.\n");
                }
				break;

			case UP:
                if(temp->currentRoom->neighbors->up != NULL){
                    temp->setCurrentRoom(temp->currentRoom->neighbors->up);
                    temp->setNeighbors(temp->currentRoom->getNeighbors());
                    moveFlag=1;
                    this->getPlayer()->incrementMoves();
                } else {
                    printf("\nThere is no apparent exit in that direction.\n");
                }
				break;

			case DOWN:
                if(temp->currentRoom->neighbors->down != NULL){
                    temp->setCurrentRoom(temp->currentRoom->neighbors->down);
                    temp->setNeighbors(temp->currentRoom->getNeighbors());
                    moveFlag=1;
                    this->getPlayer()->incrementMoves();
                } else {
                    printf("\nThere is no apparent exit in that direction.\n");
                }
				break;

			default:
                printf("\nThat is not a valid direction.\n");
				break;

		}

		return moveFlag;
	}



	void World::printLogo(){

	//source - https://www.uow.edu.au/~lukes/TEXTBOOK/notes-cpp/io/readtextfile.html

		cout << green;
		ifstream inFile;
		inFile.unsetf(std::ios_base::skipws);
		inFile.open("./cetus.txt");

		char temp;

		while(inFile >> temp){

			cout << temp;

		}
		cout << endl;
		cout << reset;
	}

	void World::ClearScreen(){

		//This is the least complex way to clear the screen and remain system agnostic

		for(int i = 0; i < 75; i++){

			cout << endl;

		}

	}

	void World::cetusPrint(string* inText, int color){

		switch(color){

			case 0:
				cout << red;
				break;

			case 1:

				cout << green;
				break;

			case 2:

				cout << yellow;
				break;

			case 3:

				cout << cyan;
				break;

			case 4:

				cout << magenta;
				break;

			default:

				break;

		}

		int count = 0;

		for (size_t i = 0; i < inText->length(); i++){

			if(count <= LINESIZE){


				cout << inText->at(i);
				count++;
				if(inText->at(i) == '\n'){

					count = 0;

				}

			}

			else{

						if(inText->at(i) != ' ' && inText->at(i) != '\n'){

					cout << inText->at(i);
								count++;

							}
				else{

									cout << endl;
									count = 0;

							}

			}

		}
		cout << reset;

		return;

}


	int	World::createRooms(std::vector <Room*> rmVect) {
		this->worldRooms = rmVect;
        return 0;
	}

	std::vector<Room*> World::getRooms() {
		return this->worldRooms;
	}

int World::getAct(){
    return this->act;
}

void World::incrementAct(){
    this->act++;
}

int World::actController(string item){

    std::string ritualInterrupt = "Shrouded figures surround the altar.  There is a gutteral chanting from all. Taking a few steps further, you see a sphere of mystical energy surrounding the altar.  Walking forward in astonishment, you catch the attention of one of the figures.  When his focus breaks, the sphere shatters into jagged pieces of energy, and creates a vacuum.  Chanting turns to screams and groans as the robed figures start getting sucked in.  Others try to hold on.  You aren't so lucky.  One of the robed figures uses you to work his way toward the door.  You are flung toward the energy vortex, and everything goes dark.\n\nYou wake up groggily with your head pounding.  You open your eyes and see a room that looks wrong.  It seems to be the same room, but the light looks wrong and all the angles seem to be off.  Did something happen when you hit the vortex?";
    std::string touchAltar = "You touched the altar. Your body fragments as you pass through the dimensional rift.  When the world stops spinning, you're standing alternate dimension.\n";
    std::string touchBear = "You touched the doll. Your body fragments as you pass through the dimensional rift.  When the world stops spinning, you're standing in the normal dimension.\n";
    Room* target = NULL;
    int moveAct=0;
    //end of first act
    if(this->getPlayer()->getCurrentRoom()->getID() == "normLair" && this->getAct() == 1 && item == "Ritual"){
        cout << std::endl << ritualInterrupt << endl;
        this->incrementAct();
        Item* temp = findRoomItem(item, true);
		if (temp != NULL){
			this->addWorldItem(temp);
		}
        for(int i=0; i< worldRooms.size(); i++){
            if(this->worldRooms[i]->getID() == "altLair"){
                target = this->worldRooms[i];
                moveAct=1;
            }
        }

    }
    //going back into bad dimension
    if(!moveAct && this->getPlayer()->getCurrentRoom()->getID() == "normLair" && this->getAct() >= 2 && item == "Altar"){
        cout << std::endl << touchAltar << endl;
        for(int i=0; i< worldRooms.size(); i++){
            if(this->worldRooms[i]->getID() == "altLair"){
                target = this->worldRooms[i];
                moveAct=1;
            }
        }

    }


    //inspecting bear
    if(!moveAct && this->getPlayer()->getCurrentRoom()->getID() == "altBed1" && this->getAct() >= 2 && item == "Doll"){
        cout << std::endl << touchBear << endl;
        for(int i=0; i< worldRooms.size(); i++){
            if(this->worldRooms[i]->getID() == "normBed1"){
                target = this->worldRooms[i];
                moveAct=1;
            }
        }

    }

	if(!moveAct && this->getPlayer()->getCurrentRoom()->getID() == "altChurch" && this->getAct() == 2 && item == "Windows") {
		this->incrementAct();
	}
    if(moveAct){
        this->setCurrentRoom(target);
    }
    return moveAct;
}

	int	World::createItems(std::vector <Item*> itemVect) {
		this->worldItems = itemVect;
        return 0;
	}

	std::vector<Item*> World::getItems() {
		return this->worldItems;
	}

	void World::setAct(int currentAct) {
        this->act = currentAct;
	}

    void World::addWorldItem(Item* current){

		this->worldItems.push_back(current);
		return;

	}

Item* World::findWorldItem(string current, bool drop){
    
    string tempString;
    std::transform(current.begin(), current.end(), current.begin(), ::tolower);
    
    for (int i = 0; i < worldItems.size(); i++){
        
        tempString = worldItems[i]->getName();
        std::transform(tempString.begin(), tempString.end(), tempString.begin(), ::tolower);
        
        if (!tempString.compare(current)){
            
            Item* currentItem = worldItems[i];
            
            if(drop == true){
                worldItems.erase(worldItems.begin()+i);
            }
            
            return currentItem;
        }
        
    }
    
    return NULL;
    
}
void World::destroyItem(string current){
        
        Item* temp = findItem(current, true);
        if (temp != NULL){
            this->addWorldItem(temp);
        }
        
        return;
    }
    


