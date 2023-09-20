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
			cout << endl << "컴퓨터가 말한 갯수: " << num << endl;
			num31 = playgame(num, num31);
			cout << endl;
			player_turn = true;
		}
		
	}
	if (player_turn == true) {
		cout << "인간의 승리";
	}
	else {
		cout << "인간의 패배";
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
	cout << "갯수를 입력하세요: ";
	cin >> num;
	if (num >= 1 && num < 4) {
		return num;
	}
	else {
		cout << "1~3의 수를 입력해주세요." << endl << endl;
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