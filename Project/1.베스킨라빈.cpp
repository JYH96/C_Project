#include <iostream>
#include <random>'
#include <vector>
using namespace std;

int rannum();

int getnum();

int playgame(int num,int num31);

int main() {
	bool player_turn = true;
	int num;
	int num31 = 0;

	while (true) {
		if (player_turn == true) {
			num=getnum();
			for (int i = 0; i < num && num31!=31; i++) {
				num31++;
				cout << num31 << endl;
			}
			player_turn = false;
		}
		else {
			num = rannum();
			cout << endl << "��ǻ�Ͱ� ���� ����: " << num << endl;
			for (int i = 0; i < num && num31 != 31; i++) {
				num31++;
				cout << num31 << endl;
			}
			cout << endl;
			player_turn = true;
		}
		if (num31 == 31) {
			break;
		}
	}
	if (player_turn == true) {
		cout << "�ΰ��� �¸�";
	}
	else {
		cout << "�ΰ��� �й�";
	}
}


int rannum() {
	std::random_device rd;
	std::mt19937 gen(rd()); // �޸��� Ʈ������ ������ ����Ͽ� ������ �� ����

	// ���� ���� ����
	std::uniform_int_distribution<int> distribution(1, 3);

	// ���� ���� �� ���
	int random_number = distribution(gen);

	return random_number;
}

int getnum() {
	int num;
	cout << "������ �Է��ϼ���: ";
	cin >> num;
	if (num >= 1 && num < 4) {
		return num;
	}
	else {
		cout << "1~3�� ���� �Է����ּ���." << endl << endl;
		getnum();
	}
}

int playgame(int num, int num31) {
	for (int i = 0; i < num && num31 != 31; i++) {
		num31++;
		cout << num31 << endl;
	}
	return num31;
}