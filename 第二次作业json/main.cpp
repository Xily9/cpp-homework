/**
* ����ļ�<br/>
* Copyright (c) 2018 Xily.All Rights Reserved.<br/>
* ���л�������ΪVisual Studio 2017<br/>
* ���Ҫ�������֧��C++11����������޷�����<br/>
* ע�⣺����Ŀ����������Windowsϵͳ��<br/>
* ����Ŀ��Visual Studio 2017��Mingw gcc on windows 6.3.0(using g++ command with -std=c++11)�±���ͨ��<br/>
* ������ʹ��json��Ϊ���ݴ洢��ʽ<br/>
* @author ���꽡 221701423 572089608@qq.com
* @date 2018.5.1
*/

#include "dbhelper.h"
#include "function.h"
#include "student.h"
#include <iostream>
#include <iomanip>
using namespace std;

void showMainMenu();
void showTime();

/**
 * ��ں���
 */
int main() {
    setConsoleTitle("ѧ����Ϣ����ϵͳ");
    try {
        DbHelper dbHelper("data/data.json");
        Student student(move(dbHelper));
        while (true) {
            showMainMenu(); //��ʾ���˵�
            switch (getKey()) {
                case 'A':
                    student.addData();//���
                    break;
                case 'B':
                    student.showData();//չʾ
                    break;
                case 'C':
                    student.findData();//����
                    break;
                case 'D':
                    student.sortData();//����
                    break;
                case 'E':
                    student.countData();//ͳ��
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


/**
* ��ʾ���˵�
*/
void showMainMenu() {
    cout << "Copyright (C) 2018 ���꽡(221701423).All Rights Reserved." << endl << endl;
    showTime();
    drawLine('*', 60);
    cout.setf(ios_base::left, ios_base::adjustfield);
    cout << "*    " << setw(54) << "A�����ѧ������" << "*" << endl
        << "*    " << setw(54) << "B����ʾѧ������" << "*" << endl
        << "*    " << setw(54) << "C������ѧ������" << "*" << endl
        << "*    " << setw(54) << "D������ѧ������" << "*" << endl
        << "*    " << setw(54) << "E��ͳ�Ʒ���ѧ������" << "*" << endl
        << "*    " << setw(54) << "Q���˳�ϵͳ" << "*" << endl;
    drawLine('*', 60);
    cout << "��ѡ��A,B,C,D,E,Q����";
}

/**
* ��ʾϵͳ��ǰʱ��
*/
void showTime() {
    const char* weekday[7] = { "��", "һ", "��", "��", "��", "��", "��" };
    tm* timeInfo = getTime(); //��õ�ǰʱ��
    printf("��ǰ���ڡ�ʱ�䣺%04d.%02d.%02d(����%s)  %02d:%02d:%02d\n",
        timeInfo->tm_year + 1900,
        timeInfo->tm_mon + 1,
        timeInfo->tm_mday,
        weekday[timeInfo->tm_wday],
        timeInfo->tm_hour,
        timeInfo->tm_min,
        timeInfo->tm_sec);
}