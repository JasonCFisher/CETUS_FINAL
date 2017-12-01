/****************************************************************************
 **Program Filename:  CETUS_Parser.cpp
 **Author:  Josh Sears
 **Date:  11/12/17
 **Description:  Parses user commands into game actions and items
 ****************************************************************************/

#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <string.h>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <cstdlib>

#include "CETUS_World.hpp"
#include "CETUS_Items.hpp"
#include "CETUS_Player.hpp"
#include "CETUS_Room.hpp"
#include "CETUS_data.hpp"
#include "battle.hpp"
#include "CETUS_Print.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::map;

/*
 Required verbs:
 look - repeats the long form explanation of the room
 look at <feature/object> - gives a fictionally interesting explanation of the specified feature/object. Player should be able to “look at” items in inventory
 Directional verbs - player should be able to specify “go north” or “north” to be able to move north. Other room travel verbs should be considered, such as “jump north”
 take - acquire an object and place it in player’s inventory
 help - list a set of verbs the game understands. Not all verbs must be disclosed within this action in case some actions should remain fictionally hidden.
 inventory - list contents of inventory
 savegame - saves the state of the current game to a file
 Loadgame - confirms with the user that this really is desired, then loads the game state from the file
 */

//functions to create verb and noun lists for searching
World* loadhelper(World* current){
    int choice;
    while(1){
        cout << "\nPlease pick a number:\n1. Load from Save.\n2. Load New Game.\nAny other number to cancel load.\nEnter your choice: ";
        cin >> choice;
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        switch(choice){
            case 1:
                return loadWorld("save");
                break;
            case 2:
                return loadWorld("source");
                break;
            default:
                return current;
                break;
        }
        std::cin.seekg(0,std::ios::end);
        std::cin.clear();
    }
}
void helper(){

    //cout << yellow;
    string spacer = "\t\t\t\t\t\t\t[";
    cout << "\nCommand Help List\n----------------------------------------------------------------------------------\n";
    cout << "Quit" << spacer << "Exits the game.]\n";
    cout << "Status" << spacer << "Shows player stats.]\n";
    cout << "Look" << spacer << "View the room and objects in the current area.]\n";
    cout << "Look At <object>" << "\t\t\t\t\t["  << "Inspect the <object>.]\n";
	cout << "Touch <object>" <<  "\t\t\t\t\t\t[" << "Touch the <object>.]\n";
    cout << "Eat <object>" << "\t\t\t\t\t\t[" << "Consume <object>. (Choose wisely!)]\n";
    cout << "Attack <target>" << "\t\t\t\t\t\t[" << "Tries to punch <target> with fists.]\n";
    cout << "Attack <target> with <object>\t\t\t\t[" << "Hit <target> with <object>.]\n";
	cout << "Throw <object> at <target>\t\t\t\t[" << "Throws <object> at <target>.]\n";
	cout << "Apply <object>" << "\t\t\t\t\t\t[" << "Use healing <object> on self.]\n";
	cout << "Make <object>" << "\t\t\t\t\t\t[" << "Create <object> and add to player inventory.]\n";
	cout << "Push <object>" << "\t\t\t\t\t\t[" << "Attempt to push <object>.]\n";
	cout << "Check phone" << "\t\t\t\t\t\t[" << "See latest phone message.]\n";
    cout << "North/South/East/West/Up/Down\t\t\t\t[" << "Move in that direction.]\n";
    cout << "Take <object>" << "\t\t\t\t\t\t[" << "Try to pick up <object>.]\n";
    cout << "Drop <object>" << "\t\t\t\t\t\t[" << "Drop <object> from inventory.]\n";
    cout << "Inventory" << "\t\t\t\t\t\t[" << "Browse contents of inventory.]\n";
    cout << "Savegame" << "\t\t\t\t\t\t[" << "Saves current game progress.]\n";
    cout << "Loadgame" << "\t\t\t\t\t\t[" << "Loads last saved state.]\n";
    cout << "Scan" << "\t\t\t\t\t\t[" << "Displays list of Item names in a room.]\n";
    cout << "----------------------------------------------------------------------------------\n";
    //cout << reset;

}

