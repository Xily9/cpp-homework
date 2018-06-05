/**
* 入口文件<br/>
* Copyright (c) 2018 Xily.All Rights Reserved.<br/>
* 运行环境建议为Visual Studio 2017<br/>
* 最低要求编译器支持C++11，否则程序将无法运行<br/>
* 注意：该项目必须运行在Windows系统下<br/>
* 该项目在Visual Studio 2017和Mingw gcc on windows 6.3.0(using g++ command with -std=c++11)下编译通过<br/>
* @author 曾宏健 221701423 572089608@qq.com
* @date 2018.6.4
*/

#include "function.h"
#include "hugeInt.h"
#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
    try {
        while (true) {
            showMainMenu(); //显示主菜单
            switch (getKey()) {
                case 'A':
                    testCalculate(); //各种运算测试
                    break;
                case 'B':
                    testOperators(); //关系运算符测试
                    break;
                case 'C':
                    testSystem(); //进制转换测试
                    break;
                case 'D':
                    testOthers(); //杂项测试
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
    } catch (...) {
        cout << "程序异常终止!" << endl;
    }
}
