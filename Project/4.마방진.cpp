#include <iostream>
#include <vector>
using namespace std;
vector<int> direction(int c, int n);
vector<int> move(vector<int> point, vector<int> direction);
vector<int> setting(vector<int> point, vector<int> temp);

int main() {
	cout << "홀수 입력" << endl;
	int n;
	cin >> n;
	vector<vector<int>> matrix(n, vector<int>(n, 0));
	vector<int> point = { 0,(n + 1) / 2 - 1 };
	vector<int> temp;

	int number = 2;
	matrix[point[0]][point[1]] = 1;
	temp = move(point, direction(1, n));

	while (number != n * n + 1) {

		//첫번째 행의 마지막 열에서는 우상단으로 이동하는 것이 아니라 바로 아래칸으로 이동
		if (point[0] == 0 && point[1] == n - 1) {
			temp = move(point, direction(2, n));
		}
		//첫번째 행에서 우상단으로 이동할 때는 마지막 행의 다음 열로 이동한다.
		else if (point[0] == 0) {
			temp = move(point, direction(3, n));
		}
		//마지막 열에서 우상단으로 이동할 때는 첫번째 열의 이전 행으로 이동한다.
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

	//출력파트
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
		m = { -1, 1 }; // 1시방향 이동
		break;
	case 2:
		m = { 1, 0 }; // 바로 아래칸으로 이동
		break;
	case 3:
		m = { n - 1, 1 }; // 마지막 행의 다음 열로 이동
		break;
	case 4:
		m = { -1, 1 - n }; // 첫번째 열의 이전 행으로 이동
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