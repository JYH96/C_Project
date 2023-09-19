#include <iostream>
#include <vector>

#include "���ݸ�.h"
#include "ĵ��.h"
using namespace std;

int main() {
    int x;
    string y;
    vector<Snack*> s;

    do {
        cout << "���� �ٱ��Ͽ� �߰��� ���� (1.���� 2.���ݸ� 0.����) : ";
        cin >> x;
        cout << endl;

        switch (x) {
        case 0:
            cout << "���� �ٱ��Ͽ� ��� ������ ������ " << Snack::get_count() << "�� �Դϴ�." << endl;
            cout << "�ٱ��� �� ���� Ȯ���ϱ�" << endl;
            for (Snack* snack : s) {
                snack->show_info();
            }
            break;
        case 1:
            cout << "���� �Է��ϼ���" << endl;
            cin >> y;
            s.push_back(new Candy(y));
            break;
        case 2:
            cout << "����� �Է��ϼ���" << endl;
            cin >> y;
            s.push_back(new Chocolate(y));
            break;
        default:
            cout << "0~2 ������ ���ڸ� �Է��ϼ���." << endl;
            break;
        }
    } while (x != 0);

    // ���Ϳ� �߰��� ��ü���� �޸𸮿��� ����
    for (Snack* snack : s) {
        delete snack;
    }

    return 0;
}