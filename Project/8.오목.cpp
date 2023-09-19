#include <iostream>
#include <vector>
#include <string>
using namespace std;

void matrixprint(vector<vector <int>> board);
int 가로체크(vector<vector <int>> board);
vector<vector <int>> 세로로바꾸기(vector<vector <int>> board);
vector<vector <int>> 대각으로바꾸기(vector<vector <int>> board);
vector<vector <int>> 대각으로바꾸기2(vector<vector <int>> board);
int 가로세로대각12체크(vector<vector <int>> board);
vector<vector <int>> 입력받기(vector<vector <int>> board, bool turn);
int main() {
	cout << "10*10 오목 시작" << endl;
	vector<vector <int>> board;
	for (int i = 0; i < 10; i++) {
		board.push_back({ 0,0,0,0,0,0,0,0,0,0 });
	}
	bool gameisover = false;
	bool turn = true;
	int x = 0;
	int y = 0;
	while (!gameisover) {
		board=입력받기(board, turn);
		int result = 가로세로대각12체크(board);
		if (result == 1) {
			cout << "A의 승리" << endl;
			gameisover = true; // 게임 종료 표시
		}
		else if (result == 2) {
			cout << "B의 승리" << endl;
			gameisover = true; // 게임 종료 표시
		}
		else {
			turn = !turn; // 턴을 바꾸는 것만 남음
		}
		matrixprint(board);
	}
}
int 가로체크(vector<vector <int>> board) {
	string check = "";
	for (vector <int> line : board) {
		check = "";
		for (int i : line) {
			check.append(to_string(i));
		}
		if (check.find("11111") != std::string::npos) {
			return 1;
		}
		else if (check.find("22222") != std::string::npos) {
			return 2;
		}
	}
	return 0;
}
vector<vector <int>> 세로로바꾸기(vector<vector <int>> board) {
	vector<vector <int>> 세로판;
	vector<int>temp;
	for (int j = 0; j < 10; j++) {
		for (int i = 0; i < 10; i++) {
			temp.push_back(board[i][j]);
		}
		세로판.push_back(temp);
		temp = {};
	}
	return 세로판;
}
void matrixprint(vector<vector <int>> board) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}
vector<vector <int>> 대각으로바꾸기(vector<vector <int>> board) {
	vector<vector <int>> 대각판;
	for (int num = 0; num <= 18; num++) {
		대각판.push_back({});
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (i + j == num) {
					대각판[num].push_back(board[i][j]);
				}
			}
		}
	}
	return 대각판;
}
vector<vector <int>> 대각으로바꾸기2(vector<vector <int>> board) {
	vector<vector <int>> 대각판;
	for (int num = -9; num <= 9; num++) {
		대각판.push_back({});
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (i - j == num) {
					대각판[(num+9)/2].push_back(board[i][j]);
				}
			}
		}
	}
	return 대각판;
}

vector<vector <int>> 입력받기(vector<vector <int>> board,bool turn) {
	int x, y;
	string c = (turn == true) ? "A의 턴 " : "B의 턴 ";
	cout << c << "행과 열을 입력해주세요" << endl;
	cin >> x >> y;
	if (board[x][y] != 0) {
		cout << "이미 둔 자리입니다. 다시 입력해주세요" << endl;
		입력받기(board, turn);
	}
	else {
		if (turn == true) {
			board[x][y] = 1;
		}
		else {
			board[x][y] = 2;
		}
		
		return board;
	}
}
int 가로세로대각12체크(vector<vector<int>> board) {
	int result = 가로체크(board); // 가로 체크
	if (result != 0) {
		return result;
	}

	result = 가로체크(세로로바꾸기(board)); // 세로 체크
	if (result != 0) {
		return result;
	}

	result = 가로체크(대각으로바꾸기(board)); // 대각선 체크
	if (result != 0) {
		return result;
	}

	result = 가로체크(대각으로바꾸기2(board)); // 대각선 체크2
	if (result != 0) {
		return result;
	}

	return 0; // 아무도 이기지 않은 경우
}