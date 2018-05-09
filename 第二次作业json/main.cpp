/**
* 入口文件<br/>
* Copyright (c) 2018 Xily.All Rights Reserved.<br/>
* 运行环境建议为Visual Studio 2017<br/>
* 最低要求编译器支持C++11，否则程序将无法运行<br/>
* 注意：该项目必须运行在Windows系统下<br/>
* 该项目在Visual Studio 2017和Mingw gcc on windows 6.3.0(using g++ command with -std=c++11)下编译通过<br/>
* 本程序使用json作为数据存储格式<br/>
* @author 曾宏健 221701423 572089608@qq.com
* @date 2018.5.1
*/

#include "dbhelper.h"
#include "function.h"
#include "student.h"
#include <iostream>
#include <iomanip>
using namespace std;

void showMainMenu();
void showTime();

/**
 * 入口函数
 */
int main() {
    setConsoleTitle("学籍信息管理系统");
    try {
        DbHelper dbHelper("data/data.json");
        Student student(move(dbHelper));
        while (true) {
            showMainMenu(); //显示主菜单
            switch (getKey()) {
                case 'A':
                    student.addData();//添加
                    break;
                case 'B':
                    student.showData();//展示
                    break;
                case 'C':
                    student.findData();//查找
                    break;
                case 'D':
                    student.sortData();//排序
                    break;
                case 'E':
                    student.countData();//统计
                    break;
                case 'Q':
                    return 0;
                default:
                    //用户按下了错误的按键
                    cout << endl << "\a选择错误，请重新选择......" << endl << endl;
                    break;
            }
            system("pause");
            system("cls");
        }
    } catch (exception& e) {
        //捕获到异常
        cout << endl << "Oh My God!程序发生运行时异常!" << endl;
        cout << "详细信息:" << endl;
        cout << e.what() << endl;
        exit(1);
    }
}


/**
* 显示主菜单
*/
void showMainMenu() {
    cout << "Copyright (C) 2018 曾宏健(221701423).All Rights Reserved." << endl << endl;
    showTime();
    drawLine('*', 60);
    cout.setf(ios_base::left, ios_base::adjustfield);
    cout << "*    " << setw(54) << "A：添加学生数据" << "*" << endl
        << "*    " << setw(54) << "B：显示学生数据" << "*" << endl
        << "*    " << setw(54) << "C：查找学生数据" << "*" << endl
        << "*    " << setw(54) << "D：排序学生数据" << "*" << endl
        << "*    " << setw(54) << "E：统计分析学生数据" << "*" << endl
        << "*    " << setw(54) << "Q：退出系统" << "*" << endl;
    drawLine('*', 60);
    cout << "请选择（A,B,C,D,E,Q）：";
}

/**
* 显示系统当前时间
*/
void showTime() {
    const char* weekday[7] = { "日", "一", "二", "三", "四", "五", "六" };
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