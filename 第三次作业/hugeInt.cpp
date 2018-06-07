/**
* 巨型整数类实现文件<br/>
* Copyright (c) 2018 Xily.All Rights Reserved.<br/>
* 运行环境建议为Visual Studio 2017<br/>
* 最低要求编译器支持C++11，否则程序将无法运行<br/>
* 注意：该项目必须运行在Windows系统下<br/>
* 该项目在Visual Studio 2017和Mingw gcc on windows 6.3.0(using g++ command with -std=c++11)下编译通过<br/>
* @author 曾宏健 221701423 572089608@qq.com
* @date 2018.6.4
*/

#include "hugeInt.h"
#include <utility>
#include <map>
#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

/**
 * 构造函数
 * @param number 字符串巨型整数
 */
HugeInt::HugeInt(const string& number) {
    setNumber(number);
}

/**
 * 构造函数
 * @param number 字符串巨型整数
 */
HugeInt::HugeInt(const char* number) {
    setNumber(number);
}

/**
 * 构造函数
 * @param number 整数
 */
HugeInt::HugeInt(const int number): HugeInt(to_string(number)) {
}

/**
 * 默认构造函数
 */
HugeInt::HugeInt() : number("0") {
}

/**
 * 构造函数
 * @param number 长整数
 */
HugeInt::HugeInt(const long long number): HugeInt(to_string(number)) {
}

/**
 * 获取十进制巨型整数的字符串
 * @return 十进制巨型整数的字符串
 */
string HugeInt::getNumber() const {
    if (isMinus) {
        //是负数就在前面加负号
        string result;
        result += '-';
        result += number;
        return result;
    }
    return number;
}

/**
 * 设置数字
 * @param number 字符串巨型整数
 */
void HugeInt::setNumber(string number) {
    if (number == "0" || number == "-0") {
        //数字为0
        isMinus = false;
        number = "0";
    } else {
        if (number[0] == '-') {
            //负数
            isMinus = true;
            number = number.substr(1); //去负号
        } else if (number[0] == '+') {
            isMinus = false;
            number = number.substr(1); //去正号
        } else {
            isMinus = false;
        }
        if (number[0] == '0') {
            if (number[1] == 'x' || number[1] == 'X') {
                //十六进制
                base = 16;
                number = number.substr(2); //去0X/0x
                //判断数字是否合法
                if (number.find_first_not_of("1234567890ABCDEFabcdef") != string::npos) {
                    throw IllegalNumberException();
                }
            } else {
                //八进制
                base = 8;
                number = number.substr(1); //去0
                //判断数字是否合法
                if (number.find_first_not_of("12345670") != string::npos) {
                    throw IllegalNumberException();
                }
            }
            number = toDec(eatZero(number));
        } else {
            base = 10;
            //判断数字是否合法
            if (number.find_first_not_of("1234567890") != string::npos) {
                throw IllegalNumberException();
            }
        }
    }
    this->number = number;
}

/**
 * 加法
 * @param hugeInt 巨型整数
 * @return 计算后的巨型整数
 */
HugeInt& HugeInt::add(const HugeInt& hugeInt) {
    if (isMinus != hugeInt.isMinus) {
        //如果两个操作数符号不一致,就转换为减法
        return subtract(-hugeInt);
    }
    int b = 0;
    string result;
    bool isNotEnd1 = true, isNotEnd2 = true;
    string temp1(number);
    string temp2(hugeInt.number);
    reverse(temp1.begin(), temp1.end()); //倒序
    reverse(temp2.begin(), temp2.end()); //倒序
    string::const_iterator iterator1 = temp1.begin(), iterator2 = temp2.begin();
    const string::const_iterator iterator1End = temp1.end(), iterator2End = temp2.end();
    while (isNotEnd1 || isNotEnd2) {
        //计算每位数字
        const int a = (isNotEnd1 ? *iterator1 - 48 : 0) + (isNotEnd2 ? *iterator2 - 48 : 0) + b;
        b = a / 10; //进位
        result += char(a % 10 + 48);
        if (isNotEnd1) {
            ++iterator1;
            if (iterator1 == iterator1End) {
                isNotEnd1 = false;
            }
        }
        if (isNotEnd2) {
            ++iterator2;
            if (iterator2 == iterator2End) {
                isNotEnd2 = false;
            }
        }
    }
    if (b > 0) {
        result += char(b + 48); //补上多余的进位
    }
    reverse(result.begin(), result.end()); //把计算结果倒过来
    number = result;
    return *this;
}

