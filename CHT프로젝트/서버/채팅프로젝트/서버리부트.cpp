#pragma comment(lib, "ws2_32.lib") //명시적인 라이브러리의 링크. 윈속 라이브러리 참조
#include <mysql/jdbc.h>
#include <WinSock2.h>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
using namespace std;
//#include "MessageS.h"
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
//#include "DB.h"////////////////////////////////////////////////////////////////////////////////
class DB {
    sql::mysql::MySQL_Driver* driver; // 추후 해제하지 않아도 Connector/C++가 자동으로 해제해 줌
    sql::Connection* con;
    sql::Statement* stmt;
    sql::ResultSet* res;
    sql::PreparedStatement* pstmt;
public:
    DB() {
        const string server = "tcp://127.0.0.1:3306"; // 데이터베이스 주소
        const string username = "root"; // 데이터베이스 사용자
        const string password = "qpwoei13"; // 데이터베이스 접속 비밀번호
        try {
            driver = sql::mysql::get_mysql_driver_instance();
            con = driver->connect(server, username, password);
        }
        catch (sql::SQLException& e) {
            cout << "Could not connect to server. Error message: " << e.what() << endl;
            exit(1);
        }
        con->setSchema("chattingproject");
        // db 한글 저장을 위한 셋팅
        stmt = con->createStatement();
        stmt->execute("set names euckr");
        if (stmt) { delete stmt; stmt = nullptr; }
    }
    ~DB() {
        if (stmt) { delete stmt; }
        if (res) { delete res; }
        if (pstmt) { delete pstmt; }
        if (con) { delete con; }
    }
    vector<MessageS> call_ID_PW() {
        vector<MessageS> result;
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM members");
        while (res->next()) {
            MessageS temp;
            temp.id = res->getString("ID");
            temp.say = res->getString("PW");
            result.push_back(temp);
        }
        if (stmt) { delete stmt; stmt = nullptr; }
        return result;
    }
    //로그아웃
    void Logout(MessageS msg) {
        for (MessageS i : call_ID_PW()) {
            if (i.id == msg.id) {
                pstmt = con->prepareStatement("UPDATE members SET ONNOFF = 'off' WHERE id = ?");
                pstmt->setString(1, msg.id);
                pstmt->execute();
                if (pstmt) { delete pstmt; pstmt = nullptr; }
                break;
            }
        }
    }
    void Write_User(MessageS msg) {
        pstmt = con->prepareStatement("INSERT INTO members(ID, PW) VALUES(?,?)");
        pstmt->setString(1, msg.id);
        pstmt->setString(2, msg.say);
        pstmt->execute();
        if (pstmt) { delete pstmt; pstmt = nullptr; }
    }
    //로그인
    string Login_process(MessageS msg) {
        string result;
        for (MessageS i : call_ID_PW()) {
            if (i.id == msg.id) {
                if (i.say == msg.say) {
                    result = "로그인 성공";
                    pstmt = con->prepareStatement("UPDATE members SET ONNOFF = 'on' WHERE id = ?");
                    pstmt->setString(1, msg.id);
                    pstmt->execute();
                    if (pstmt) { delete pstmt; pstmt = nullptr; }
                    return result;//정보가 일치하면 해당 유저의 onnoff를 on으로
                }
                else {
                    result = "비밀번호가 맞지 않습니다.";
                    return result;
                }
            }
        }
        result = "입력하신 회원정보로 가입합니다.";
        Write_User(msg);
        return result;//일치하는 아이디가 없으면 회원가입한다.
    }
    //현재 room목록을 방목록 / 방목록 / 방목록으로 출력
    string call_ROOM_LIST() {
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT ID FROM members");
        string result;
        while (res->next()) {
            result += string(" / ") + res->getString("ROOM");
        }
        if (stmt) { delete stmt; stmt = nullptr; }
        return result;
    }
    //현재 접속자 명단을 id / id / id로 출력
    string call_ON_USER() {
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT ID FROM chattingproject.chatting_log");
        string result;
        while (res->next()) {
            result += " / " + res->getString("ID");
        }
        if (stmt) { delete stmt; stmt = nullptr; }
        return result;
    }
    //입력한 ROOM의 채팅내역을 가져온다. 방제 - id : say 로 가져온다.
    string call_ROOM_CHAT_LIST(MessageS msg) {
        string result;
        stmt = con->createStatement();
        string temp = "SELECT ROOM, ID, SAY FROM chattingproject.chatting_log where room = '" + msg.room + "' and DM = '0'";
        res = stmt->executeQuery(temp);
        while (res->next()) {
            string room = res->getString("ROOM");
            string id = res->getString("ID");
            string say = res->getString("SAY");

            result += room + " - " + id + " : " + say + "\n";
        }
        if (stmt) { delete stmt; stmt = nullptr; }
        return result;
    }
    //DB에 메세지 쓰기
    void Write_Chat(MessageS msg) {
        pstmt = con->prepareStatement("INSERT INTO chatting_log(ROOM, ID, TO, SAY) VALUES(?,?,?,?)");
        pstmt->setString(1, msg.room);
        pstmt->setString(2, msg.id);
        pstmt->setString(3, msg.to);
        pstmt->setString(4, msg.say);
        pstmt->execute();
        if (pstmt) { delete pstmt; pstmt = nullptr; }
    }
};
/////////////////////////////////////////////////////////////////////////////////////////////////
#define MAX_SIZE 1024
#define MAX_CLIENT 3

