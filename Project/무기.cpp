#include "����.h"
#include <iostream>
using namespace std;
void Weapon::effect() {
    std::cout << "��" << std::endl;
}

void Weapon::attack() {
    std::cout << "��ġ - ����: " << spac << " �ʴ� " << apm << "ȸ�� ���� �ǽ�" << std::endl;
}

Sword::Sword() {
    spac = 3;
    apm = 3;
    name = "��ù�";
}

void Sword::effect() {
    std::cout << "��" << std::endl;
}

void Sword::attack() {
    std::cout << "��� - ����: " << spac << " �ʴ� " << apm << "ȸ�� ���� �ǽ�" << std::endl;
}

Gun::Gun() {
    spac = 10;
    apm = 1;
    name = "������";
}

void Gun::effect() {
    std::cout << "��" << std::endl;
}

void Gun::attack() {
    std::cout << "�ѽ�� - ����: " << spac << " �ʴ� " << apm << "ȸ�� ���� �ǽ�" << std::endl;
}