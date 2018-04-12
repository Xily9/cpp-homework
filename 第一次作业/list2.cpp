/**
 * 链表demo函数定义库
 * @author 221701423
 * @date 2018.4.5
 */

#include "list.h" //引入头文件,里面有一些必要的函数声明和结构定义
#include <iostream> //用于标准输入输出
#include <cstdlib> // 用于随机数和system函数
#include <cstdio> //用于格式化输出
#include <ctime> //用于获取系统时间
#include <conio.h> //用于实时获取用户输入
#include <fstream> //用于文件输入输出
#include <string> //用于定义字符串
using namespace std; //使std命名空间全局可用

/**
* 显示主菜单
*/
void showMainMenu() {
    cout << "Copyright (C) 2018 曾宏健(221701423).All Rights Reserved." << endl << endl;
    showTime(); //显示时间
    cout << "*****************************************************************" << endl
        << "*    C：创建一个存放日期数据的（无序）链表                      *" << endl
        << "*    O：显示链表前几个节点的日期数据                            *" << endl
        << "*    S：将整个链表的所有数据存入文件中                          *" << endl
        << "*    X：分屏显示日期数据文件的（全部）内容                      *" << endl
        << "*    N：显示不能构成合法日期的（所有）结点                      *" << endl
        << "*    D：删除链表的第一个、最后一个、不能构成合法日期的结点      *" << endl
        << "*    I：插入结点（至链头、链尾、结点之前、结点之后）            *" << endl
        << "*    T：显示结点的日期对应的天数                                *" << endl
        << "*    A：链表按日期从小到大排序                                  *" << endl
        << "*    P：查找链表中“年月日”都是素数的结点                      *" << endl
        << "*    F：（单向）链表翻转                                        *" << endl
        << "*    Q：退出系统                                                *" << endl
        << "*****************************************************************" << endl
        << "请选择（C,O,S,X,N,D,I,T,A,P,F,Q）：";
}

/**
* 显示系统当前时间
*/
void showTime() {
    const char* weekday[7] = {"日", "一", "二", "三", "四", "五", "六"};
    tm* timeInfo = getTime(); //获得当前时间
    printf("当前日期、时间：%04d.%02d.%02d(星期%s)  %02d:%02d:%02d\n",
           timeInfo->tm_year + 1900,
           timeInfo->tm_mon + 1,
           timeInfo->tm_mday,
           weekday[timeInfo->tm_wday],
           timeInfo->tm_hour,
           timeInfo->tm_min,
           timeInfo->tm_sec);
}

/**
* 创建头结点(哨兵结点)
* @return 创建结点的内存地址
*/
Node* createHead() {
    Node* head = new Node; //开辟一块内存
    if (head == nullptr) {
        //申请内存失败
        cout << "创建哨兵结点失败，可能是内存不足！" << endl;
        exit(1); //无力回天，强制退出
    }
    head->next = nullptr;
    return head;
}

/**
* 创建一个存放日期数据的（无序）链表
* @param head 哨兵结点
*/
void createList(Node* head) {
    const int n = getCreateNum();
    srand(int(time(nullptr))); //初始化随机数发生器,种子为当前时间值
    for (int i = 0; i < n; i++) {
        Node* newList = new Node;
        newList->date.year = getRand(START, STOP);
        newList->date.month = getRand(1, 12);
        newList->date.day = getRand(1, 31);
        newList->next = head->next; //将新结点拼接到哨兵结点的后面
        head->next = newList;
    }
    cout << "共创建" << n << "个日期结点(" << START << "<=年<=" << STOP
        << "，1<=月<=12，1<=日<=31)。" << endl;
    pauseAndCls();
}

/**
* 获取创建结点数
* @return 创建的结点数
*/
int getCreateNum() {
    int n;
    while (true) {
        cout << "请输入想要创建的日期节点数：";
        cin >> n;
        if (n < 0) {
            cout << "请输入一个不小于0的数！" << endl;
        } else {
            cout << endl;
            return n;
        }
    }
}

