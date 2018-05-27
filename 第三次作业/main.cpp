#include <iostream>
#include "hugeInt.h"
#include <sstream>
#include "calculate.h"
#include <iomanip>
#include "function.h"
using namespace std;

int main() {
    while (true) {
        showMainMenu(); //显示主菜单
        switch (getKey()) {
            case 'A':
                testCalculate();
                break;
            case 'B':
                testOperators();
                break;
            case 'C':
                testSystem();
                break;
            case 'D':
                testOthers();
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
}
