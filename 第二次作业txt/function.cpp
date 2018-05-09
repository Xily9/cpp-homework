#include "utils.h"
#include "function.h"
#include "dbhelper.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>

using namespace std;
const string types[] = {
    "学号", "姓名", "性别", "国别", "出生年月", "民族", "婚姻状况",
    "政治面貌", "身份证号", "学生类别", "入学年月", "入学方式", "学院", "专业", "学制",
    "培养层次", "年级", "班级号", "辅导员"
};

/**
 * 显示主菜单
 */
void showMainMenu() {
    cout << "Copyright (C) 2018 曾宏健(221701423).All Rights Reserved." << endl << endl;
    showTime();
    cout << "*************************************************************" << endl
        << "*    A：添加学生数据                                        *" << endl
        << "*    B：显示学生数据                                        *" << endl
        << "*    C：查找学生数据                                        *" << endl
        << "*    D：排序学生数据                                        *" << endl
        << "*    E：统计分析学生数据                                    *" << endl
        << "*    Q：退出系统                                            *" << endl
        << "*************************************************************" << endl
        << "请选择（A,B,C,D,E,Q）：";
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
 * 添加一条新数据
 * @param dbHelper db帮助类 
 */
void addData(DbHelper& dbHelper) {
    File value;
    inputData(dbHelper, value, false);
    dbHelper.add(value);
    cout << "添加一条新学生数据成功!" << endl;
}

/**
 * 录入数据
 * @param dbHelper db帮助类 
 * @param value txt容器 
 * @param isEdit 是否是编辑状态
 * @return 填充后的txt容器
 */
File& inputData(DbHelper& dbHelper, File& value, const bool isEdit) {
    int collegeId, inYear;
    if (!isEdit) {
        value[0] = getInput("学号", "学号必须为9位",
                               [&dbHelper, &collegeId, &inYear](const string& id) {
                                   return checkId(dbHelper, id, collegeId, inYear);
                               });
    } else {
        collegeId = strToInt(value[0].asString().substr(0, 2));
        inYear = strToInt(value[0].asString().substr(2, 2)) + 2000;
    }
    value[3] = inputCountry();
    bool isChinese = value[3].asString() == "中国";
    value[1] = getInput("姓名", isChinese ? "姓名为2-10个汉字" : "姓名应不超过40个字符",
                             [isChinese](const string& name) { return checkName(name, isChinese); });
    value[2] = getInput("性别", "只能输入男/女", [](const string& sex) { return checkSex(sex); });
    string birthDateFormat;
    value[4] = getInput("出生日期", "格式必须形如1998.11.4",
                                  [&birthDateFormat](const string& birthDate) {
                                      return checkBirthDate(birthDate, birthDateFormat);
                                  });
    value[8] = getInput("身份证号码", "",
                                 [&dbHelper, &value, &birthDateFormat](const string& personId) {
                                     return checkPersonId(dbHelper, personId,
                                                          value[2].asString() == "男" ? 1 : 2,
                                                          birthDateFormat);
                                 });
    value[5] = inputNation();
    value[7] = inputPolitics();
    value[6] = inputMarry();
    value[9] = inputStudentType();
    value[11] = inputInType();
    value[10] = getInput("入学年月", "形如2017.09.14", [inYear](const string& inDate) {
        return checkInDate(inDate, inYear);
    });
    int index;
    value[12] = inputCollege(index, collegeId);
    value[13] = inputMajor(index);
    value[16] = getInput("年级", "形如2015", [inYear](const string& grade) {
        return checkGrade(grade, inYear);
    }, true, to_string(inYear));
    value[14] = getInput("学制", "", [](const string& length) { return ""; }, true, "4");
    value[15] = inputLevel();
    value[17] = getInput("班级", "", [](const string& cls) {
        return checkClass(cls);
    });
    value[18] = getInput("辅导员", "", [&value](const string& instructor) {
        return checkInstructor(instructor, value[0].asString());
    });
    return value;
}

/**
 * 从键盘上获取字符串并做校验
 * @tparam T lambda
 * @param type 值文字
 * @param message 提示信息
 * @param check 回调函数
 * @param useDefault 是否有默认值,默认没有
 * @param defaultValue 默认值,默认空
 * @return 获取到并检验通过的字符串
 */
template <typename T>
string getInput(const string& type, const string& message, T check, const bool useDefault, const string& defaultValue) {
    string str;
    while (true) {
        cout << "请输入" << type;
        if (useDefault) {
            cout << "(默认为" << defaultValue << ")";
        }
        cout << endl;
        if (!message.empty()) {
            cout << message << endl;
        }
        if (useDefault && cin.peek() == '\n') {
            str = defaultValue;
        } else {
            cin >> str;
        }
        getchar();
        string errorMsg = check(str);
        if (errorMsg.empty()) {
            return str;
        } else {
            cout << errorMsg << endl;
        }
    }
}

/**
 * 输入国家
 * @return 国家 
 */
string inputCountry() {
    static const DbHelper dbHelper("data/country.txt");
    return inputList(dbHelper, "国家", 3);
}

/**
 * 输入民族
 * @return 民族 
 */
string inputNation() {
    static const DbHelper dbHelper("data/nation.txt");
    return inputList(dbHelper, "民族");
}

/**
 * 输入政治面貌
 * @return 政治面貌
 */
string inputPolitics() {
    static const DbHelper dbHelper("data/politics.txt");
    return inputList(dbHelper, "政治面貌");
}

/**
 * 输入婚姻状况
 * @return 婚姻状况
 */
string inputMarry() {
    static const DbHelper dbHelper("data/marry.txt");
    return inputList(dbHelper, "婚姻情况");
}

/**
 * 输入学生类别
 * @return 学生类别
 */
string inputStudentType() {
    static const DbHelper dbHelper("data/student_type.txt");
    return inputList(dbHelper, "学生类别");
}

/**
 * 输入入学方式
 * @return 入学方式
 */
string inputInType() {
    static const DbHelper dbHelper("data/in_type.txt");
    return inputList(dbHelper, "入学方式");
}

/**
 * 输入培养层次
 * @return 培养层次
 */
string inputLevel() {
    static const DbHelper dbHelper("data/level.txt");
    return inputList(dbHelper, "培养层次");
}

/**
 * 输入学院信息
 * @param index 用于回调学院编号
 * @param collegeId 学号上的学院信息
 * @return 学院信息
 */
string inputCollege(int& index, const int collegeId) {
    static const DbHelper dbHelper("data/college.txt");
    unsigned n;
    const File value = dbHelper.getValue();
    static int width = getConsoleWidth();
    cout << endl << "----------------------------------" << endl;
    cout.setf(ios_base::left, ios_base::adjustfield);
    for (unsigned i = 0; i < value.size(); i++) {
        cout << setw(width / 4) << "[" + to_string(i) + "] " + value[i][1].asString();
        if (i % 4 == 3) {
            cout << endl;
        }
    }
    cout << endl << "----------------------------------" << endl;
    while (true) {
        cout << endl << "请输入学院前面的序号：";
        cin >> n;
        getchar();
        if (cin.fail()) {
            cin.clear();
            cin.sync();
            cout << "输入的内容不合法,请重新输入!" << endl;
        } else if (n >= value.size()) {
            cout << "输入的内容有误,请重新输入!" << endl;
        } else if (value[n][0].asInt() != collegeId) {
            cout << "输入的学院信息与之前学号对应的学院信息不一致!" << endl;
        } else {
            break;
        }
    }
    index = n;
    return value[n][1].asString();
}

/**
 * 输入专业信息
 * @param index 学员编号
 * @return 专业信息
 */
string inputMajor(const int index) {
    static DbHelper dbHelper("data/college.txt");
    unsigned n;
    const File value = dbHelper[index][2];
    showListMenu(value, 4);
    while (true) {
        cout << endl << "请输入专业前面的序号：";
        cin >> n;
        getchar();
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "输入的内容不合法,请重新输入!" << endl;
        } else if (n >= value.size()) {
            cout << "输入的内容有误,请重新输入!" << endl;
        } else {
            break;
        }
    }
    return value[n].asString();
}

