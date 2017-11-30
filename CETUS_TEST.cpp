#define BOOST_TEST_MAIN MyTest
#include <boost/test/included/unit_test.hpp>
//#include <boost/log/utility/setup/console.hpp>
#include "CETUS_World.hpp"
#include "CETUS_List.hpp"
//#include "CETUS_Room.hpp"
//#include "CETUS_Items.hpp"
#include "CETUS_Player.hpp"
#include <iostream>

/*struct TestFixture{
	
	World testWorld;
	TestFixture() : testWorld(){}
	~TestFixture() = default;
};*/

//BOOST_FIXTURE_TEST_SUITE(testWorld, TestFixture);

BOOST_AUTO_TEST_CASE(World_Test){
	//adding test log to record all messages that appear on the the console
	//http://www.boost.org/doc/libs/1_54_0/libs/log/doc/html/boost/log/add_console_lo_idp21543664.html
	//logging::add_console_log(std::cout, boost::log::keywords::format = ">> %Message%");
	
	World* testWorld= new World();
	testWorld->setName("tests");
	testWorld->setDescription("test world description");
	testWorld->setRealWorld(false);
		
	BOOST_CHECK_EQUAL("test", testWorld->getName());
	BOOST_CHECK_EQUAL("test description", testWorld->getDescription());
	BOOST_CHECK_EQUAL(1, testWorld->getAct());
	testWorld->incrementAct();
	BOOST_CHECK_EQUAL(3, testWorld->getAct());
	std::cout << "\n\n";
	delete testWorld;
	
}

BOOST_AUTO_TEST_CASE(Player_Test){
	
	Player* currentPlayer = new Player();
	BOOST_CHECK_EQUAL(currentPlayer->getHealth(), 0);
	BOOST_CHECK_EQUAL(currentPlayer->getMovesCompleted(), 1);
	BOOST_CHECK_EQUAL(currentPlayer->getSpecialItemCount(), 1);
	
	currentPlayer->setHealth(50);
	currentPlayer->setMovesCompleted(5);
	currentPlayer->setSpecialItemCount(6);
	
	BOOST_CHECK_EQUAL(currentPlayer->getHealth(), 50);
	BOOST_CHECK_EQUAL(currentPlayer->getMovesCompleted(), 5);
	BOOST_CHECK_EQUAL(currentPlayer->getSpecialItemCount(), 6);
	BOOST_CHECK_EQUAL(currentPlayer->getHealth(), 100);
	BOOST_CHECK_EQUAL(currentPlayer->getMovesCompleted(), 1);
	BOOST_CHECK_EQUAL(currentPlayer->getSpecialItemCount(), 1);
	
	currentPlayer->incrementMoves();
	BOOST_CHECK_EQUAL(currentPlayer->getMovesCompleted(), 50);
	
	currentPlayer->decrementMoves();
	BOOST_CHECK_EQUAL(currentPlayer->getMovesCompleted(), 51);
	std::cout << "\n\n";
	delete currentPlayer;
}

BOOST_AUTO_TEST_CASE(Room_Test){
	
	Room* currentRoom = new Room();
	currentRoom->setName("test room");
	currentRoom->addDescriptions("test room long description", "test room short");
	currentRoom->setVisited(false);
	currentRoom->setID("1");
	
	BOOST_CHECK_EQUAL(currentRoom->getName(), "wrong test name");
	BOOST_CHECK_EQUAL(currentRoom->saveLongDesc(), "wrong test long");
	BOOST_CHECK_EQUAL(currentRoom->saveShortDesc(), "wrong test short");
	BOOST_CHECK_EQUAL(currentRoom->getVisited(), true);
	BOOST_CHECK_EQUAL(currentRoom->getID(), "2");
	std::cout << "\n\n";
	//delete currentRoom;
	
	
	
}

BOOST_AUTO_TEST_CASE(Item_Test){
	
	Item* currentItem = new Item("1", "item", "test item", "test room", 100, 100, false, false, false);
	BOOST_CHECK_EQUAL(currentItem->getID(), "2");
	BOOST_CHECK_EQUAL(currentItem->getName(), "items");
	BOOST_CHECK_EQUAL(currentItem->getDescription(), "test");
	BOOST_CHECK_EQUAL(currentItem->getRoomDescription(), "room");
	BOOST_CHECK_EQUAL(currentItem->getPower(), 10);
	BOOST_CHECK_EQUAL(currentItem->getHealing(), 10);
	BOOST_CHECK_EQUAL(currentItem->getWeapon(), true);
	BOOST_CHECK_EQUAL(currentItem->getCollectible(), true);
	BOOST_CHECK_EQUAL(currentItem->getRoomFeature(), true);
	
	std::cout << "\n\n";
}
