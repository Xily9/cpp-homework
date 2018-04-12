/**
 * 链表demo头文件
 * @author 221701423
 * @date 2018.4.5
 */

//守卫
#ifndef H_LIST_221701423
#define H_LIST_221701423
#define _CRT_SECURE_NO_WARNINGS  //忽略VS的安全警告
#include <ctime> //用于声明tm类型的函数返回值
#include <fstream> //文件输入输出对象

//日期结构
struct Date {
    int year;  //年
    int month; //月
    int day;   //日
};

//链表结点结构定义
struct Node {
    Date date;
    Node* next; //指向下一个结点
};

//定义随机生成的年份的范围
enum RandomYear {
    START=1900, //开始年份
    STOP=2300 //结束年份
};

//以下为函数的声明
void showMainMenu();
void showTime();
Node* createHead();
void createList(Node* head);
void showList(const Node* head);
void saveList(const Node* head);
std::ofstream & getSaveFile(std::ofstream & file);
void showListFile();
std::ifstream & getShowFile(std::ifstream & file);
void showListIfNotDate(const Node* head);
void deleteList(Node* head);
void deleteListHead(Node* head);
void deleteListEnd(Node* head);
void deleteListIfNotDate(Node* head);
void showDeleteMenu();
void insertList(Node* head);
void insertTodayToListHead(Node* head);
void insertTodayToListEnd(Node* head);
void insertTodayToPrev(Node* head);
void insertTodayToNext(Node* head);
Node* createTodayList();
void showInsertMenu();
void showListDays(const Node* head);
void sortList(Node* head);
void findListIfPrime(const Node* head);
void flipList(Node* head);
void quit(Node* head);
bool isNull(const Node* head);
void pauseAndCls();
char getKey();
int getShowNum();
int getCreateNum();
void printDate(const Date &date);
int getRand(int start, int stop);
int switchTimeToInt(const Date & date, int baseYear);
bool isLeapYear(int year);
tm* getTime();
bool checkDate(const Date & date);
int compareDate(const Date & date1, const Date & date2);
bool isPrime(int num);
#endif
