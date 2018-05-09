#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <vector>
using namespace std;
char getPersonId18(const string& s);
tm* getTime();
bool isLeapYear(const int year);
bool checkDate(int year, int month, int day);
bool isInt(const string& str);
int strToInt(const string& str);
int strToDouble(const string& str);
int findInInt(int all, int in);
bool isAllChinese(const string& str);
int getConsoleWidth();
void setConsoleTitle(const char* title);
char getKey();
vector<string> split(string str, const string& pattern);
/**
* ��������
* @tparam T ��������
* @tparam U lambda
* @param array ������ļ���
* @param left ���±�
* @param right ���±�
* @param complete �ȽϺ���
*/
template <typename T, typename U>
void quickSort(T& array, int left, int right, U complete) {
    //��������֮ǰ���ж�һ�µ�ǰ����������Ԫ�ظ����ǲ��Ǵ���1 �����û�б�Ҫ����
    if (left >= right) {
        //ֱ���˳��������  û�б�Ҫ����������
        return;
    }
    //��ʼ���п����㷨
    //���������ȱ���left������Ӧ������  ��ǰ������Ϊ�и��������
    T piovt = array[left];
    //������ʱ��������������˵�����
    int leftIndex = left;
    int rightIndex = right;
    while (leftIndex < rightIndex) {
        //��������ͨ��ѭ�����ұ߿�ʼ����һ������ֵС������
        while (leftIndex < rightIndex) {
            //����ұߵ������ڵ�ǰ�Ĳ�����ֵ
            if (complete(piovt, array[rightIndex]) <= 0) {
                //�Ҷ�����ָʾ������
                rightIndex--;
            } else {
                //˵�������Ҷ˳��ֱ���ֵ���������
                //���ʱ�����ǾͿ��԰���������������䵽������������Ӧ�ĵط�
                array[leftIndex] = array[rightIndex];
                leftIndex++;
                //������Ҫ����ѭ���˵�ǰ�������
                break;
            }
        }
        //����߿�ʼ����һ������ֵ���������д�ϴ����µĿ�
        while (leftIndex < rightIndex) {
            //�����ߵ�����С����ֵ ��������ָʾ����������
            if (complete(piovt, array[leftIndex]) >= 0) {
                leftIndex++;
            } else {
                //˵������������ҵ��˱���ֵ���������
                array[rightIndex] = array[leftIndex];
                rightIndex--;
                break;
            }
        }
    }
    //��ʱleftIndex=rightIndex,���԰�֮ǰ��¼��ֵ�������λ��
    array[leftIndex] = piovt;
    //�ݹ���ã���leftIndexǰ����������
    quickSort(array, left, leftIndex - 1, complete);
    //�ݹ���ã���rightIndex������������
    quickSort(array, rightIndex + 1, right, complete);
}
