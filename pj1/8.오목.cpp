#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
/*터미널 또는 콘솔 창에서 문자를 입력하고 출력하는 작업을 위해 사용됩니다. */
#include <iomanip>
/*숫자의 출력 형식 조정: 소수점 이하 자릿수, 정수의 필드 너비 등을 조절할 수 있습니다.
텍스트의 정렬: 텍스트를 좌측, 우측, 또는 가운데 정렬할 수 있습니다.
날짜 및 시간 형식 지정: 날짜 및 시간을 원하는 형식으로 출력할 수 있습니다.*/
using namespace std;

void matrixprint(vector<vector<int>> board, int currentX, int currentY);
int 가로체크(vector<vector <int>> board);
vector<vector <int>> 세로로바꾸기(vector<vector <int>> board);
vector<vector <int>> 대각으로바꾸기(vector<vector <int>> board);
vector<vector <int>> 대각으로바꾸기2(vector<vector <int>> board);
int 가로세로대각12체크(vector<vector <int>> board);

int main() {
	cout << "10*10 오목 시작" << endl;
	vector<vector<int>> board;
	for (int i = 0; i < 10; i++) {
		board.push_back({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
	}
	bool gameisover = false;
	bool turn = true;

	int currentX = 0;
	int currentY = 0;
	char input;
	string turnplayer;
	while (!gameisover) {
		system("cls"); // 화면을 지우고 새로 그림
		turnplayer = (turn == true) ? "1st Player의 턴 " : "2nd Player의 턴 ";
		cout << turnplayer <<  endl;
		matrixprint(board, currentX, currentY); // 현재 위치에 {}출력

		input = _getch();
		/*키보드에서 문자를 입력 받는 함수
		사용자가 키를 누를 때까지 대기한 다음 입력된 키를 반환
		conio.h로부터 가져옴*/
		switch (input) {
		case 'w':
			if (currentX > 0) {
				currentX--;
			}
			break;
		case 's':
			if (currentX < 9) {
				currentX++;
			}
			break;
		case 'a':
			if (currentY > 0) {
				currentY--;
			}
			break;
		case 'd':
			if (currentY < 9) {
				currentY++;
			}
			break;
		case 'q':
			gameisover = true;
			break;
		case ' ': // 스페이스바를 누르면 바둑알을 둠
			if (board[currentX][currentY] == 0) {
				if (turn) {
					board[currentX][currentY] = 1;
				}
				else {
					board[currentX][currentY] = 2;
				}

				int result = 가로세로대각12체크(board);
				if (result == 1) {
					cout << "1의 승리" << endl;
					gameisover = true;
				}
				else if (result == 2) {
					cout << "2의 승리" << endl;
					gameisover = true;
				}

				else {
					turn = !turn;
				}
			}
			break;
		}
	}

	return 0;
}

void matrixprint(vector<vector<int>> board, int currentX, int currentY) {
	
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (i == currentX && j == currentY) {
				cout << setw(3) << "{" << board[i][j] << "} " << setw(3);// setw: 현재 위치를 중괄호로 표시 iomanip에서 가져옴
			}
			else {
				cout << setw(3) << board[i][j] << setw(3) << " ";
			}
		}
		cout << endl << endl;
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
					대각판[(num + 9)].push_back(board[i][j]);
				}
			}
		}
	}
	return 대각판;
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

vector<vector <int>> 입력받기(vector<vector <int>> board, bool turn) {
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