//선언
DB db;
struct SOCKET_INFO {
    SOCKET sck;
    MessageS last;
};
int client_count = 0;
int channel_count = 0;
SOCKET server_sck;
vector<SOCKET_INFO> sck_list;//////////////////////////////////////////////////////////////////////
//함수 색인
void server_init();

void add_client();
void recv_msg(int i);
void CMD_process(int i, MessageS reply);
void ROOM_process(int i, MessageS reply);
void DM_process(int i, MessageS reply);
void LOGIN_process(int i, MessageS reply);

void send_To_ALL(MessageS reply);


void LOGIN_process(int i, MessageS reply) {
    MessageS server_reply;
    server_reply.say = db.Login_process(reply);
    if (server_reply.say == "로그인 성공") {
        client_count++;
        MessageS New_man_announce;
        New_man_announce.say = reply.id + "님이 입장하셨습니다. 현재 접속자 수 " + to_string(client_count) + "명";
        send_To_ALL(New_man_announce);
    }
    send(sck_list[i].sck, reply.pack().c_str(), reply.pack().length(), 0);
    return;
}
void ROOM_process(int i, MessageS reply) {
    for (int i = 0; i < channel_count; i++) {
        if (reply.room == sck_list[i].last.room) {
            send(sck_list[i].sck, reply.pack().c_str(), reply.pack().length(), 0);
        }
    }
    return;
}
void DM_process(int i, MessageS reply) {
    for (int i = 0; i < channel_count; i++) {
        if (reply.to == sck_list[i].last.id) {
            send(sck_list[i].sck, reply.pack().c_str(), reply.pack().length(), 0);
        }
    }
    return;
}
void CMD_process(int i, MessageS reply) {
    MessageS server_reply;
    server_reply.to = reply.id;
    server_reply.cmd = reply.cmd;
    int cmd = stoi(reply.cmd);
    switch (cmd) {
    case 방목록가져오기:
        server_reply.say = db.call_ROOM_LIST();
        break;
    case 방채팅목록가져오기:
        server_reply.say = db.call_ROOM_CHAT_LIST(reply);
        break;
    case 로그인한사람명단:
        server_reply.say = db.call_ON_USER();
        break;
    }
    send(sck_list[i].sck, server_reply.pack().c_str(), server_reply.pack().length(), 0);
    return;
}
void recv_msg(int i) {
    char buffer[MAX_SIZE] = {};
    while (true) {
        ZeroMemory(&buffer, MAX_SIZE);
        int len = recv(sck_list[i].sck, buffer, MAX_SIZE, 0);
        if (len > 0) {
            MessageS reply;
            reply = decode(buffer);
            sck_list[i].last = reply;
            if (reply.lock == "0") {//이때의 요청은 아이디 비번을 입력한 것
                LOGIN_process(i, reply);
            }
            else {//로그인한 사람이 보낸 것
                sck_list[i].last = reply;//이므로 소켓에 적어둔다
                if (reply.cmd != to_string(일반대화)) {//CMD처리
                    CMD_process(i, reply);
                }
                else if (reply.to != default_VAL) {//DM처리
                    DM_process(i, reply);
                }
                else {//일반대화이므로 방이 맞는 사람에게 전함
                    ROOM_process(i, reply);
                }
            }
        }
        else if (len < 0) {
            client_count--;
            MessageS exit_announce;
            exit_announce.say = sck_list[i].last.id + "님이 퇴장하셨습니다.\n현재 접속자 수 - " + to_string(client_count) + "명";
            send_To_ALL(exit_announce);
            closesocket(sck_list[i].sck);
            break;
        }
    }
    return;
}

void del_client(int i) {
    closesocket(sck_list[i].sck);
    //sck_list.erase(sck_list.begin() + idx); // 배열에서 클라이언트를 삭제하게 될 경우 index가 달라지면서 런타임 오류 발생....ㅎ
    client_count--;
}

void send_To_ALL(MessageS reply) {
    for (int i = 0; i < channel_count; i++) {
        send(sck_list[i].sck, reply.pack().c_str(), reply.pack().length(), 0);
    }
}

void add_client() {
    SOCKADDR_IN addr = {};
    int addrsize = sizeof(addr);
    char buf[MAX_SIZE] = { };

    ZeroMemory(&addr, addrsize); // addr의 메모리 영역을 0으로 초기화

    SOCKET_INFO new_client = {};

    new_client.sck = accept(server_sck, (sockaddr*)&addr, &addrsize);

    sck_list.push_back(new_client);

    thread channelon(recv_msg, client_count);

    //client_count++; // client 수 증가.
    channel_count++;

    channelon.join();
}

void server_init() {
    server_sck = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    SOCKADDR_IN server_addr = {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(7777);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); 

    bind(server_sck, (sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_sck, SOMAXCONN); 
    cout << "Server On" << endl;
}

int main() {
    WSADATA wsa;
    int code = WSAStartup(MAKEWORD(2, 2), &wsa);
    MessageS gm;
    gm.room = "[공지]";
    gm.id = "GM주인장";
    if (!code) {
        server_init();
        std::thread channel[MAX_CLIENT];
        for (int i = 0; i < MAX_CLIENT; i++) {
            channel[i] = std::thread(add_client);
        }
        while (1) {
            string text = "";
            getline(cin, gm.say);
            send_To_ALL(gm);
        }
        for (int i = 0; i < MAX_CLIENT; i++) {
            channel[i].join();
        }
        closesocket(server_sck);
    }
    else {
        cout << "프로그램 종료. (Error code : " << code << ")";
    }
    WSACleanup();
    return 0;
}