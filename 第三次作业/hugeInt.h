#pragma once

/**
* 巨型整数类头<br/>
* Copyright (c) 2018 Xily.All Rights Reserved.<br/>
* 运行环境建议为Visual Studio 2017<br/>
* 最低要求编译器支持C++11，否则程序将无法运行<br/>
* 注意：该项目必须运行在Windows系统下<br/>
* 该项目在Visual Studio 2017和Mingw gcc on windows 6.3.0(using g++ command with -std=c++11)下编译通过<br/>
* @author 曾宏健 221701423 572089608@qq.com
* @date 2018.6.4
*/

#include <string>
#include <utility>
#include <iostream>
using std::string;

class HugeInt {
public:
    HugeInt(const string& number);
    HugeInt(const char* number);
    HugeInt(int number);
    HugeInt();
    HugeInt(long long number);
    HugeInt(const HugeInt& hugeInt) = default;
    HugeInt(HugeInt&& hugeInt) = default;
    HugeInt& operator=(const HugeInt& hugeInt) = default;
    HugeInt& operator=(HugeInt&& hugeInt) = default;
    ~HugeInt() = default;
    string getNumber() const;
    void setNumber(string number);
    HugeInt& add(const HugeInt& hugeInt);
    HugeInt& subtract(const HugeInt& hugeInt);
    HugeInt& multiply(const HugeInt& hugeInt);
    HugeInt& divide(const HugeInt& hugeInt);
    HugeInt& mod(const HugeInt& hugeInt);
    HugeInt& pow(const HugeInt& number);
    HugeInt& factorial();
    static HugeInt abs(HugeInt hugeInt);
    string toOct() const;
    string toHex() const;
    friend HugeInt operator+(const HugeInt& left, const HugeInt& right);
    HugeInt& operator+=(const HugeInt& hugeInt);
    friend HugeInt operator-(const HugeInt& left, const HugeInt& right);
    HugeInt& operator-=(const HugeInt& hugeInt);
    friend HugeInt operator*(const HugeInt& left, const HugeInt& right);
    HugeInt& operator*=(const HugeInt& hugeInt);
    friend HugeInt operator/(const HugeInt& left, const HugeInt& right);
    HugeInt& operator/=(const HugeInt& hugeInt);
    friend HugeInt operator%(const HugeInt& left, const HugeInt& right);
    HugeInt& operator%=(const HugeInt& hugeInt);
    friend HugeInt operator^(const HugeInt& left, const HugeInt& right);
    HugeInt& operator^=(const HugeInt& number);
    HugeInt& operator++();
    HugeInt& operator--();
    HugeInt operator++(int);
    HugeInt operator--(int);
    HugeInt operator-() const;
    friend bool operator<(const HugeInt& left, const HugeInt& right);
    friend bool operator<=(const HugeInt& left, const HugeInt& right);
    friend bool operator==(const HugeInt& left, const HugeInt& right);
    friend bool operator>(const HugeInt& left, const HugeInt& right);
    friend bool operator>=(const HugeInt& left, const HugeInt& right);
    friend bool operator!=(const HugeInt& left, const HugeInt& right);
    explicit operator string() const;
    explicit operator int() const;
    explicit operator long long() const;

    //定义异常
    class HugeIntException : public std::logic_error {
    public:
        explicit HugeIntException(const char* s) : std::logic_error(s) {
        }
    };

    //除以0异常
    class DivideByZeroException : public HugeIntException {
    public:
        explicit DivideByZeroException() : HugeIntException("Cann't divide by zero") {
        }
    };

    //数字非法异常
    class IllegalNumberException : public HugeIntException {
    public:
        explicit IllegalNumberException(): HugeIntException("Illegal number!") {
        }
    };

private:
    string number;//存储数字
    bool isMinus = false;//是否为负数
    int base = 10;//进制
    static string eatZero(const string& number);
    string toDec(const string& number) const;
};

std::ostream& operator<<(std::ostream& out, const HugeInt& hugeInt);
std::istream& operator>>(std::istream& in, HugeInt& hugeInt);
