#include <string>
#include <iostream>
#include "check.h"
using namespace std;

int main() {
    cout << "ʹ��˵�������������ļ������·��/����·���������ж��ļ�������" << endl;
    string f1, f2;
    cout << "�������һ���ļ���·��:" << endl;
    cin >> f1;
    cout << "������ڶ����ļ���·��:" << endl;
    cin >> f2;
    Check(f1, f2);
}
