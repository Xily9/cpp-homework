/**
* ����������ʵ���ļ�<br/>
* Copyright (c) 2018 Xily.All Rights Reserved.<br/>
* ���л�������ΪVisual Studio 2017<br/>
* ���Ҫ�������֧��C++11����������޷�����<br/>
* ע�⣺����Ŀ����������Windowsϵͳ��<br/>
* ����Ŀ��Visual Studio 2017��Mingw gcc on windows 6.3.0(using g++ command with -std=c++11)�±���ͨ��<br/>
* @author ���꽡 221701423 572089608@qq.com
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
 * ���캯��
 * @param number �ַ�����������
 */
HugeInt::HugeInt(const string& number) {
    setNumber(number);
}

/**
 * ���캯��
 * @param number �ַ�����������
 */
HugeInt::HugeInt(const char* number) {
    setNumber(number);
}

/**
 * ���캯��
 * @param number ����
 */
HugeInt::HugeInt(const int number): HugeInt(to_string(number)) {
}

/**
 * Ĭ�Ϲ��캯��
 */
HugeInt::HugeInt() : number("0") {
}

/**
 * ���캯��
 * @param number ������
 */
HugeInt::HugeInt(const long long number): HugeInt(to_string(number)) {
}

/**
 * ��ȡʮ���ƾ����������ַ���
 * @return ʮ���ƾ����������ַ���
 */
string HugeInt::getNumber() const {
    if (isMinus) {
        //�Ǹ�������ǰ��Ӹ���
        string result;
        result += '-';
        result += number;
        return result;
    }
    return number;
}

/**
 * ��������
 * @param number �ַ�����������
 */
void HugeInt::setNumber(string number) {
    if (number == "0" || number == "-0") {
        //����Ϊ0
        isMinus = false;
        number = "0";
    } else {
        if (number[0] == '-') {
            //����
            isMinus = true;
            number = number.substr(1); //ȥ����
        } else if (number[0] == '+') {
            isMinus = false;
            number = number.substr(1); //ȥ����
        } else {
            isMinus = false;
        }
        if (number[0] == '0') {
            if (number[1] == 'x' || number[1] == 'X') {
                //ʮ������
                base = 16;
                number = number.substr(2); //ȥ0X/0x
                //�ж������Ƿ�Ϸ�
                if (number.find_first_not_of("1234567890ABCDEFabcdef") != string::npos) {
                    throw IllegalNumberException();
                }
            } else {
                //�˽���
                base = 8;
                number = number.substr(1); //ȥ0
                //�ж������Ƿ�Ϸ�
                if (number.find_first_not_of("12345670") != string::npos) {
                    throw IllegalNumberException();
                }
            }
            number = toDec(eatZero(number));
        } else {
            base = 10;
            //�ж������Ƿ�Ϸ�
            if (number.find_first_not_of("1234567890") != string::npos) {
                throw IllegalNumberException();
            }
        }
    }
    this->number = number;
}

/**
 * �ӷ�
 * @param hugeInt ��������
 * @return �����ľ�������
 */
HugeInt& HugeInt::add(const HugeInt& hugeInt) {
    if (isMinus != hugeInt.isMinus) {
        //����������������Ų�һ��,��ת��Ϊ����
        return subtract(-hugeInt);
    }
    int b = 0;
    string result;
    bool isNotEnd1 = true, isNotEnd2 = true;
    string temp1(number);
    string temp2(hugeInt.number);
    reverse(temp1.begin(), temp1.end()); //����
    reverse(temp2.begin(), temp2.end()); //����
    string::const_iterator iterator1 = temp1.begin(), iterator2 = temp2.begin();
    const string::const_iterator iterator1End = temp1.end(), iterator2End = temp2.end();
    while (isNotEnd1 || isNotEnd2) {
        //����ÿλ����
        const int a = (isNotEnd1 ? *iterator1 - 48 : 0) + (isNotEnd2 ? *iterator2 - 48 : 0) + b;
        b = a / 10; //��λ
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
        result += char(b + 48); //���϶���Ľ�λ
    }
    reverse(result.begin(), result.end()); //�Ѽ�����������
    number = result;
    return *this;
}