/**
* 减法
* @param hugeInt 巨型整数
* @return 计算后的巨型整数
*/
HugeInt& HugeInt::subtract(const HugeInt& hugeInt) {
    if (isMinus != hugeInt.isMinus) {
        //如果两个操作数符号不一致,就转换为加法
        return add(-hugeInt);
    }
    if (abs(*this) < INT_MAX && abs(hugeInt) < INT_MAX) {
        //两个操作数均在int范围内,直接减
        *this = int(*this) - int(hugeInt);
    } else {
        int b = 0;
        string result, temp1, temp2;
        bool isNotEnd = true;
        if (*this == hugeInt) {
            number = "0";
            return *this;
        }
        //判断两个操作数绝对值的大小,大的作为被减数,小的作为减数
        if (abs(*this) > abs(hugeInt)) {
            temp1 = number;
            temp2 = hugeInt.number;
        } else {
            temp1 = hugeInt.number;
            temp2 = number;
            isMinus = !isMinus;
        }
        reverse(temp1.begin(), temp1.end());
        reverse(temp2.begin(), temp2.end());
        string::const_iterator iterator1 = temp1.begin(), iterator2 = temp2.begin();
        const string::const_iterator iterator1End = temp1.end(), iterator2End = temp2.end();
        //被减数肯定比减数大,所以不需要考虑减数比被减数先读完的情况
        while (iterator1 != iterator1End) {
            //计算每一位的数字
            const int a = (*iterator1 - 48) - (isNotEnd ? *iterator2 - 48 : 0) + b;
            b = (a - 9) / 10; //计算补差
            result += char(a - b * 10 + 48);
            ++iterator1;
            if (isNotEnd) {
                ++iterator2;
                if (iterator2 == iterator2End) {
                    isNotEnd = false;
                }
            }
        }
        reverse(result.begin(), result.end());
        number = eatZero(result); //把数字倒过来并去除多余的0
    }
    return *this;
}

/**
* 乘法
* @param hugeInt 巨型整数
* @return 计算后的巨型整数
*/
HugeInt& HugeInt::multiply(const HugeInt& hugeInt) {
    int b = 0, c = 0;
    if (*this == 0 || hugeInt == 0) {
        //任何数乘0结果都为0
        number = "0";
        isMinus = false;
    } else {
        const bool check1 = abs(*this) <= INT_MAX / 10;
        const bool check2 = abs(hugeInt) <= INT_MAX / 10;
        if (check1 || check2) {
            //如果其中一个操作数小于INT_MAX/10,可对其做优化,即直接用大数的每一位直接与小数相乘,不必模拟简单乘法
            int aint;
            HugeInt bHuge;
            string result;
            if (check1) {
                aint = std::abs(int(*this));
                bHuge = hugeInt;
            } else {
                aint = std::abs(int(hugeInt));
                bHuge = *this;
            }
            string temp(bHuge.number);
            reverse(temp.begin(), temp.end()); //倒序
            const string::const_iterator iteratorEnd = temp.end();
            for (auto iterator = temp.begin(); iterator != iteratorEnd; ++iterator) {
                b = (*iterator - 48) * aint + c;
                result += char(b % 10 + 48);
                c = b / 10;
            }
            if (c > 0) {
                while (c > 0) {
                    result += char(c % 10 + 48);
                    c /= 10;
                }
            }
            reverse(result.begin(), result.end()); //把计算结果倒过来
            number = eatZero(result);
        } else {
            HugeInt result;
            string temp1(hugeInt.number), temp2(number);
            reverse(temp1.begin(), temp1.end()); //倒序
            reverse(temp2.begin(), temp2.end()); //倒序
            const string::const_iterator iterator1End = temp1.end(), iterator2End = temp2.end();
            for (auto iterator = temp1.begin(); iterator != iterator1End; ++iterator) {
                if (*iterator == '0') {
                    //如果读到0,0与任何数相乘都为0,所以直接不加
                    c++;
                } else if (*iterator == '1') {
                    //读到1则加本身*10
                    result += number + string(c++, '0');
                } else {
                    string temp(c++, '0');
                    for (auto iterator2 = temp2.begin(); iterator2 != iterator2End; ++iterator2) {
                        //计算每一位数字
                        const int a = int(*iterator - 48) * int(*iterator2 - 48) + b;
                        //计算进位
                        b = a / 10;
                        temp += char(a % 10 + 48);
                    }
                    if (b > 0) {
                        temp += char(b + 48); //补上多余的进位
                        b = 0;
                    }
                    reverse(temp.begin(), temp.end()); //把计算结果倒过来
                    result += temp;
                }
            }
            number = result.number;
        }
        isMinus = isMinus ^ hugeInt.isMinus; //判断正负
    }
    return *this;
}

