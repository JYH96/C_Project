#include <iostream>
#include <vector>
#include <string>
using namespace std;

void matrixprint(vector<vector <int>> board);
int ����üũ(vector<vector <int>> board);
vector<vector <int>> ���ηιٲٱ�(vector<vector <int>> board);
vector<vector <int>> �밢���ιٲٱ�(vector<vector <int>> board);
vector<vector <int>> �밢���ιٲٱ�2(vector<vector <int>> board);
int ���μ��δ밢12üũ(vector<vector <int>> board);
vector<vector <int>> �Է¹ޱ�(vector<vector <int>> board, bool turn);
int main() {
	cout << "10*10 ���� ����" << endl;
	vector<vector <int>> board;
	for (int i = 0; i < 10; i++) {
		board.push_back({ 0,0,0,0,0,0,0,0,0,0 });
	}
	bool gameisover = false;
	bool turn = true;
	int x = 0;
	int y = 0;
	while (!gameisover) {
		board=�Է¹ޱ�(board, turn);
		int result = ���μ��δ밢12üũ(board);
		if (result == 1) {
			cout << "A�� �¸�" << endl;
			gameisover = true; // ���� ���� ǥ��
		}
		else if (result == 2) {
			cout << "B�� �¸�" << endl;
			gameisover = true; // ���� ���� ǥ��
		}
		else {
			turn = !turn; // ���� �ٲٴ� �͸� ����
		}
		matrixprint(board);
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
void matrixprint(vector<vector <int>> board) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
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
					�밢��[(num+9)/2].push_back(board[i][j]);
				}
			}
		}
	}
	return �밢��;
}

vector<vector <int>> �Է¹ޱ�(vector<vector <int>> board,bool turn) {
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