/**
 * 从列表中获取输入
 * @param dbHelper db帮助类 
 * @param type 值文字
 * @param lineLength 一行显示数量 
 * @return 获取到的字符串
 */
string inputList(const DbHelper& dbHelper, const string& type, const unsigned lineLength) {
    unsigned n;
    const File value = dbHelper.getValue();
    showListMenu(value, lineLength);
    while (true) {
        cout << "请输入" << type << "前面的序号(默认为" << value[0].asString() << ")：";
        if (cin.peek() != '\n') {
            cin >> n;
            getchar();
            if (cin.fail()) {
                cin.clear();
                cin.sync();
                cout << "输入的内容不合法,请重新输入!" << endl;
            } else if (n >= value.size()) {
                cout << "输入的内容有误,请重新输入!" << endl;
            } else {
                break;
            }
        } else {
            getchar();
            n = 0;
            break;
        }

    }
    return value[n].asString();
}

/**
 * 展示数据
 * @param dbHelper db帮助类 
 * @param value txt容器,默认为空
 */
void showData(DbHelper& dbHelper, File value) {
    if (value.isNull()) {
        value = dbHelper.getValue();
    }
    int page = 1;
    const int pageNum = value.size() / 20 + 1;
    cin.clear();
    fflush(stdin);
    while (true) {
        system("cls");
        cout.setf(ios_base::left, ios_base::adjustfield);
        cout << setw(5) << "序号" << setw(10) << "学号" << setw(10) << "姓名" << endl;
        for (int i = 0; i < 20; i++) {
            const File& array = value[(page - 1) * 20 + i];
            if (array.isNull()) {
                break;
            }
            cout << setw(5) << (page - 1) * 20 + i + 1 << setw(10) << array[0].asString()
                << setw(10) << array[1].asString() << endl;
        }
        bool out = false;
        while (!out) {
            cout << "----------------------------------" << endl
                << "请选择操作：上一页(A)，下一页(D)，查看学生信息(S)，返回上一级(Q)" << endl;
            switch (getKey()) {
                case 'A':
                    if (page > 1) {
                        page--;
                    }
                    out = true;
                    break;
                case 'D':
                    if (page < pageNum) {
                        page++;
                    }
                    out = true;
                    break;
                case 'Q':
                    return;
                case 'S':
                    unsigned n;
                    while (true) {
                        cout << "请输入序号:";
                        cin >> n;
                        if (n >= value.size()) {
                            cout << "请输入一个合法的序号!" << endl;
                            cin.clear();
                            cin.ignore(1024, '\n');
                        } else {
                            break;
                        }
                    }
                    showLine(dbHelper, value[n - 1][0].asString());
                    out = true;
                    break;
                default:
                    cout << endl << "\a选择错误，请重新选择......" << endl << endl;
                    break;
            }
        }
    }
}