/**
* 除法
* @param hugeInt 巨型整数
* @return 计算后的巨型整数
*/
HugeInt& HugeInt::divide(const HugeInt& hugeInt) {
    if (hugeInt == 0) {
        //除数不能为0
        throw DivideByZeroException();
    }
    if (abs(*this) < abs(hugeInt)) {
        //如果被除数的绝对值小于除数,结果就为0
        number = "0";
        isMinus = false;
        return *this;
    }
    if (abs(*this) < INT_MAX && abs(hugeInt) < INT_MAX) {
        //两个操作数均在int范围内,直接除
        *this = int(*this) / int(hugeInt);
    } else {
        //e.g. 123456/21 首先得先截取12然后除以21
        const int a = hugeInt.number.size();
        HugeInt temp = number.substr(0, a);
        const bool check = abs(hugeInt) < int(10e8);
        string result;
        int temp3 = 0, div = 0;
        if (check) {
            //如果除数小于10^8,可对其做优化,即直接将截取的数字与除数相除,不必模拟除法
            temp3 = int(temp);
            div = int(hugeInt);
        }
        for (unsigned b = a; b <= number.size(); b++) {
            if (check) {
                result += char(temp3 / div + 48);
                if (b < number.size()) {
                    temp3 = temp3 % div * 10 + number.at(b) - 48;
                }
            } else {
                int c = 0; //每一位的数字
                //e.g. 12345*?=123456,以下通过123456-c*12345<0计算c
                while (true) {
                    temp -= hugeInt.number;
                    if (temp.isMinus) {
                        break;
                    }
                    c++;
                }
                result += char(c + 48);
                temp += hugeInt;
                if (b < number.size()) {
                    if (temp == "0") {
                        temp.number = number.at(b); //把被除数后一位数字继承下来
                    } else {
                        temp.number += number.at(b); //把被除数后一位数字继承下来
                    }
                    temp.number = eatZero(temp.number);
                }
            }
        }
        number = eatZero(result);            //去除多余的0
        isMinus = isMinus ^ hugeInt.isMinus; //判断正负
    }
    return *this;
}

/**
* 求余数
* @param hugeInt 巨型整数
* @return 计算后的巨型整数
*/
HugeInt& HugeInt::mod(const HugeInt& hugeInt) {
    //e.g. 12%5=12-(12/5)*5=12-2*5=2
    return subtract(hugeInt * (*this / hugeInt));
}

/**
 * 求n次方
 * @param number 幂指数
 * @return 计算后的巨型整数
 */
HugeInt& HugeInt::pow(const HugeInt& number) {
    if (number >= 1) {
        HugeInt a = number;
        HugeInt temp = *this;
        while ((--a).number != "1") {
            temp *= *this;
        }
        *this = temp;
    } else if (number == 0) {
        //任何数的0次方等于1
        setNumber("1");
    } else {
        //因为是巨型整数类,如果幂指数是负数,那么结果必然不是整数
        throw HugeIntException("Power index cann't be negative");
    }
    return *this;
}

/**
 * 求阶乘
 * @return 计算后的巨型整数
 */
HugeInt& HugeInt::factorial() {
    if (isMinus) {
        //负数没有阶乘
        throw HugeIntException("Cann't perform factorial operations on negative numbers");
    }
    if (number == "0") {
        //0的阶乘为1
        number = "1";
        return *this;
    }
    //int n = 0;
    HugeInt temp = *this;
    while ((--temp).number != "1") {
        *this *= temp;
    }
    return *this;
}

/**
 * 求绝对值
 * @param hugeInt 巨型整数
 * @return 计算后的巨型整数
 */
