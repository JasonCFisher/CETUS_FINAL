//C++ Command Line parsing tester

#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <string.h>
#include <sstream>
#include <vector>
#include <map>

#include "CETUS_Items.hpp"
#include "CETUS_Player.hpp"
#include "CETUS_Room.hpp"
#include "creature.hpp"
#include "ghost.hpp"
#include "battle.hpp"

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

void helper(){
    string spacer = "     [";
    cout << "\nCommand Help List\n-----------------\n";
    cout << "Quit" << spacer << "Exits the game.]\n";
    cout << "Look" << spacer << "View the room and objects in the current area.]\n";
    cout << "Look At <object>" << spacer << "Inspect the <object>.]\n";
    cout << "Attack <target>" << spacer << "Tries to punch <target> with fists.]\n";
    cout << "Attack <target> with <object>" << spacer << "Hit <target> with <object>.]\n";
    cout << "North/South/East/West/Up/Down" << spacer << "Move in that direction.]\n";
    cout << "Take <object>" << spacer << "Try to pick up <object>.]\n";
    cout << "Drop <object>" << spacer << "Drop <object> from inventory.]\n";
    cout << "Inventory" << spacer << "Browse contents of inventory.]\n";
    cout << "Savegame" << spacer << "Saves current game progress.]\n";
    cout << "Loadgame" << spacer << "Loads last saved state.]\n";
    cout << "-----------------\n";
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
    return;
}

void nounListMaker(std::vector <std::string> *list){
    list->push_back("axe");
    list->push_back("pipe");
    list->push_back("jacket");
    return;
}