/**
* 显示链表前几个节点的日期数据
* @param head 哨兵结点
*/
void showList(const Node* head) {
    //判断链表是否为空
    if (isNull(head)) {
        cout << "链表为空!" << endl;
    } else {
        int n = getShowNum();
        int i = 0;
        for (head = head->next; head != nullptr; head = head->next) {
            i++;
            if (n == 0 || i <= n) {
                printDate(head->date);
                if (i % 5 == 0) {
                    //每5个数据换行一次
                    cout << endl;
                }
            }
        }
        cout << endl << endl << "结点总数：" << i
            << "，当前显示的结点数:" << (n == 0 ? i : n < i ? n : i) << endl << endl;
    }
    pauseAndCls();
}

/**
* 将整个链表的所有数据存入文件中
* @param head 哨兵结点
*/
void saveList(const Node* head) {
    //判断链表是否为空
    if (isNull(head)) {
        cout << "链表为空!" << endl;
    } else {
        char temp[50];
        ofstream file;
        getSaveFile(file);
        int i = 0;
        for (head = head->next; head != nullptr; head = head->next) {
            i++;
            //利用sprintf格式化输出到文件
            sprintf(temp, "%04d.%02d.%02d\t", head->date.year, head->date.month, head->date.day);
            file << temp;
            if (i % 5 == 0) {
                //每5个数据换行一次
                file << endl;
            }
        }
        cout << "已将" << i << "个结点存入文件中!" << endl;
        file.close();
    }
    pauseAndCls();
}

/**
 * 获取要存储的文件对象
 * @param file 空文件对象
 * @return 已打开文件的对象
 */
ofstream& getSaveFile(ofstream& file) {
    string name;
    while (true) {
        cout << "请输入文件名：";
        cin >> name;
        file.open(name);
        if (!file.is_open()) {
            cout << "Error！文件打开(创建)失败，请检查权限或硬盘空间是否充足！" << endl;
        } else {
            return file;
        }
    }
}

/**
* 分屏显示日期数据文件的（全部）内容
*/
void showListFile() {
    string text;
    ifstream file;
    getShowFile(file);
    system("cls");
    for (int i = 1; getline(file, text); i++) {
        printf("%4d：", i);
        cout << text << endl;
        if (i % 20 == 0) {
            //每20行换页
            cout << "按任意键继续显示下一页......" << endl;
            _getch();
        }
    }
    file.close();
    pauseAndCls();
}

/**
 * 获取要打开的文件对象
 * @param file 空文件对象
 * @return 已打开文件的对象
 */
ifstream& getShowFile(ifstream& file) {
    string name;
    while (true) {
        cout << "请输入文件名：";
        cin >> name;
        file.open(name);
        if (!file.is_open()) {
            cout << "Error！文件打开失败，请检查文件名是否正确或文件是否拥有打开权限！" << endl;
        } else {
            return file;
        }
    }
}

/**
* 显示不能构成合法日期的（所有）结点
* @param head 哨兵结点
*/
void showListIfNotDate(const Node* head) {
    //判断链表是否为空
    if (isNull(head)) {
        cout << "链表为空!" << endl;
    } else {
        cout << endl;
        int i = 0;
        for (head = head->next; head != nullptr; head = head->next) {
            if (!checkDate(head->date)) {
                i++;
                printDate(head->date);
                if (i % 5 == 0) {
                    //每5个数据换行一次
                    cout << endl;
                }
            }
        }
        cout << endl << "不能构成合法日期的结点总数：" << i << endl << endl;
    }
    pauseAndCls();
}

