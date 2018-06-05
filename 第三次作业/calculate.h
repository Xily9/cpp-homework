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

#include <stack>
#include "hugeInt.h"
using std::stack;
using std::string;
class Calculate {
public:
    static HugeInt calculate(const string& expression);
    class ParseException :public std::logic_error {
    public:
        explicit ParseException(const string& s) :std::logic_error(s) {}
    };
private:
    static int getLevel(char c);
    static stack<string> getRpn(string expression);
    static stack<string> reserveStack(stack<string> s);
    static HugeInt doRpn(stack<string> rpn);
};