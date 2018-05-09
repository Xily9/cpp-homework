#include "utils.h"
#include "dbhelper.h"
#include "function.h"
#include <iostream>

using namespace std;

/**
 * 入口函数
 */
int main() {
    setConsoleTitle("学籍信息管理系统");
    try {
        DbHelper dbHelper("data/data.txt");
        while (true) {
            showMainMenu(); //显示主菜单
            switch (getKey()) {
                case 'A':
                    addData(dbHelper);
                    break;
                case 'B':
                    showData(dbHelper);
                    break;
                case 'C':
                    findData(dbHelper);
                    break;
                case 'D':
                    sortData(dbHelper);
                    break;
                case 'E':
                    countData(dbHelper);
                    break;
                case 'Q':
                    return 0;
                default:
                    //用户按下了错误的按键
                    cout << endl << "\a选择错误，请重新选择......" << endl << endl;
                    break;
            }
            system("pause");
            system("cls");
        }
    } catch (exception& e) {
        //捕获到异常
        cout << endl << "Oh My God!程序发生运行时异常!" << endl;
        cout << "详细信息:" << endl;
        cout << e.what() << endl;
        exit(1);
    }
}
