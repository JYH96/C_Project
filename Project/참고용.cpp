#include <iostream>
#include <vector>

#include "초콜릿.h"
#include "캔디.h"
using namespace std;

int main() {
    int x;
    string y;
    vector<Snack*> s;

    do {
        cout << "과자 바구니에 추가할 간식 (1.사탕 2.초콜릿 0.종료) : ";
        cin >> x;
        cout << endl;

        switch (x) {
        case 0:
            cout << "과자 바구니에 담긴 간식의 개수는 " << Snack::get_count() << "개 입니다." << endl;
            cout << "바구니 속 간식 확인하기" << endl;
            for (Snack* snack : s) {
                snack->show_info();
            }
            break;
        case 1:
            cout << "맛을 입력하세요" << endl;
            cin >> y;
            s.push_back(new Candy(y));
            break;
        case 2:
            cout << "모양을 입력하세요" << endl;
            cin >> y;
            s.push_back(new Chocolate(y));
            break;
        default:
            cout << "0~2 사이의 숫자를 입력하세요." << endl;
            break;
        }
    } while (x != 0);

    // 벡터에 추가한 객체들을 메모리에서 해제
    for (Snack* snack : s) {
        delete snack;
    }

    return 0;
}