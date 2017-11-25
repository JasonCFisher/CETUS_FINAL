/****************************************************************************
**Program Filename:  data.cpp
**Author:  Jason Fisher
**Date:  10/6/2017
**Description:  data.cpp file for CMD1 project.  Data files will control game
**data input from source files and data output to save files
****************************************************************************/

#include "CETUS_data.hpp"


/***************************************************************************
**Function:  loadFile
**Description:  Opens input source file, parses file data into map, and
**				returns the map
**Parameters:  std::string fileName
**Pre-Condition:  File exists and correct fileName is passed to function
**Post-Condition:  Map containing the source file data returned
**
**Code for parsing source file input from
**https://stackoverflow.com/questions/31103883/reading-key-value-pairs-from-a-file-and-ignoring-comment-lines
****************************************************************************/
std::map<std::string, std::string> loadFile(std::string fileName) {
	//declare variables
	std::ifstream inputFile;
	std::string line;
	std::map<std::string, std::string> myMap;

	//open file
	inputFile.open(fileName.c_str());

	if (inputFile) {//if inputFile was opened correctly
		//parse inputFile to map
		while (std::getline(inputFile, line)){
			std::istringstream istring_line(line);
			std::string key;
			std::string value;
			if (std::getline(istring_line, key, '=')) {
				if (std::getline(istring_line, value)) {
					if (value[value.size()-1] == '\r') {
						value.erase(value.size()-1);
					}
					myMap[key] = value;
				}
			}
		}
	}
	else {//file was not opened correctly
		std::cout << fileName << " did not load correctly." << std::endl;
	}

	//close file
	inputFile.close();

	return myMap;
}




/***************************************************************************
**Function:  saveFile
**Description:  Opens or creates .txt save file based on path passed as string.
**				save map data to .txt save file, and closes file
**Parameters:  std::string fileName, std::map myMap
**Pre-Condition:  map exists and passed to function
**Post-Condition:  new save file is created or old save file is updated
**
**map output code based on the following source
**https://www.tutorialspoint.com/cpp_standard_library/cpp_map_end.htm
****************************************************************************/
void saveFile(std::string fileName, std::map<std::string, std::string> myMap) {
	//open or create output file
	std::ofstream outFile;
	outFile.open(fileName.c_str());

	if (outFile) {//if file opened correctly
		std::map<std::string, std::string>::iterator x;//declare iterator for loop
		//write values to file
		for (x = myMap.begin(); x != myMap.end(); x++) {
			outFile << x->first << "=" << x->second << std::endl;
		}
	}
	else {//if the file did not open
		std::cout << fileName << " did not save correctly." << std::endl;
	}

	//close file
	outFile.close();
}


/***************************************************************************
**Function:  loadItem
**Description:  Creates Item object based on .txt source file data
**Parameters:  std::string location
**Pre-Condition:  .txt source file exists
**Post-Condition:  new Item object is created and pointer is returned
****************************************************************************/
Item* loadItem(std::string location) {
	//declare variables
	std::map <std::string, std::string> tempMap;

	tempMap = loadFile(location);//load file data into tempMap

	Item* tempItem = new Item(tempMap["ID"], tempMap["Name"], tempMap["Description"], tempMap["roomDescription"], std::stoi(tempMap["Power"]), std::stoi(tempMap["Healing"]),
		std::stoi(tempMap["weapon"]), std::stoi(tempMap["roomFeature"]), std::stoi(tempMap["collectible"]));

	std::cout << tempItem->getID() << " Loaded" << std::endl;

	return tempItem;
}