/**
* ����
* @param hugeInt ��������
* @return �����ľ�������
*/
HugeInt& HugeInt::subtract(const HugeInt& hugeInt) {
    if (isMinus != hugeInt.isMinus) {
        //����������������Ų�һ��,��ת��Ϊ�ӷ�
        return add(-hugeInt);
    }
    if (abs(*this) < INT_MAX && abs(hugeInt) < INT_MAX) {
        //��������������int��Χ��,ֱ�Ӽ�
        *this = int(*this) - int(hugeInt);
    } else {
        int b = 0;
        string result, temp1, temp2;
        bool isNotEnd = true;
        if (*this == hugeInt) {
            number = "0";
            return *this;
        }
        //�ж���������������ֵ�Ĵ�С,�����Ϊ������,С����Ϊ����
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
        //�������϶��ȼ�����,���Բ���Ҫ���Ǽ����ȱ������ȶ�������
        while (iterator1 != iterator1End) {
            //����ÿһλ������
            const int a = (*iterator1 - 48) - (isNotEnd ? *iterator2 - 48 : 0) + b;
            b = (a - 9) / 10; //���㲹��
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
        number = eatZero(result); //�����ֵ�������ȥ�������0
    }
    return *this;
}

/**
* �˷�
* @param hugeInt ��������
* @return �����ľ�������
*/
HugeInt& HugeInt::multiply(const HugeInt& hugeInt) {
    int b = 0, c = 0;
    if (*this == 0 || hugeInt == 0) {
        //�κ�����0�����Ϊ0
        number = "0";
        isMinus = false;
    } else {
        const bool check1 = abs(*this) <= INT_MAX / 10;
        const bool check2 = abs(hugeInt) <= INT_MAX / 10;
        if (check1 || check2) {
            //�������һ��������С��INT_MAX/10,�ɶ������Ż�,��ֱ���ô�����ÿһλֱ����С�����,����ģ��򵥳˷�
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
            reverse(temp.begin(), temp.end()); //����
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
            reverse(result.begin(), result.end()); //�Ѽ�����������
            number = eatZero(result);
        } else {
            HugeInt result;
            string temp1(hugeInt.number), temp2(number);
            reverse(temp1.begin(), temp1.end()); //����
            reverse(temp2.begin(), temp2.end()); //����
            const string::const_iterator iterator1End = temp1.end(), iterator2End = temp2.end();
            for (auto iterator = temp1.begin(); iterator != iterator1End; ++iterator) {
                if (*iterator == '0') {
                    //�������0,0���κ�����˶�Ϊ0,����ֱ�Ӳ���
                    c++;
                } else if (*iterator == '1') {
                    //����1��ӱ���*10
                    result += number + string(c++, '0');
                } else {
                    string temp(c++, '0');
                    for (auto iterator2 = temp2.begin(); iterator2 != iterator2End; ++iterator2) {
                        //����ÿһλ����
                        const int a = int(*iterator - 48) * int(*iterator2 - 48) + b;
                        //�����λ
                        b = a / 10;
                        temp += char(a % 10 + 48);
                    }
                    if (b > 0) {
                        temp += char(b + 48); //���϶���Ľ�λ
                        b = 0;
                    }
                    reverse(temp.begin(), temp.end()); //�Ѽ�����������
                    result += temp;
                }
            }
            number = result.number;
        }
        isMinus = isMinus ^ hugeInt.isMinus; //�ж�����
    }
    return *this;
}

/**
* ����
* @param hugeInt ��������
* @return �����ľ�������
*/
HugeInt& HugeInt::divide(const HugeInt& hugeInt) {
    if (hugeInt == 0) {
        //��������Ϊ0
        throw DivideByZeroException();
    }
    if (abs(*this) < abs(hugeInt)) {
        //����������ľ���ֵС�ڳ���,�����Ϊ0
        number = "0";
        isMinus = false;
        return *this;
    }
    if (abs(*this) < INT_MAX && abs(hugeInt) < INT_MAX) {
        //��������������int��Χ��,ֱ�ӳ�
        *this = int(*this) / int(hugeInt);
    } else {
        //e.g. 123456/21 ���ȵ��Ƚ�ȡ12Ȼ�����21
        const int a = hugeInt.number.size();
        HugeInt temp = number.substr(0, a);
        const bool check = abs(hugeInt) < int(10e8);
        string result;
        int temp3 = 0, div = 0;
        if (check) {
            //�������С��10^8,�ɶ������Ż�,��ֱ�ӽ���ȡ��������������,����ģ�����
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
                int c = 0; //ÿһλ������
                //e.g. 12345*?=123456,����ͨ��123456-c*12345<0����c
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
                        temp.number = number.at(b); //�ѱ�������һλ���ּ̳�����
                    } else {
                        temp.number += number.at(b); //�ѱ�������һλ���ּ̳�����
                    }
                    temp.number = eatZero(temp.number);
                }
            }
        }
        number = eatZero(result);            //ȥ�������0
        isMinus = isMinus ^ hugeInt.isMinus; //�ж�����
    }
    return *this;
}

