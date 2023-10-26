#pragma comment(lib, "ws2_32.lib")

#include <WinSock2.h> //Winsock 헤더파일 include. WSADATA 들어있음.
#include <WS2tcpip.h>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include <chrono>
//#include "MessageP.h"///////////////////////////////////////////////////////////////////////
#define default_VAL "0"
using namespace std;
enum Get {
    Xcmd,//0
    Xroom,//1
    Xid,//2
    Xto,//3
    Xsay,//4
    Xlock,//5
    Xname//6
};
enum Cmdlist {
    일반대화,// 0
    회원가입,//발신자와 대화를 아이디와 패스워드로 저장 1
    로그인,//대화를 아이디와 비교하고, 대화2를 패스워드와 비교 2
    방목록가져오기,//방목록을 대화로 보냄 3
    방채팅목록가져오기,// 4
    로그인한사람명단//5
};
enum LoginStatus {
    OFF,
    ON
};
class MessageP {
public:
    string cmd = to_string(일반대화);
    string room = "자유채널";
    string id = default_VAL;
    string name = default_VAL;
    string to = default_VAL;
    string say = default_VAL;
    string lock = to_string(OFF);
    string pack() {
        return cmd + "#" + room + "#" + id + "#" + to + "#" + say + "#" + lock + "#" + name + "#";
    }
};
vector<string> split(const string& str) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, '#')) {
        tokens.push_back(token);
    }
    return tokens;
}
MessageP decode(const string& str) {
    vector<string> item;
    item = split(str);
    MessageP reply;
    reply.cmd = item[Xcmd];
    reply.id = item[Xid];
    reply.room = item[Xroom];
    reply.say = item[Xsay];
    reply.to = item[Xto];
    reply.lock = item[Xlock];
    reply.name = item[Xname];
    return reply;
}//////////////////////////////////////////////////////////////////////////////////////////////
#define MAX_SIZE 1024

SOCKET client_sock;
MessageP player;

int chat_recv();
void login();
void changemode();
void chattingmode();

int main() {
    WSADATA wsa;
    int code = WSAStartup(MAKEWORD(2, 2), &wsa);
    while (code) {
        cout << "Setting..." << endl;
    }
    client_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    SOCKADDR_IN client_addr = {};
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(7777);
    InetPton(AF_INET, TEXT("127.0.0.1"), &client_addr.sin_addr);
    while (connect(client_sock, (SOCKADDR*)&client_addr, sizeof(client_addr))) {
        cout << "Connecting..." << endl;
    }
    cout << "Server Connect" << endl;

    std::thread channelon(chat_recv);

    login();

    channelon.join();
    closesocket(client_sock);

    WSACleanup();
    return 0;
}

int chat_recv() {
    char buffer[MAX_SIZE] = {};
    MessageP reply;
    while (1) {
        ZeroMemory(&buffer, MAX_SIZE);
        int len = recv(client_sock, buffer, MAX_SIZE, 0);
        if (len > 0) {
            reply=decode(buffer);
        }
        else if (len < 0) {
            cout << "Server Off" << endl;
            return -1;
        }
    }
}
void login() {
    player.lock = to_string(OFF);
    cout << "id를 입력하세요.";
    cin >> player.id;
    cout << "pw를 입력하세요.";
    cin >> player.say;
    send(client_sock, player.pack().c_str(), player.pack().length(), 0);
    while (player.lock == to_string(OFF)) {

    }
    return changemode();
}
void changemode() {
    cout << "사용가능한 명령어: @changeRoom, @DM , @exit " << endl;
    cout << "명령어를 입력해주세요" << endl;
    string text;
    std::getline(cin, text);
    player.say = text;
    if (player.say == "@changeRoom") {
        player.cmd = to_string(방목록가져오기);
        send(client_sock, player.pack().c_str(), player.pack().length(), 0);
    }
    else if (player.say == "@DM") {
        player.cmd = to_string(로그인한사람명단);
        send(client_sock, player.pack().c_str(), player.pack().length(), 0);
    }
    else if (player.say == "@exit") {
        cout << "다음에 또 만나요!!!" << endl;
        return login();
    }
    else {
        cout << "잘못 입력하셨네요" << endl;
        return changemode();
    }
    return chattingmode();
}
void chattingmode() {
    string headline = player.room;
    if (player.to != "0") {
        headline = "DM - " + player.to;
    }
    headline += " @out를 누르면 채팅모드를 벗어납니다.";
    cout << headline << endl;
    while (player.say != "@out") {
        string text;
        std::getline(cin, text);
        player.say = text;
        send(client_sock, player.pack().c_str(), player.pack().length(), 0);
    }
    player.room = "자유채널";//나가면 자유채널행
    player.to = "0";//DM인 경우에 해제함
    return changemode();
}