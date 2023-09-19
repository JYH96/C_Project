for (int i = 0; i < 10; i++) {
	board.push_back({ 0,0,0,0,0,0,0,0,0,0 });
}
bool gameisover = false;
bool turn = true;
int x = 0;
int y = 0;
while (gameisover != true) {

	if (turn == true) {
		cout << "A의 차례, 행과 열을 입력해주세요" << endl;
		cin >> x >> y;
		board[x][y] = 1;
		matrixprint(board);
	}
	else {
		cout << "B의 차례, 행과 열을 입력해주세요" << endl;
		cin >> x >> y;
		board[x][y] = 2;
		matrixprint(board);
	}
	if (가로체크(board) == 1) {
		cout << "A의 승리" << endl;
		gameisover = true;
	}
	else if (가로체크(board) == 2) {
		cout << "B의 승리" << endl;
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
//board = 세로로바꾸기(board);
//matrixprint(board);