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
	cout << "���ڸ� �Է��ϼ���" << endl;
	cin >> a;
	com.setnum1st(a);
	do {
		process(com);
		cout << "���μ��� �� " << com.getnum() << endl;
	} while (qustion(com));

}
void process(cal &ccom) {
	float b;
	string opr;
	cout << "���� �Է��ϼ���" << endl;
	cin >> b;
	ccom.setnum2nd(b);
	cout <<"������ ������ �Է��ϼ���" << endl;
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
		cout << "�߸� �Է��ϼ̽��ϴ�."<<endl;
	}
}
bool qustion(cal vcom) {
	float a;
	string opr;
	cout << "������ ��� �����Ͻðڽ��ϱ�? Y:��� AC:�ʱ�ȭ EXIT:����" << endl;
	cin >> opr;
	if (opr == "Y") {
		return true;
	}
	else if (opr == "AC") {
		cout << "���ڸ� �Է��ϼ���" << endl;
		cin >> a;
		vcom.setnum1st(a);
		return true;
	}
	else if (opr == "EXIT") {
		return false;
	}
}