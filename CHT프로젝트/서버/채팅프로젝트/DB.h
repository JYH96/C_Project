#pragma once
#include <mysql/jdbc.h>
#include <iostream>
#include <vector>
#include <string>
#include "MessageS.h"

using namespace std;

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