/**
 * 展示一条数据
 * @param dbHelper db帮助类 
 * @param id 学号
 */
void showLine(DbHelper& dbHelper, const string& id) {
    system("cls");
    const int index = dbHelper.findById(id);
    if (index < 0) {
        cout << "获取学生信息错误!" << endl;
        system("pause");
    } else {
        File value = dbHelper[index];
        cout << "------------------------------" << endl;
        for (unsigned i = 0; i < 19; i++) {
            cout << types[i] << "：" << value[i].asString() << endl;
        }
        bool out = false;
        while (!out) {
            cout << "---------------------------------" << endl
                << "请选择操作：删除当前(D),删除整个年级+专业(G),修改(E),返回上级(Q)";
            switch (getKey()) {
                case 'D':
                    deleteByIndex(dbHelper, index);
                    system("pause");
                    out = true;
                    break;
                case 'G':
                    deleteData(dbHelper, value[13].asString(), value[16].asString());
                    system("pause");
                    out = true;
                    break;
                case 'E':
                    editByIndex(dbHelper, index);
                    system("pause");
                    out = true;
                    break;
                default:
                    cout << endl << "\a选择错误，请重新选择......" << endl << endl;
                    break;
            }
        }
    }
}

/**
 * 查找数据
 * @param dbHelper db帮助类 
 */
