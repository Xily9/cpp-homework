#pragma once

/**
* ����������ͷ<br/>
* Copyright (c) 2018 Xily.All Rights Reserved.<br/>
* ���л�������ΪVisual Studio 2017<br/>
* ���Ҫ�������֧��C++11����������޷�����<br/>
* ע�⣺����Ŀ����������Windowsϵͳ��<br/>
* ����Ŀ��Visual Studio 2017��Mingw gcc on windows 6.3.0(using g++ command with -std=c++11)�±���ͨ��<br/>
* @author ���꽡 221701423 572089608@qq.com
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

    //�����쳣
    class HugeIntException : public std::logic_error {
    public:
        explicit HugeIntException(const char* s) : std::logic_error(s) {
        }
    };

    //����0�쳣
    class DivideByZeroException : public HugeIntException {
    public:
        explicit DivideByZeroException() : HugeIntException("Cann't divide by zero") {
        }
    };

    //���ַǷ��쳣
    class IllegalNumberException : public HugeIntException {
    public:
        explicit IllegalNumberException(): HugeIntException("Illegal number!") {
        }
    };

private:
    string number;//�洢����
    bool isMinus = false;//�Ƿ�Ϊ����
    int base = 10;//����
    static string eatZero(const string& number);
    string toDec(const string& number) const;
};

std::ostream& operator<<(std::ostream& out, const HugeInt& hugeInt);
std::istream& operator>>(std::istream& in, HugeInt& hugeInt);
