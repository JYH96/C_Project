#pragma once
#include <mysql/jdbc.h>
#include <iostream>
#include <vector>
#include <string>
#include "MessageS.h"

using namespace std;

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