void findData(DbHelper& dbHelper) {
    string str;
    File value = dbHelper.getValue();
    showListMenu(types, 19);
    cout << "请输入上面的一项或多项条件前的序号作为搜索条件" << endl
        << "条件和值之间用逗号隔开，多个条件之间用换行隔开，输入EOF结束" << endl;
    while (cin >> str) {
        const int pos = str.find(',');
        const string val = str.substr(pos + 1);
        value = DbHelper::findAll(value,strToInt(str.substr(0, pos)) , val);
        if (value.isNull()) {
            cout << "查找结果为空!!" << endl;
            return;
        }
    }
    showData(dbHelper, value);
}

/**
 * 删除整个专业+年级数据
 * @param dbHelper db帮助类 
 * @param major 专业
 * @param grade 年级
 */
void deleteData(DbHelper& dbHelper, const string& major, const string& grade) {
    if (getTime()->tm_year + 1904 - strToInt(grade) < 10) {
        cout << "仅能删除毕业10年以上的学生!" << endl;
    } else {
        cout << "确定要删除吗?????" << endl
            << "删除后数据将无法进行恢复" << endl
            << "确定请按Y,取消请按其他任意键" << endl;
        if (getKey() == 'Y') {
            File values = dbHelper.findAll(13, major);
            values = DbHelper::findAll(values, 16, grade);
            int i = 0;
            for (File value : values) {
                const int index = dbHelper.findById(value[0].asString());
                if (index >= 0) {
                    dbHelper.del(index);
                    i++;
                }
            }
            cout << "执行完毕,共删除" << i << "条数据!" << endl;
        }
    }
}

/**
 * 删除一条数据
 * @param dbHelper db帮助类 
 * @param index 
 */
void deleteByIndex(DbHelper& dbHelper, const int index) {
    cout << "确定要删除吗?????" << endl
        << "确定请按Y,取消请按其他任意键" << endl;
    if (getKey() == 'Y') {
        if (dbHelper.del(index)) {
            cout << "删除成功!";
        } else {
            cout << "删除失败!";
        }
    }
}

/**
 * 编辑一条数据
 * @param dbHelper db帮助类 
 * @param index 数据下标
 */
void editByIndex(DbHelper& dbHelper, int index) {
    File value = dbHelper[index];
    inputData(dbHelper, value, true);
    dbHelper.update(index, value);
    cout << "编辑成功!!" << endl;
}

/**
 * 排序
 * @param dbHelper db帮助类
 */
void sortData(DbHelper& dbHelper) {
    File value = dbHelper.getValue();
    showListMenu(types, 19);
    unsigned n;
    int isDesc;
    while (true) {
        cout << "请输入上面的条件前的序号作为排序条件" << endl;
        cin >> n;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "输入的内容不合法,请重新输入!" << endl;
        } else if (n >= 19) {
            cout << "输入的内容有误,请重新输入!" << endl;
        } else {
            break;
        }
    }
    while (true) {
        cout << "是升序还是降序呢?(1升序2降序)" << endl;
        cin >> isDesc;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "输入的内容不合法,请重新输入!" << endl;
        } else if (isDesc != 1 && isDesc != 2) {
            cout << "输入的内容有误,请重新输入!" << endl;
        } else {
            break;
        }
    }
    cout << "正在排序中,请稍后..." << endl;
    isDesc = isDesc == 1 ? 1 : -1;
    quickSort(value, 0, value.size()-1, [isDesc,n](const File& left,const File& right) {
        return left[n].asString().compare(right[n].asString())*isDesc;
    });
    dbHelper.setValue(value);
    cout << "排序完成!" << endl;
}

/**
 * 统计
 * @param dbHelper db帮助类 
 */
