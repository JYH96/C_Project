#pragma comment(lib, "ws2_32.lib") //������� ���̺귯���� ��ũ. ���� ���̺귯�� ����
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
//#include "DB.h"////////////////////////////////////////////////////////////////////////////////
class DB {
    sql::mysql::MySQL_Driver* driver; // ���� �������� �ʾƵ� Connector/C++�� �ڵ����� ������ ��
    sql::Connection* con;
    sql::Statement* stmt;
    sql::ResultSet* res;
    sql::PreparedStatement* pstmt;
public:
    DB() {
        const string server = "tcp://127.0.0.1:3306"; // �����ͺ��̽� �ּ�
        const string username = "root"; // �����ͺ��̽� �����
        const string password = "qpwoei13"; // �����ͺ��̽� ���� ��й�ȣ
        try {
            driver = sql::mysql::get_mysql_driver_instance();
            con = driver->connect(server, username, password);
        }
        catch (sql::SQLException& e) {
            cout << "Could not connect to server. Error message: " << e.what() << endl;
            exit(1);
        }
        con->setSchema("chattingproject");
        // db �ѱ� ������ ���� ����
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
    //�α׾ƿ�
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
    //�α���
    string Login_process(MessageS msg) {
        string result;
        for (MessageS i : call_ID_PW()) {
            if (i.id == msg.id) {
                if (i.say == msg.say) {
                    result = "�α��� ����";
                    pstmt = con->prepareStatement("UPDATE members SET ONNOFF = 'on' WHERE id = ?");
                    pstmt->setString(1, msg.id);
                    pstmt->execute();
                    if (pstmt) { delete pstmt; pstmt = nullptr; }
                    return result;//������ ��ġ�ϸ� �ش� ������ onnoff�� on����
                }
                else {
                    result = "��й�ȣ�� ���� �ʽ��ϴ�.";
                    return result;
                }
            }
        }
        result = "�Է��Ͻ� ȸ�������� �����մϴ�.";
        Write_User(msg);
        return result;//��ġ�ϴ� ���̵� ������ ȸ�������Ѵ�.
    }
    //���� room����� ���� / ���� / �������� ���
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
    //���� ������ ����� id / id / id�� ���
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
    //�Է��� ROOM�� ä�ó����� �����´�. ���� - id : say �� �����´�.
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
    //DB�� �޼��� ����
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

//����
DB db;
struct SOCKET_INFO {
    SOCKET sck;
    MessageS last;
};
int client_count = 0;
int channel_count = 0;
SOCKET server_sck;
vector<SOCKET_INFO> sck_list;//////////////////////////////////////////////////////////////////////
//�Լ� ����
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
    if (server_reply.say == "�α��� ����") {
        client_count++;
        MessageS New_man_announce;
        New_man_announce.say = reply.id + "���� �����ϼ̽��ϴ�. ���� ������ �� " + to_string(client_count) + "��";
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
    case ���ϰ�������:
        server_reply.say = db.call_ROOM_LIST();
        break;
    case ��ä�ø�ϰ�������:
        server_reply.say = db.call_ROOM_CHAT_LIST(reply);
        break;
    case �α����ѻ�����:
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
            if (reply.lock == "0") {//�̶��� ��û�� ���̵� ����� �Է��� ��
                LOGIN_process(i, reply);
            }
            else {//�α����� ����� ���� ��
                sck_list[i].last = reply;//�̹Ƿ� ���Ͽ� ����д�
                if (reply.cmd != to_string(�Ϲݴ�ȭ)) {//CMDó��
                    CMD_process(i, reply);
                }
                else if (reply.to != default_VAL) {//DMó��
                    DM_process(i, reply);
                }
                else {//�Ϲݴ�ȭ�̹Ƿ� ���� �´� ������� ����
                    ROOM_process(i, reply);
                }
            }
        }
        else if (len < 0) {
            client_count--;
            MessageS exit_announce;
            exit_announce.say = sck_list[i].last.id + "���� �����ϼ̽��ϴ�.\n���� ������ �� - " + to_string(client_count) + "��";
            send_To_ALL(exit_announce);
            closesocket(sck_list[i].sck);
            break;
        }
    }
    return;
}

void del_client(int i) {
    closesocket(sck_list[i].sck);
    //sck_list.erase(sck_list.begin() + idx); // �迭���� Ŭ���̾�Ʈ�� �����ϰ� �� ��� index�� �޶����鼭 ��Ÿ�� ���� �߻�....��
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

    ZeroMemory(&addr, addrsize); // addr�� �޸� ������ 0���� �ʱ�ȭ

    SOCKET_INFO new_client = {};

    new_client.sck = accept(server_sck, (sockaddr*)&addr, &addrsize);

    sck_list.push_back(new_client);

    thread channelon(recv_msg, client_count);

    //client_count++; // client �� ����.
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
    gm.room = "[����]";
    gm.id = "GM������";
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
        cout << "���α׷� ����. (Error code : " << code << ")";
    }
    WSACleanup();
    return 0;
}