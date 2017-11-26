
#ifndef creature_class
#define creature_class

#include <string>
//#include "CETUS_Items.hpp"
using std::string;

class Creature{
    
private:
    
protected:
    
    int armor;
    int health;
    string name;
    string desc;
    
    
public:
    Creature(int, int, string);
    virtual ~Creature();
    virtual int attack();
    virtual void defense(int);
    virtual string getName() = 0;  //True virtual function
    virtual bool isDead(int);
    virtual void adjName(string);
    virtual void getDesc() = 0;
    virtual void getRoomDesc() = 0;
    friend bool operator==(Creature&, Creature&);
    virtual void healme(int);
    virtual int getHP();
    virtual void setBurned() = 0;
    virtual int getBurned() = 0;
};

#endif 