/**
* 删除链表的第一个、最后一个、不能构成合法日期的结点
* @param head 哨兵结点
*/
void deleteList(Node* head) {
    //判断链表是否为空
    if (isNull(head)) {
        cout << "链表为空!" << endl;
    } else {
        showDeleteMenu(); //显示菜单
        switch (getKey()) {
            case 'A':
                deleteListHead(head); //删除头
                break;
            case 'B':
                deleteListEnd(head); //删除尾
                break;
            case 'C':
                deleteListIfNotDate(head); //删除不是日期的节点
                break;
            case 'Q':
                break;
            default:
                //用户按下了错误的按键
                cout << endl << "\a选择错误，请重新选择......" << endl << endl;
                deleteList(head);
                return;
        }
    }
    pauseAndCls();
}

/**
* 删除链表的第一个结点
* @param head 哨兵结点
*/
void deleteListHead(Node* head) {
    Node* temp = head->next;
    head->next = head->next->next;
    delete temp;
    cout << "成功删除链表的第一个结点" << endl;
}

/**
* 删除链表的最后一个结点
* @param head 哨兵结点
*/
void deleteListEnd(Node* head) {
    while (head->next->next != nullptr) {
        head = head->next;
    }
    Node* temp = head->next;
    head->next = nullptr;
    delete temp;
    cout << "成功删除链表的最后一个结点" << endl;
}

/**
* 删除链表中不能构成合法日期的结点
* @param head 哨兵结点
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
    cout << "成功删除" << i << "个不能构成合法日期的结点" << endl;
}

/**
* 显示删除结点菜单
*/
void showDeleteMenu() {
    cout << endl
        << "********************************************************" << endl
        << "*    A：删除链表的第一个结点                           *" << endl
        << "*    B：删除链表的最后一个结点                         *" << endl
        << "*    C：删除链表中不能构成合法日期的结点               *" << endl
        << "*    Q：返回到主菜单                                   *" << endl
        << "********************************************************" << endl
        << "请选择（A，B，C，Q）：";
}

/**
* 插入结点（至链头、链尾、结点之前、结点之后）
* @param head 哨兵结点
*/
void insertList(Node* head) {
    showInsertMenu(); //显示菜单
    switch (getKey()) {
        case 'A':
            insertTodayToListHead(head); //添加头
            break;
        case 'B':
            insertTodayToListEnd(head); //添加尾
            break;
        case 'C':
            insertTodayToPrev(head); //添加到前面
            break;
        case 'D':
            insertTodayToNext(head); //添加到后面
            break;
        case 'Q':
            break;
        default:
            //用户按下了错误的按键
            cout << endl << "\a选择错误，请重新选择......" << endl << endl;
            insertList(head);
            return;
    }
    pauseAndCls();
}

/**
* 将用当前日期构造的一个新结点加到链头
* @param head 哨兵结点
*/
void insertTodayToListHead(Node* head) {
    Node* node = createTodayList();
    if (node == nullptr) {
        cout << "创建结点失败，可能是内存不足！" << endl;
    } else {
        node->next = head->next;
        head->next = node;
        cout << "成功插入一个新结点!" << endl;
    }
}

/**
* 将用当前日期构造的一个新结点加到链尾
* @param head 哨兵结点
*/
void insertTodayToListEnd(Node* head) {
    Node* node = createTodayList();
    if (node == nullptr) {
        cout << "创建结点失败，可能是内存不足！" << endl;
    } else {
        while (head->next != nullptr) {
            head = head->next;
        }
        head->next = node;
        cout << "成功插入一个新结点!" << endl;
    }
}

/**
* 将用当前日期构造的一个新结点插入到第一个大于该结点日期的前面
* @param head 哨兵结点
*/
void insertTodayToPrev(Node* head) {
    Node* node = createTodayList();
    if (node == nullptr) {
        cout << "创建结点失败，可能是内存不足！" << endl;
    } else {
        while (head->next != nullptr) {
            if (compareDate(node->date, head->next->date) < 0) {
                node->next = head->next;
                head->next = node;
                cout << "成功插入一个新结点!" << endl;
                break;
            }
            head = head->next;
        }
        if (head->next == nullptr) {
            //已经移动到链表尾仍然没有新结点插入
            cout << "Error~~没有任何新结点被插入!" << endl;
        }
    }
}