void countData(const DbHelper& dbHelper) {
    int by[17];
    File value = dbHelper.getValue();
    showListMenu(types, 19);
    cout << "请输入上面的一项或多项分类前的序号作为分类方式,条件之间用空格隔开" << endl;
    int i = 0, n;
    while (cin.peek() != '\n') {
        cin >> n;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "输入的内容不合法,请重新输入!" << endl;
        } else if (n >= 17) {
            cout << "输入的内容有误,请重新输入!" << endl;
        } else {
            by[i++] = n;
        }
    }
    getchar();
    vector<vector<string>> vecs;
    for (int j = 0; j < i; j++) {
        vector<string> vec;
        quickSort(value, 0, value.size()-1, [by,j](const File& left, const File& right) {
            return left[by[j]].asString().compare(right[by[j]].asString());
        });
        for (auto& k : value) {
            const string str = k[by[j]].asString();
            if (vec.empty() || str != vec.back()) {
                vec.push_back(str);
            }
        }
        vecs.push_back(vec);
    }
    cout << "---------------------------------" << endl;
    cout.setf(ios_base::left, ios_base::adjustfield);
    for (int j = 0; j < i;j++) {
        cout << setw(30) << types[by[j]];
    }
    cout << "数量" << endl;
    showCountData(vecs, 0, value, by);
    cout << "---------------------------------" << endl;
}

/**
 * 展示统计数据
 * @param vecs 所有的类型的vector容器
 * @param i 下标
 * @param value txt容器
 * @param by 条件
 */
void showCountData(const vector<vector<string>>& vecs, const unsigned i, const File& value, int by[]) {
    if (i < vecs.size()) {
        for (unsigned j = 0; j < vecs[i].size(); j++) {
            const File value1 = DbHelper::findAll(value, by[i],vecs[i][j]);
            if (!value1.isNull()) {
                showCountData(vecs, i + 1, value1, by);
            }
        }
    } else {
        for(unsigned j=0;j<i;j++) {
            cout << setw(30) << value[0][by[j]].asString();
        }
        cout << value.size() << endl;
    }
}

/**
 * 展示列表菜单
 * @param list string数组
 * @param size 数组大小
 */
void showListMenu(const string list[], unsigned size) {
    cout << "---------------------------------" << endl;
    for (unsigned i = 0; i < size; i++) {
        cout << "[" << i << "] " << list[i] << "\t";
        if (i % 6 == 5) {
            cout << endl;
        }
    }
    cout << endl << "---------------------------------" << endl;
}

/**
 * 展示列表菜单
 * @param value txt容器
 * @param lineLength 一行显示数量
 */
void showListMenu(const File& value, const unsigned lineLength) {
    static int width = getConsoleWidth();
    cout << endl << "----------------------------------" << endl;
    cout.setf(ios_base::left, ios_base::adjustfield);
    for (unsigned i = 0; i < value.size(); i++) {
        cout << setw(width / lineLength) << "[" + to_string(i) + "] " + value[i].asString();
        if (i % lineLength == lineLength - 1) {
            cout << endl;
        }
    }
    cout << endl << "----------------------------------" << endl;
}

/**
 * 校验学号
 * @param dbHelper db帮助类 
 * @param id 学号
 * @param collegeId 学号上的学院信息,用于回调
 * @param inYear 学号上的入学年份,用于回调
 * @return 错误信息
 */
string checkId(const DbHelper& dbHelper, const string& id, int& collegeId, int& inYear) {
    if (!isInt(id)) {
        return "学号必须为数字!";
    }
    if (dbHelper.findById(id) >= 0) {
        return "该学号已经被添加过!";
    }
    static DbHelper dbHelper2("data/college.txt");
    const int college = strToInt(id.substr(0, 2));
    const int index = dbHelper2.find(0, college);
    if (index < 0) {
        return "输入的学号的学院码有误!";
    }
    File value = dbHelper2[index];
    const int year = strToInt(id.substr(2, 2)) + 2000;
    if (getTime()->tm_year + 1900 != year) {
        cout << "学号中的入学年份与当前年份不一致!" << endl;
    }
    int major = strToInt(id.substr(4, 2));
    int cls = strToInt(id.substr(6, 1));
    collegeId = value[0].asInt();
    inYear = year;
    return "";
}

/**
 * 校验性别
 * @param sex 性别
 * @return 错误信息
 */
string checkSex(const string& sex) {
    if (sex == "男" || sex == "女") {
        return "";
    } else {
        return "性别只能是男或女!";
    }
}

