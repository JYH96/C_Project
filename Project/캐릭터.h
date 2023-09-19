#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "¹«±â.h"
#include <string>
using namespace std;
class Character {
public:
    int hp, level;
    std::string name = "Á¹°³";
    Weapon* weapon;

    Character(int h = 10, int l = 1);

    void grab(Weapon* x);

    void losthp(int x);

    bool fight(Character B);
};