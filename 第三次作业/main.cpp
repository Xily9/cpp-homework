/**
* ����ļ�<br/>
* Copyright (c) 2018 Xily.All Rights Reserved.<br/>
* ���л�������ΪVisual Studio 2017<br/>
* ���Ҫ�������֧��C++11����������޷�����<br/>
* ע�⣺����Ŀ����������Windowsϵͳ��<br/>
* ����Ŀ��Visual Studio 2017��Mingw gcc on windows 6.3.0(using g++ command with -std=c++11)�±���ͨ��<br/>
* @author ���꽡 221701423 572089608@qq.com
* @date 2018.6.4
*/

#include "function.h"
#include "hugeInt.h"
#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
    try {
        while (true) {
            showMainMenu(); //��ʾ���˵�
            switch (getKey()) {
                case 'A':
                    testCalculate(); //�����������
                    break;
                case 'B':
                    testOperators(); //��ϵ���������
                    break;
                case 'C':
                    testSystem(); //����ת������
                    break;
                case 'D':
                    testOthers(); //�������
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
    } catch (...) {
        cout << "�����쳣��ֹ!" << endl;
    }
}