void mapMaker(std::map<std::string, int> *map){
    map->insert (std::pair<std::string, int>("quit", 0));
    map->insert (std::pair<std::string, int>("attack", 1));
    map->insert (std::pair<std::string, int>("hit", 1));
    map->insert (std::pair<std::string, int>("north", 2));
    map->insert (std::pair<std::string, int>("n", 2));
    map->insert (std::pair<std::string, int>("south", 3));
    map->insert (std::pair<std::string, int>("s", 3));
    map->insert (std::pair<std::string, int>("east", 4));
    map->insert (std::pair<std::string, int>("e", 4));
    map->insert (std::pair<std::string, int>("west", 5));
    map->insert (std::pair<std::string, int>("w", 5));
    map->insert (std::pair<std::string, int>("up", 6));
    map->insert (std::pair<std::string, int>("u", 6));
    map->insert (std::pair<std::string, int>("down", 7));
    map->insert (std::pair<std::string, int>("d", 7));
    map->insert (std::pair<std::string, int>("take", 8));
    map->insert (std::pair<std::string, int>("grab", 8));
    map->insert (std::pair<std::string, int>("pick up", 8));
    map->insert (std::pair<std::string, int>("inv", 9));
    map->insert (std::pair<std::string, int>("inventory", 9));
    map->insert (std::pair<std::string, int>("help", 10));
    map->insert (std::pair<std::string, int>("savegame", 11));
    map->insert (std::pair<std::string, int>("loadgame", 12));
    map->insert (std::pair<std::string, int>("l", 13));
    map->insert (std::pair<std::string, int>("look", 13));
    map->insert (std::pair<std::string, int>("look_at", 14));
    map->insert (std::pair<std::string, int>("inspect", 14));
    map->insert (std::pair<std::string, int>("drop", 15));
    map->insert (std::pair<std::string, int>("apply", 16));
    map->insert (std::pair<std::string, int>("heal", 16));
    map->insert (std::pair<std::string, int>("make molotov", 17));
    map->insert (std::pair<std::string, int>("throw", 18));
    map->insert (std::pair<std::string, int>("toss", 18));
    map->insert (std::pair<std::string, int>("eat", 19));
    map->insert (std::pair<std::string, int>("consume", 19));
    map->insert (std::pair<std::string, int>("use", 20));
    map->insert (std::pair<std::string, int>("status", 21));
	map->insert (std::pair<std::string, int>("touch", 22));
    map->insert (std::pair<std::string, int>("check", 23));
    map->insert (std::pair<std::string, int>("push", 24));
    map->insert (std::pair<std::string, int>("scan", 25));
    return;
}

void displayRoom(World* world, int look){

	cout << cyan;
    Player* player = world->getPlayer();
    string temp;

    cout << "\n" << player->getCurrentRoom()->getName() << std::endl << std::endl;
    if((player->getCurrentRoom()->getVisited()==true) && (look==0)){
        player->getCurrentRoom()->getShort();
    }else {
        player->getCurrentRoom()->getLong();
        world->printRoomInventory();//Prints room description of items under room appearance paragraph
        player->getCurrentRoom()->setVisited(true);
    }


    if(player->getCurrentRoom()->hasEnemy()){
        std::cout <<"\n\n";
        player->getCurrentRoom()->getEnemy()->getRoomDesc();
    } else {
        cout << "\n";
    }

    std::cout << "\nExits:\n";
    world->printAllAdjacent();


    std::cout << "\n";
	cout << reset;
}


void verbFinder(std::map<std::string, int> mymap, string* verb, bool*foundVerb, bool* found, const string first){
    if(mymap.count(first)>0){
        *foundVerb = true;
        *verb = first;
        *found = true;
    }

    return;
}

