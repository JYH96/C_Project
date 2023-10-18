#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;
#define default_VAL "0"
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
    �α���,//from�� ���̵�� ���ϰ�, say2�� �н������ �� 2
    ���ϰ�������,//������ ��ȭ�� ���� 3
    ��ä�ø�ϰ�������,// 4
    �α����ѻ�����//5
};
enum LoginStatus {
    OFF,
    ON
};
//�޼�������

class MessageS {
public:
    string cmd = default_VAL;
    string room = "[Information]";
    string id = "server";
    string to = "ALL";//server���� ��ο��� ���� ��
    string say = default_VAL;
    string lock = "1";
    string name = "�϶���";
    string pack() {
        return cmd + "#" + room + "#" + id + "#" + to + "#" + say + "#" + lock + "#";
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
MessageS decode(const string& str) {
    vector<string> item;
    item = split(str);
    MessageS reply;
    reply.cmd = item[Xcmd];
    reply.id = item[Xid];
    reply.room = item[Xroom];
    reply.say = item[Xsay];
    reply.to = item[Xto];
    reply.lock = item[Xlock];
    reply.name = item[Xname];
    return reply;
}