/**
* 将用当前日期构造的一个新结点插入到第一个小于该结点日期的后面
* @param head 哨兵结点
*/
void insertTodayToNext(Node* head) {
    Node* node = createTodayList();
    if (node == nullptr) {
        cout << "创建结点失败，可能是内存不足！" << endl;
    } else {
        for (head = head->next; head != nullptr; head = head->next) {
            if (compareDate(node->date, head->date) > 0) {
                node->next = head->next;
                head->next = node;
                cout << "成功插入一个新结点!" << endl;
                break;
            }
        }
        if (head->next == nullptr) {
            //已经移动到链表尾仍然没有新结点插入
            cout << "Error~~没有任何新结点被插入!" << endl;
        }
    }
}

/**
* 新建一个当前日期的结点
* @return 当前日期的结点
*/
Node* createTodayList() {
    tm* timeinfo = getTime();
    Node* node = new Node;
    if (node == nullptr) {
        //申请内存失败，直接返回空指针让调用方判断是否为空，避免接下来的赋值操作出错
        return nullptr;
    }
    node->date.year = timeinfo->tm_year + 1900;
    node->date.month = timeinfo->tm_mon + 1;
    node->date.day = timeinfo->tm_mday;
    node->next = nullptr;
    return node;
}

/**
* 显示插入结点菜单
*/
void showInsertMenu() {
    cout << "" << endl
        << "************************************************************************" << endl
        << "*    A：将用当前日期构造的一个新结点加到链头                           *" << endl
        << "*    B：将用当前日期构造的一个新结点加到链尾                           *" << endl
        << "*    C：将用当前日期构造的一个新结点插入到第一个大于该结点日期的前面   *" << endl
        << "*    D：将用当前日期构造的一个新结点插入到第一个小于该结点日期的后面   *" << endl
        << "*    Q：返回到主菜单                                                   *" << endl
        << "************************************************************************" << endl
        << "请选择（A，B，C，D，Q）：";
}

/**
* 显示结点的日期对应的天数(从1900.1.1开始)
* @param head 哨兵结点
*/
void showListDays(const Node* head) {
    //判断链表是否为空
    if (isNull(head)) {
        cout << "链表为空!" << endl;
    } else {
        int n = getShowNum();
        int i = 0;
        for (head = head->next; head != nullptr; head = head->next) {
            i++;
            if (n == 0 || i <= n) {
                cout << switchTimeToInt(head->date, 1900) << "\t";
                if (i % 5 == 0) {
                    //每5个数据换行一次
                    cout << endl;
                }
            }
        }
        cout << endl << endl << "结点总数：" << i
            << "，当前显示的结点数:" << (n == 0 ? i : n < i ? n : i) << endl << endl;
    }
    pauseAndCls();
}

/**
* 链表按日期从小到大排序
* @param head 哨兵结点
*/
void sortList(Node* head) {
    //判断链表是否为空
    if (isNull(head)) {
        cout << "链表为空!" << endl;
    } else {
        cout << "正在排序，请稍候......" << endl;
        Node* stop = nullptr;
        clock_t start = clock();
        //冒泡排序法，将日期大的移动到链表尾部
        while (head->next != stop) {
            Node* prev = head;
            Node* temp = head->next;
            while (temp->next != stop) {
                if (compareDate(temp->date, temp->next->date) > 0) {
                    //调换前后元素的地址实现排序
                    prev->next = temp->next;
                    temp->next = temp->next->next;
                    prev->next->next = temp;
                    temp = prev->next;
                }
                prev = prev->next;
                temp = temp->next;
            }
            stop = temp; //记录下最后一个结点的前一个结点位置，作为下个循环的结束点
        }
        clock_t end = clock();
        cout << endl << "排序结束。用时" << (double(end - start)) / CLK_TCK << "s" << endl;
    }
    pauseAndCls();
}

