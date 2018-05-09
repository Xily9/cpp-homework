#include "utils.h"
#include "dbhelper.h"
#include "function.h"
#include <iostream>

using namespace std;

/**
 * ��ں���
 */
int main() {
    setConsoleTitle("ѧ����Ϣ����ϵͳ");
    try {
        DbHelper dbHelper("data/data.txt");
        while (true) {
            showMainMenu(); //��ʾ���˵�
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
                    //�û������˴���İ���
                    cout << endl << "\aѡ�����������ѡ��......" << endl << endl;
                    break;
            }
            system("pause");
            system("cls");
        }
    } catch (exception& e) {
        //�����쳣
        cout << endl << "Oh My God!����������ʱ�쳣!" << endl;
        cout << "��ϸ��Ϣ:" << endl;
        cout << e.what() << endl;
        exit(1);
    }
}
