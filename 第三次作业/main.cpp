#include <iostream>
#include "hugeInt.h"
#include <sstream>
#include "calculate.h"
#include <iomanip>
#include "function.h"
using namespace std;

int main() {
    while (true) {
        showMainMenu(); //��ʾ���˵�
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
                //�û������˴���İ���
                cout << endl << "\aѡ�����������ѡ��......" << endl << endl;
                break;
        }
        system("pause");
        system("cls");
    }
}
