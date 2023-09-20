#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Weapon {
public:
    int spac = 1;
    int apm = 1;
    std::string name = "∏«¡÷∏‘";

    Weapon() {}

    virtual void effect();

    virtual void attack();
};

class Sword : public Weapon {
public:
    Sword();

    void effect() override;
    void attack() override;
};

class Gun : public Weapon {
public:
    Gun();

    void effect() override;
    void attack() override;
};