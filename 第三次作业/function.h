#pragma once

/**
* ������ͷ�ļ�<br/>
* Copyright (c) 2018 Xily.All Rights Reserved.<br/>
* ���л�������ΪVisual Studio 2017<br/>
* ���Ҫ�������֧��C++11����������޷�����<br/>
* ע�⣺����Ŀ����������Windowsϵͳ��<br/>
* ����Ŀ��Visual Studio 2017��Mingw gcc on windows 6.3.0(using g++ command with -std=c++11)�±���ͨ��<br/>
* @author ���꽡 221701423 572089608@qq.com
* @date 2018.6.4
*/

#include <ctime>
//�������ڲ��Եĺ�
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
