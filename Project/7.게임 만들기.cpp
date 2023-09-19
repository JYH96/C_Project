#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Weapon {
public:
    int spac = 1;
    int apm = 1;

    Weapon() {}

    virtual void attack() {
        cout << "주먹 - 딜량: " << spac << " 초당 " << apm << "회의 공격 실시" << endl;
    }
};

class Sword : public Weapon {
public:
    Sword() {
        spac = 3;
        apm = 3;
    }

    void attack() override {
        cout << "찌르기 - 딜량: " << spac << " 초당 " << apm << "회의 공격 실시" << endl;
    }
};

class Gun : public Weapon {
public:
    Gun() {
        spac = 10;
        apm = 1;
    }

    void attack() override {
        cout << "총쏘기 - 딜량: " << spac << " 초당 " << apm << "회의 공격 실시" << endl;
    }
};

class Character {
public:
    int hp, level;
    string name = "졸개";
    Weapon weapon = Weapon();

    Character(int h = 10, int l = 1) : hp(h), level(l) {}

    void grab(Weapon x) {
        weapon=x;
    }

    void losthp(int x) {
        cout << x << "의 데미지" << endl;
        hp -= x;
    }
};
bool fight(Character A, Character B);
int main() {
    Character player;
    cout << "캐릭터를 생성합니다." << endl << "캐릭터명을 입력해주세요." << endl;
    cin >> player.name;

    cout << "한량 등장" << endl;
    Character 한량(5, 1);
    한량.name = "한량";

    cout << "전투를 시작합니다." << endl;
    cout << player.name << "은 주먹을 꽉 쥔다.." << endl;
    cout << 한량.name << "도 주먹을 꽉 쥔다.." << endl;
   
    cout << "공격합니다." << endl;
    fight(player, 한량);

    cout << "새로운 무기를 얻었다." << endl;
    player.weapon = Sword();
    cout << "추가체력을 얻었다." << endl;
    player.hp += 10;
    cout << "협객 등장" << endl;
    Character 협객(10, 1);
    협객.name = "협객";
    협객.weapon = Sword();
    fight(player, 협객);
    return 0;
}

bool fight(Character A, Character B) {
    while (A.hp > 0 && B.hp > 0) {
        cout << A.name << "의 공격!!!" << endl;
        for (int i = 0; i < A.weapon.apm; i++) {
            A.weapon.attack();
            B.losthp(A.weapon.spac);
        }
        cout << B.name<<"의 남은 체력: " << B.hp << endl;
        cout << B.name << "의 공격!!!" << endl;
        for (int i = 0; i < B.weapon.apm; i++) {
            B.weapon.attack();
            A.losthp(B.weapon.spac);
        }
        cout << A.name << "의 남은 체력: " << A.hp << endl;
    }
    if (A.hp > B.hp) {
        cout << A.name << " 승리" << endl;
        return true;
    }
    else {
        cout << A.name << " 패배" << endl;
        return false;
    }
}