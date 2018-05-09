#include "utils.h"
#include <string>
#include <ctime>
#include <windows.h>
#include <sstream>
#include <iostream>
#include <conio.h>
#include <vector>
using namespace std;

/**
 * ��ȡ���֤����ĵ�18λ
 * @param s ǰ17λ�ַ���
 * @return ��18λ�ַ�
 */
char getPersonId18(const string& s) {
    static int b[17] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
    static char c[11] = {'1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2'};
    int sum = 0;
    for (int i = 0; i < 17; i++) {
        sum += (s[i] - 48) * b[i];
    }
    return c[sum % 11];
}

/**
* ��ô洢��ǰʱ���ʱ��ṹָ��
* @return ʱ��ṹָ��
*/
tm* getTime() {
    time_t rawtime;
    time(&rawtime);
    return localtime(&rawtime);
}

/**
* �ж�����
* @param year ���
* @return true ������
* @return false ��������
*/
bool isLeapYear(const int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

/**
* ������ڵĺϷ���
* @param year ��
* @param month ��
* @param day ��
* @return true ���ںϷ�
* @return false ���ڲ��Ϸ�
*/
bool checkDate(const int year, const int month, const int day) {
    int dayOfMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isLeapYear(year)) {
        dayOfMonth[1] = 29;
    }
    return month <= 12 && month >= 1
        && day <= dayOfMonth[month - 1] && day >= 1;
}

/**
 * �ж��ַ����Ƿ�Ϊ(�Ǹ�)����
 * @param str Ҫ�жϵ��ַ���
 * @return true ������
 * @return false ��������
 */
bool isInt(const string& str) {
    for (char i : str) {
        if (i < 48 || i > 57) {
            return false;
        }
    }
    return true;
}

/**
 * ���ַ���ת��Ϊ����
 * @param str Ҫת�����ַ���
 * @return ת���������
 */
int strToInt(const string& str) {
    int temp;
    stringstream stream(str);
    stream >> temp;
    return temp;
}

/**
* ���ַ���ת��Ϊ������
* @param str Ҫת�����ַ���
* @return ת���������
*/
int strToDouble(const string& str) {
    double temp;
    stringstream stream(str);
    stream >> temp;
    return temp;
}

/**
 * �ж��ַ����Ƿ�Ϊ����
 * @param str Ҫ�жϵ��ַ���
 * @return true ������
 * @return false ��������
 */
bool isAllChinese(const string& str) {
    for (unsigned i = 0; i < str.size() - 1; i += 2) {
        if (!(str[i] & 0x80 && str[i + 1] & 0x80)) {
            return false;
        }
    }
    return true;
}

/**
 * �������в�������
 * @param all �����ҵ�����
 * @param in Ҫ���ҵ�����
 * @return Ҫ���ҵ�������λ��(-1Ϊδ�ҵ�)
 */
int findInInt(const int all, const int in) {
    return to_string(all).find(to_string(in));
}

/**
 * ��ȡ����̨���
 * @return ����̨���
 */
int getConsoleWidth() {
    static int width = 0;
    if (!width) {
        CONSOLE_SCREEN_BUFFER_INFO bInfo;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bInfo);
        width = bInfo.dwSize.X - 1;
    }
    return width;
}

/**
 * ���ÿ���̨����
 * @param title 
 */
void setConsoleTitle(const char* title) {
    SetConsoleTitleA(title);
}


/**
* ��ȡ����ʾ�������ĸ
* @return ��ȡ������ĸ(��ת��Ϊ��д)
*/
char getKey() {
    const char key = toupper(_getch()); //ʵʱ��ȡ���벢ת��Ϊ��д
    cout << key << endl;                //��ʾ���������
    return key;
}

vector<string> split(string str, const string& pattern) {
    vector<std::string> result;
    str += pattern;//��չ�ַ����Է������  
    const string::size_type size = str.size();
    for (string::size_type i = 0; i<size; i++) {
        const string::size_type pos = str.find(pattern, i);
        if (pos<size) {
            const std::string s = str.substr(i, pos - i);
            result.push_back(s);
            i = pos + pattern.size() - 1;
        }
    }
    return result;
}