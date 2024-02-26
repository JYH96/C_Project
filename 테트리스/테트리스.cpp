#include <iostream>
#include <conio.h>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>
#include <mutex>
#include <numeric>
#include <random>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string>
#include <atomic>
#include <condition_variable>
using namespace std;

mutex mtx;
int width = 8;
int height = 20;


class Box {
public:
	vector<vector<vector<int>>> blist = {
		{ { 1,1,1,1 }},
		{ { 2,2,2 }, {0,0,2} },
		{ { 3,3,3 }, {3,0,0} },
		{ { 4,4 },	 {4,4} },
		{ { 5,5,5 }, {0,5,0} },
		{ { 6,6,0 }, {0,6,6} },
		{ { 0,7,7 }, {7,7,0} },
		{{0,0},{0,0}}
	};
	vector<int>line = vector<int>(width + 2, 0);
	vector<vector<int>> boxlayer;
	Box() {
		block = blist[rand() % 6];
		boxlayer = vector<vector<int>>(height+1, line);
		boxlayer[height]= vector<int>(width + 2, 4);
	}
	vector<vector<int>> block = blist[4];
	int currentX = 0;
	int currentY = int(width / 2);

	vector<vector<int>>RotateRight(vector<vector<int>>bblock) {
		vector<vector<int>> rotated;
		if (bblock.size() != 1 && bblock.size() != 4) {
			vector<int> 가로열 = vector<int>(bblock[0].size(), 0);
			vector<int> 세로열 = vector<int>(bblock.size(), 0);
			rotated = vector<vector<int>>(bblock[0].size(), 세로열);

			for (int x = 0; x < bblock.size(); x++) {
				for (int y = 0; y < bblock[0].size(); y++) {
					rotated[y][bblock.size() - x - 1] = bblock[x][y];
				}
			}
		}
		else if (bblock.size() == 4) {
			rotated = { { 1,1,1,1 } };
		}
		else {
			rotated = { {1},{1},{1},{1} };
		}
		return rotated;
	}

	Box move(char key) {
		Box tempbox = Box();
		tempbox.currentX = this->currentX;
		tempbox.currentY = this->currentY;
		tempbox.block = this->block;
		switch (key) {
		case 'w':
			tempbox.block = RotateRight(tempbox.block);
			break;
		case 's':
			tempbox.block = RotateRight(RotateRight(RotateRight(tempbox.block)));
			break;
		case 'd':
			tempbox.currentY += 1;
			break;
		case 'a':
			tempbox.currentY -= 1;
			break;
		case ' ':
			tempbox.currentX += 1;
			break;
		default:
			break;
		}
		return tempbox;
	}
	vector<vector<int>> getboxlayer() {
		vector<vector<int>> bboxlayer = boxlayer;
		for (int i = 0; i < bboxlayer.size(); i++) {
			for (int j = 0; j < bboxlayer[0].size(); j++) {
				if (currentX <= i && i < currentX + block.size() && currentY <= j && j < currentY + block[0].size()) {
					bboxlayer[i][j] += block[i - currentX][j - currentY];
				}
			}
		}
		return bboxlayer;
	}
};

void Color(int x) {
	switch (x)
	{
	case 0:
		cout << "\x1B[30m" << "■" << "\x1B[0m" << " ";
		break;
	case 1:
		cout << "\x1B[31m" << "■" << "\x1B[0m" << " ";
		break;
	case 2:
		cout << "\x1B[32m" << "■" << "\x1B[0m" << " ";
		break;
	case 3:
		cout << "\x1B[33m" << "■" << "\x1B[0m" << " ";
		break;
	case 4:
		cout << "\x1B[34m" << "■" << "\x1B[0m" << " ";
		break;
	case 5:
		cout << "\x1B[35m" << "■" << "\x1B[0m" << " ";
		break;
	case 6:
		cout << "\x1B[36m" << "■" << "\x1B[0m" << " ";
		break;
	case 7:
		cout << "\x1B[37m" << "■" << "\x1B[0m" << " ";
		break;
	default:
		cout << "■" << " ";
		break;
	}
	return ;
}

void print(Box b, Box m) {
	for (int i = 0; i < b.boxlayer.size(); i++) {
		for (int j = 0; j < b.boxlayer[0].size(); j++) {
			if (b.currentX <= i && i < b.currentX + b.block.size() && b.currentY <= j && j < b.currentY + b.block[0].size()) {
				b.boxlayer[i][j] += b.block[i - b.currentX][j - b.currentY];
			}
			Color(b.boxlayer[i][j] + m.boxlayer[i][j]);
		}
		cout << endl;
	}
}
Box b = Box();
Box m = Box();
char o;
bool GAMEOVER = false;
void Explode() {
	int dot;
	for (int i = 0; i < m.boxlayer.size() - 1; i++) {
		dot = 1;
		for (int j = 0; j < m.boxlayer[j].size(); j++) {
			dot *= m.boxlayer[i][j]+b.boxlayer[i][j];
		}
		if (dot > 0) {
			for (int j=i; j > 0; j--) {
				m.boxlayer[j] = m.boxlayer[j-1];
			}
			return;
		}
	}
	return;
}
bool Decision() {
	int dot = 1;
	bool stack = false;
	
	if (mtx.try_lock()) {

			b = b.move(o);
	o = 'e';
	if (b.currentY < 0) {
		b.currentY = 0;
	}
	else if (b.currentY + b.block[0].size() > m.boxlayer[0].size()) {
		b.currentY = m.boxlayer[0].size() - b.block[0].size();
	}
	dot = 1;
	vector<vector<int>> layer;
	while (dot != 0) {
		dot = 0;
		layer = b.getboxlayer();
		for (int i = 0; i < m.boxlayer.size() - 1; i++) {
			for (int j = 0; j < m.boxlayer[0].size(); j++) {
				dot += m.boxlayer[i][j] * layer[i][j];
			}
		}
		if (dot != 0) {
			b.currentX -= 1;
			stack = true;
			if (b.currentX < 0) {
				GAMEOVER = true;
				mtx.unlock();
				return true;
			}

		}
		else if (stack == true) {
			for (int i = 0; i < layer.size() - 1; i++) {
				for (int j = 0; j < layer[0].size(); j++) {
					m.boxlayer[i][j] += layer[i][j];
				}
			}

			Explode();
			b = Box();
			stack = false;
			break;
		}
		else if (b.currentX + b.block.size() >= m.boxlayer.size() - 1) {
			for (int i = 0; i < layer.size() - 1; i++) {
				for (int j = 0; j < layer[0].size(); j++) {
					m.boxlayer[i][j] += layer[i][j];
				}
			}
			Explode();
			b = Box();
			break;
		}

	}
	system("cls");
	print(b, m);

		mtx.unlock();
	}
	return false;
}

void Clock() {
	while (true) {
		this_thread::sleep_for(chrono::milliseconds(300));
		if (GAMEOVER) {
			break;
		}
		else {
			GAMEOVER = Decision();
			b.currentX += 1;
		}
	}
}
int main() {
	m.block = m.blist[7];
	
	thread CClock(Clock);
	while (!GAMEOVER) {
		o = _getch();
		GAMEOVER = Decision();
	}
	cout << "GAME_OVER";
	CClock.join();
}
