#pragma once

/**
* 计算类头文件<br/>
* Copyright (c) 2018 Xily.All Rights Reserved.<br/>
* 运行环境建议为Visual Studio 2017<br/>
* 最低要求编译器支持C++11，否则程序将无法运行<br/>
* 注意：该项目必须运行在Windows系统下<br/>
* 该项目在Visual Studio 2017和Mingw gcc on windows 6.3.0(using g++ command with -std=c++11)下编译通过<br/>
* @author 曾宏健 221701423 572089608@qq.com
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