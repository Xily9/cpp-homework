/**
 * ����demo������
 * @author 221701423
 * @date 2018.4.1
 */

#include "list.h" //����ͷ�ļ�,������һЩ��Ҫ�ĺ��������ͽṹ����
#include <iostream> //���ڱ�׼�������
using namespace std; //ʹstd�����ռ�ȫ�ֿ���

/**
 * ��ں���
 */
int main() {
    Node* head = createHead();
    while (true) {
        showMainMenu(); //��ʾ���˵�
        switch (getKey()) {
            case 'C':
                createList(head); //��������
                break;
            case 'O':
                showList(head); //չʾ�б�
                break;
            case 'S':
                saveList(head); //�洢����
                break;
            case 'X':
                showListFile(); //��ȡ�����ļ�
                break;
            case 'N':
                showListIfNotDate(head); //��ʾ���ܹ������ڵĽ��
                break;
            case 'D':
                deleteList(head); //ɾ�����
                break;
            case 'I':
                insertList(head); //������
                break;
            case 'T':
                showListDays(head); //��ʾ����
                break;
            case 'A':
                sortList(head); //��������
                break;
            case 'P':
                findListIfPrime(head); //�ҳ������ն��������Ľ��
                break;
            case 'F':
                flipList(head); //����ת
                break;
            case 'Q':
                quit(head); //�˳�
                break;
            default:
                //�û������˴���İ���
                cout << endl << "\aѡ�����������ѡ��......" << endl << endl;
                break;
        }
    }
}