/**
 * 校验出生日期
 * @param birthDate 出生日期
 * @param birthDateFormat 格式化后的出生日期,用于回调
 * @return 错误信息
 */
string checkBirthDate(const string& birthDate, string& birthDateFormat) {
    int year, month, day;
    char birthDateFormatChar[40];
    sscanf(birthDate.c_str(), "%d.%d.%d", &year, &month, &day);
    if (!checkDate(year, month, day)) {
        return "出生日期不合法!";
    }
    const int years = getTime()->tm_year + 1900 - year;
    if (years > 100 || years < 10) {
        return "入学年龄必须在10-100之间";
    }
    sprintf(birthDateFormatChar, "%04d%02d%02d", year, month, day);
    birthDateFormat = birthDateFormatChar;
    return "";
}

/**
 * 校验身份证号码
 * @param dbHelper db帮助类 
 * @param personId 身份证号码
 * @param sex 性别
 * @param birthDate 出生日期
 * @return 错误信息
 */
string checkPersonId(const DbHelper& dbHelper, const string& personId, const int sex, const string& birthDate) {
    if (personId.size() != 18) {
        return "身份证号码必须为18位!";
    }
    if (dbHelper.find(8, personId) >= 0) {
        return "该身份证已经被添加过!";
    }
    const string locate = personId.substr(0, 6);
    static DbHelper dbHelper1("data/locate.txt");
    
    if (dbHelper1[locate].isNull()) {
        return "行政区划码错误!";
    }
    const string birthDate1 = personId.substr(6, 8);
    if (birthDate != birthDate1) {
        return "身份证上的出生日期与之前输入的出生日期不一致!";
    }
    if ((strToInt(personId.substr(16, 1)) + 1) % 2 + 1 != sex) {
        return "身份证上的性别与之前输入的性别不一致!";
    }
    if (personId.at(17) != getPersonId18(personId)) {
        return "身份证校验码错误!";
    }
    return "";
}

/**
 * 校验姓名
 * @param name 姓名
 * @param isChinese 是否是中国人
 * @return 错误信息
 */
string checkName(const string& name, const bool isChinese) {
    if (isChinese) {
        if (name.size() < 4 || name.size() > 40 || !isAllChinese(name)) {
            return "姓名必须为二到十个汉字!";
        }
    } else {
        if (name.size() > 40) {
            return "姓名必须小于40个字母!";
        }
    }
    return "";
}

/**
 * 校验年级
 * @param grade 年级
 * @param inYear 学号上的入学年份
 * @return 错误信息
 */
string checkGrade(const string& grade, const int inYear) {
    if (grade != to_string(inYear)) {
        cout << "输入的年级与学号的入学年龄不一致!";
    }
    return "";
}

/**
 * 校验入学时间
 * @param inDate 入学时间
 * @param inYear 学号上的入学年份
 * @return 错误信息
 */
string checkInDate(const string& inDate, const int inYear) {
    int year, month, day;
    sscanf(inDate.c_str(), "%d.%d.%d", &year, &month, &day);
    if (!checkDate(year, month, day)) {
        return "入学日期不合法!";
    }
    if (month < 8 || month > 10) {
        return "入学月份必须在8月-10月之间";
    }
    if (year != inYear) {
        return "入学年份必须与学号的入学年份一致!";
    }
    return "";
}

/**
 * 校验班级
 * @param cls 班级
 * @return 错误信息
 */
string checkClass(const string& cls) {
    if (cls < "01" || cls > "10") {
        return "班级号必须在01-10之间!";
    }
    return "";
}

/**
 * 校验辅导员
 * @param instructor 辅导员名字
 * @param id 学号
 * @return 错误信息
 */
string checkInstructor(const string& instructor, const string& id) {
    static DbHelper dbHelper("data/instructor.txt");
    const string key = id.substr(0, 7);
    File value = dbHelper[key];
    if (value.isNull()) {
        dbHelper.add(key, instructor);
    } else {
        if (value.asString() != instructor) {
            return "输入的辅导员信息与存储的该班级辅导员信息不一致!";
        }
    }
    return "";
}
