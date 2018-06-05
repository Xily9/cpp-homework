/**
* 计算类实现文件<br/>
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
#include "calculate.h"
using namespace std;

/**
 * 计算表达式
 * @param expression 表达式
 * @return 计算结果
 */
HugeInt Calculate::calculate(const string& expression) {
    return doRpn(getRpn(expression));
}

/**
 * 获取运算符优先级
 * @param c 运算符
 * @return 运算符等级
 */
int Calculate::getLevel(const char c) {
    if (c == '+' || c == '-') {
        return 1;
    }
    if (c == '*' || c == '/' || c == '%') {
        return 2;
    }
    if (c == '^') {
        return 3;
    }
    if (c == '!') {
        return 4;
    }
    if (c == '(' || c == ')') {
        return 0;
    }
    return -1;
}

/**
 * 解析表达式并转化为后缀表达式栈
 * @param expression 表达式
 * @return 后缀表达式栈
 */
stack<string> Calculate::getRpn(string expression) {
    bool isFirst = true;
    stack<char> s1;
    stack<string> s2;
    string temp;
    for (char c : expression) {
        const int level = getLevel(c);
        if (level >= 0) {
            if (!temp.empty()) {
                s2.push(temp);
                temp.clear();
            }
            if (c == '(') {
                isFirst = true;
                s1.push('(');
            } else if (c == ')') {
                while (s1.top() != '(') {
                    s2.push(string(1, s1.top()));
                    s1.pop();
                }
                s1.pop();
            } else {
                if (level == 1 && isFirst) {
                    s2.push("0");
                }
                isFirst = false;
                while (!s1.empty() && getLevel(s1.top()) >= level) {
                    s2.push(string(1, s1.top()));
                    s1.pop();
                }
                s1.push(c);
            }
        } else {
            isFirst = false;
            temp += c;
        }
    }
    if (!temp.empty()) {
        s2.push(temp);
    }
    while (!s1.empty()) {
        if(s1.top()=='(') {
            throw ParseException("Unclosed bracket!");
        }
        s2.push(string(1, s1.top()));
        s1.pop();
    }
    return reserveStack(s2);
}

/**
 * 反转栈
 * @param s 栈
 * @return 反转后的栈
 */
stack<string> Calculate::reserveStack(stack<string> s) {
    stack<string> temp;
    while (!s.empty()) {
        temp.push(s.top());
        s.pop();
    }
    return temp;
}

/**
 * 根据后缀表达式计算出结果
 * @param rpn 后缀表达式栈
 * @return 计算结果
 */
HugeInt Calculate::doRpn(stack<string> rpn) {
    stack<string> stack;
    while (!rpn.empty()) {
        const string temp = rpn.top();
        rpn.pop();
        if (temp == "+" || temp == "-" || temp == "*" || temp == "/" || temp == "%" || temp == "^" || temp == "!") {
            if (stack.size() < 2) {
                throw ParseException("Illegal expression!");
            }
            const HugeInt h1(stack.top());
            stack.pop();
            HugeInt h2(stack.top());
            stack.pop();
            if (temp == "+") {
                stack.push(string(h2 + h1));
            } else if (temp == "-") {
                stack.push(string(h2 - h1));
            } else if (temp == "*") {
                stack.push(string(h2 * h1));
            } else if (temp == "/") {
                stack.push(string(h2 / h1));
            } else if (temp == "^") {
                stack.push(string(h2 ^ h1));
            } else if (temp == "!") {
                stack.push(string(h2.factorial()));
            } else {
                stack.push(string(h2 % h1));
            }
        } else {
            stack.push(temp);
        }
    }
    return stack.top();
}
