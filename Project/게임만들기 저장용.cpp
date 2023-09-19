#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Weapon {
public:
    int spac = 1;
    int apm = 1;
    string name = "���ָ�";
    Weapon() {}
    virtual void effect() {
        cout << "��" << endl;
    }

    virtual void attack() {
        cout << "��ġ - ����: " << spac << " �ʴ� " << apm << "ȸ�� ���� �ǽ�" << endl;
    }
};

class Sword : public Weapon {
public:
    Sword() {
        spac = 3;
        apm = 3;
        name = "��ù�";
    }
    void effect() {
        cout << "��" << endl;
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
        name = "������";
    }
    void effect() {
        cout << "��" << endl;
    }
    void attack() override {
        cout << "�ѽ�� - ����: " << spac << " �ʴ� " << apm << "ȸ�� ���� �ǽ�" << endl;
    }
};
class Character {
public:
    int hp, level;
    string name = "����";
    Weapon* weapon = new Weapon();

    Character(int h = 10, int l = 1) : hp(h), level(l) {}

    void grab(Weapon* x) { // �Ķ���� Ÿ���� Weapon*�� ����
        weapon = x; // �����͸� ���� �Ҵ�
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
    Weapon* get = new Sword();
    player.grab(get);
    cout << "�߰�ü���� �����." << endl;
    player.hp += 10;
    cout << "���� ����" << endl;
    Character ����(10, 1);
    ����.name = "����";
    ����.weapon = new Sword();
    fight(player, ����);
    return 0;
}

bool fight(Character A, Character B) {
    cout << endl;
    while (A.hp > 0 && B.hp > 0) {
        cout << A.name << "�� ����!!!" << endl;
        A.weapon->attack();
        for (int i = 0; i < A.weapon->apm; i++) {
            A.weapon->effect();
            B.losthp(A.weapon->spac);
        }
        cout << B.name << "�� ���� ü��: " << B.hp << endl;
        cout << B.name << "�� ����!!!" << endl;
        B.weapon->attack();
        for (int i = 0; i < B.weapon->apm; i++) {
            B.weapon->effect();
            A.losthp(B.weapon->spac);
        }
        cout << A.name << "�� ���� ü��: " << A.hp << endl;
    }
    cout << endl;
    if (A.hp > B.hp) {
        cout << A.name << " �¸�" << endl;
        return true;
    }
    else {
        cout << A.name << " �й�" << endl;
        return false;
    }
}