Creature* enemySearch(Player* player, bool* found, bool* foundEnemy, const string first){
    std::string enemyName = player->getCurrentRoom()->getEnemy()->getName();
    std::transform(enemyName.begin(), enemyName.end(), enemyName.begin(), ::tolower);
    if(enemyName == first){
        *found = true;
        *foundEnemy=true;
        return player->getCurrentRoom()->getEnemy();
    }
    return NULL;
}

void checkPlayerInv(World* world, bool *foundNoun1, bool* foundNoun2, bool* found, bool* foundInv, Item* noun1, Item* noun2, const string first){

	Item* temp = NULL;
	if (world->findItem(first,0) != nullptr){

		temp = world->findItem(first,0);

	}

    if(temp != nullptr){
		//cout << temp->getName();
        if(!(*foundNoun1)){
            //printf("Found a noun match! - Player\n");
            *foundNoun1=true;
            *noun1 = *temp;
            *foundInv = true;
            *found=true;

        } else {
            //printf("Found a second noun match!\n");
            *foundNoun2=true;
            *noun2 = *temp;
            *foundInv = true;
            *found = true;
        }
    }
    temp = NULL;
}

void checkRoomInv(World* world, bool *foundNoun1, bool* foundNoun2, bool* found, bool* foundRoom, Item* noun1, Item* noun2, const string first){
    Player* player=world->getPlayer();
    Item* temp = player->getCurrentRoom()->findItem(first, 0);
    if(temp != NULL){
        if(!(*foundNoun1)){
            //printf("Found a noun match! - Room\n");
            *foundNoun1=true;
            *noun1 = *temp;
            *foundRoom = true;
            *found = true;
        } else {
            //printf("Found a second noun match!\n");
            *foundNoun2=true;
            *noun2 = *temp;
            *foundRoom = true;
            *found = true;
        }
    }
    temp = NULL;
}

string nameDirectionChecker(Player* player, string name, bool* found, bool* foundVerb){
    string verb, temp;
    int answer=-5;
    for(int i=0; i<6; i++){
        if(player->getCurrentRoom()->getNeighbors()->getAdjName(i) != NULL){
            temp = player->getCurrentRoom()->getNeighbors()->getAdjName(i)->getName();
            std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            if(temp == name){
                answer = i;
                *found = true;
                *foundVerb = true;
            }
        }
    }
    switch (answer){
        case 0:
            verb = "north";
            break;
        case 1:
            verb = "south";
            break;
        case 2:
            verb = "east";
            break;
        case 3:
            verb = "west";
            break;
        case 4:
            verb = "up";
            break;
        case 5:
            verb = "down";
            break;
        default:
            verb = "";

    }

    return verb;
}

string useSpecifier(bool *foundNoun1, bool *foundNoun2, bool *found, bool *foundRoom, bool *foundInv, bool *foundEnemy, Item* noun1, Item* noun2, string combo, Creature* baddie){
    std::string verb;
    if(foundNoun1 && noun1->getWeapon()){
        verb = "attack";
    } else if(noun1->getName() == "Chips" || noun1->getName()== "Candy Bar"){
        verb = "eat";
    } else if(noun1->getName() == "Bandaid" || noun1->getName()== "Salve"){
        verb = "apply";
    } else if(noun1->getName() == "Molotov Cocktail"){
        verb = "throw";
    }

    return verb;
}

