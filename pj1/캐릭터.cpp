#include "캐릭터.h"
#include "무기.h"
#include <iostream>
using namespace std;
Character::Character(int h, int l) : hp(h), level(l) {
    weapon = new Weapon();
}

void Character::grab(Weapon* x) {
    weapon = x;
}

void Character::losthp(int x) {
    std::cout << x << "의 데미지" << std::endl;
    hp -= x;
}

bool fight(Character A, Character B) {
    cout << endl;
    while (A.hp > 0 && B.hp > 0) {
        cout << A.name << "의 공격!!!" << endl;
        A.weapon->attack();
        for (int i = 0; i < A.weapon->apm; i++) {
            A.weapon->effect();
            B.losthp(A.weapon->spac);
        }
        cout << B.name << "의 남은 체력: " << B.hp << endl;
        cout << B.name << "의 공격!!!" << endl;
        B.weapon->attack();
        for (int i = 0; i < B.weapon->apm; i++) {
            B.weapon->effect();
            A.losthp(B.weapon->spac);
        }
        cout << A.name << "의 남은 체력: " << A.hp << endl;
    }
    cout << endl;
    if (A.hp > B.hp) {
        cout << A.name << " 승리" << endl;
        return true;
    }
    else {
        cout << A.name << " 패배" << endl;
        return false;
    }
}