#pragma once
#include <stack>
#include "hugeInt.h"
using std::stack;
using std::string;
class Calculate {
public:
    static HugeInt calculate(const string& expression);
private:
    static int getLevel(char c);
    static stack<string> getRpn(string expression);
    static stack<string> reserveStack(stack<string> s);
    static HugeInt doRpn(stack<string> rpn);
};