/*
void randomEnemyGenerator(Room* currentRoom, int act) {
    return;
}
*/
int parser(World* world){


    //create variables to simulate a room, actions, items, etc
    std::string input, first, verb, prev, combo;
    Item* noun1 = new Item;
    Item* noun2 = new Item;
    Creature* baddie = NULL;
    int choice;
    Player* player = world->getPlayer();
    std::map<std::string, int> mymap;
    mapMaker(&mymap);

    std::stringstream sstream;
    displayRoom(world, 0);

    while(1){

        sstream.str("");
        sstream.clear();
        first.clear();
        verb.clear();
        combo.clear();

        choice = -1;
        bool foundVerb = false;
        bool foundEnemy = false;
        bool foundNoun1 = false;
        bool foundNoun2 = false;
        bool withFlag = false;
        bool foundInv = false;
        bool foundRoom = false;
        bool found=false;
        bool selfFlag = false;

        printf("\nWhat are you going to do?\n");

        //Parse the input

        input.clear();
        std::cin.seekg(0,std::ios::end);
        std::cin.clear();


        std::getline(std::cin, input);

        //move to uppercase for matching purposes
        for(int i=0; i<input.size(); i++){
            input.at(i) = std::tolower(input.at(i));
        }
        sstream.str(input);

        //Look through all words for key verbs or nouns
        while(sstream >> first){
            found = false;

            //special case "self"
            if(first == "self"){
                    selfFlag = true;
                    found = true;
            }
            
            //check for special case "look at"
            if(verb == "look" && first == "at"){
                verb="look_at";
                found = true;
                foundVerb = true;
            }
            
            //check for special case "with", "at" or "on"
            if(first == "with" || first=="on" || first=="at"){
                withFlag = true;
                found = true;
            }
            
            //check for special case "pick up"
            if(prev == "pick" && first == "up"){
                verb="pick up";
                found = true;
                foundVerb = true;
            }

            if(!foundVerb && !found){
                verbFinder(mymap, &verb, &foundVerb, &found, first);
            }
            if(!foundVerb && !found){
               verb = nameDirectionChecker(player, first, &found, &foundVerb);
            }

            if(foundVerb && mymap.count(verb) > 0){

            	choice = mymap.find(verb)->second;
       		}

            //search for enemy
            if(!found && (choice == 1 || choice == 14 || choice == 18 || choice == 24) && !foundEnemy && player->getCurrentRoom()->hasEnemy()){
                baddie = enemySearch(player, &found, &foundEnemy, first);

            }

            //search player inventory
            if(!found && !player->invIsEmpty()){
                checkPlayerInv(world, &foundNoun1, &foundNoun2, &found, &foundInv, noun1, noun2, first);
			}

            //search room inventory
            if(!found && !player->getCurrentRoom()->invIsEmpty()){

				checkRoomInv(world, &foundNoun1, &foundNoun2, &found, &foundRoom, noun1, noun2, first);

            }

            if(!found && (prev.empty() == false) ){
                combo = prev + " " + first;

                //look for two word action
                if(!found && !foundVerb){
                    verbFinder(mymap, &verb, &foundVerb, &found, combo);

                }
                if(!foundVerb && !found){
                    verb = nameDirectionChecker(player, combo, &found, &foundVerb);
                }
                if(foundVerb && mymap.count(verb) > 0){
                    
                    choice = mymap.find(verb)->second;
                }
                //search for enemy
                if(!found && (choice == 1 || choice == 14 || choice ==18 || choice == 24) && !foundEnemy && player->getCurrentRoom()->hasEnemy()){
                    baddie = enemySearch(player, &found, &foundEnemy, combo);

                }

                //search player inventory
                if(!found && !player->invIsEmpty()){
                    checkPlayerInv(world, &foundNoun1, &foundNoun2, &found, &foundInv, noun1, noun2, combo);
                }

                //search room inventory
                if(!found && !player->getCurrentRoom()->invIsEmpty()){
                    checkRoomInv(world, &foundNoun1, &foundNoun2, &found, &foundRoom, noun1, noun2, combo);

                }

            }


            if(!found ){
                prev=first;
            } else {
                prev.clear();
            }


        }

        if(verb=="use"){
            verb = useSpecifier(&foundNoun1, &foundNoun2, &found, &foundRoom, &foundInv, &foundEnemy, noun1, noun2, combo, baddie);
        }
        
        if(verb == "check"){
            if(foundInv && foundNoun1 && noun1->getName() == "Phone"){
                verb = "check";
            } else {
                verb = "inspect";
            }
        }

        if(mymap.count(verb) > 0){

            choice = mymap.find(verb)->second;
        }

        switch(choice){
            case 0:  //Quit game
				cout << yellow;
                std::cout << "So sad to see you leave...\n";
                cout << reset;
				return 0;
            case 1:  //Attack, Hit
				cout << green;
                if(foundNoun1 && withFlag && foundEnemy && noun1->getWeapon()){
                    if(battle(player, baddie, noun1->getPower(), 0)==0){
                        world = loadWorld("source");
                        if(world!=NULL){
                            player = world->getPlayer();
                        } else {
                            cout << "Error loading game!\n";
                        }
                        break;
                    }
                }else if(withFlag && foundEnemy && !noun1->getWeapon()){
                    cout << "You didn't pick a valid weapon.\n";
                } else if (foundEnemy){
                    if(battle(player, baddie, 0, 0)==0){
                        world = loadhelper(world);
                        if(world!=NULL){
                            player = world->getPlayer();
                        } else {
                            cout << "Error loading game!\n";
                        }
                        break;
                    }
                }else if(!foundEnemy && selfFlag){
                    cout <<"\nWhy would you attack yourself?\n";
                } else {
                    cout << "What do you want to attack?\n";

                }
				cout << reset;
                break;
            case 2: //North, n
                if(world->getCurrentRoom()->hasEnemy() && !world->getCurrentRoom()->getEnemy()->isDead(0)){
                    if(battle(player, world->getCurrentRoom()->getEnemy(), 0, 1)==0){
                        world = loadhelper(world);
                        if(world!=NULL){
                            player = world->getPlayer();
                        } else {
                            cout << "Error loading game!\n";
                        }
                        break;
                    }
                }
                if(world->move(0)){
                    randomEnemyGenerator(world->getCurrentRoom(), world->getAct());
                    displayRoom(world, 0);
                }
                break;
            case 3:  //South, s
            if(world->getCurrentRoom()->hasEnemy() && !world->getCurrentRoom()->getEnemy()->isDead(0)){
                    if(battle(player, world->getCurrentRoom()->getEnemy(), 0, 1)==0){
                        world = loadhelper(world);
                        if(world!=NULL){
                            player = world->getPlayer();
                        } else {
                            cout << "Error loading game!\n";
                        }
                        break;
                    }
                }
                if(world->move(1)){
                    randomEnemyGenerator(world->getCurrentRoom(), world->getAct());
                    displayRoom(world, 0);
                }
                break;

            case 4:  //East, e
            if(world->getCurrentRoom()->hasEnemy() && !world->getCurrentRoom()->getEnemy()->isDead(0)){
                    if(battle(player, world->getCurrentRoom()->getEnemy(), 0, 1)==0){
                        world = loadhelper(world);
                        if(world!=NULL){
                            player = world->getPlayer();
                        } else {
                            cout << "Error loading game!\n";
                        }
                        break;
                    }
                }
                if(world->move(2)){
                    randomEnemyGenerator(world->getCurrentRoom(), world->getAct());
                    displayRoom(world, 0);
                }
                break;
            case 5:  //West, w
            if(world->getCurrentRoom()->hasEnemy() && !world->getCurrentRoom()->getEnemy()->isDead(0)){
                if(battle(player, world->getCurrentRoom()->getEnemy(), 0, 1)==0){
                    world = loadhelper(world);
                    if(world!=NULL){
                        player = world->getPlayer();
                    } else {
                        cout << "Error loading game!\n";
                    }
                    break;
                }
            }
			if (world->getAct() < 3 && world->getPlayer()->getCurrentRoom()->getID() == "altChurchyard") {
				cout << yellow;
				cout << "A strange force prevents you from opening the door." << endl;
				cout << reset;
				break;
			}
            if(world->move(3)){
                if(world->getCurrentRoom()->hasEnemy() && !world->getCurrentRoom()->getEnemy()->isDead(0)){
					if(battle(player, world->getCurrentRoom()->getEnemy(), 0, 1)==0){
						world = loadhelper(world);
						if(world!=NULL){
							player = world->getPlayer();
						} else {
							cout << "Error loading game!\n";
						}
                    break;
					}
				}
                randomEnemyGenerator(world->getCurrentRoom(), world->getAct());
                displayRoom(world, 0);
            }
            break;
            case 6:  //Up, u
            if(world->getCurrentRoom()->hasEnemy() && !world->getCurrentRoom()->getEnemy()->isDead(0)){
                    if(battle(player, world->getCurrentRoom()->getEnemy(), 0, 1)==0){
                        world = loadhelper(world);
                        if(world!=NULL){
                            player = world->getPlayer();
                        } else {
                            cout << "Error loading game!\n";
                        }
                        break;
                    }
                }
                if(world->move(4)){
                    randomEnemyGenerator(world->getCurrentRoom(), world->getAct());
                    displayRoom(world, 0);
                }
                break;
            case 7:  //Down, d
            if(world->getCurrentRoom()->hasEnemy() && !world->getCurrentRoom()->getEnemy()->isDead(0)){
                    if(battle(player, world->getCurrentRoom()->getEnemy(), 0, 1)==0){
                        world = loadhelper(world);
                        if(world!=NULL){
                            player = world->getPlayer();
                        } else {
                            cout << "Error loading game!\n";
                        }
                        break;
                    }
                }
                if(world->move(5)){
                    randomEnemyGenerator(world->getCurrentRoom(), world->getAct());
                    displayRoom(world, 0);
                }
                break;
            case 8:  //Grab, Take, Pick up
		cout << magenta;
                if(foundRoom && foundNoun1 && noun1->getCollectible()){
                    player->addItem(player->getCurrentRoom()->removeItem(noun1));
                    cout << "\nYou pick up a " << noun1->getName() << "\n";
                }else if(foundRoom && foundNoun1 && !noun1->getCollectible()){
                    cout << "You cannot take that.\n";
                }else {
                    cout << "I don't see that in the room.\n";
                }
				cout << reset;
                break;
            case 9:  //Inventory, inv
                world->printInventory();
                break;
            case 10:  //Help
                helper();
                break;
            case 11:  //Savegame
                saveWorld(world);
                break;
            case 12:  //Loadgame
                world = loadhelper(world);
                if(world!=NULL){
                    player = world->getPlayer();
                    displayRoom(world, 0);
                } else {
                    cout << "Error loading game!\n";
                }
                break;
            case 13:  //Look
                //Display the correct room description.
                displayRoom(world, 1);

                break;
            case 14:  //Look At
                cout << yellow;
                if(foundNoun1 && world->getCurrentRoom()->getID() == "normCellar" && noun1->getID() == "normDistDust" && !world->checkDir(3)){
                    cout << noun1->getDescription() << "\n";
                    world->openPassage(1);
                }else if(foundNoun1){
                    if(!(world->actController(noun1->getName(), "Look"))){
                        cout << noun1->getDescription() << "\n";
                    }
                }else if(foundEnemy){
                    baddie->getDesc();
                } else {
                    cout << "I don't know what you want to look at.\n";
                }


				cout << reset;
                break;
            case 15: //Drop
				cout << yellow;
                if(foundInv && foundNoun1){
                    world->dropItem(noun1->getName());
                    cout << "\nYou drop a " << noun1->getName() << "\n";
                } else {
                    cout << "I don't see that in your inventory.\n";
                }
                cout << reset;
                break;
            case 17: //make for molotov cocktail
                if(world->findItem("whiskey", 0) && world->findItem("rag",0)){
                    cout << "\nYou stuff the rag into the bottle.  Make it count, this will only work once.\n";
                    world->destroyItem("whiskey");
                    world->destroyItem("rag");
                    world->addItem(world->findWorldItem("molotov cocktail", 1));
                } else {
                    cout << "\nYou don't have all the right stuff to make that.\n";
                }
                break;
            case 16: //heal, apply
                if(foundInv && foundNoun1 && (noun1->getHealing() > 0)){
                    if(player->getHealth() < 100){
                        player->healPlayer(noun1->getHealing());
                        cout << "\nYou apply the " << noun1->getName() << " and are healed for " << noun1->getHealing() << " points.\n";
                    }else {
                        cout << "\nYou don't need any healing!\n";
                    }
                } else if(foundNoun1 && !foundInv){
                    cout << "\n" << noun1->getName() << " is not in your inventory.\n";
                } else if(foundNoun1 && noun1->getHealing() <= 0){
                    cout << "\nThat will not aid in your healing!\n";
                } else {
                    cout << "\nI don't know what you are asking.\n";
                }
                break;
            case 18:
                if(foundInv && foundNoun1 && foundEnemy && withFlag){
                    if(noun1->getName() != "Molotov Cocktail"){
                        cout << "\nYou don't want to throw that.\n";
                    } else if(world->findItem("Lighter",0)==NULL){
                        cout << "\nYou have nothing to light that with!\n";
                    } else if(world->getCurrentRoom()->getEnemy()->getName() != "Cetus"){
                        cout << "\nThat creature isn't worth losing an item!\n";
                    } else {
                        throwMolotov(world);
                    }
                }else if(foundInv && foundNoun1){
                    cout << "\nWho are you going to throw that at?\n";
                }else if(foundEnemy && !foundNoun1){
                    cout << "\nYou can't throw the bad guy!\n";
                } else if(foundEnemy && foundNoun1 && !foundInv){
                    cout << "\nYou don't have that to throw!\n";
                } else {
                    cout << "I don't know what you are talking about.";
                }
                break;
            case 19: //eat, consume
                if(foundInv && foundNoun1){
                    if(noun1->getName() == "Candy Bar"){
                        cout << "\nMmmm...chocolate.\n";
                        world->destroyItem("Candy Bar");
                    }else if(noun1->getName() == "Chips"){
                        cout << "\nYum.  Can't eat just one...\n";
                        world->destroyItem("Chips");
                    }else{
                        cout << "\nYou really shouldn't eat a " << noun1->getName() <<".\n";
                    }
                } else {
                    std::cout << "I don't know what you are asking for.\n";
                }
                break;
            case 21:
                cout << "\nCurrent Health: " << player->getHealth()<<".\n";
                cout << "Move Count: " << player->getMovesCompleted() << ".\n";
                break;
			case 22:
                cout << yellow;
                if(foundNoun1){
                    if(!(world->actController(noun1->getName(), "touch"))){
                        cout << "Nothing happens.\n";
                    }
                }else if(foundEnemy){
                    cout << "I don't think that just touching something that is trying to kill you is such a good idea.\n";
                } else {
                    cout << "I don't know what you want to touch.\n";
                }


				cout << reset;
                break;
            case 23:
                if(foundInv && foundNoun1 && noun1->getName()=="Phone"){
                    world->getVoicemails();
                }
                break;
            case 24:
                if(foundRoom && foundNoun1 && noun1->getName() == "Block"){
                    world->openPassage(2);
                } else if(foundEnemy){
                    if(world->getCurrentRoom()->hasEnemy() && !world->getCurrentRoom()->getEnemy()->isDead(0)){
                        cout << "\nYou pushed the " << baddie->getName() << ".\n";
                        if(battle(player, world->getCurrentRoom()->getEnemy(), 0, 1)==0){
                            world = loadhelper(world);
                            if(world!=NULL){
                                player = world->getPlayer();
                            } else {
                                cout << "Error loading game!\n";
                            }
                            break;
                        }
                    } else { cout << "\nPushing a corpse?  Tough guy...\n";}
                    
                } else if(foundNoun1) { cout << "Nothing happens.\n";
                } else { cout << "I don't know what you are wanting to push.\n";
                }break;
            case 25:
                if(world->getCurrentRoom()->getItems().size() == 0){
                    cout << "No room items found\n";
                } else {
                    cout << "\nRoom Items\n----------\n";
                
                    for (int i = 0; i < world->getCurrentRoom()->getItems().size(); i++){
                        
                        if (world->getCurrentRoom()->getItems()[i] != NULL){
                            cout << world->getCurrentRoom()->getItems()[i]->getName() << "\n";
                        }
                    }
                } break;
            default:
                std::cout << "I don't know what you are asking for.\n";
        }
    }

    return 0;


}
