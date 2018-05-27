//去除VS的安全警告
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "hugeInt.h"
#include "calculate.h"
#include "function.h"
#include <iomanip>
#include <conio.h>
#include <cassert>
#include <string>
using namespace std;

/**
* 显示主菜单
*/
void showMainMenu() {
    cout << "Copyright (C) 2018 曾宏健(221701423).All Rights Reserved." << endl << endl;
    showTime();
    drawLine('*', 60);
    cout.setf(ios_base::left, ios_base::adjustfield);
    cout << "*    " << setw(54) << "A：各种运算测试" << "*" << endl
        << "*    " << setw(54) << "B：关系运算符测试" << "*" << endl
        << "*    " << setw(54) << "C：测试进制转换" << "*" << endl
        << "*    " << setw(54) << "D：杂项测试" << "*" << endl
        << "*    " << setw(54) << "Q：退出系统" << "*" << endl;
    drawLine('*', 60);
    cout << "请选择（A,B,C,D,Q）：";
}

/**
* 显示系统当前时间
*/
void showTime() {
    const char* weekday[7] = {"日", "一", "二", "三", "四", "五", "六"};
    tm* timeInfo = getTime(); //获得当前时间
    printf("当前日期、时间：%04d.%02d.%02d(星期%s)  %02d:%02d:%02d\n",
           timeInfo->tm_year + 1900,
           timeInfo->tm_mon + 1,
           timeInfo->tm_mday,
           weekday[timeInfo->tm_wday],
           timeInfo->tm_hour,
           timeInfo->tm_min,
           timeInfo->tm_sec);
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
* 测试计算
*/
void testCalculate() {
    showCalculateTips();
    while (true) {
        try {
            string s;
            cout << "表达式：";
            cin >> s;
            cout << "计算结果：" << Calculate::calculate(s) << endl;
        } catch (exception& e) {
            cout << e.what() << endl;
        }
    }
}

/**
* 显示运算操作说明
*/
void showCalculateTips() {
    drawLine('-', 40);
    cout << "操作说明：" << endl
        << "支持的操作符：+ 加，- 减，* 乘，/ 除 ，% 取余，^ 求幂，！阶乘（必须写右操作数，数字随意）" << endl
        << "支持括号运算，支持负数，支持十六进制与八进制运算（输出结果为十进制数）" << endl
        << "一些简单合法的例子：(5+3)*5 ，-5+3，3-(-5)，5^2+3!0，123*(((5+3)*2)^5)" << endl
        << "Enjoy it!" << endl;
    drawLine('-', 40);
}

/**
 * 测试操作符
 */
void testOperators() {
    int n;
    HugeInt left, right;
    bool result = false;
    while (true) {
        showOperators();
        cout << "请输入上面运算符前的序号：";
        cin >> n;
        cout << "请输入左操作数：";
        cin >> left;
        cout << "请输入右操作数：";
        cin >> right;
        switch (n) {
            case 0:
                result = left < right;
                break;
            case 1:
                result = left <= right;
                break;
            case 2:
                result = left == right;
                break;
            case 3:
                result = left > right;
                break;
            case 4:
                result = left >= right;
                break;
            case 5:
                result = left != right;
                break;
            default:
                break;
        }
        cout << "结果：" << (result ? "true" : "false") << endl;
    }
}

/**
* 显示操作符列表
*/
void showOperators() {
    static const char operators[6][3]{"<", "<=", "==", ">", ">=", "!="};
    drawLine('-', 40);
    for (unsigned i = 0; i < 6; i++) {
        cout << setw(10) << "[" + to_string(i) + "]" + operators[i];
        if (i % 4 == 3) {
            cout << endl;
        }
    }
    cout << endl;
}

/**
 * 测试进制转换
 */
void testSystem() {
    HugeInt hugeInt;
    showSystemMenu();
    const char key = getKey();
    cout << "请输入待转换的数字：(八进制在数字前加0，十六进制在数字前加0X或0x)" << endl;
    cin >> hugeInt;
    cout << "转换结果：";
    switch (key) {
        case 'A':
            cout << hugeInt;
            break;
        case 'B':
            cout << hugeInt.toOct();
            break;
        case 'C':
            cout << hugeInt.toHex();
            break;
        default:
            break;
    }
    cout << endl;
}

/**
 * 显示进制转换菜单
 */
void showSystemMenu() {
    drawLine('*', 60);
    cout.setf(ios_base::left, ios_base::adjustfield);
    cout << "*    " << setw(54) << "A：转十进制" << "*" << endl
        << "*    " << setw(54) << "B：转十六进制" << "*" << endl
        << "*    " << setw(54) << "C：转十六进制" << "*" << endl;
    drawLine('*', 60);
    cout << "请选择（A,B,C）：";
}

/**
 * 测试其他功能
 */
void testOthers() {
    const clock_t start = clock();
    //测试前后++ --
    HugeInt a = HugeInt("1");
    assert(a++ == HugeInt("1"));
    assert(++a == HugeInt("3"));
    assert(a-- == HugeInt("3"));
    assert(--a == HugeInt("1"));
    //测试+= -= *= /= %=
    assert((a += 3) == HugeInt("4"));
    assert((a -= 3) == HugeInt("1"));
    assert((a *= 3) == HugeInt("3"));
    assert((a /= 3) == HugeInt("1"));
    assert((a %= 3) == HugeInt("1"));
    //测试整型或字符串与巨型整数的计算
    assert(345 + HugeInt("123") == 468);
    assert(HugeInt(100) + HugeInt(900) == 1000);
    assert(HugeInt(1000) / 10 == HugeInt(100));
    assert(HugeInt(1000) - 900 == 100);
    assert("1000" - HugeInt(900) == 100);
    assert(HugeInt(900) - "100" == 800);
    const clock_t end = clock();
    cout << "恭喜,全部样例通过!用时" << (double(end - start)) / CLK_TCK << "s" << endl;
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
* 画分割线
* @param c 分割字符
* @param length 字符个数
*/
void drawLine(const char c, const int length) {
    cout << string(length, c) << std::endl;
}
