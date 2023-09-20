#include <iostream>
#include <random>
#include <list>
using namespace std;
int rannum();
int list_rnum_add(list <int> a);
int list_element_add(list <int> a);
void printlist(list <int> a);
using namespace std;

int main() {
    list <int> comlist;
    list <int> playerlist;

    
    for (int i = 0; i < 6; i++) {
        comlist.push_back(list_rnum_add(comlist));
    }
    cout << "당신이 고른 6개의 번호 입력" << endl;;
    int temp;
    for (int i = 0; i < 6; i++) {
        playerlist.push_back(list_element_add(playerlist));
    }

    cout << "로또 번호 출력"<<endl;
    printlist(comlist);
    cout << endl << "당신의 번호 출력" << endl;
    printlist(playerlist);
    cout << endl;
    int count = 0;
    for (int i : comlist) {
        for (int j : playerlist) {
            if (i == j) {
                count += 1;
            }
        }
    }
    int rank = 7 - count;
    cout << count << "개 맞추셨습니다. " << rank << "등입니다.";
}

int rannum() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> distribution(1, 25);
    return distribution(gen);
}

int list_rnum_add(list <int> a) {
    int rnum = rannum();
    int elementcount = count(a.begin(), a.end(), rnum);
    if (elementcount == 0) {
        a.push_back(rnum);
        return rnum;
    }
    else {
        list_rnum_add(a);
    }
}
int list_element_add(list <int> a) {
    int num;
    cout << "수를 입력하세요" << endl;
    cin >> num;
    int elementcount = count(a.begin(), a.end(), num);
    if (elementcount == 0) {
        return num;
    }
    else {
        cout << "중복이네요." << endl;
        list_element_add(a);
    }
}

void printlist(list <int> a) {
    for (int i : a) {
        cout << i << " ";
    }
}