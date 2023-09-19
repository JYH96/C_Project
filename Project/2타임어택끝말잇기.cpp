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

	cout << "첫 단어를 입력해주세요," << endl;
	cin >> word;
	wordlist.push_back(word);

	while (true) {
		lastword = wordlist.back();
		laststr = lastword[lastword.length() - 1];

		for (string s : wordlist) {
			cout << s << "->";
		}

		cout << endl << endl << "단어를 입력해주세요," << endl;
		clock_t startTime = clock();
		cin >> word;
		clock_t endTime = clock();
		time_diff = (endTime - startTime) / CLOCKS_PER_SEC;
		cout << "걸린 시간 : " << time_diff << endl;
		if (time_diff > 30) {
			cout << "타임 오버로 사망" << endl;
			break;
		}
		else if (laststr != word[0]) {
			cout << "이어지지 않음, 재입력" << endl;
		}
		else {
			bool check = false;
			for (string s : wordlist) {
				if (s == word) {
					check = true;
					cout << "중복 단어, 재입력" << endl;
				}
			}
			if (check == false) {
				wordlist.push_back(word);
				cout << "확인" << endl;
			}
		}
	}
	
}

	/*{
		for (string s : wordlist) {

		}
		wordlist.push_back(word);
		cout << "확인" << endl;
	}(laststr == word[0] && time_diff <= 30)
		else if (time_diff > 30) {
			cout << "타임 오버로 사망" << endl;
			break;
		}*/