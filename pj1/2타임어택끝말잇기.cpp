#include <iostream>
#include <list>
#include <ctime>
#include <algorithm>
using namespace std;

int main() {
	list <string> wordlist;
	string word,lastword;
	char laststr;
	int time_diff;

	cout << "ù �ܾ �Է����ּ���," << endl;
	cin >> word;
	wordlist.push_back(word);

	while (true) {
		lastword = wordlist.back();
		laststr = lastword[lastword.length() - 1];

		for (string s : wordlist) {
			cout << s << "->";
		}

		cout << endl << endl << "�ܾ �Է����ּ���," << endl;
		clock_t startTime = clock();
		cin >> word;
		clock_t endTime = clock();
		time_diff = (endTime - startTime) / CLOCKS_PER_SEC;
		cout << "�ɸ� �ð� : " << time_diff << endl;
		if (time_diff > 30) {
			cout << "Ÿ�� ������ ���" << endl;
			break;
		}
		else if (laststr != word[0]) {
			cout << "�̾����� ����, ���Է�" << endl;
		}
		else {
			bool check = false;
			for (string s : wordlist) {
				if (s == word) {
					check = true;
					cout << "�ߺ� �ܾ�, ���Է�" << endl;
				}
			}
			if (check == false) {
				wordlist.push_back(word);
				cout << "Ȯ��" << endl;
			}
		}
	}
	
}

	/*{
		for (string s : wordlist) {

		}
		wordlist.push_back(word);
		cout << "Ȯ��" << endl;
	}(laststr == word[0] && time_diff <= 30)
		else if (time_diff > 30) {
			cout << "Ÿ�� ������ ���" << endl;
			break;
		}*/