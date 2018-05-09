/**
* ������ʵ���ļ�<br/>
* Copyright (c) 2018 Xily.All Rights Reserved.
* @author ���꽡 221701423 572089608@qq.com
* @date 2018.4.29
*/

#include "function.h"
#include "dbhelper.h"
#include <string>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

/**
* ���ָ���
* @param c �ָ��ַ�
* @param length �ַ�����
*/
void drawLine(const char c, const int length) {
    cout << string(length, c) << std::endl;
}

/**
* ��ȡ���֤����ĵ�18λ
* @param s ǰ17λ�ַ���
* @return ��18λ�ַ�
*/
char getPersonId18(const string& s) {
    static const int b[17] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
    static const char c[11] = {'1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2'};
    int sum = 0;
    for (int i = 0; i < 17; i++) {
        sum += (s[i] - 48) * b[i];
    }
    return c[sum % 11];
}

/**
* ��ô洢��ǰʱ���ʱ��ṹָ��
* @return ʱ��ṹָ��
*/
tm* getTime() {
    time_t rawtime;
    time(&rawtime);
    return localtime(&rawtime);
}

/**
* �ж�����
* @param year ���
* @return true ������
* @return false ��������
*/
bool isLeapYear(const int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

/**
* ������ڵĺϷ���
* @param year ��
* @param month ��
* @param day ��
* @return true ���ںϷ�
* @return false ���ڲ��Ϸ�
*/
bool checkDate(const int year, const int month, const int day) {
    int dayOfMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isLeapYear(year)) {
        dayOfMonth[1] = 29;
    }
    return month <= 12 && month >= 1
        && day <= dayOfMonth[month - 1] && day >= 1;
}

/**
* �ж��ַ����Ƿ�Ϊ(�Ǹ�)����
* @param str Ҫ�жϵ��ַ���
* @return true ������
* @return false ��������
*/
bool isInt(const string& str) {
    for (char i : str) {
        if (i < 48 || i > 57) {
            return false;
        }
    }
    return true;
}

/**
* �ж��ַ����Ƿ�Ϊ����
* @param str Ҫ�жϵ��ַ���
* @return true ������
* @return false ��������
*/
bool isAllChinese(const string& str) {
    for (unsigned i = 0; i < str.size() - 1; i += 2) {
        if (!(str[i] & 0x80 && str[i + 1] & 0x80)) {
            return false;
        }
    }
    return true;
}

/**
* �������в�������
* @param all �����ҵ�����
* @param in Ҫ���ҵ�����
* @return Ҫ���ҵ�������λ��(-1Ϊδ�ҵ�)
*/
int findInInt(const int all, const int in) {
    return to_string(all).find(to_string(in));
}

/**
* ��ȡ����̨���
* @return ����̨���
*/
int getConsoleWidth() {
    static int width = 0;
    if (!width) {
        CONSOLE_SCREEN_BUFFER_INFO bInfo;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bInfo);
        width = bInfo.dwSize.X - 1;
    }
    return width;
}

/**
* ���ÿ���̨����
* @param title
*/
void setConsoleTitle(const char* title) {
    SetConsoleTitleA(title);
}

/**
* ��ȡ����ʾ�������ĸ
* @return ��ȡ������ĸ(��ת��Ϊ��д)
*/
char getKey() {
    const char key = toupper(_getch()); //ʵʱ��ȡ���벢ת��Ϊ��д
    cout << key << endl;                //��ʾ���������
    return key;
}


/**
* չʾ�б�˵�
* @param list string����
* @param size �����С
*/
void showListMenu(const char* list[], const unsigned size) {
    const int width = getConsoleWidth();
    const int lineLength = 6;
    drawLine('-', 40);
    cout.setf(ios_base::left, ios_base::adjustfield);
    for (unsigned i = 0; i < size; i++) {
        cout << setw(width / lineLength) << "[" + to_string(i) + "] " + list[i];
        if (i % lineLength == lineLength - 1 && i < size - 1) {
            cout << endl;
        }
    }
    cout << endl;
    drawLine('-', 40);
}

/**
* չʾ�б�˵�
* @param value json����
* @param lineLength һ����ʾ����
* @param key Ҫչʾ�ļ���(Ĭ��Ϊ��)
*/
void showListMenu(const Json::Value& value, const unsigned lineLength, const string& key) {
    const int width = getConsoleWidth();
    drawLine('-', 40);
    cout.setf(ios_base::left, ios_base::adjustfield);
    for (unsigned i = 0; i < value.size(); i++) {
        cout << setw(width / lineLength) << "[" + to_string(i) + "] " +
            (key.empty() ? value[i].asString() : value[i][key].asString());
        if (i % lineLength == lineLength - 1 && i < value.size() - 1) {
            cout << endl;
        }
    }
    cout << endl;
    drawLine('-', 40);
}

/**
* ���б��л�ȡ����
* @param dbHelper ���ݰ�����
* @param type ֵ����
* @param lineLength һ����ʾ����
* @return ��ȡ�����ַ���
*/
string inputList(const DbHelper& dbHelper, const string& type, const unsigned lineLength) {
    unsigned n;
    const Json::Value&& value = dbHelper.getValue();
    showListMenu(value, lineLength);
    while (true) {
        cout << "������" << type << "ǰ������(Ĭ��Ϊ" << value[0].asString() << ")��";
        if (cin.peek() != '\n') {
            cin >> n;
            cin.ignore(1024, '\n');
            if (cin.fail()) {
                cout << "��������ݲ��Ϸ�,����������!" << endl;
                cin.clear();
                cin.ignore(1024, '\n');
            } else if (n >= value.size()) {
                cout << "�������������,����������!" << endl;
            } else {
                break;
            }
        } else {
            cin.ignore(1024, '\n');
            n = 0;
            break;
        }
    }
    cout << "��ѡ�����[" << n << "] " + value[n].asString() << endl;
    return value[n].asString();
}
