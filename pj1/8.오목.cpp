#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
/*�͹̳� �Ǵ� �ܼ� â���� ���ڸ� �Է��ϰ� ����ϴ� �۾��� ���� ���˴ϴ�. */
#include <iomanip>
/*������ ��� ���� ����: �Ҽ��� ���� �ڸ���, ������ �ʵ� �ʺ� ���� ������ �� �ֽ��ϴ�.
�ؽ�Ʈ�� ����: �ؽ�Ʈ�� ����, ����, �Ǵ� ��� ������ �� �ֽ��ϴ�.
��¥ �� �ð� ���� ����: ��¥ �� �ð��� ���ϴ� �������� ����� �� �ֽ��ϴ�.*/
using namespace std;

void matrixprint(vector<vector<int>> board, int currentX, int currentY);
int ����üũ(vector<vector <int>> board);
vector<vector <int>> ���ηιٲٱ�(vector<vector <int>> board);
vector<vector <int>> �밢���ιٲٱ�(vector<vector <int>> board);
vector<vector <int>> �밢���ιٲٱ�2(vector<vector <int>> board);
int ���μ��δ밢12üũ(vector<vector <int>> board);

int main() {
	cout << "10*10 ���� ����" << endl;
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
		system("cls"); // ȭ���� ����� ���� �׸�
		turnplayer = (turn == true) ? "1st Player�� �� " : "2nd Player�� �� ";
		cout << turnplayer <<  endl;
		matrixprint(board, currentX, currentY); // ���� ��ġ�� {}���

		input = _getch();
		/*Ű���忡�� ���ڸ� �Է� �޴� �Լ�
		����ڰ� Ű�� ���� ������ ����� ���� �Էµ� Ű�� ��ȯ
		conio.h�κ��� ������*/
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
		case ' ': // �����̽��ٸ� ������ �ٵϾ��� ��
			if (board[currentX][currentY] == 0) {
				if (turn) {
					board[currentX][currentY] = 1;
				}
				else {
					board[currentX][currentY] = 2;
				}

				int result = ���μ��δ밢12üũ(board);
				if (result == 1) {
					cout << "1�� �¸�" << endl;
					gameisover = true;
				}
				else if (result == 2) {
					cout << "2�� �¸�" << endl;
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
				cout << setw(3) << "{" << board[i][j] << "} " << setw(3);// setw: ���� ��ġ�� �߰�ȣ�� ǥ�� iomanip���� ������
			}
			else {
				cout << setw(3) << board[i][j] << setw(3) << " ";
			}
		}
		cout << endl << endl;
	}

}
int ����üũ(vector<vector <int>> board) {
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
vector<vector <int>> ���ηιٲٱ�(vector<vector <int>> board) {
	vector<vector <int>> ������;
	vector<int>temp;
	for (int j = 0; j < 10; j++) {
		for (int i = 0; i < 10; i++) {
			temp.push_back(board[i][j]);
		}
		������.push_back(temp);
		temp = {};
	}
	return ������;
}
vector<vector <int>> �밢���ιٲٱ�(vector<vector <int>> board) {
	vector<vector <int>> �밢��;
	for (int num = 0; num <= 18; num++) {
		�밢��.push_back({});
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (i + j == num) {
					�밢��[num].push_back(board[i][j]);
				}
			}
		}
	}
	return �밢��;
}
vector<vector <int>> �밢���ιٲٱ�2(vector<vector <int>> board) {
	vector<vector <int>> �밢��;
	for (int num = -9; num <= 9; num++) {
		�밢��.push_back({});
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (i - j == num) {
					�밢��[(num + 9)].push_back(board[i][j]);
				}
			}
		}
	}
	return �밢��;
}

int ���μ��δ밢12üũ(vector<vector<int>> board) {
	int result = ����üũ(board); // ���� üũ
	if (result != 0) {
		return result;
	}

	result = ����üũ(���ηιٲٱ�(board)); // ���� üũ
	if (result != 0) {
		return result;
	}

	result = ����üũ(�밢���ιٲٱ�(board)); // �밢�� üũ
	if (result != 0) {
		return result;
	}

	result = ����üũ(�밢���ιٲٱ�2(board)); // �밢�� üũ2
	if (result != 0) {
		return result;
	}

	return 0; // �ƹ��� �̱��� ���� ���
}

vector<vector <int>> �Է¹ޱ�(vector<vector <int>> board, bool turn) {
	int x, y;
	string c = (turn == true) ? "A�� �� " : "B�� �� ";
	cout << c << "��� ���� �Է����ּ���" << endl;
	cin >> x >> y;
	if (board[x][y] != 0) {
		cout << "�̹� �� �ڸ��Դϴ�. �ٽ� �Է����ּ���" << endl;
		�Է¹ޱ�(board, turn);
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