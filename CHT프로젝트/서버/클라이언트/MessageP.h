#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
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
}