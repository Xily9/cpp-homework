#pragma once

/**
* 函数库头文件<br/>
* Copyright (c) 2018 Xily.All Rights Reserved.<br/>
* 运行环境建议为Visual Studio 2017<br/>
* 最低要求编译器支持C++11，否则程序将无法运行<br/>
* 注意：该项目必须运行在Windows系统下<br/>
* 该项目在Visual Studio 2017和Mingw gcc on windows 6.3.0(using g++ command with -std=c++11)下编译通过<br/>
* @author 曾宏健 221701423 572089608@qq.com
* @date 2018.6.4
*/

#include <ctime>
//定义用于测试的宏
#define TEST(x) testExpression(#x,x);
void showMainMenu();
void showTime();
tm* getTime();
void testCalculate();
void showCalculateTips();
void testOperators();
void showOperators();
void testSystem();
void showSystemMenu();
void testOthers();
void drawLine(char c, int length);
char getKey();
void testExpression(const char* x, bool b);
void setColor(unsigned short ForeColor = 7, unsigned short BackGroundColor = 0);