/***************************************************************************
**Function:  loadRoom
**Description:  Creates Room object based on .txt source file data
**Parameters:  std::string location, map of Item pointers, map of string vectors by reference
**Pre-Condition:  .txt source file exists, itemMap has already been filled
**Post-Condition:  new Room object is created and pointer is returned
**		Also, will add adjacency list to map of string vectors
****************************************************************************/
Room* loadRoom(std::string location, std::map<std::string, Item*> itemMap, std::map<std::string, std::vector<std::string>> *adj) {
	//declare variables
	std::map<std::string, std::string> tempMap;
	std::map<std::string, std::string>::iterator it;//will be used to find Items in map
	std::vector<std::string> list;//will hold list of adjacent rooms to add to adj

	tempMap = loadFile(location);//load file data into tempMap

	Room* tempRoom = new Room;//create new Room with default constructor
	tempRoom->addDescriptions(tempMap["longDesc"], tempMap["shortDesc"]);//populate descriptions from tempMap
	tempRoom->setName(tempMap["Name"]);//set room name from map
	tempRoom->setID(tempMap["ID"]);//set room ID from map
	tempRoom->setVisited(std::stoi(tempMap["visited"]));//set room visited bool from map


	//Place items in Room
	//set map iterator to first item in map
	if (tempMap.count("Item01")) {
		it = tempMap.find("Item01");
		while (it->first.compare(0, 4, "Item") == 0) {
			std::string itemID = it->second;
			tempRoom->addItem(itemMap[itemID]);
			it++;
		}
	}


	//save adjacent Rooms to map of vectors to populate List later
	//List must be populated after all Rooms have been created
	//set map iterator to first adjacent room in map
	it = tempMap.find("adj0");
	while (it->first.compare(0, 3, "adj") == 0) {
		list.push_back(it->second);
		it++;
	}

	adj->insert(std::pair<string, std::vector<std::string>>(tempMap["ID"], list));

	std::cout << tempRoom->getID() << " Loaded" << std::endl;


	return tempRoom;
}


/***************************************************************************
**Function:  loadList
**Description:  Populates Room objects with neighbor Lists
**Parameters:  map of string vectors holding adjacency lists, map of existing Room pointers, vector of Room pointers
**Pre-Condition:  Rooms have been created, adjacency list has been filled
**Post-Condition:  Rooms have populated neighbor Lists
****************************************************************************/


void loadList(std::map<std::string, std::vector<std::string>> *adj, std::map<std::string, Room*> *roomMap){
	std::string curRoom;//will hold a string denoting the current room being worked on
	std::string adjRoom;//will hold string denoting an adjacent room to the current room
	std::map <std::string, Room*>::iterator it;//iterator for roomMap
	std::map <std::string, std::vector<std::string>>::iterator aI;//iterator for adj
	//loop through vector of Room* to fill adjacency lists
	for (it = roomMap->begin(); it != roomMap->end(); it++) {
		curRoom = it->first;//assign ID of Room being accessed to curRoom
		aI = adj->find(curRoom);
		List* tempList = new List;
		//loop through vector in adj
		//use ID for adj vector to place correct neighbors into rooms[x]
		for (int y = 0; y < aI->second.size(); y++) {
			adjRoom = aI->second[y];//place an adjacent room ID in adjRoom
			//std::cout << "adjRoom = " << adjRoom << std::endl;
			if (adjRoom.compare(0, 4, "NULL") != 0) {
				//std::cout << "in if statement" << std::endl;
				tempList->addAdjacent(y, roomMap->find(adjRoom)->second);
			}
		it->second->createNeighbors(tempList);
		}
	}
}


/***************************************************************************
**Function:  loadPlayer
**Description:  Creates Player object based on .txt source file data
**Parameters:  std::string location, map of Item pointers, map of Room pointers
**Pre-Condition:  .txt source file exists, itemMap has already been filled, Rooms have been created
**Post-Condition:  new Player object is created returned
****************************************************************************/
Player* loadPlayer(std::string location, const std::map<std::string, Room*> *rooms, std::map<std::string, Item*> itemMap) {
	//declare variables
	std::map <std::string, std::string> tempMap;
	std::map <std::string, std::string>::iterator it;//will be used to find Items in map

	tempMap = loadFile(location);//load file data into tempMap

	//call player constructor using tempMap to find current room from map of Room pointers
	Player* tempPlayer = new Player(rooms->at(tempMap["currentRoom"]), std::stoi(tempMap["health"]), std::stoi(tempMap["movesCompleted"]), std::stoi(tempMap["specialItemCount"]));

	std::cout << "Loading player items now" << std::endl;

	//Populate player inventory with Items
	//set map iterator to first item in map
	if (tempMap.count("Item01")) {
		it = tempMap.find("Item01");
		while (it->first.compare(0, 4, "Item") == 0) {
			std::string itemID = it->second;
			tempPlayer->addItem(itemMap[itemID]);
			it++;
		}
	}

	return tempPlayer;
}



