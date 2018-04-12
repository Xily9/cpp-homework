/**
 * ����demo���������
 * @author 221701423
 * @date 2018.4.5
 */

#include "list.h" //����ͷ�ļ�,������һЩ��Ҫ�ĺ��������ͽṹ����
#include <iostream> //���ڱ�׼�������
#include <cstdlib> // �����������system����
#include <cstdio> //���ڸ�ʽ�����
#include <ctime> //���ڻ�ȡϵͳʱ��
#include <conio.h> //����ʵʱ��ȡ�û�����
#include <fstream> //�����ļ��������
#include <string> //���ڶ����ַ���
using namespace std; //ʹstd�����ռ�ȫ�ֿ���

/**
* ��ʾ���˵�
*/
void showMainMenu() {
    cout << "Copyright (C) 2018 ���꽡(221701423).All Rights Reserved." << endl << endl;
    showTime(); //��ʾʱ��
    cout << "*****************************************************************" << endl
        << "*    C������һ������������ݵģ���������                      *" << endl
        << "*    O����ʾ����ǰ�����ڵ����������                            *" << endl
        << "*    S��������������������ݴ����ļ���                          *" << endl
        << "*    X��������ʾ���������ļ��ģ�ȫ��������                      *" << endl
        << "*    N����ʾ���ܹ��ɺϷ����ڵģ����У����                      *" << endl
        << "*    D��ɾ������ĵ�һ�������һ�������ܹ��ɺϷ����ڵĽ��      *" << endl
        << "*    I�������㣨����ͷ����β�����֮ǰ�����֮��            *" << endl
        << "*    T����ʾ�������ڶ�Ӧ������                                *" << endl
        << "*    A���������ڴ�С��������                                  *" << endl
        << "*    P�����������С������ա����������Ľ��                      *" << endl
        << "*    F������������ת                                        *" << endl
        << "*    Q���˳�ϵͳ                                                *" << endl
        << "*****************************************************************" << endl
        << "��ѡ��C,O,S,X,N,D,I,T,A,P,F,Q����";
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
* ����ͷ���(�ڱ����)
* @return ���������ڴ��ַ
*/
Node* createHead() {
    Node* head = new Node; //����һ���ڴ�
    if (head == nullptr) {
        //�����ڴ�ʧ��
        cout << "�����ڱ����ʧ�ܣ��������ڴ治�㣡" << endl;
        exit(1); //�������죬ǿ���˳�
    }
    head->next = nullptr;
    return head;
}

/**
* ����һ������������ݵģ���������
* @param head �ڱ����
*/
void createList(Node* head) {
    const int n = getCreateNum();
    srand(int(time(nullptr))); //��ʼ�������������,����Ϊ��ǰʱ��ֵ
    for (int i = 0; i < n; i++) {
        Node* newList = new Node;
        newList->date.year = getRand(START, STOP);
        newList->date.month = getRand(1, 12);
        newList->date.day = getRand(1, 31);
        newList->next = head->next; //���½��ƴ�ӵ��ڱ����ĺ���
        head->next = newList;
    }
    cout << "������" << n << "�����ڽ��(" << START << "<=��<=" << STOP
        << "��1<=��<=12��1<=��<=31)��" << endl;
    pauseAndCls();
}

/**
* ��ȡ���������
* @return �����Ľ����
*/
int getCreateNum() {
    int n;
    while (true) {
        cout << "��������Ҫ���������ڽڵ�����";
        cin >> n;
        if (n < 0) {
            cout << "������һ����С��0������" << endl;
        } else {
            cout << endl;
            return n;
        }
    }
}

/**
* ��ʾ����ǰ�����ڵ����������
* @param head �ڱ����
*/
void showList(const Node* head) {
    //�ж������Ƿ�Ϊ��
    if (isNull(head)) {
        cout << "����Ϊ��!" << endl;
    } else {
        int n = getShowNum();
        int i = 0;
        for (head = head->next; head != nullptr; head = head->next) {
            i++;
            if (n == 0 || i <= n) {
                printDate(head->date);
                if (i % 5 == 0) {
                    //ÿ5�����ݻ���һ��
                    cout << endl;
                }
            }
        }
        cout << endl << endl << "���������" << i
            << "����ǰ��ʾ�Ľ����:" << (n == 0 ? i : n < i ? n : i) << endl << endl;
    }
    pauseAndCls();
}

/**
* ������������������ݴ����ļ���
* @param head �ڱ����
*/
void saveList(const Node* head) {
    //�ж������Ƿ�Ϊ��
    if (isNull(head)) {
        cout << "����Ϊ��!" << endl;
    } else {
        char temp[50];
        ofstream file;
        getSaveFile(file);
        int i = 0;
        for (head = head->next; head != nullptr; head = head->next) {
            i++;
            //����sprintf��ʽ��������ļ�
            sprintf(temp, "%04d.%02d.%02d\t", head->date.year, head->date.month, head->date.day);
            file << temp;
            if (i % 5 == 0) {
                //ÿ5�����ݻ���һ��
                file << endl;
            }
        }
        cout << "�ѽ�" << i << "���������ļ���!" << endl;
        file.close();
    }
    pauseAndCls();
}

/**
 * ��ȡҪ�洢���ļ�����
 * @param file ���ļ�����
 * @return �Ѵ��ļ��Ķ���
 */
ofstream& getSaveFile(ofstream& file) {
    string name;
    while (true) {
        cout << "�������ļ�����";
        cin >> name;
        file.open(name);
        if (!file.is_open()) {
            cout << "Error���ļ���(����)ʧ�ܣ�����Ȩ�޻�Ӳ�̿ռ��Ƿ���㣡" << endl;
        } else {
            return file;
        }
    }
}

/**
* ������ʾ���������ļ��ģ�ȫ��������
*/
void showListFile() {
    string text;
    ifstream file;
    getShowFile(file);
    system("cls");
    for (int i = 1; getline(file, text); i++) {
        printf("%4d��", i);
        cout << text << endl;
        if (i % 20 == 0) {
            //ÿ20�л�ҳ
            cout << "�������������ʾ��һҳ......" << endl;
            _getch();
        }
    }
    file.close();
    pauseAndCls();
}

/**
 * ��ȡҪ�򿪵��ļ�����
 * @param file ���ļ�����
 * @return �Ѵ��ļ��Ķ���
 */
ifstream& getShowFile(ifstream& file) {
    string name;
    while (true) {
        cout << "�������ļ�����";
        cin >> name;
        file.open(name);
        if (!file.is_open()) {
            cout << "Error���ļ���ʧ�ܣ������ļ����Ƿ���ȷ���ļ��Ƿ�ӵ�д�Ȩ�ޣ�" << endl;
        } else {
            return file;
        }
    }
}

/**
* ��ʾ���ܹ��ɺϷ����ڵģ����У����
* @param head �ڱ����
*/
void showListIfNotDate(const Node* head) {
    //�ж������Ƿ�Ϊ��
    if (isNull(head)) {
        cout << "����Ϊ��!" << endl;
    } else {
        cout << endl;
        int i = 0;
        for (head = head->next; head != nullptr; head = head->next) {
            if (!checkDate(head->date)) {
                i++;
                printDate(head->date);
                if (i % 5 == 0) {
                    //ÿ5�����ݻ���һ��
                    cout << endl;
                }
            }
        }
        cout << endl << "���ܹ��ɺϷ����ڵĽ��������" << i << endl << endl;
    }
    pauseAndCls();
}

/**
* ɾ������ĵ�һ�������һ�������ܹ��ɺϷ����ڵĽ��
* @param head �ڱ����
*/
void deleteList(Node* head) {
    //�ж������Ƿ�Ϊ��
    if (isNull(head)) {
        cout << "����Ϊ��!" << endl;
    } else {
        showDeleteMenu(); //��ʾ�˵�
        switch (getKey()) {
            case 'A':
                deleteListHead(head); //ɾ��ͷ
                break;
            case 'B':
                deleteListEnd(head); //ɾ��β
                break;
            case 'C':
                deleteListIfNotDate(head); //ɾ���������ڵĽڵ�
                break;
            case 'Q':
                break;
            default:
                //�û������˴���İ���
                cout << endl << "\aѡ�����������ѡ��......" << endl << endl;
                deleteList(head);
                return;
        }
    }
    pauseAndCls();
}

/**
* ɾ������ĵ�һ�����
* @param head �ڱ����
*/
void deleteListHead(Node* head) {
    Node* temp = head->next;
    head->next = head->next->next;
    delete temp;
    cout << "�ɹ�ɾ������ĵ�һ�����" << endl;
}

/**
* ɾ����������һ�����
* @param head �ڱ����
*/
void deleteListEnd(Node* head) {
    while (head->next->next != nullptr) {
        head = head->next;
    }
    Node* temp = head->next;
    head->next = nullptr;
    delete temp;
    cout << "�ɹ�ɾ����������һ�����" << endl;
}

/**
* ɾ�������в��ܹ��ɺϷ����ڵĽ��
* @param head �ڱ����
*/
void deleteListIfNotDate(Node* head) {
    int i = 0;
    while (head->next != nullptr) {
        if (!checkDate(head->next->date)) {
            i++;
            Node* temp = head->next;
            head->next = head->next->next;
            delete temp;
        } else {
            head = head->next;
        }
    }
    cout << "�ɹ�ɾ��" << i << "�����ܹ��ɺϷ����ڵĽ��" << endl;
}

/**
* ��ʾɾ�����˵�
*/
void showDeleteMenu() {
    cout << endl
        << "********************************************************" << endl
        << "*    A��ɾ������ĵ�һ�����                           *" << endl
        << "*    B��ɾ����������һ�����                         *" << endl
        << "*    C��ɾ�������в��ܹ��ɺϷ����ڵĽ��               *" << endl
        << "*    Q�����ص����˵�                                   *" << endl
        << "********************************************************" << endl
        << "��ѡ��A��B��C��Q����";
}

/**
* �����㣨����ͷ����β�����֮ǰ�����֮��
* @param head �ڱ����
*/
void insertList(Node* head) {
    showInsertMenu(); //��ʾ�˵�
    switch (getKey()) {
        case 'A':
            insertTodayToListHead(head); //���ͷ
            break;
        case 'B':
            insertTodayToListEnd(head); //���β
            break;
        case 'C':
            insertTodayToPrev(head); //��ӵ�ǰ��
            break;
        case 'D':
            insertTodayToNext(head); //��ӵ�����
            break;
        case 'Q':
            break;
        default:
            //�û������˴���İ���
            cout << endl << "\aѡ�����������ѡ��......" << endl << endl;
            insertList(head);
            return;
    }
    pauseAndCls();
}

/**
* ���õ�ǰ���ڹ����һ���½��ӵ���ͷ
* @param head �ڱ����
*/
void insertTodayToListHead(Node* head) {
    Node* node = createTodayList();
    if (node == nullptr) {
        cout << "�������ʧ�ܣ��������ڴ治�㣡" << endl;
    } else {
        node->next = head->next;
        head->next = node;
        cout << "�ɹ�����һ���½��!" << endl;
    }
}

/**
* ���õ�ǰ���ڹ����һ���½��ӵ���β
* @param head �ڱ����
*/
void insertTodayToListEnd(Node* head) {
    Node* node = createTodayList();
    if (node == nullptr) {
        cout << "�������ʧ�ܣ��������ڴ治�㣡" << endl;
    } else {
        while (head->next != nullptr) {
            head = head->next;
        }
        head->next = node;
        cout << "�ɹ�����һ���½��!" << endl;
    }
}

/**
* ���õ�ǰ���ڹ����һ���½����뵽��һ�����ڸý�����ڵ�ǰ��
* @param head �ڱ����
*/
void insertTodayToPrev(Node* head) {
    Node* node = createTodayList();
    if (node == nullptr) {
        cout << "�������ʧ�ܣ��������ڴ治�㣡" << endl;
    } else {
        while (head->next != nullptr) {
            if (compareDate(node->date, head->next->date) < 0) {
                node->next = head->next;
                head->next = node;
                cout << "�ɹ�����һ���½��!" << endl;
                break;
            }
            head = head->next;
        }
        if (head->next == nullptr) {
            //�Ѿ��ƶ�������β��Ȼû���½�����
            cout << "Error~~û���κ��½�㱻����!" << endl;
        }
    }
}

/**
* ���õ�ǰ���ڹ����һ���½����뵽��һ��С�ڸý�����ڵĺ���
* @param head �ڱ����
*/
void insertTodayToNext(Node* head) {
    Node* node = createTodayList();
    if (node == nullptr) {
        cout << "�������ʧ�ܣ��������ڴ治�㣡" << endl;
    } else {
        for (head = head->next; head != nullptr; head = head->next) {
            if (compareDate(node->date, head->date) > 0) {
                node->next = head->next;
                head->next = node;
                cout << "�ɹ�����һ���½��!" << endl;
                break;
            }
        }
        if (head->next == nullptr) {
            //�Ѿ��ƶ�������β��Ȼû���½�����
            cout << "Error~~û���κ��½�㱻����!" << endl;
        }
    }
}

/**
* �½�һ����ǰ���ڵĽ��
* @return ��ǰ���ڵĽ��
*/
Node* createTodayList() {
    tm* timeinfo = getTime();
    Node* node = new Node;
    if (node == nullptr) {
        //�����ڴ�ʧ�ܣ�ֱ�ӷ��ؿ�ָ���õ��÷��ж��Ƿ�Ϊ�գ�����������ĸ�ֵ��������
        return nullptr;
    }
    node->date.year = timeinfo->tm_year + 1900;
    node->date.month = timeinfo->tm_mon + 1;
    node->date.day = timeinfo->tm_mday;
    node->next = nullptr;
    return node;
}

/**
* ��ʾ������˵�
*/
void showInsertMenu() {
    cout << "" << endl
        << "************************************************************************" << endl
        << "*    A�����õ�ǰ���ڹ����һ���½��ӵ���ͷ                           *" << endl
        << "*    B�����õ�ǰ���ڹ����һ���½��ӵ���β                           *" << endl
        << "*    C�����õ�ǰ���ڹ����һ���½����뵽��һ�����ڸý�����ڵ�ǰ��   *" << endl
        << "*    D�����õ�ǰ���ڹ����һ���½����뵽��һ��С�ڸý�����ڵĺ���   *" << endl
        << "*    Q�����ص����˵�                                                   *" << endl
        << "************************************************************************" << endl
        << "��ѡ��A��B��C��D��Q����";
}

/**
* ��ʾ�������ڶ�Ӧ������(��1900.1.1��ʼ)
* @param head �ڱ����
*/
void showListDays(const Node* head) {
    //�ж������Ƿ�Ϊ��
    if (isNull(head)) {
        cout << "����Ϊ��!" << endl;
    } else {
        int n = getShowNum();
        int i = 0;
        for (head = head->next; head != nullptr; head = head->next) {
            i++;
            if (n == 0 || i <= n) {
                cout << switchTimeToInt(head->date, 1900) << "\t";
                if (i % 5 == 0) {
                    //ÿ5�����ݻ���һ��
                    cout << endl;
                }
            }
        }
        cout << endl << endl << "���������" << i
            << "����ǰ��ʾ�Ľ����:" << (n == 0 ? i : n < i ? n : i) << endl << endl;
    }
    pauseAndCls();
}

/**
* �������ڴ�С��������
* @param head �ڱ����
*/
void sortList(Node* head) {
    //�ж������Ƿ�Ϊ��
    if (isNull(head)) {
        cout << "����Ϊ��!" << endl;
    } else {
        cout << "�����������Ժ�......" << endl;
        Node* stop = nullptr;
        clock_t start = clock();
        //ð�����򷨣������ڴ���ƶ�������β��
        while (head->next != stop) {
            Node* prev = head;
            Node* temp = head->next;
            while (temp->next != stop) {
                if (compareDate(temp->date, temp->next->date) > 0) {
                    //����ǰ��Ԫ�صĵ�ַʵ������
                    prev->next = temp->next;
                    temp->next = temp->next->next;
                    prev->next->next = temp;
                    temp = prev->next;
                }
                prev = prev->next;
                temp = temp->next;
            }
            stop = temp; //��¼�����һ������ǰһ�����λ�ã���Ϊ�¸�ѭ���Ľ�����
        }
        clock_t end = clock();
        cout << endl << "�����������ʱ" << (double(end - start)) / CLK_TCK << "s" << endl;
    }
    pauseAndCls();
}

/**
* ���������С������ա����������Ľ��
* @param head �ڱ����
*/
void findListIfPrime(const Node* head) {
    //�ж������Ƿ�Ϊ��
    if (isNull(head)) {
        cout << "����Ϊ��!" << endl;
    } else {
        int i = 0;
        cout << endl;
        for (head = head->next; head != nullptr; head = head->next) {
            //�����ն�������
            if (isPrime(head->date.year) && isPrime(head->date.month) && isPrime(head->date.day)) {
                i++;
                printDate(head->date);
                if (i % 5 == 0) {
                    //ÿ5�����ݻ���һ��
                    cout << endl;
                }
            }
        }
        cout << endl << "��" << i << "�������ն��������Ľ��!" << endl;
    }
    pauseAndCls();
}

/**
* ����ת
* @param head �ڱ����
*/
void flipList(Node* head) {
    //�ж������Ƿ�Ϊ��
    if (isNull(head)) {
        cout << "����Ϊ��!" << endl;
    } else {
        Node* p = head->next;
        head->next = nullptr;
        while (p != nullptr) {
            Node* temp = p->next;
            p->next = head->next;
            head->next = p;
            p = temp;
        }
        cout << endl << "�����ѳɹ���ת��" << endl;
    }
    pauseAndCls();
}

/**
* �˳�
* @param head �ڱ����
*/
void quit(Node* head) {
    Node* p = head->next;
    //�����н���ڴ��ͷŵ�
    while (p != nullptr) {
        Node* temp = p->next;
        delete p;
        p = temp;
    }
    delete head; //�ͷ��ڱ�����ڴ�
    exit(0);     //�����˳�
}

/**
 * �ж������Ƿ�Ϊ��
 * @param head �ڱ����
 * @return true ����Ϊ��
 * @return false ����Ϊ��
 */
bool isNull(const Node* head) {
    return head->next == nullptr;
}

/**
 * ��ͣ���������Ļ
 */
void pauseAndCls() {
    system("pause"); //�����������
    system("cls");   //�����Ļ
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
 * ��ȡ��������
 * @return ����Ľ����(0Ϊȫ�����)
 */
int getShowNum() {
    int n;
    while (true) {
        cout << "������Ҫ��������ڽ����������0�����ȫ����㣩:";
        cin >> n;
        if (n < 0) {
            cout << "������һ������0������" << endl;
        } else {
            cout << endl;
            return n;
        }
    }
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
 * ��ʽ���������
 * @param date ���ڽṹ
 */
void printDate(const Date& date) {
    //��ʽ�����,����printf
    printf("%04d.%02d.%02d\t", date.year, date.month, date.day);
}

/**
* ������ڵĺϷ���
* @param date ���ڽṹ
* @return true ���ںϷ�
* @return false ���ڲ��Ϸ�
*/
bool checkDate(const Date& date) {
    int aday[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (((date.year % 4 == 0 && date.year % 100 != 0) || date.year % 400 == 0)) {
        aday[1] = 29;
    }
    return date.month <= 12 && date.month >= 1
        && date.day <= aday[date.month - 1] && date.day >= 1;
}

/**
* ����һ��ָ������������
* @param start ��ʼ��
* @param stop ��ֹ��
* @return һ��ָ������������
*/
int getRand(const int start, const int stop) {
    return rand() % (stop - start + 1) + start;
}

/**
* ��ʱ��ת��Ϊ����
* @param date ���ڽṹ
* @param baseYear ���㿪ʼ�����
* @return ת����ɵ�����
*/
int switchTimeToInt(const Date& date, int baseYear) {
    int result = 0;
    int dayOfMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    while (baseYear < date.year) {
        if (isLeapYear(baseYear)) {
            result += 366;
        } else {
            result += 365;
        }
        baseYear++;
    }
    if (isLeapYear(baseYear)) {
        dayOfMonth[1] = 29;
    } else {
        dayOfMonth[1] = 28;
    }
    for (int i = 0; i < date.month - 1; i++) {
        result += dayOfMonth[i];
    }
    return result + date.day - 1;
}

/**
 * �ж�����
 * @param year ���
 * @return true ������ 
 * @return false ��������
 */
bool isLeapYear(const int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

/**
* �Ƚ��������ڴ�С
* @param date1 ��һ�����ڽṹ
* @param date2 �ڶ������ڽṹ
* @return 1 ��һ������ > �ڶ�������
* @return 0 ��һ������ = �ڶ�������
* @return -1 ��һ������ < �ڶ�������
*/
int compareDate(const Date& date1, const Date& date2) {
    if (date1.year < date2.year) {
        return -1;
    }
    if (date1.year > date2.year) {
        return 1;
    }
    if (date1.month < date2.month) {
        return -1;
    }
    if (date1.month > date2.month) {
        return 1;
    }
    if (date1.day < date2.day) {
        return -1;
    }
    if (date1.day > date2.day) {
        return 1;
    }
    return 0;
}

/**
* �ж�һ�������Ƿ�Ϊ����
* @param num ����
* @return true ������
* @return false ��������
*/
bool isPrime(const int num) {
    if (num == 1 || (num > 5 && (num % 10 == 5 || num % 2 == 0))) {
        return false;
    }
    for (int d = 2; d < num; d++) {
        if (num % d == 0) {
            return false;
        }
    }
    return true;
}
