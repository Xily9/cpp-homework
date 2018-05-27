//ȥ��VS�İ�ȫ����
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "hugeInt.h"
#include "calculate.h"
#include "function.h"
#include <iomanip>
#include <conio.h>
#include <cassert>
#include <string>
using namespace std;

/**
* ��ʾ���˵�
*/
void showMainMenu() {
    cout << "Copyright (C) 2018 ���꽡(221701423).All Rights Reserved." << endl << endl;
    showTime();
    drawLine('*', 60);
    cout.setf(ios_base::left, ios_base::adjustfield);
    cout << "*    " << setw(54) << "A�������������" << "*" << endl
        << "*    " << setw(54) << "B����ϵ���������" << "*" << endl
        << "*    " << setw(54) << "C�����Խ���ת��" << "*" << endl
        << "*    " << setw(54) << "D���������" << "*" << endl
        << "*    " << setw(54) << "Q���˳�ϵͳ" << "*" << endl;
    drawLine('*', 60);
    cout << "��ѡ��A,B,C,D,Q����";
}

/**
* ��ʾϵͳ��ǰʱ��
*/
void showTime() {
    const char* weekday[7] = {"��", "һ", "��", "��", "��", "��", "��"};
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

/**
* ��ô洢��ǰʱ���ʱ��ṹָ��
* @return ʱ��ṹָ��
*/
tm* getTime() {
    time_t rawtime;
    time(&rawtime);
    return localtime(&rawtime);
}

/**
* ���Լ���
*/
void testCalculate() {
    showCalculateTips();
    while (true) {
        try {
            string s;
            cout << "���ʽ��";
            cin >> s;
            cout << "��������" << Calculate::calculate(s) << endl;
        } catch (exception& e) {
            cout << e.what() << endl;
        }
    }
}

/**
* ��ʾ�������˵��
*/
void showCalculateTips() {
    drawLine('-', 40);
    cout << "����˵����" << endl
        << "֧�ֵĲ�������+ �ӣ�- ����* �ˣ�/ �� ��% ȡ�࣬^ ���ݣ����׳ˣ�����д�Ҳ��������������⣩" << endl
        << "֧���������㣬֧�ָ�����֧��ʮ��������˽������㣨������Ϊʮ��������" << endl
        << "һЩ�򵥺Ϸ������ӣ�(5+3)*5 ��-5+3��3-(-5)��5^2+3!0��123*(((5+3)*2)^5)" << endl
        << "Enjoy it!" << endl;
    drawLine('-', 40);
}

/**
 * ���Բ�����
 */
void testOperators() {
    int n;
    HugeInt left, right;
    bool result = false;
    while (true) {
        showOperators();
        cout << "���������������ǰ����ţ�";
        cin >> n;
        cout << "���������������";
        cin >> left;
        cout << "�������Ҳ�������";
        cin >> right;
        switch (n) {
            case 0:
                result = left < right;
                break;
            case 1:
                result = left <= right;
                break;
            case 2:
                result = left == right;
                break;
            case 3:
                result = left > right;
                break;
            case 4:
                result = left >= right;
                break;
            case 5:
                result = left != right;
                break;
            default:
                break;
        }
        cout << "�����" << (result ? "true" : "false") << endl;
    }
}

/**
* ��ʾ�������б�
*/
void showOperators() {
    static const char operators[6][3]{"<", "<=", "==", ">", ">=", "!="};
    drawLine('-', 40);
    for (unsigned i = 0; i < 6; i++) {
        cout << setw(10) << "[" + to_string(i) + "]" + operators[i];
        if (i % 4 == 3) {
            cout << endl;
        }
    }
    cout << endl;
}

/**
 * ���Խ���ת��
 */
void testSystem() {
    HugeInt hugeInt;
    showSystemMenu();
    const char key = getKey();
    cout << "�������ת�������֣�(�˽���������ǰ��0��ʮ������������ǰ��0X��0x)" << endl;
    cin >> hugeInt;
    cout << "ת�������";
    switch (key) {
        case 'A':
            cout << hugeInt;
            break;
        case 'B':
            cout << hugeInt.toOct();
            break;
        case 'C':
            cout << hugeInt.toHex();
            break;
        default:
            break;
    }
    cout << endl;
}

/**
 * ��ʾ����ת���˵�
 */
void showSystemMenu() {
    drawLine('*', 60);
    cout.setf(ios_base::left, ios_base::adjustfield);
    cout << "*    " << setw(54) << "A��תʮ����" << "*" << endl
        << "*    " << setw(54) << "B��תʮ������" << "*" << endl
        << "*    " << setw(54) << "C��תʮ������" << "*" << endl;
    drawLine('*', 60);
    cout << "��ѡ��A,B,C����";
}

/**
 * ������������
 */
void testOthers() {
    const clock_t start = clock();
    //����ǰ��++ --
    HugeInt a = HugeInt("1");
    assert(a++ == HugeInt("1"));
    assert(++a == HugeInt("3"));
    assert(a-- == HugeInt("3"));
    assert(--a == HugeInt("1"));
    //����+= -= *= /= %=
    assert((a += 3) == HugeInt("4"));
    assert((a -= 3) == HugeInt("1"));
    assert((a *= 3) == HugeInt("3"));
    assert((a /= 3) == HugeInt("1"));
    assert((a %= 3) == HugeInt("1"));
    //�������ͻ��ַ�������������ļ���
    assert(345 + HugeInt("123") == 468);
    assert(HugeInt(100) + HugeInt(900) == 1000);
    assert(HugeInt(1000) / 10 == HugeInt(100));
    assert(HugeInt(1000) - 900 == 100);
    assert("1000" - HugeInt(900) == 100);
    assert(HugeInt(900) - "100" == 800);
    const clock_t end = clock();
    cout << "��ϲ,ȫ������ͨ��!��ʱ" << (double(end - start)) / CLK_TCK << "s" << endl;
}

/**
* ��ȡ����ʾ�������ĸ
* @return ��ȡ������ĸ(��ת��Ϊ��д)
*/
char getKey() {
    const char key = toupper(_getch()); //ʵʱ��ȡ���벢ת��Ϊ��д
    cout << key << endl;                //��ʾ���������
    return key;
}

/**
* ���ָ���
* @param c �ָ��ַ�
* @param length �ַ�����
*/
void drawLine(const char c, const int length) {
    cout << string(length, c) << std::endl;
}