int main(){
    
    //create variables to simulate a room, actions, items, etc
    std::string input, first, verb;
    Item* noun1 = new Item;
    Item* noun2 = new Item;
    Creature* baddie = new Ghost;
    int choice;
    
    //Item* tester = new Item("tester", "testItem", 0, 0, true);
   
    std::vector <Item*> playerInv;
    std::map<std::string, int> mymap;
    mapMaker(&mymap);

    std::stringstream sstream;
    
    //Make a couple rooms
    Room* testRoomB = new Room(NULL, NULL, NULL, NULL, NULL, NULL, "Test Room B", "Longer Desc", "Shorter", false );
    
    Room* testRoomC = new Room(NULL, NULL, NULL, NULL, NULL, NULL, "Test Room C", "Longest Desc", "Shortest", false);
    Room* testRoomD = new Room(NULL, NULL, NULL, NULL, NULL, NULL, "Test Room D", "Longest Desc", "Shortest", false);
    Room* testRoomE = new Room(NULL, NULL, NULL, NULL, NULL, NULL, "Test Room E", "Longest Desc", "Shortest", false);
    Room* testRoomA = new Room(testRoomB, testRoomC, testRoomD, testRoomE, NULL, NULL, "Test Room Home", "Long Desc", "Short", false );
    
    testRoomB->addAdjacent(1, testRoomA);
    testRoomC->addAdjacent(0,testRoomA);
    testRoomD->addAdjacent(3, testRoomA);
    testRoomE->addAdjacent(2, testRoomA);
    
    //Create new player
    Player* player = new Player (testRoomA);
    
    //Put item in inventory
    Item* torch = new Item("torch", "A stick with light.", 20, 0, true, false, false);
    player->getCurrentRoom()->addItem(torch);
    
    //Create a new ghost.
    Creature* ghost1 = new Ghost;
    player->getCurrentRoom()->addEnemy(ghost1);
    
    //Start display
    player->displayRoom();
    
    std::vector<Creature*> eList = player->getCurrentRoom()->getEnemies();
    cout << eList[0]->getName();
    
    while(1){
        sstream.str("");
        sstream.clear();
        first.clear();
        verb.clear();
       
        choice = -1;
        bool foundVerb = false;
        bool foundEnemy = false;
        bool foundNoun1 = false;
        bool foundNoun2 = false;
        bool withFlag = false;
        
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
            
            if(mymap.count(first)>0){
                    //printf("Found a verb match!\n");
                    foundVerb = true;
                    verb = first;
            
            }
            
            std::vector<Creature*> eList = player->getCurrentRoom()->getEnemies();
            for(int i = 0; i<eList.size();++i){
                if(first == eList[i]->getName()){
                    if(!foundNoun1){
                        //printf("Found a noun match!\n");
                        foundNoun1=true;
                        foundEnemy=true;
                        baddie = eList[i];
                    }
                }
            }
            
            /*
            //look for bad guy
            for(std::vector<Creature*>::iterator it = player->getCurrentRoom()->getEnemies().begin(); it != player->getCurrentRoom()->getEnemies().end(); ++it){
                if(first == (*it)->getName()){
                    if(!foundNoun1){
                        //printf("Found a noun match!\n");
                        foundNoun1=true;
                        foundEnemy=true;
                        baddie = *it;
                    }
                }
            }
            */
            for(std::vector<Item*>::iterator it = player->getInventory().begin(); it != player->getInventory().end(); ++it){
                if(first == (*it)->getName()){
                    if(!foundNoun1){
                        //printf("Found a noun match!\n");
                        foundNoun1=true;
                        noun1 = *it;
                    } else {
                        //printf("Found a second noun match!\n");
                        foundNoun2=true;
                        noun2 = *it;
                    }
                }
            }
            
            //look for other nouns
            for(std::vector<Item*>::iterator it = player->getInventory().begin(); it != player->getInventory().end(); ++it){
                if(first == (*it)->getName()){
                    if(!foundNoun1){
                        //printf("Found a noun match!\n");
                        foundNoun1=true;
                        noun1 = *it;
                    } else {
                        //printf("Found a second noun match!\n");
                        foundNoun2=true;
                        noun2 = *it;
                    }
                }
            }
            
            

            
            if(first == "with"){
                withFlag = true;
            }
            if(verb == "look" && first == "at"){
                verb="look_at";
            }
            
        }
        
        if(mymap.count(verb) > 0){
            
            choice = mymap.find(verb)->second;
       }

        switch(choice){
            case 0:  //Quit game
                std::cout << "So sad to see you leave...\n";
                return 0;
            case 1:  //Attack, Hit
                if(foundNoun2 && withFlag && foundEnemy){
                    battle(player, ghost1, noun2->getPower());
                } else if (foundEnemy){
                        battle(player, ghost1, 0);
                } else {
                    cout << "What do you want to attack?\n";

                }
                break;
            case 2: //North, n
                player->move(0);
                break;
            case 3:  //South, s
                player->move(1);
                break;
                
            case 4:  //East, e
                player->move(2);
                break;
            case 5:  //West, w
                player->move(3);
                break;
            case 6:  //Up, u
                player->move(4);
                break;
            case 7:  //Down, d
                player->move(5);
                break;
            case 8:  //Grab, Take
                //player->addItem(noun1);
               // player->getCurrentRoom()->removeItem(noun1);
                break;
            case 9:  //Inventory, inv
                player->printInventory();
                break;
            case 10:  //Help
                helper();
                break;
            case 11:  //Savegame
                std::cout << "Your game was saved succesfully.\n";
                break;
            case 12:  //Loadgame
                std::cout << "Your game was successfully loaded!\n";
                break;
            case 13:  //Look
                //Display the correct room description.
                cout << player->getCurrentRoom()->getName() << "\n\n";
                player->getCurrentRoom()->getLong();
                player->getCurrentRoom()->printRoomItems();
               
                break;
            case 14:  //Look At
                if(foundNoun1){
                    noun1->getDescription();
                } else {
                    cout << "I don't know what you want to look at.\n";
                }
                break;
            case 15: //Drop
                 player->getCurrentRoom()->addItem(noun2);
                player->dropItem(noun2);
                break;
            default:
                std::cout << "I don't know what you are asking for.\n";
        }
    }
    
    return 0;


}
