/****************************************************************************
**Program Filename:  main.cpp
**Author:  Jason Fisher
**Date:  10/6/2017
**Description:  Used to initiate and run game
****************************************************************************/
#include "CETUS_data.hpp"
const std::string red("\033[0;31m");
const std::string green("\033[1;32m");
const std::string yellow("\033[1;33m");
const std::string cyan("\033[0;36m");
const std::string magenta("\033[0;35m");
const std::string reset("\033[0m");

int parser(World*);

int main() {
	


	World* gameWorld;
	gameWorld->ClearScreen();
    gameWorld->printLogo();
    gameWorld = loadWorld("source");

    parser(gameWorld);

	return 0;
}