/***************************************************************************
**Function:  loadWorld
**Description:  Control function to create World object, load all data for world from
**		files, and return World object to game engine
**Parameters:  std::string location
**Pre-Condition:  .txt source files exist
**Post-Condition:  new World object is created and returned
****************************************************************************/
World* loadWorld(std::string location) {

	std::cout << "Entered loadWorld" << std::endl << std::endl;

	//Declare Variables
	const int itemNum = 137;//set number of item files for array access - Will be 133 with full implementation
    const int roomNum = 62;//set number of room files for array access
	Item* tempItem;//will be used to temporarily store created items
	Room* tempRoom;//will be used to temporarily store created rooms
	Player *curPlayer;//to hold player object
	std::string fileLocation;//will hold file path for data loading
	std::map<std::string, Item*> itemMap;//will store Item pointers for assignment to Rooms
	std::map<std::string, Room*> roomMap;//will store Room pointers for assignment to World
	std::map<std::string, std::vector<std::string>> adj;//map of vectors to contain room neighbors prior to assigning Lists in Rooms
	std::string key;//used to set key values for maps
	std::vector<Room*> rmVect;
	std::vector<Item*> itemVect;
	World *gameWorld = new World;
	std::map <std::string, std::string>::iterator it;

	//create array holding list of all Item files
	//Update this list
    std::string itemList[] = {"Lead Pipe.txt", "normBusinesses.txt", "normCar.txt", "altBusinesses.txt", "altCar.txt", "normBarBodies.txt", "normTables.txt",
		"altTables.txt", "altSeats.txt", "normChurchSign.txt", "normChurchGate.txt", "altChurchSign.txt", "altChurchGate.txt", "normChurchBodies.txt",
		"normPulpit.txt", "altPews.txt", "altStainedGlass.txt", "normGravestone.txt", "normGrave.txt", "altGravestone.txt", "altGrave.txt", "normStonewall.txt",
		"normMausoleum.txt", "altStonewall.txt", "altMausoleum.txt", "normFor1Tree.txt", "normFor1Bodies.txt", "altFor1Tree.txt", "altWoodpile.txt",
		"normFor2Tree.txt", "normFor2Marks.txt", "altFor2Tree.txt", "altFor2Thicket.txt", "normCliff.txt", "normOcean.txt", "altCliff.txt", "altOcean.txt",
		"normMansGate.txt", "normBarnFeat.txt", "altMansGate.txt", "altBarnFeat.txt", "normTools.txt", "normBench.txt", "altTools.txt", "altBench.txt",
		"normStatues.txt", "normPorchSteps.txt", "altStatues.txt", "altPorchSteps.txt", "normPainting1.txt", "normPainting2.txt", "altPainting1.txt",
		"altPainting2.txt", "normBookshelves.txt", "normDesk.txt", "altBookshelves.txt", "altDesk.txt", "normFridge.txt", "normCounter.txt", "altFridge.txt",
		"altCounter.txt", "normTable.txt", "normChinaCab.txt", "altTable.txt", "altChinaCab.txt", "normServBeds.txt", "normBoxes.txt", "altServBeds.txt",
		"altBoxes.txt", "normTV.txt", "normFireplace.txt", "altTV.txt", "altFireplace.txt", "normBannister.txt", "normSteps.txt", "altBannister.txt", "altSteps.txt",
		"normMirror.txt", "normDoll.txt", "altMirror.txt", "altDoll.txt", "normTub.txt", "normBathSink.txt", "altTub.txt", "altBathSink.txt", "normWindow.txt",
		"normPainting3.txt", "altWindow.txt", "altPainting3.txt", "normShelves.txt", "normMop.txt", "altShelves.txt", "altMop.txt", "normKidsBed.txt",
		"normToyChest.txt", "altKidsBed.txt", "altToyChest.txt", "normWineRack.txt", "normDistDust.txt", "altCobwebs.txt", "altWineRack.txt", "normMarkings1.txt",
		"normScorchMarks1.txt", "altMarkings1.txt", "altTapestry1.txt", "normMarkings2.txt", "normScorchMarks2.txt", "altMarkings2.txt", "altTapestry2.txt",
		"normMarkings3.txt", "normHidOrnStatues.txt", "altMarkings3.txt", "altHidOrnStatues.txt", "normAltar.txt", "normIdol.txt", "altAltar.txt", "altIdol.txt",
		"normCobwebs.txt", "normHidStorShelves.txt", "altHidStorShelves.txt", "altHidChest.txt", "normCultBeds.txt", "normCultChests.txt", "altCultBeds.txt",
		"altCultChests.txt", "Tome.txt", "Axe.txt", "Bandaid.txt", "Salve.txt", "Trident.txt", "Molotov.txt", "Lighter.txt", "Rag.txt", "Whiskey.txt",
		"Ritual.txt", "Chips.txt", "Candybar.txt"};
	//create Item objects and store pointers in map
	for (int x = 0; x < itemNum; x++) {
		fileLocation = "./" + location + "/" + itemList[x];
		tempItem = loadItem(fileLocation);
		key = tempItem->getID();
		itemMap[key] = tempItem;
	}

	std::cout << "Items created" << std::endl << std::endl;

	//create array holding list of all Room files
	//Update this list
    std::string roomList[] = {"normMain.txt", "normBar.txt", "normChurchyard.txt", "normChurch.txt", "normCem1.txt", "normCem2.txt", "normForest1.txt",
		"normForest2.txt", "normForest3.txt", "normEntranceway.txt", "normBarn.txt", "normMansion.txt", "normFoyer.txt", "normLibrary.txt", "normKitchen.txt",
		"normDiningRm.txt", "normServant.txt", "normLivingRm.txt", "normStairs.txt", "normBed1.txt", "normBath.txt", "normHall.txt", "normStorage.txt",
		"normBed2.txt", "normCellar.txt", "normHidEntry.txt", "normHidHall.txt", "normHidOrnateHall.txt", "normLair.txt", "normHidStorage.txt", "normHidBeds.txt",
		"altMain.txt", "altBar.txt", "altChurchyard.txt", "altChurch.txt", "altCem1.txt", "altCem2.txt", "altForest1.txt",
		"altForest2.txt", "altForest3.txt", "altEntranceway.txt", "altBarn.txt", "altMansion.txt", "altFoyer.txt", "altLibrary.txt", "altKitchen.txt",
		"altDiningRm.txt", "altServant.txt", "altLivingRm.txt", "altStairs.txt", "altBed1.txt", "altBath.txt", "altHall.txt", "altStorage.txt",
		"altBed2.txt", "altCellar.txt", "altHidEntry.txt", "altHidHall.txt", "altHidOrnateHall.txt", "altLair.txt", "altHidStorage.txt", "altHidBeds.txt"};
	//create Room objects and store pointers in map
	for (int x = 0; x < roomNum; x++) {
		fileLocation = "./" + location + "/" + roomList[x];
		tempRoom = loadRoom(fileLocation, itemMap, &adj);
		key = tempRoom->getID();
		roomMap[key] = tempRoom;
	}

	std::cout << "Rooms created" << std::endl << std::endl;

	//Populate Room neighbor Lists
	loadList(&adj, &roomMap);

	std::cout << "Lists Loaded" << std::endl << std::endl;

	//create Player object
	fileLocation = "./" + location + "/player.txt";
	curPlayer = loadPlayer(fileLocation, &roomMap, itemMap);

	std::cout << "Player Loaded" << std::endl << std::endl;

	//place Room objects in vector
	std::map<std::string, Room*>::iterator i;
	for (i = roomMap.begin(); i != roomMap.end(); i++) {
		rmVect.push_back(i->second);
	}

	//create and populate world with all above loaded data
	std::map <std::string, std::string> tempMap;
	fileLocation = "./" + location + "/world.txt";
	tempMap = loadFile(fileLocation);

	gameWorld->setName(tempMap["Name"]);
	gameWorld->setDescription(tempMap["Description"]);
	gameWorld->setPlayer(curPlayer);
	gameWorld->setRealWorld(std::stoi(tempMap["realWorld"]));
	gameWorld->setAct(std::stoi(tempMap["act"]));
	gameWorld->createRooms(rmVect);

	//Populate world with listed items
	if (tempMap.count("Item01")) {
		it = tempMap.find("Item01");
		while (it->first.compare(0, 4, "Item") == 0) {
			std::string itemID = it->second;
			itemVect.push_back(itemMap[itemID]);
			it++;
			std::cout << itemMap[itemID]->getID() << " added to world" << std::endl << std::endl;
		}
	}
	gameWorld->createItems(itemVect);

	std::cout << "gameWorld loaded" << std::endl << std::endl;

	return gameWorld;
}


