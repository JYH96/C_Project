#include <iostream>
#include <random>'
#include <vector>
using namespace std;

int rannum();
int getnum();
int playgame(int num, int num31);

int main() {
	bool player_turn = true;
	int num;
	int num31 = 0;

	while (num31 != 31) {
		if (player_turn == true) {
			num = getnum();
			num31 = playgame(num, num31);
			player_turn = false;
		}
		else {
			num = rannum();
			cout << endl << "��ǻ�Ͱ� ���� ����: " << num << endl;
			num31 = playgame(num, num31);
			cout << endl;
			player_turn = true;
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
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(1, 3);

	int rannum = distribution(gen);
	return rannum;
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