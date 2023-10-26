#pragma comment(lib, "ws2_32.lib")

#include <WinSock2.h> //Winsock ������� include. WSADATA �������.
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
    �Ϲݴ�ȭ,// 0
    ȸ������,//�߽��ڿ� ��ȭ�� ���̵�� �н������ ���� 1
    �α���,//��ȭ�� ���̵�� ���ϰ�, ��ȭ2�� �н������ �� 2
    ���ϰ�������,//������ ��ȭ�� ���� 3
    ��ä�ø�ϰ�������,// 4
    �α����ѻ�����//5
};
enum LoginStatus {
    OFF,
    ON
};
class MessageP {
public:
    string cmd = to_string(�Ϲݴ�ȭ);
    string room = "����ä��";
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
    cout << "id�� �Է��ϼ���.";
    cin >> player.id;
    cout << "pw�� �Է��ϼ���.";
    cin >> player.say;
    send(client_sock, player.pack().c_str(), player.pack().length(), 0);
    while (player.lock == to_string(OFF)) {

    }
    return changemode();
}
void changemode() {
    cout << "��밡���� ��ɾ�: @changeRoom, @DM , @exit " << endl;
    cout << "��ɾ �Է����ּ���" << endl;
    string text;
    std::getline(cin, text);
    player.say = text;
    if (player.say == "@changeRoom") {
        player.cmd = to_string(���ϰ�������);
        send(client_sock, player.pack().c_str(), player.pack().length(), 0);
    }
    else if (player.say == "@DM") {
        player.cmd = to_string(�α����ѻ�����);
        send(client_sock, player.pack().c_str(), player.pack().length(), 0);
    }
    else if (player.say == "@exit") {
        cout << "������ �� ������!!!" << endl;
        return login();
    }
    else {
        cout << "�߸� �Է��ϼ̳׿�" << endl;
        return changemode();
    }
    return chattingmode();
}
void chattingmode() {
    string headline = player.room;
    if (player.to != "0") {
        headline = "DM - " + player.to;
    }
    headline += " @out�� ������ ä�ø�带 ����ϴ�.";
    cout << headline << endl;
    while (player.say != "@out") {
        string text;
        std::getline(cin, text);
        player.say = text;
        send(client_sock, player.pack().c_str(), player.pack().length(), 0);
    }
    player.room = "����ä��";//������ ����ä����
    player.to = "0";//DM�� ��쿡 ������
    return changemode();
}