/***************************************************************************
**Function:  saveItem
**Description:  Save Item object data to .txt file
**Parameters:  Item object pointer
**Pre-Condition:  Item object exists
**Post-Condition:  new .txt file is created with Item data
****************************************************************************/
void saveItem(Item *tempItem) {
	std::map <std::string, std::string> tempMap;
	std::string saveLocation;
	tempMap["ID"] = tempItem->getID();
	tempMap["Name"] = tempItem->getName();
	tempMap["Description"] = tempItem->getDescription();
	tempMap["roomDescription"] = tempItem->getRoomDescription();
	tempMap["Power"] = std::to_string(tempItem->getPower());
	tempMap["Healing"] = std::to_string(tempItem->getHealing());
	tempMap["weapon"] = std::to_string(tempItem->getWeapon());
	tempMap["roomFeature"] = std::to_string(tempItem->getRoomFeature());
	tempMap["collectible"] = std::to_string(tempItem->getCollectible());
	saveLocation = "./save/" + tempItem->getID() + ".txt";
	saveFile(saveLocation, tempMap);
	return;
}


/***************************************************************************
**Function:  saveRoom
**Description:  Save Room object data to .txt file
**Parameters:  Room object pointer
**Pre-Condition:  Room object exists
**Post-Condition:  new .txt file is created with Room data
****************************************************************************/
void saveRoom(Room *tempRoom) {
	std::cout << "Creating " << tempRoom->getID() << std::endl;

	std::map <std::string, std::string> tempMap;
	std::string saveLocation;
	std::vector<Item*> itemVect;
	std::string itemNum;
	std::string adjNum;
	Room *adjRoom;
	List *neighbors;
	tempMap["ID"] = tempRoom->getID();
	tempMap["Name"] = tempRoom->getName();
	tempMap["longDesc"] = tempRoom->saveLongDesc();
	tempMap["shortDesc"] = tempRoom->saveShortDesc();
	tempMap["visited"] = std::to_string(tempRoom->getVisited());

	std::cout << "ID, Name, descriptions, and visited set" << std::endl;

	itemVect = tempRoom->getItems();//get vector of Items in Room
	for (int i = 1; i <= itemVect.size(); i++) {//initialized i to 1 and used <= to correctly create itemNum for key
		saveItem(itemVect[i-1]);//save all Items in room as separate .txt file
		if (i < 10) {//create key for map
			itemNum = "Item0" + std::to_string(i);
		}
		else {
			itemNum = "Item" + std::to_string(i);
		}
		//std::cout << "itemNum = " << itemNum << std::endl;
		tempMap[itemNum] = itemVect[i-1]->getID();//set map value to Item ID
	}

	std::cout << "Items set" << std::endl;

	//get adjacent rooms
	neighbors = tempRoom->getNeighbors();
	for (int i = 0; i < 6; i++) {
		adjNum = "adj" + std::to_string(i);
		adjRoom = neighbors->getAdjName(i);//actually returns a room pointer
		if (adjRoom != NULL) {
			tempMap[adjNum] = adjRoom->getID();
		}
		else {
			tempMap[adjNum] = "NULL";
		}
	}

	std::cout << "Adjacent Rooms Set" << std::endl;

	saveLocation = "./save/" + tempRoom->getID() + ".txt";
	saveFile(saveLocation, tempMap);

	std::cout << "Room saved" << std::endl << std::endl;
}


