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
    일반대화,// 0
    회원가입,//발신자와 대화를 아이디와 패스워드로 저장 1
    로그인,//from을 아이디와 비교하고, say2를 패스워드와 비교 2
    방목록가져오기,//방목록을 대화로 보냄 3
    방채팅목록가져오기,// 4
    로그인한사람명단//5
};
enum LoginStatus {
    OFF,
    ON
};
//메세지관련

class MessageS {
public:
    string cmd = default_VAL;
    string room = "[Information]";
    string id = "server";
    string to = "ALL";//server에서 모두에게 보낼 때
    string say = default_VAL;
    string lock = "1";
    string name = "싹뚝이";
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