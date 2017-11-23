/****************************************************************************
**Program Filename:  CETUS_data.hpp
**Author:  Jason Fisher
**Date:  10/6/2017
**Description:  data.hpp File for CMD1 project.  Data files will control game
**data input from source files and data output to save files
****************************************************************************/

#ifndef CETUS_DATA_HPP
#define CETUS_DATA_HPP
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include "CETUS_Items.hpp"
#include "CETUS_List.hpp"
#include "CETUS_Player.hpp"
#include "CETUS_Room.hpp"
#include "CETUS_World.hpp"
//Control Functions
World* loadWorld(std::string location);//takes source or save to determine load location
void saveWorld(World *gameState);//saves current game state to save location

//Will load source file data into map and return map
std::map<std::string, std::string> loadFile(std::string);
void saveFile(std::string, std::map<std::string, std::string>);

//Functions to create game objects
Item* loadItem(std::string location);//creates Item from .txt file
Room* loadRoom(std::string location, std::map<std::string, Item*> itemMap, std::map<std::string, std::vector<std::string> > *adj);//creates Room from .txt file.
Player* loadPlayer(std::string location, const std::map<std::string, Room*> *rooms, std::map<std::string, Item*> itemMap);//create Player from .txt file
void loadList(std::map<std::string, std::vector<std::string> > *adj, std::map<std::string, Room*> *roomMap);//create Lists from data that is already loaded

//Functions to save game object data to .txt files
void saveItem(Item *tempItem);
void saveRoom(Room *tempRoom);
void savePlayer(Player tempPlayer);

#endif
