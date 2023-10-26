#include <iostream>


using namespace std;


#include "hero.h"





Hero::Hero() {} // when there's no parameter

Hero::Hero(string name, short HP) // overloading constructor based on params

{

    this->name = name;

    this->HP = HP;

}




void Hero::info()

{

    cout << "--------------------" << endl;

    cout << "name: " << this->name << endl;

    cout << "HP: " << this->HP << endl;

}




void Hero::set_info(string name, short HP)

{

    this->name = name;

    this->HP = HP;

}