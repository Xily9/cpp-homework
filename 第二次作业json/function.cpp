/**
* 函数库实现文件<br/>
* Copyright (c) 2018 Xily.All Rights Reserved.
* @author 曾宏健 221701423 572089608@qq.com
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
* 画分割线
* @param c 分割字符
* @param length 字符个数
*/
void drawLine(const char c, const int length) {
    cout << string(length, c) << std::endl;
}

/**
* 获取身份证号码的第18位
* @param s 前17位字符串
* @return 第18位字符
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
* 获得存储当前时间的时间结构指针
* @return 时间结构指针
*/
tm* getTime() {
    time_t rawtime;
    time(&rawtime);
    return localtime(&rawtime);
}

/**
* 判断闰年
* @param year 年份
* @return true 是闰年
* @return false 不是闰年
*/
bool isLeapYear(const int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

/**
* 检查日期的合法性
* @param year 年
* @param month 月
* @param day 日
* @return true 日期合法
* @return false 日期不合法
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
* 判断字符串是否为(非负)整数
* @param str 要判断的字符串
* @return true 是整数
* @return false 不是整数
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
* 判断字符串是否为中文
* @param str 要判断的字符串
* @return true 是中文
* @return false 不是中文
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
* 在整数中查找整数
* @param all 被查找的整数
* @param in 要查找的整数
* @return 要查找的整数的位置(-1为未找到)
*/
int findInInt(const int all, const int in) {
    return to_string(all).find(to_string(in));
}

/**
* 获取控制台宽度
* @return 控制台宽度
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
* 设置控制台标题
* @param title
*/
void setConsoleTitle(const char* title) {
    SetConsoleTitleA(title);
}

/**
* 获取并显示输入的字母
* @return 获取到的字母(已转化为大写)
*/
char getKey() {
    const char key = toupper(_getch()); //实时获取输入并转换为大写
    cout << key << endl;                //显示输入的内容
    return key;
}


/**
* 展示列表菜单
* @param list string数组
* @param size 数组大小
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
* 展示列表菜单
* @param value json容器
* @param lineLength 一行显示数量
* @param key 要展示的键名(默认为空)
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
* 从列表中获取输入
* @param dbHelper 数据帮助类
* @param type 值文字
* @param lineLength 一行显示数量
* @return 获取到的字符串
*/
string inputList(const DbHelper& dbHelper, const string& type, const unsigned lineLength) {
    unsigned n;
    const Json::Value&& value = dbHelper.getValue();
    showListMenu(value, lineLength);
    while (true) {
        cout << "请输入" << type << "前面的序号(默认为" << value[0].asString() << ")：";
        if (cin.peek() != '\n') {
            cin >> n;
            cin.ignore(1024, '\n');
            if (cin.fail()) {
                cout << "输入的内容不合法,请重新输入!" << endl;
                cin.clear();
                cin.ignore(1024, '\n');
            } else if (n >= value.size()) {
                cout << "输入的内容有误,请重新输入!" << endl;
            } else {
                break;
            }
        } else {
            cin.ignore(1024, '\n');
            n = 0;
            break;
        }
    }
    cout << "您选择的是[" << n << "] " + value[n].asString() << endl;
    return value[n].asString();
}
