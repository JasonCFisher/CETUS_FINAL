#include "battle.hpp"
const std::string red("\033[0;31m");
const std::string green("\033[1;32m");
const std::string yellow("\033[1;33m");
const std::string cyan("\033[0;36m");
const std::string magenta("\033[0;35m");
const std::string reset("\033[0m");

using std::cin;
using std::cout;
using std::endl;
using std::string;

void printLogo();
void ClearScreen();
void cetusPrint(string* temp, int color);

int battle(Player *p1, Creature* c2, int modifier, int escaping){
    int atkValue;
	cout << red;
    if(!escaping){
        cout << red << "You attack!" << endl;
        atkValue = rand()%20+1+modifier;
        c2->defense(atkValue);
        
        if(c2->isDead(0)){
            cout << endl << "The " << c2->getName() << " was defeated!" << endl;
            if(c2->getName() == "Cetus"){
                gameEnd();
            }
            return 1;
        }
    }
        cout << red << endl << "The " << c2->getName() << " attacks!" << endl;
        atkValue = c2->attack();
        if(atkValue > 12){
        	p1->damagePlayer(rand()%5+(atkValue/2));
        } else {
            cout << red << "Its attack missed!\n";
        }
        
        if(p1->getHealth() <= 0){
            cout << red << "You died!" << endl;
            string temp = "The world swirls about you and goes black.  You thought you had something important to do, but the recollection fades.  You realize your eyes were closed, which was bad, since you were driving.  \"I must need some sleep\" you think as you continue.  As if in response, a sign appears from around a turn, \"Schuykill - 5 miles\".\n";
            cetusPrint(&temp, 0);
            return 0;
        }
    return 1;
}


void randomEnemyGenerator(Room* room, int act){
    srand(time(0));
    Creature* newCreat = NULL;
    if(act > 1){
        if(room->getName() == "Forest3" && room->hasEnemy() == 0 && act==4){
            newCreat = new Cetus();
            room->setEnemy(newCreat);
        } else if(room->hasEnemy()==0 && room->getName()!="forest3" && room->getName() != "lair"){
            
            int choice = rand()%10 + 1;
            if(choice < 6){
                room->setEnemy(NULL);
            } else if(choice == 6){
                newCreat= new Ghost();
            } else if(choice == 7){
                newCreat = new Cultist();
            } else if(choice == 8){
                newCreat = new Merman();
            } else {
                return;
            }
            room->setEnemy(newCreat);
        }
    }
    return;
}

void makeMolotov(World* world){
    
    if(world->getCurrentRoom()->getName() == "Forest2" &&
       world->findItem("lighter",0) != NULL &&
       world->findItem("rag",0)!=NULL &&
       world->findItem("whiskey",0)!=NULL){
        
        //drop items
        world->findItem("lighter",1);
        world->findItem("rag",1);
        world->findItem("whiskey",1);
        
    }
}

void throwMolotov(World* world){
	cout << red;
    std::string thrownMolotov = "\n\nWith a mighty hurl, the bottle flips end over end toward the creature.  With the barely audible\n cracking of glass, fire jumps across the alcohol and onto the creature.  It's less than impressive - for a second.  With insane speed, the flames spread, almost unnaturally, across the creature's form.  Then *poof* gone.  The creature looks weakened from the exposure.\n";
    //cout << thrownMolotov;
    cetusPrint(&thrownMolotov, 0); 
	world->getCurrentRoom()->getEnemy()->setBurned();
    world->destroyItem("Molotov Cocktail");
    return;
}

void gameEnd(){
    std::string endString = "\n\nWith the final blow, the creature arches back in pain.  With increasing convulsions, Cetus twists and reels, until its entire body is rigid and shaking.  With a sickening, wet sound, the creature explodes, its entrails covering the entire area...including you and your daughter.  Off to the side, your daughter lies limp, still hanging from the chains.   Running to her aid, you find she is still breathing and just barely conscious. With little effort, you are able to free her from the chains and carry her back towards town in your arms.\n\nThe walk back to the town reveals just how far the creature's pieces were thrown.  As you approach the town with your daughter, cheers erupt from the sidewalks around Main Street.  Buildings and cars are speckled with Cetus meat, and some people are completely covered in goo.You take your daughter and head back to your vehicle, with the crowd swarming you and your vehicle - singing your praises.  As you get in and drive away, someone in the crowd yells \"I love this town!\" and laughs heartily.\n";
    //cout << endString;
	cetusPrint(&endString, 0);
    cout << cyan << "\n\nYOU HAVE COMPLETED THE CETUS MYSTERY AND SAVED YOUR DAUGHTER!\n\nTHANK YOU FOR PLAYING!\n";
    exit(0);
}
