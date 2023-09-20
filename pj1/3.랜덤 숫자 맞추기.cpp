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
    cout << "����� �� 6���� ��ȣ �Է�" << endl;;
    int temp;
    for (int i = 0; i < 6; i++) {
        playerlist.push_back(list_element_add(playerlist));
    }

    cout << "�ζ� ��ȣ ���"<<endl;
    printlist(comlist);
    cout << endl << "����� ��ȣ ���" << endl;
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
    cout << count << "�� ���߼̽��ϴ�. " << rank << "���Դϴ�.";
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
    cout << "���� �Է��ϼ���" << endl;
    cin >> num;
    int elementcount = count(a.begin(), a.end(), num);
    if (elementcount == 0) {
        return num;
    }
    else {
        cout << "�ߺ��̳׿�." << endl;
        list_element_add(a);
    }
}

void printlist(list <int> a) {
    for (int i : a) {
        cout << i << " ";
    }
}