#include <string>
#include <iostream>
#include <algorithm>
#include "CETUS_Room.hpp"
#include "CETUS_List.hpp"
#include "CETUS_Items.hpp"
#include "CETUS_Player.hpp"


using std::endl;
using std::cout;
using std::cin;
using std::string;

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3
#define UP 4
#define DOWN 5

int main(){
	
	//test run to display data structure and room class
	
	cout<<"Welcome to the short demo of the CETUS command line adventure game!\n\nToday, we will be demonstrating the List data structure that keeps track of all the adjacent rooms \n\nfor each room, as well as showing the details of the Room class\n\nLet's begin!\n"<<endl;
	
	
	Player Matt = Player();
		
	cout<<"Thanks for checking out the demo! Stay tuned for much more in the weeks to come!"<<endl;
	
	return 0;
	
}