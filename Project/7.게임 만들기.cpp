#include <iostream>
#include <string>
#include <vector>
#include "무기.h"
#include "캐릭터.h"
using namespace std;


bool fight(Character A, Character B);
int main() {
    Character player;
    cout << "캐릭터를 생성합니다." << endl << "캐릭터명을 입력해주세요." << endl;
    cin >> player.name;

    cout << "한량 등장" << endl;
    Character 한량(5, 1);
    한량.name = "한량";

    cout << "전투를 시작합니다." << endl;
    cout << player.name << "은 주먹을 꽉 쥔다.." << endl;
    cout << 한량.name << "도 주먹을 꽉 쥔다.." << endl;
   
    cout << "공격합니다." << endl;
    fight(player, 한량);

    cout << "새로운 무기를 얻었다." << endl;
    Weapon* get = new Sword();
    player.grab(get);
    cout << "추가체력을 얻었다." << endl;
    player.hp += 10;
    cout << "협객 등장" << endl;
    Character 협객(10, 1);
    협객.name = "협객";
    협객.weapon = new Sword();
    fight(player, 협객);
    return 0;
}

