#include <iostream>
#include <string>
#include <vector>
#include "����.h"
#include "ĳ����.h"
using namespace std;


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

