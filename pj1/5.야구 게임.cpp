#include <iostream>
#include <vector>
#include <random>

using namespace std;
int vector_rnum_add(vector <int> a);
int vector_element_add(vector <int> a);
int rannum();
void printvector(vector <int> a);
int playgame(vector <int> comvector);
int main() {
    vector <int> comvector;
    vector <int> playervector;

    cout << "��ǻ�Ͱ� 3���� ���ڸ� �̽��ϴ�." << endl;
    for (int i = 0; i < 3; i++) {
        comvector.push_back(vector_rnum_add(comvector));
    }
    cout << "��ǻ���� ����" << endl;
    printvector(comvector);
    int trynum=0;
    int resultofgame;
    while (true) {
        resultofgame = playgame(comvector);
        trynum += resultofgame;
        if (resultofgame == 1) {
            break;
        }
    }


    cout << "��ǻ���� ����" << endl;
    printvector(comvector);
    cout << endl;
    cout << trynum << "���� ���߼̽��ϴ�." << endl;
    
}

int vector_rnum_add(vector <int> a) {
    int rnum = rannum();
    int elementcount = count(a.begin(), a.end(), rnum);
    if (elementcount == 0) {
        return rnum;
    }
    else {
        return vector_rnum_add(a);
    }
}
int vector_element_add(vector <int> a) {
    int num;
    cout << "���� �Է��ϼ���" << endl;
    cin >> num;
    int elementcount = count(a.begin(), a.end(), num);
    if (elementcount == 0) {
        return num;
    }
    else {
        cout << "�ߺ��̳׿�." << endl;
        vector_element_add(a);
    }
}
int rannum() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> distribution(1, 9);
    return distribution(gen);
}
void printvector(vector <int> a) {
    for (int i : a) {
        cout << i << " ";
    }
}

int playgame(vector <int> comvector) {
    vector <int> playervector;
    cout << "����� �� 3���� ��ȣ �Է�" << endl;
    for (int i = 0; i < 3; i++) {
        playervector.push_back(vector_element_add(playervector));
    }

    int strikecount = 0;
    int ballcount = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (comvector[i] == playervector[j]) {
                if (i == j) {
                    strikecount += 1;
                }
                else {
                    ballcount += 1;
                }
            }
        }
    }
    if (strikecount == 3) {
        cout << "��Ʈ!!"<<endl;
        return 1;
    }
    else {
        cout << strikecount << "���� ��Ʈ����ũ    " << ballcount << "���� ��" << endl;
        return 0;
    }
}