/**
 * ����demoͷ�ļ�
 * @author 221701423
 * @date 2018.4.5
 */

//����
#ifndef H_LIST_221701423
#define H_LIST_221701423
#define _CRT_SECURE_NO_WARNINGS  //����VS�İ�ȫ����
#include <ctime> //��������tm���͵ĺ�������ֵ
#include <fstream> //�ļ������������

//���ڽṹ
struct Date {
    int year;  //��
    int month; //��
    int day;   //��
};

//������ṹ����
struct Node {
    Date date;
    Node* next; //ָ����һ�����
};

//����������ɵ���ݵķ�Χ
enum RandomYear {
    START=1900, //��ʼ���
    STOP=2300 //�������
};

//����Ϊ����������
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