HugeInt HugeInt::abs(HugeInt hugeInt) {
    hugeInt.isMinus = false;
    return hugeInt;
}

/**
* 加法
* @param left 左操作数
* @param right 右操作数
* @return 计算后的巨型整数
*/
HugeInt operator+(const HugeInt& left, const HugeInt& right) {
    HugeInt result = left;
    result += right;
    return result;
}

/**
* 加法
* @param hugeInt 巨型整数
* @return 计算后的巨型整数
*/
HugeInt& HugeInt::operator+=(const HugeInt& hugeInt) {
    return add(hugeInt);
}

/**
* 减法
* @param left 左操作数
* @param right 右操作数
* @return 计算后的巨型整数
*/
HugeInt operator-(const HugeInt& left, const HugeInt& right) {
    HugeInt result = left;
    result -= right;
    return result;
}

/**
* 减法
* @param hugeInt 巨型整数
* @return 计算后的巨型整数
*/
HugeInt& HugeInt::operator-=(const HugeInt& hugeInt) {
    return subtract(hugeInt);
}

/**
* 乘法
* @param left 左操作数
* @param right 右操作数
* @return 计算后的巨型整数
*/
HugeInt operator*(const HugeInt& left, const HugeInt& right) {
    HugeInt result = left;
    result *= right;
    return result;
}

/**
* 乘法
* @param hugeInt 巨型整数
* @return 计算后的巨型整数
*/
HugeInt& HugeInt::operator*=(const HugeInt& hugeInt) {
    return multiply(hugeInt);
}

/**
* 除法
* @param left 左操作数
* @param right 右操作数
* @return 计算后的巨型整数
*/
HugeInt operator/(const HugeInt& left, const HugeInt& right) {
    HugeInt result = left;
    result /= right;
    return result;
}

/**
* 除法
* @param hugeInt 巨型整数
* @return 计算后的巨型整数
*/
HugeInt& HugeInt::operator/=(const HugeInt& hugeInt) {
    return divide(hugeInt);
}

/**
* 求余数
* @param left 左操作数
* @param right 右操作数
* @return 计算后的巨型整数
*/
HugeInt operator%(const HugeInt& left, const HugeInt& right) {
    HugeInt result = left;
    result %= right;
    return result;
}

/**
* 求余数
* @param hugeInt 巨型整数
* @return 计算后的巨型整数
*/
HugeInt& HugeInt::operator%=(const HugeInt& hugeInt) {
    return mod(hugeInt);
}

/**
* 求n次方
* @param left 底数
* @param right 幂指数
* @return 计算后的巨型整数
*/
HugeInt operator^(const HugeInt& left, const HugeInt& right) {
    HugeInt result = left;
    result ^= right;
    return result;
}

/**
* 求n次方
* @param number 幂指数
* @return 计算后的巨型整数
*/
HugeInt& HugeInt::operator^=(const HugeInt& number) {
    return pow(number);
}

/**
* 加1
* @return 计算后的巨型整数
*/
HugeInt& HugeInt::operator++() {
    return add(1);
}

/**
* 减1
* @return 计算后的巨型整数
*/
HugeInt& HugeInt::operator--() {
    return subtract(1);
}

/**
* 加1
* @return 计算后的巨型整数
*/
HugeInt HugeInt::operator++(int) {
    HugeInt result = *this;
    ++*this;
    return result;
}

/**
* 减1
* @return 计算后的巨型整数
*/
HugeInt HugeInt::operator--(int) {
    HugeInt result = *this;
    --*this;
    return result;
}

/**
* 求负
* @return 计算后的巨型整数
*/
HugeInt HugeInt::operator-() const {
    HugeInt result = *this;
    result.isMinus = !result.isMinus;
    return result;
}

/**
* 小于
* @return 判断结果
*/
bool operator<(const HugeInt& left, const HugeInt& right) {
    bool result;
    if (left.isMinus && !right.isMinus) {
        return true;
    }
    if (!left.isMinus && right.isMinus) {
        return false;
    }
    if (left.number.size() < right.number.size()) {
        result = true;
    } else if (left.number.size() > right.number.size()) {
        result = false;
    } else {
        result = left.number < right.number;
    }
    return left.isMinus ^ result;
}

