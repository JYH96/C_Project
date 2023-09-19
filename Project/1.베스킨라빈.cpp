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
			cout << endl << "컴퓨터가 말한 갯수: " << num << endl;
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
		cout << "인간의 승리";
	}
	else {
		cout << "인간의 패배";
	}
}


int rannum() {
	std::random_device rd;
	std::mt19937 gen(rd()); // 메르센 트위스터 엔진을 사용하여 무작위 수 생성

	// 난수 범위 설정
	std::uniform_int_distribution<int> distribution(1, 3);

	// 난수 생성 및 출력
	int random_number = distribution(gen);

	return random_number;
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