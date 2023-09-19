#include "무기.h"
#include <iostream>
using namespace std;
void Weapon::effect() {
    std::cout << "퍽" << std::endl;
}

void Weapon::attack() {
    std::cout << "펀치 - 딜량: " << spac << " 초당 " << apm << "회의 공격 실시" << std::endl;
}

Sword::Sword() {
    spac = 3;
    apm = 3;
    name = "사시미";
}

void Sword::effect() {
    std::cout << "퓩" << std::endl;
}

void Sword::attack() {
    std::cout << "찌르기 - 딜량: " << spac << " 초당 " << apm << "회의 공격 실시" << std::endl;
}

Gun::Gun() {
    spac = 10;
    apm = 1;
    name = "리볼버";
}

void Gun::effect() {
    std::cout << "탕" << std::endl;
}

void Gun::attack() {
    std::cout << "총쏘기 - 딜량: " << spac << " 초당 " << apm << "회의 공격 실시" << std::endl;
}