/**
* ������
* @param hugeInt ��������
* @return �����ľ�������
*/
HugeInt& HugeInt::mod(const HugeInt& hugeInt) {
    //e.g. 12%5=12-(12/5)*5=12-2*5=2
    return subtract(hugeInt * (*this / hugeInt));
}

/**
 * ��n�η�
 * @param number ��ָ��
 * @return �����ľ�������
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
        //�κ�����0�η�����1
        setNumber("1");
    } else {
        //��Ϊ�Ǿ���������,�����ָ���Ǹ���,��ô�����Ȼ��������
        throw HugeIntException("Power index cann't be negative");
    }
    return *this;
}

/**
 * ��׳�
 * @return �����ľ�������
 */
HugeInt& HugeInt::factorial() {
    if (isMinus) {
        //����û�н׳�
        throw HugeIntException("Cann't perform factorial operations on negative numbers");
    }
    if (number == "0") {
        //0�Ľ׳�Ϊ1
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
 * �����ֵ
 * @param hugeInt ��������
 * @return �����ľ�������
 */
HugeInt HugeInt::abs(HugeInt hugeInt) {
    hugeInt.isMinus = false;
    return hugeInt;
}

/**
* �ӷ�
* @param left �������
* @param right �Ҳ�����
* @return �����ľ�������
*/
HugeInt operator+(const HugeInt& left, const HugeInt& right) {
    HugeInt result = left;
    result += right;
    return result;
}

/**
* �ӷ�
* @param hugeInt ��������
* @return �����ľ�������
*/
HugeInt& HugeInt::operator+=(const HugeInt& hugeInt) {
    return add(hugeInt);
}

/**
* ����
* @param left �������
* @param right �Ҳ�����
* @return �����ľ�������
*/
HugeInt operator-(const HugeInt& left, const HugeInt& right) {
    HugeInt result = left;
    result -= right;
    return result;
}

/**
* ����
* @param hugeInt ��������
* @return �����ľ�������
*/
HugeInt& HugeInt::operator-=(const HugeInt& hugeInt) {
    return subtract(hugeInt);
}

/**
* �˷�
* @param left �������
* @param right �Ҳ�����
* @return �����ľ�������
*/
HugeInt operator*(const HugeInt& left, const HugeInt& right) {
    HugeInt result = left;
    result *= right;
    return result;
}

/**
* �˷�
* @param hugeInt ��������
* @return �����ľ�������
*/
HugeInt& HugeInt::operator*=(const HugeInt& hugeInt) {
    return multiply(hugeInt);
}

/**
* ����
* @param left �������
* @param right �Ҳ�����
* @return �����ľ�������
*/
HugeInt operator/(const HugeInt& left, const HugeInt& right) {
    HugeInt result = left;
    result /= right;
    return result;
}

/**
* ����
* @param hugeInt ��������
* @return �����ľ�������
*/
HugeInt& HugeInt::operator/=(const HugeInt& hugeInt) {
    return divide(hugeInt);
}

/**
* ������
* @param left �������
* @param right �Ҳ�����
* @return �����ľ�������
*/
HugeInt operator%(const HugeInt& left, const HugeInt& right) {
    HugeInt result = left;
    result %= right;
    return result;
}

/**
* ������
* @param hugeInt ��������
* @return �����ľ�������
*/
HugeInt& HugeInt::operator%=(const HugeInt& hugeInt) {
    return mod(hugeInt);
}

/**
* ��n�η�
* @param left ����
* @param right ��ָ��
* @return �����ľ�������
*/
HugeInt operator^(const HugeInt& left, const HugeInt& right) {
    HugeInt result = left;
    result ^= right;
    return result;
}

/**
* ��n�η�
* @param number ��ָ��
* @return �����ľ�������
*/
HugeInt& HugeInt::operator^=(const HugeInt& number) {
    return pow(number);
}

/**
* ��1
* @return �����ľ�������
*/
HugeInt& HugeInt::operator++() {
    return add(1);
}

/**
* ��1
* @return �����ľ�������
*/
HugeInt& HugeInt::operator--() {
    return subtract(1);
}

/**
* ��1
* @return �����ľ�������
*/
HugeInt HugeInt::operator++(int) {
    HugeInt result = *this;
    ++*this;
    return result;
}

/**
* ��1
* @return �����ľ�������
*/
HugeInt HugeInt::operator--(int) {
    HugeInt result = *this;
    --*this;
    return result;
}

/**
* ��
* @return �����ľ�������
*/
HugeInt HugeInt::operator-() const {
    HugeInt result = *this;
    result.isMinus = !result.isMinus;
    return result;
}

/**
* С��
* @return �жϽ��
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
* С����
* @return �жϽ��
*/
bool operator<=(const HugeInt& left, const HugeInt& right) {
    return left < right || left == right;
}

/**
* ����
* @return �жϽ��
*/
bool operator==(const HugeInt& left, const HugeInt& right) {
    if (left.isMinus != right.isMinus) {
        return false;
    }
    return left.number == right.number;
}

/**
* ����
* @return �жϽ��
*/
bool operator>(const HugeInt& left, const HugeInt& right) {
    return !(left <= right);
}

/**
* �����
* @return �жϽ��
*/
bool operator>=(const HugeInt& left, const HugeInt& right) {
    return !(left < right);
}

/**
* ������
* @return �жϽ��
*/
bool operator!=(const HugeInt& left, const HugeInt& right) {
    return !(left == right);
}

/**
* ת��Ϊstring����
* @return ת�����
*/
HugeInt::operator string() const {
    return getNumber();
}

/**
* ת��Ϊ����
* @return ת�����
*/
HugeInt::operator int() const {
    int result = 0;
    for (auto& c : number) {
        result = result * 10 + (isMinus ? -(c - 48) : c - 48);
    }
    return result;
}

/**
* ת��Ϊ������
* @return ת�����
*/
HugeInt::operator long long() const {
    long long result = 0LL;
    for (auto& c : number) {
        result = result * 10 + (isMinus ? -(c - 48) : c - 48);
    }
    return result;
}

/**
* ȥ������ǰ������0
* @return ȥ������ַ���
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
        //�����е�0��ȥ��֮��ɶ��û��,��ôԭ��Ϊ0
        return "0";
    }
    return number.substr(i);
}

/**
* ʮ������ת��Ϊ�˽�����
* @return ת�����
*/
string HugeInt::toOct() const {
    HugeInt temp = number;
    string result;
    //��8ȡ�෨
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
* ʮ������ת��Ϊʮ��������
* @return ת�����
*/
string HugeInt::toHex() const {
    HugeInt temp = number;
    string result;
    //��16ȡ�෨
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
* ת��Ϊʮ������
* @return ת�����
*/
string HugeInt::toDec(const string& number) const {
    HugeInt result, temp = 1;
    if (base == 10) {
        //ʮ����������Ҫת��
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
* ��������
* @return ת�����
*/
ostream& operator<<(ostream& out, const HugeInt& hugeInt) {
    return out << hugeInt.getNumber();
}

/**
* ���������
* @return ת�����
*/
istream& operator>>(istream& in, HugeInt& hugeInt) {
    string s;
    in >> s;
    hugeInt.setNumber(s);
    return in;
}