/**
* 小等于
* @return 判断结果
*/
bool operator<=(const HugeInt& left, const HugeInt& right) {
    return left < right || left == right;
}

/**
* 等于
* @return 判断结果
*/
bool operator==(const HugeInt& left, const HugeInt& right) {
    if (left.isMinus != right.isMinus) {
        return false;
    }
    return left.number == right.number;
}

/**
* 大于
* @return 判断结果
*/
bool operator>(const HugeInt& left, const HugeInt& right) {
    return !(left <= right);
}

/**
* 大等于
* @return 判断结果
*/
bool operator>=(const HugeInt& left, const HugeInt& right) {
    return !(left < right);
}

/**
* 不等于
* @return 判断结果
*/
bool operator!=(const HugeInt& left, const HugeInt& right) {
    return !(left == right);
}

/**
* 转换为string类型
* @return 转换结果
*/
HugeInt::operator string() const {
    return getNumber();
}

/**
* 转换为整数
* @return 转换结果
*/
HugeInt::operator int() const {
    int result = 0;
    for (auto& c : number) {
        result = result * 10 + (isMinus ? -(c - 48) : c - 48);
    }
    return result;
}

/**
* 转换为长整数
* @return 转换结果
*/
HugeInt::operator long long() const {
    long long result = 0LL;
    for (auto& c : number) {
        result = result * 10 + (isMinus ? -(c - 48) : c - 48);
    }
    return result;
}

/**
* 去除数字前面多余的0
* @return 去除后的字符串
*/
string HugeInt::eatZero(const string& number) {
    unsigned i = 0;
    for (auto& c : number) {
        if (c == '0') {
            i++;
        } else {
            break;
        }
    }
    if (i == number.size()) {
        //把所有的0都去掉之后啥都没有,那么原数为0
        return "0";
    }
    return number.substr(i);
}

/**
* 十进制数转换为八进制数
* @return 转换结果
*/
string HugeInt::toOct() const {
    HugeInt temp = number;
    string result;
    //除8取余法
    while (temp.number != "0") {
        const HugeInt temp2 = temp / 8;
        result += (temp - temp2 * 8).number;
        temp = temp2;
    }
    result += '0';
    if (isMinus) {
        result += '-';
    }
    return string(result.rbegin(), result.rend());
}

/**
* 十进制数转换为十六进制数
* @return 转换结果
*/
string HugeInt::toHex() const {
    HugeInt temp = number;
    string result;
    //除16取余法
    while (temp.number != "0") {
        const HugeInt temp2 = temp / 16;
        string temp3 = (temp - temp2 * 16).number;
        if (temp3.size() > 1) {
            result += char(temp3[1] + 17);
        } else {
            result += temp3;
        }
        temp = temp2;
    }
    result += "X0";
    if (isMinus) {
        result += '-';
    }
    return string(result.rbegin(), result.rend());
}

/**
* 转换为十进制数
* @return 转换结果
*/
string HugeInt::toDec(const string& number) const {
    HugeInt result, temp = 1;
    if (base == 10) {
        //十进制数不需要转换
        return number;
    }
    map<char, int> map;
    map['0'] = 0;
    map['1'] = 1;
    map['2'] = 2;
    map['3'] = 3;
    map['4'] = 4;
    map['5'] = 5;
    map['6'] = 6;
    map['7'] = 7;
    map['8'] = 8;
    map['9'] = 9;
    map['a'] = 10;
    map['b'] = 11;
    map['c'] = 12;
    map['d'] = 13;
    map['e'] = 14;
    map['f'] = 15;
    map['A'] = 10;
    map['B'] = 11;
    map['C'] = 12;
    map['D'] = 13;
    map['E'] = 14;
    map['F'] = 15;
    //e.g. FF(16)=15*16+15=255(10)
    for (auto iterator = number.rbegin(); iterator < number.rend(); ++iterator) {
        result += temp * map[*iterator];
        temp *= base;
    }
    return result.number;
}

/**
* 输出运算符
* @return 转换结果
*/
ostream& operator<<(ostream& out, const HugeInt& hugeInt) {
    return out << hugeInt.getNumber();
}

/**
* 输入运算符
* @return 转换结果
*/
istream& operator>>(istream& in, HugeInt& hugeInt) {
    string s;
    in >> s;
    hugeInt.setNumber(s);
    return in;
}
