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
 * 获取身份证号码的第18位
 * @param s 前17位字符串
 * @return 第18位字符
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
* 获得存储当前时间的时间结构指针
* @return 时间结构指针
*/
tm* getTime() {
    time_t rawtime;
    time(&rawtime);
    return localtime(&rawtime);
}

/**
* 判断闰年
* @param year 年份
* @return true 是闰年
* @return false 不是闰年
*/
bool isLeapYear(const int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

/**
* 检查日期的合法性
* @param year 年
* @param month 月
* @param day 日
* @return true 日期合法
* @return false 日期不合法
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
 * 判断字符串是否为(非负)整数
 * @param str 要判断的字符串
 * @return true 是整数
 * @return false 不是整数
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
 * 把字符串转化为整数
 * @param str 要转化的字符串
 * @return 转化后的数字
 */
int strToInt(const string& str) {
    int temp;
    stringstream stream(str);
    stream >> temp;
    return temp;
}

/**
* 把字符串转化为浮点数
* @param str 要转化的字符串
* @return 转化后的数字
*/
int strToDouble(const string& str) {
    double temp;
    stringstream stream(str);
    stream >> temp;
    return temp;
}

/**
 * 判断字符串是否为中文
 * @param str 要判断的字符串
 * @return true 是中文
 * @return false 不是中文
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
 * 在整数中查找整数
 * @param all 被查找的整数
 * @param in 要查找的整数
 * @return 要查找的整数的位置(-1为未找到)
 */
int findInInt(const int all, const int in) {
    return to_string(all).find(to_string(in));
}

/**
 * 获取控制台宽度
 * @return 控制台宽度
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
 * 设置控制台标题
 * @param title 
 */
void setConsoleTitle(const char* title) {
    SetConsoleTitleA(title);
}


/**
* 获取并显示输入的字母
* @return 获取到的字母(已转化为大写)
*/
char getKey() {
    const char key = toupper(_getch()); //实时获取输入并转换为大写
    cout << key << endl;                //显示输入的内容
    return key;
}

vector<string> split(string str, const string& pattern) {
    vector<std::string> result;
    str += pattern;//扩展字符串以方便操作  
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