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
    gameWorld = loadWorld("source");
	gameWorld->ClearScreen();
    gameWorld->printLogo();
	std::cout << "After a solid day of driving, you're finally getting close to Schuylkill, Maine late into the night.  You smile to yourself remembering the last call you got from Amy - you've never heard your daughter so excited.  She's rented an old, historic house on the outskirts of town where she can stay while she's studying the rare red tide that suddenly hit the coast at the town.  You can't wait to finish the drive and see her.\n\nYou're driving down Main Street Schuylkill and getting close to the house Amy's rented when you start to realize that things don't quite look right.  It's too dark and quiet, even for this time of night.  Most of the lights are out, including the streetlights, but if you look closely you can just make out what looks like lumps on the sidewalks and up against the few cars parked on the street.  If it weren't so dark, you'd swear that most of the shops have had their windows broken.  You're looking so intently to pierce the gloom on the side of the road that you almost don't see something run out in front of your car.  You swerve wildly to miss it, lose control, and smash head first into a parked car.  The world goes black for a while...\n\nYou come to with the airbag in your face.  Your body feels like one huge bruise.  As you pull yourself out of the car, you realized in a detached way that your phone is buzzing with a new message." << std::endl << std::endl;

    parser(gameWorld);

	return 0;
}
