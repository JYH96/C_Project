#include <iostream>
#include <stack>
#include <conio.h>
#include <string>
using namespace std;

class MyClass
{
    string name = "��ƹ���";
    stack<char> combo;
public:
    MyClass() {
        setname();
        setcombo();
        cout << "�Է� Ȯ��" << endl << endl;
    }
    MyClass(string n, stack<char> c) :name(n), combo(c) {}
    ~MyClass() {}
    string getname() {
        return name;
    }
    stack<char> getcombo() {
        return combo;
    }
    void setcombo() {
        char x;
        int num = 5;
        cout << "5�� �޺� �Է�" << endl;
        while (num > 0) {
            x = _getch();
            combo.push(x);
            num--;
        }
        cout << endl;
    }
    void setname() {
        cout << "ĳ���͸� �Է�" << endl;
        cin >> name;
    }
};
void �޺�Ȯ��(MyClass player) {
    cout << player.getname() << "�� 5�� �޺��� �Է����ּ���" << endl;
    int num = 5;
    char x;
    stack<char> temp = player.getcombo();

    while (num > 0) {
        x = _getch();
        if (x != temp.top()) {
            break;
        }
        else {
            temp.pop();
        }
        num--;
    }

    if (num == 0) {
        cout << "�޺� �Ϸ�-�¸�!!" << endl;
    }
    else {
        cout << 5 - num << " ���� �޺� �Է�... ����!!!" << endl;
    }
}

int main() {
    MyClass player;
    �޺�Ȯ��(player);
    return 0;
}