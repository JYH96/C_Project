#include <iostream>
#include <string>
using namespace std;
class cal {
	float x, y;
public:
	cal() {}
	cal(float a, float b) :x(a), y(b) {}
	float add() {
		return x + y;
	}
	float sub() {
		return x - y;
	}
	float mul() {
		return x * y;
	}
	float div() {
		return (float)(x / y);
	}
	void setnum1st(float q) {
		x = q;
	}
	void setnum2nd(float q) {
		y = q;
	}
	float getnum() {
		return x;
	}
	float getnum2() {
		return y;
	}
};

void process(cal &ccom);
bool qustion(cal vcom);

int main() {
	cal com;
	float a;
	string opr;
	cout << "숫자를 입력하세요" << endl;
	cin >> a;
	com.setnum1st(a);
	do {
		process(com);
		cout << "프로세스 후 " << com.getnum() << endl;
	} while (qustion(com));

}
void process(cal &ccom) {
	float b;
	string opr;
	cout << "수를 입력하세요" << endl;
	cin >> b;
	ccom.setnum2nd(b);
	cout <<"수행할 연산을 입력하세요" << endl;
	cin >> opr;
	if (opr == "+") {
		ccom.setnum1st(ccom.add());
		cout << ccom.getnum() << endl;
	}
	else if (opr == "-") {
		ccom.setnum1st(ccom.sub());
		cout << ccom.getnum() << endl;
	}
	else if (opr == "*") {
		ccom.setnum1st(ccom.mul());
		cout << ccom.getnum() << endl;
	}
	else if (opr == "/") {
		ccom.setnum1st(ccom.div());
		cout << ccom.getnum() << endl;
	}
	else {
		cout << "잘못 입력하셨습니다."<<endl;
	}
}
bool qustion(cal vcom) {
	float a;
	string opr;
	cout << "연산을 계속 진행하시겠습니까? Y:계속 AC:초기화 EXIT:종료" << endl;
	cin >> opr;
	if (opr == "Y") {
		return true;
	}
	else if (opr == "AC") {
		cout << "숫자를 입력하세요" << endl;
		cin >> a;
		vcom.setnum1st(a);
		return true;
	}
	else if (opr == "EXIT") {
		return false;
	}
}