/**
 * 链表demo主程序
 * @author 221701423
 * @date 2018.4.1
 */

#include "list.h" //引入头文件,里面有一些必要的函数声明和结构定义
#include <iostream> //用于标准输入输出
using namespace std; //使std命名空间全局可用

/**
 * 入口函数
 */
int main() {
    Node* head = createHead();
    while (true) {
        showMainMenu(); //显示主菜单
        switch (getKey()) {
            case 'C':
                createList(head); //创建链表
                break;
            case 'O':
                showList(head); //展示列表
                break;
            case 'S':
                saveList(head); //存储链表
                break;
            case 'X':
                showListFile(); //读取链表文件
                break;
            case 'N':
                showListIfNotDate(head); //显示不能构成日期的结点
                break;
            case 'D':
                deleteList(head); //删除结点
                break;
            case 'I':
                insertList(head); //插入结点
                break;
            case 'T':
                showListDays(head); //显示天数
                break;
            case 'A':
                sortList(head); //链表排序
                break;
            case 'P':
                findListIfPrime(head); //找出年月日都是质数的结点
                break;
            case 'F':
                flipList(head); //链表翻转
                break;
            case 'Q':
                quit(head); //退出
                break;
            default:
                //用户按下了错误的按键
                cout << endl << "\a选择错误，请重新选择......" << endl << endl;
                break;
        }
    }
}
