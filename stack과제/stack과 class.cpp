#include <iostream>
#include <stack>
#include <conio.h>
#include <string>
using namespace std;

class MyClass
{
    string name = "김아무개";
    stack<char> combo;
public:
    MyClass() {
        setname();
        setcombo();
        cout << "입력 확인" << endl << endl;
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
        cout << "5단 콤보 입력" << endl;
        while (num > 0) {
            x = _getch();
            combo.push(x);
            num--;
        }
        cout << endl;
    }
    void setname() {
        cout << "캐릭터명 입력" << endl;
        cin >> name;
    }
};
void 콤보확인(MyClass player) {
    cout << player.getname() << "의 5단 콤보를 입력해주세요" << endl;
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
        cout << "콤보 완료-승리!!" << endl;
    }
    else {
        cout << 5 - num << " 개의 콤보 입력... 실패!!!" << endl;
    }
}

int main() {
    MyClass player;
    콤보확인(player);
    return 0;
}