/***************************************************************************
**Function:  savePlayer
**Description:  Save Player object data to .txt file
**Parameters:  Player object
**Pre-Condition:  Player object exists
**Post-Condition:  new .txt file is created with Player data
****************************************************************************/
void savePlayer(Player *tempPlayer) {
	std::map <std::string, std::string> tempMap;
	std::string saveLocation = "./save/player.txt";
	std::vector<Item*> itemVect;
	std::string itemNum;
	tempMap["health"] = std::to_string(tempPlayer->getHealth());
	tempMap["movesCompleted"] = std::to_string(tempPlayer->getMovesCompleted());
	tempMap["specialItemCount"] = std::to_string(tempPlayer->getSpecialItemCount());
	itemVect = tempPlayer->getItems();//get vector of Items in Room
	for (int i = 1; i <= itemVect.size(); i++) {//initialized i to 1 and used <= to correctly create itemNum for key
		saveItem(itemVect[i-1]);//save all Items in room as separate .txt file
		if (i < 10) {//create key for map
			itemNum = "Item0" + std::to_string(i);
		}
		else {
			itemNum = "Item" + std::to_string(i);
		}
		tempMap[itemNum] = itemVect[i-1]->getID();//set map value to Item ID
	}
	tempMap["currentRoom"] = tempPlayer->getCurrentRoom()->getID();
	saveFile(saveLocation, tempMap);
}

