#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Weapon {
public:
    int spac = 1;
    int apm = 1;
    string name = "맨주먹";
    Weapon() {}
    virtual void effect() {
        cout << "퍽" << endl;
    }

    virtual void attack() {
        cout << "펀치 - 딜량: " << spac << " 초당 " << apm << "회의 공격 실시" << endl;
    }
};

class Sword : public Weapon {
public:
    Sword() {
        spac = 3;
        apm = 3;
        name = "사시미";
    }
    void effect() {
        cout << "퓩" << endl;
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
        name = "리볼버";
    }
    void effect() {
        cout << "탕" << endl;
    }
    void attack() override {
        cout << "총쏘기 - 딜량: " << spac << " 초당 " << apm << "회의 공격 실시" << endl;
    }
};
class Character {
public:
    int hp, level;
    string name = "졸개";
    Weapon* weapon = new Weapon();

    Character(int h = 10, int l = 1) : hp(h), level(l) {}

    void grab(Weapon* x) { // 파라미터 타입을 Weapon*로 변경
        weapon = x; // 포인터를 직접 할당
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
    Weapon* get = new Sword();
    player.grab(get);
    cout << "추가체력을 얻었다." << endl;
    player.hp += 10;
    cout << "협객 등장" << endl;
    Character 협객(10, 1);
    협객.name = "협객";
    협객.weapon = new Sword();
    fight(player, 협객);
    return 0;
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