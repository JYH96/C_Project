#include <iostream>
#include <vector>
using namespace std;
vector<int> direction(int c, int n);
vector<int> move(vector<int> point, vector<int> direction);
vector<int> setting(vector<int> point, vector<int> temp);

int main() {
	cout << "Ȧ�� �Է�" << endl;
	int n;
	cin >> n;
	vector<vector<int>> matrix(n, vector<int>(n, 0));
	vector<int> point = { 0,(n + 1) / 2 - 1 };
	vector<int> temp;

	int number = 2;
	matrix[point[0]][point[1]] = 1;
	temp = move(point, direction(1, n));

	while (number != n * n + 1) {

		//ù��° ���� ������ �������� �������� �̵��ϴ� ���� �ƴ϶� �ٷ� �Ʒ�ĭ���� �̵�
		if (point[0] == 0 && point[1] == n - 1) {
			temp = move(point, direction(2, n));
		}
		//ù��° �࿡�� �������� �̵��� ���� ������ ���� ���� ���� �̵��Ѵ�.
		else if (point[0] == 0) {
			temp = move(point, direction(3, n));
		}
		//������ ������ �������� �̵��� ���� ù��° ���� ���� ������ �̵��Ѵ�.
		else if (point[1] == n - 1) {
			temp = move(point, direction(4, n));
		}

		if (matrix[temp[0]][temp[1]] == 0) {
			point = setting(point, temp);
			temp = move(point, direction(1, n));
			matrix[point[0]][point[1]] = number;
			number++;
		}
		else { temp = move(point, direction(2, n)); }
	}

	//�����Ʈ
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

vector<int> direction(int c, int n) {
	vector<int> m;
	switch (c) {
	case 1:
		m = { -1, 1 }; // 1�ù��� �̵�
		break;
	case 2:
		m = { 1, 0 }; // �ٷ� �Ʒ�ĭ���� �̵�
		break;
	case 3:
		m = { n - 1, 1 }; // ������ ���� ���� ���� �̵�
		break;
	case 4:
		m = { -1, 1 - n }; // ù��° ���� ���� ������ �̵�
		break;
	}
	return m;
}
vector<int> move(vector<int> point, vector<int> direction) {
	point[0] += direction[0];
	point[1] += direction[1];
	return point;
}
vector<int> setting(vector<int> point, vector<int> temp) {
	point[0] = temp[0];
	point[1] = temp[1];
	return point;
}