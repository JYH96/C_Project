for (int i = 0; i < 10; i++) {
	board.push_back({ 0,0,0,0,0,0,0,0,0,0 });
}
bool gameisover = false;
bool turn = true;
int x = 0;
int y = 0;
while (gameisover != true) {

	if (turn == true) {
		cout << "A�� ����, ��� ���� �Է����ּ���" << endl;
		cin >> x >> y;
		board[x][y] = 1;
		matrixprint(board);
	}
	else {
		cout << "B�� ����, ��� ���� �Է����ּ���" << endl;
		cin >> x >> y;
		board[x][y] = 2;
		matrixprint(board);
	}
	if (����üũ(board) == 1) {
		cout << "A�� �¸�" << endl;
		gameisover = true;
	}
	else if (����üũ(board) == 2) {
		cout << "B�� �¸�" << endl;
		gameisover = true;
	}
	else {
		if (turn == true) {
			turn = false;
		}
		else {
			turn = true;
		}
	}
}
//board = ���ηιٲٱ�(board);
//matrixprint(board);