#include "battle.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::string;

void battle(Player *p1, Creature* c2, int modifier){
    int atkValue;
    int ignore = 0;
    
    while (ignore < 1){
        cout << endl << p1->getName() << " attacks!" << endl;
        atkValue = rand()%20+1+modifier;
        cout << "Atk: " << atkValue << endl;
        c2->defense(atkValue);
        
        if(c2->isDead(1)){
            cout << endl << c2->getName() << " has died!" << endl;
            cout << p1->getName() << " wins!" << endl;
            return;
        }
        
        cout << endl << c2->getName() << " attacks!" << endl;
        atkValue = c2->attack();
        cout << "Atk: " << atkValue << endl;
        if(atkValue > 12){
        	p1->damagePlayer(10);
        }
        
        if(p1->getHealth() <= 0){
            cout << endl << p1->getName() << " has died!" << endl;
            cout << c2->getName() << " wins!" << endl;
            return;
        }
    }
}


//battle test code
/*int main(){
    srand(time(0));
    Player* player = new Player;
    Creature* ghost1 = new Ghost;


    battle(player, ghost1, 0);
    return 0;


}*/
