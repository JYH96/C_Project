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
        cout << "�ָ� - ����: " << spac << " �ʴ� " << apm << "ȸ�� ���� �ǽ�" << endl;
    }
};

class Sword : public Weapon {
public:
    Sword() {
        spac = 3;
        apm = 3;
    }

    void attack() override {
        cout << "��� - ����: " << spac << " �ʴ� " << apm << "ȸ�� ���� �ǽ�" << endl;
    }
};

class Gun : public Weapon {
public:
    Gun() {
        spac = 10;
        apm = 1;
    }

    void attack() override {
        cout << "�ѽ�� - ����: " << spac << " �ʴ� " << apm << "ȸ�� ���� �ǽ�" << endl;
    }
};

class Character {
public:
    int hp, level;
    string name = "����";
    Weapon weapon = Weapon();

    Character(int h = 10, int l = 1) : hp(h), level(l) {}

    void grab(Weapon x) {
        weapon=x;
    }

    void losthp(int x) {
        cout << x << "�� ������" << endl;
        hp -= x;
    }
};
bool fight(Character A, Character B);
int main() {
    Character player;
    cout << "ĳ���͸� �����մϴ�." << endl << "ĳ���͸��� �Է����ּ���." << endl;
    cin >> player.name;

    cout << "�ѷ� ����" << endl;
    Character �ѷ�(5, 1);
    �ѷ�.name = "�ѷ�";

    cout << "������ �����մϴ�." << endl;
    cout << player.name << "�� �ָ��� �� ���.." << endl;
    cout << �ѷ�.name << "�� �ָ��� �� ���.." << endl;
   
    cout << "�����մϴ�." << endl;
    fight(player, �ѷ�);

    cout << "���ο� ���⸦ �����." << endl;
    player.weapon = Sword();
    cout << "�߰�ü���� �����." << endl;
    player.hp += 10;
    cout << "���� ����" << endl;
    Character ����(10, 1);
    ����.name = "����";
    ����.weapon = Sword();
    fight(player, ����);
    return 0;
}

bool fight(Character A, Character B) {
    while (A.hp > 0 && B.hp > 0) {
        cout << A.name << "�� ����!!!" << endl;
        for (int i = 0; i < A.weapon.apm; i++) {
            A.weapon.attack();
            B.losthp(A.weapon.spac);
        }
        cout << B.name<<"�� ���� ü��: " << B.hp << endl;
        cout << B.name << "�� ����!!!" << endl;
        for (int i = 0; i < B.weapon.apm; i++) {
            B.weapon.attack();
            A.losthp(B.weapon.spac);
        }
        cout << A.name << "�� ���� ü��: " << A.hp << endl;
    }
    if (A.hp > B.hp) {
        cout << A.name << " �¸�" << endl;
        return true;
    }
    else {
        cout << A.name << " �й�" << endl;
        return false;
    }
}