/**
* 查找链表中“年月日”都是素数的结点
* @param head 哨兵结点
*/
void findListIfPrime(const Node* head) {
    //判断链表是否为空
    if (isNull(head)) {
        cout << "链表为空!" << endl;
    } else {
        int i = 0;
        cout << endl;
        for (head = head->next; head != nullptr; head = head->next) {
            //年月日都是质数
            if (isPrime(head->date.year) && isPrime(head->date.month) && isPrime(head->date.day)) {
                i++;
                printDate(head->date);
                if (i % 5 == 0) {
                    //每5个数据换行一次
                    cout << endl;
                }
            }
        }
        cout << endl << "有" << i << "个年月日都是素数的结点!" << endl;
    }
    pauseAndCls();
}

/**
* 链表翻转
* @param head 哨兵结点
*/
void flipList(Node* head) {
    //判断链表是否为空
    if (isNull(head)) {
        cout << "链表为空!" << endl;
    } else {
        Node* p = head->next;
        head->next = nullptr;
        while (p != nullptr) {
            Node* temp = p->next;
            p->next = head->next;
            head->next = p;
            p = temp;
        }
        cout << endl << "链表已成功翻转！" << endl;
    }
    pauseAndCls();
}

/**
* 退出
* @param head 哨兵结点
*/
void quit(Node* head) {
    Node* p = head->next;
    //将所有结点内存释放掉
    while (p != nullptr) {
        Node* temp = p->next;
        delete p;
        p = temp;
    }
    delete head; //释放哨兵结点内存
    exit(0);     //正常退出
}

/**
 * 判断链表是否为空
 * @param head 哨兵结点
 * @return true 链表为空
 * @return false 链表不为空
 */
bool isNull(const Node* head) {
    return head->next == nullptr;
}

/**
 * 暂停程序并清除屏幕
 */
void pauseAndCls() {
    system("pause"); //按任意键继续
    system("cls");   //清除屏幕
}

/**
 * 获取并显示输入的字母
 * @return 获取到的字母(已转化为大写)
 */
char getKey() {
    const char key = toupper(_getch()); //实时获取输入并转换为大写
    cout << key << endl;                //显示输入的内容
    return key;
}

/**
 * 获取输出结点数
 * @return 输出的结点数(0为全部结点)
 */
int getShowNum() {
    int n;
    while (true) {
        cout << "请输入要输出的日期结点数（输入0则输出全部结点）:";
        cin >> n;
        if (n < 0) {
            cout << "请输入一个大于0的数！" << endl;
        } else {
            cout << endl;
            return n;
        }
    }
}

/**
 * 获得存储当前时间的时间结构指针
 * @return 时间结构指针
 */
tm* getTime() {
    time_t rawtime;
    time(&rawtime);
    return localtime(&rawtime);
}

/**
 * 格式化输出日期
 * @param date 日期结构
 */
void printDate(const Date& date) {
    //格式化输出,故用printf
    printf("%04d.%02d.%02d\t", date.year, date.month, date.day);
}

/**
* 检查日期的合法性
* @param date 日期结构
* @return true 日期合法
* @return false 日期不合法
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
* 生成一个指定区间的随机数
* @param start 起始数
* @param stop 终止数
* @return 一个指定区间的随机数
*/
int getRand(const int start, const int stop) {
    return rand() % (stop - start + 1) + start;
}

/**
* 把时间转化为数字
* @param date 日期结构
* @param baseYear 计算开始的年份
* @return 转化完成的数字
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
 * 判断闰年
 * @param year 年份
 * @return true 是闰年 
 * @return false 不是闰年
 */
bool isLeapYear(const int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

/**
* 比较两个日期大小
* @param date1 第一个日期结构
* @param date2 第二个日期结构
* @return 1 第一个日期 > 第二个日期
* @return 0 第一个日期 = 第二个日期
* @return -1 第一个日期 < 第二个日期
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
* 判断一个整数是否为质数
* @param num 整数
* @return true 是质数
* @return false 不是质数
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
