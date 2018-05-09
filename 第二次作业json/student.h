#pragma once

/**
* ѧ����ͷ�ļ�<br/>
* ��ѧ��������ɾ�Ĳ�Ȳ���<br/>
* Copyright (c) 2018 Xily.All Rights Reserved.
* @author ���꽡 221701423 572089608@qq.com
* @date 2018.5.5
*/

#include "json.h"
#include "dbhelper.h"
#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;
using std::cin;

class Student {
public:
    explicit Student(DbHelper&& dbHelper): dbHelper(dbHelper) {
    }

    void addData();
    void showData(Json::Value value = Json::Value());
    void findData();
    void sortData();
    void countData();
private:
    string id;                  //ѧ��
    string collegeId;           //ѧ���е�ѧԺ����
    string majorId;             //ѧ���е�רҵ����
    int inYear = 0;             //ѧ���е���ѧ���
    bool isChinese = false;     //�Ƿ����й���
    string birthDateFormat;     //��λ��ʽ����ĳ�������
    int sex = 0;                //�Ա�
    int collegeIndex = 0;       //��¼ѧԺ�������±������ж�רҵ
    bool isUpdate = false;      //��¼��û�з������ݸ����¼�
    DbHelper& dbHelper;         //���ݰ�����
    static const int size = 19; //�ֶ�����
    const char* types[size] = {
        "ѧ��", "����", "�Ա�", "����", "��������", "����", "����״��",
        "������ò", "���֤��", "ѧ�����", "��ѧ����", "��ѧ��ʽ", "ѧԺ", "רҵ", "ѧ��",
        "�������", "�꼶", "�༶��", "����Ա"
    }; //�ֶμ��
    const char* keys[size] = {
        "id", "name", "sex", "country", "birthDate", "nation", "marry",
        "politics", "personId", "studentType", "inDate", "inType", "college", "major",
        "length", "level", "grade", "class", "instructor"
    }; //�ֶ���
    Json::Value inputData();
    static string inputCountry();
    static string inputNation();
    static string inputPolitics();
    static string inputMarry();
    static string inputStudentType();
    static string inputInType();
    static string inputLevel();
    string inputCollege();
    string inputMajor() const;
    template <typename T>
    static string getInput(const string& type, const string& message, T check, bool useDefault = false,
        const string& defaultValue = "");
    void showLine(const string& id);
    void deleteData(const string& major, const string& grade);
    void deleteByIndex(int index);
    void editByIndex(int index);
    void showCountData(const vector<vector<string>>& vecs, unsigned i, const Json::Value& value, int by[]) const;
    string checkId(const string& id);
    string checkBirthDate(const string& birthDate);
    string checkSex(const string& sex);
    string checkPersonId(const string& personId) const;
    string checkName(const string& name) const;
    string checkGrade(const string& grade) const;
    string checkInDate(const string& inDate) const;
    string checkClass(const string& cls) const;
    string checkInstructor(const string& instructor) const;
    //����ʧ���쳣
    class CheckException :public std::exception {
    public:
        explicit CheckException(const string& s) :exception(std::logic_error(s.c_str())) {}
    };
};

/**
* �Ӽ����ϻ�ȡ�ַ�������У��
* @tparam T ��������
* @param type ֵ����
* @param message ��ʾ��Ϣ
* @param check �ص�����
* @param useDefault �Ƿ���Ĭ��ֵ,Ĭ��û��
* @param defaultValue Ĭ��ֵ,Ĭ�Ͽ�
* @return ��ȡ��������ͨ�����ַ���
*/
template <typename T>
string Student::getInput(const string& type, const string& message, T check,const bool useDefault,
    const string& defaultValue) {
    string str;
    while (true) {
        cout << "������" << type;
        if (useDefault) {
            cout << "(Ĭ��Ϊ" << defaultValue << ")";
        }
        cout << std::endl;
        if (!message.empty()) {
            cout << message << std::endl;
        }
        if (useDefault && cin.peek() == '\n') {
            str = defaultValue;
        } else {
            cin >> str;
        }
        cin.ignore(1024, '\n');
        try {
            return check(str);
        } catch (CheckException& e) {
            cout << e.what() << std::endl;
        }
    }
}