/***************************************************************************
**Function:  saveWorld
**Description:  Control function to save all world data
**Parameters:  World object
**Pre-Condition:  World object exists
**Post-Condition:  new .txt files are created with all World data
****************************************************************************/
void saveWorld(World *gameState) {
	std::map <std::string, std::string> tempMap;
	std::string saveLocation = "./save/world.txt";
	std::vector<Room*> rmVect;
	std::vector<Item*> itemVect;
	std::string itemNum;

	std::cout << "Now saving game" << std::endl << std::endl;

	//Save items stored in world object
	itemVect = gameState->getItems();
	for (int i = 1; i <= itemVect.size(); i++) {
		saveItem(itemVect[i-1]);
		if (i < 10) {//create key for map
			itemNum = "Item0" + std::to_string(i);
		}
		else {
			itemNum = "Item" + std::to_string(i);
		}
		tempMap[itemNum] = itemVect[i-1]->getID();//set map value to Item ID
	}

	std::cout << "Items Saved" << std::endl << std::endl;

	//Place data in map for World attributes and save to file
	tempMap["Name"]=gameState->getName();
	tempMap["Description"]=gameState->getDescription();
	tempMap["realWorld"]=std::to_string(gameState->getRealWorld());
	tempMap["act"]=std::to_string(gameState->getAct());
	saveFile(saveLocation, tempMap);

	//Save room data
	rmVect = gameState->getRooms();
	for (int i = 0; i < rmVect.size(); i++) {
		saveRoom(rmVect[i]);
	}

	//Save player data
	savePlayer(gameState->getPlayer());

}
