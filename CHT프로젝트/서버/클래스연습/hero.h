#ifndef HERO_H


#define HERO_H
#include <string>
using namespace std;



class Hero

{

    string name;

    short HP;


public:

    Hero();

    Hero(string name, short HP);

    void info();

    void set_info(string name, short HP);

};




#endif