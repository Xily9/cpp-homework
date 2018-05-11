/**
 * 学生类实现文件<br/>
 * 对学生进行增删改查等操作<br/>
 * Copyright (c) 2018 Xily.All Rights Reserved.<br/>
 * @author 曾宏健 221701423 572089608@qq.com
 * @date 2018.5.10
 */

#include "student.h"
#include "function.h"
#include "dbhelper.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <conio.h>
#include <algorithm>
#include <stdexcept>

using namespace std;

/**
* 添加一条新数据
*/
void Student::addData() {
    system("cls");
    const Json::Value&& value = inputData();
    if (dbHelper.add(value)) {
        cout << "添加一条新学生数据成功!" << endl;
    } else {
        cout << "添加一条新学生数据失败!" << endl;
    }
}

/**
* 录入数据
* @return 填充后的json容器
*/
Json::Value Student::inputData() {
    Json::Value value;
    //学号
    value["id"] = getInput(
        "学号", "9位数字，学院编码（2位）+入学年份（2位）+数字编码（5位），"
        "形如：221500555。\n学号为唯一码，即不允许重复，也不允许为空，输入后学号不允许修改。",
        [this](const string& s) { return checkId(s); });
    //此处用lambda表达式封装验证函数,解决函数对象不能使用类成员函数的问题,以下同理
    //国家
    value["country"] = inputCountry();
    isChinese = value["country"].asString() == "中国"; //判断是否为中国人
    //姓名
    value["name"] = getInput("姓名", isChinese ? "形如：刘国庆，2～20个汉字" : "姓名应不超过40个字符",
                             [this](const string& s) { return checkName(s); });
    //性别
    value["sex"] = getInput("性别", "输入1为男，输入2为女",
                            [this](const string& s) { return checkSex(s); });
    //出生日期
    value["birthDate"] = getInput("出生日期", "格式形如1998.11.4或1998/11/4或1998-11-4\n"
                                  "入学时10<=年龄<=100，日期必须是合法的日期。",
                                  [this](const string& s) { return checkBirthDate(s); });
    //身份证号
    value["personId"] = getInput(
        "身份证号码", isChinese
                     ? "18位：前17位都是数字，最后一位为0～9或X，\n"
                     "行政区划（6位）+出生日期（8位）+顺序码（3位）+校验码（1位），身份证号不能重复"
                     : "作为外国人，身份证可以留空（输入任意字母即可）",
        [this](const string& s) { return checkPersonId(s); });
    //民族
    value["nation"] = inputNation();
    //政治面貌
    value["politics"] = inputPolitics();
    //婚姻状况
    value["marry"] = inputMarry();
    //学生类型
    value["studentType"] = inputStudentType();
    //入学方式
    value["inType"] = inputInType();
    //入学年月
    value["inDate"] = getInput("入学年月", "格式形如2017.9.14或2017/9/14或2017-9-14\n"
                               "8=<月份<=10，日期必须是合法的日期。",
                               [this](const string& s) { return checkInDate(s); });
    //学院
    value["college"] = inputCollege();
    //专业
    value["major"] = inputMajor();
    //年级
    value["grade"] = getInput("年级", "形如：2017，年级与学号的年级应该要一致",
                              [this](const string& s) { return checkGrade(s); }
                              , true, to_string(inYear));
    //学制
    value["length"] = getInput("学制", "", [](const string& length) { return length; }, true, "4");
    //培养层次
    value["level"] = inputLevel();
    //班级
    value["class"] = getInput("班级", "范围：1～10",
                              [this](const string& s) { return checkClass(s); });
    //辅导员
    value["instructor"] = getInput("辅导员", "辅导员必须与该班级的辅导员信息一致\n"
                                   "如果没有存储该班级的辅导员信息\n"
                                   "这就意味着你录入的是该班级的第一条信息,请务必保证输入的辅导员是正确的",
                                   [this](const string& s) { return checkInstructor(s); });
    return value;
}

/**
* 输入国家
* @return 国家
*/
string Student::inputCountry() {
    static const DbHelper dbHelper("data/country.json");
    return inputList(dbHelper, "国家", 3);
}

/**
* 输入民族
* @return 民族
*/
string Student::inputNation() {
    static const DbHelper dbHelper("data/nation.json");
    return inputList(dbHelper, "民族");
}

/**
* 输入政治面貌
* @return 政治面貌
*/
string Student::inputPolitics() {
    static const DbHelper dbHelper("data/politics.json");
    return inputList(dbHelper, "政治面貌");
}

/**
* 输入婚姻状况
* @return 婚姻状况
*/
string Student::inputMarry() {
    static const DbHelper dbHelper("data/marry.json");
    return inputList(dbHelper, "婚姻情况");
}

/**
* 输入学生类别
* @return 学生类别
*/
string Student::inputStudentType() {
    static const DbHelper dbHelper("data/student_type.json");
    return inputList(dbHelper, "学生类别");
}

/**
* 输入入学方式
* @return 入学方式
*/
string Student::inputInType() {
    static const DbHelper dbHelper("data/in_type.json");
    return inputList(dbHelper, "入学方式");
}

/**
* 输入培养层次
* @return 培养层次
*/
string Student::inputLevel() {
    static const DbHelper dbHelper("data/level.json");
    return inputList(dbHelper, "培养层次");
}

/**
* 输入学院信息
* @return 学院信息
*/
string Student::inputCollege() {
    static const DbHelper dbHelper("data/college.json");
    unsigned n;
    const Json::Value value = dbHelper.getValue();
    showListMenu(value, 3, "name");
    while (true) {
        cout << "请输入学院前面的序号：";
        cin >> n;
        cin.ignore(1024, '\n');
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "输入的内容不合法,请重新输入!" << endl;
        } else if (n >= value.size()) {
            cout << "输入的内容有误,请重新输入!" << endl;
        } else if (value[n]["id"].asString() != collegeId) {
            cout << "输入的学院信息与之前学号对应的学院信息不一致!" << endl;
        } else {
            break;
        }
    }
    collegeIndex = n;
    cout << "您选择的是[" << n << "] " + value[n]["name"].asString() << endl;
    return value[n]["name"].asString();
}

/**
* 输入专业信息
* @return 专业信息
*/
string Student::inputMajor() const {
    static DbHelper dbHelper("data/college.json");
    unsigned n;
    const Json::Value value = dbHelper[collegeIndex]["majors"];
    showListMenu(value, 4, "name");
    while (true) {
        cout << "请输入专业前面的序号：";
        cin >> n;
        cin.ignore(1024, '\n');
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "输入的内容不合法,请重新输入!" << endl;
        } else if (n >= value.size()) {
            cout << "输入的内容有误,请重新输入!" << endl;
        } else if (value[n]["id"].asString() != majorId) {
            cout << "输入的专业信息与之前学号对应的专业信息不一致!" << endl;
        } else {
            break;
        }
    }
    cout << "您选择的是[" << n << "] " + value[n]["name"].asString() << endl;
    return value[n]["name"].asString();
}

/**
* 展示数据
* @param value json容器,默认为空
*/
void Student::showData(Json::Value value) {
    bool isFind = true; //是否为查找模式
    if (value.isNull()) {
        isFind = false;
        value = dbHelper.getValue();
    }
    int page = 1;
    const int pageNum = value.size() / 20 + (value.size() % 20 > 0); //页数
    while (true) {
        system("cls");
        cout << "当前第" << page << "页，共有" << pageNum << "页" << endl;
        drawLine('-', 40);
        cout.setf(ios_base::left, ios_base::adjustfield);
        cout << setw(10) << "序号" << setw(20) << "学号" << setw(20) << "姓名" << endl;
        for (int i = 0; i < 20; i++) {
            const Json::Value&& array = move(value[(page - 1) * 20 + i]);
            if (array.isNull()) {
                break;
            }
            cout << setw(10) << (page - 1) * 20 + i + 1 << setw(20) << array["id"].asString()
                << setw(20) << array["name"].asString() << endl;
        }
        bool out = false;
        while (!out) {
            drawLine('-', 40);
            cout << "请选择操作：查看学生信息(输入前面的数字)，上一页(A)，下一页(D)，返回上一级(Q)" << endl;
            char key = _getch(); //先立刻获取用户按下的信息
            if (isdigit(key)) {
                //如果按下的是数字,那么认为用户要看学生信息
                cout << key; //回显
                //注:这里存在一个bug,即用户无法删除第一个字符,解决方案暂无
                ungetc(key, stdin); //把第一个数字放回缓冲区
                unsigned n;
                cin >> n;
                cin.ignore(1024, '\n');
                if (cin.fail()) {
                    cout << "输入的内容不合法,请重新输入!" << endl;
                    cin.clear();
                    cin.ignore(1024, '\n');
                } else if (n > value.size()) {
                    cout << "输入的内容有误,请重新输入!" << endl;
                } else {
                    showLine(value[n - 1]["id"].asString());
                    out = true;
                }
            } else {
                key = toupper(key);
                cout << key << endl;
                switch (key) {
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
                    default:
                        cout << endl << "\a选择错误，请重新选择......" << endl << endl;
                        break;
                }
            }
        }
        if (isUpdate) {
            //有数据发生更新
            isUpdate = false; //先消费掉事件
            if (isFind) {
                //是查找模式就直接退出
                break;
            }
            showData(); //不是的话就直接递归刷新数据
            break;
        }
    }
}

/**
* 展示一条数据
* @param id 学号
*/
void Student::showLine(const string& id) {
    system("cls");
    const int index = dbHelper.findById(id); //查找该学号对应的下标
    if (index < 0) {
        cout << "获取学生信息错误!" << endl;
    } else {
        Json::Value&& value = dbHelper.get(index); //获取该学生信息
        drawLine('-', 30);
        for (unsigned i = 0; i < size; i++) {
            cout << types[i] << "：" << value[keys[i]].asString() << endl;
        }
        drawLine('-', 30);
        bool out = false;
        while (!out) {
            cout << "请选择操作：删除当前(D),删除整个年级+专业(G),修改(E),返回上级(Q)";
            switch (getKey()) {
                case 'D':
                    deleteByIndex(index);
                    out = true;
                    break;
                case 'G':
                    deleteData(value["major"].asString(), value["grade"].asString());
                    out = true;
                    break;
                case 'E':
                    editByIndex(index);
                    out = true;
                    break;
                case 'Q':
                    return;
                default:
                    cout << endl << "\a选择错误，请重新选择......" << endl;
                    break;
            }
        }
    }
    system("pause");
}

/**
* 查找数据
*/
void Student::findData() {
    system("cls");
    string key, val;
    Json::Value&& value = dbHelper.getValue();
    showListMenu(types, size);
    cout << "请输入上面的一项或多项条件前的序号作为搜索条件" << endl
        << "条件和值之间用空格隔开，多个条件之间用换行隔开，输入EOF结束" << endl
        << "支持模糊匹配,即搜索17014可搜索到221701423或者170140123等结果" << endl;
    while (cin >> key) {
        cin >> val;
        value = DbHelper::findAll(value, keys[stoi(key)], val); //根据键名和键值查找数据
        if (value.isNull()) {
            cout << "查找结果为空!!" << endl;
            return;
        }
    }
    cin.clear();
    showData(value);
}

/**
* 删除整个专业+年级数据
* @param major 专业
* @param grade 年级
*/
void Student::deleteData(const string& major, const string& grade) {
    if (getTime()->tm_year + 1896 - stoi(grade) < 10) {
        cout << "仅能删除毕业10年以上的学生!" << endl;
    } else {
        cout << "确定要删除吗?????" << endl
            << "删除后数据将无法进行恢复" << endl
            << "确定请按Y,取消请按其他任意键" << endl;
        if (getKey() == 'Y') {
            map<string, string> map;
            map["major"] = major;
            map["grade"] = grade;
            Json::Value&& values = dbHelper.findAll(map); //查找专业年级符合条件的所有学生
            int i = 0;
            for (Json::Value& value : values) {
                const int index = dbHelper.findById(value["id"].asString());
                if (index >= 0) {
                    if (dbHelper.del(index)) {
                        i++;
                    }
                }
            }
            isUpdate = true;
            cout << "执行完毕,共删除" << i << "条数据!" << endl;
        }
    }
}

/**
* 删除一条数据
* @param index
*/
void Student::deleteByIndex(const int index) {
    cout << "确定要删除吗?????" << endl
        << "确定请按Y,取消请按其他任意键" << endl;
    if (getKey() == 'Y') {
        if (dbHelper.del(index)) {
            isUpdate = true;
            cout << "删除成功!" << endl;
        } else {
            cout << "删除失败!" << endl;
        }
    }
}

/**
* 编辑一条数据
* @param index 数据下标
*/
void Student::editByIndex(const int index) {
    const int size = 11;
    const char* types[size] = {
        "姓名", "国别", "民族", "婚姻状况",
        "政治面貌", "学生类别", "入学年月", "入学方式",
        "培养层次", "年级", "班级号"
    };
    int by[size];
    Json::Value&& value = dbHelper.get(index);
    cout << "注：由于数据关联性的原因，仅能提供以下字段的修改" << endl
        << "如果你想修改不在列表中的数据，请删除该条数据后再添加！" << endl;
    showListMenu(types, size);
    cout << "请输入上面的一项或多项字段前的序号作为你想修改的字段,序号之间用空格隔开" << endl;
    unsigned i = 0, n;
    while (cin.peek() != '\n') {
        cin >> n;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "输入的内容不合法,请重新输入!" << endl;
        } else if (n >= size) {
            cout << "输入的内容有误,请重新输入!" << endl;
        } else {
            by[i++] = n;
        }
    }
    inYear = stoi(value["id"].asString().substr(2, 2)) + 2000; //入学年份
    isChinese = value["country"].asString() == "中国";           //是否是中国人
    for (unsigned j = 0; j < i; j++) {
        switch (by[j]) {
            case 0:
                //姓名
                value["name"] = getInput("姓名", isChinese ? "姓名为2-10个汉字" : "姓名应不超过40个字符",
                                         [this](const string& s) { return checkName(s); });
                break;
            case 1:
                //国家
                value["country"] = inputCountry();
                isChinese = value["country"].asString() == "中国";
                break;
            case 2:
                //民族
                value["nation"] = inputNation();
                break;
            case 3:
                //婚姻状况
                value["marry"] = inputMarry();
                break;
            case 4:
                //政治面貌
                value["politics"] = inputPolitics();
                break;
            case 5:
                //学生类型
                value["studentType"] = inputStudentType();
                break;
            case 6:
                //入学年月
                value["inDate"] = getInput("入学年月", "形如2017.09.14",
                                           [this](const string& s) { return checkInDate(s); });
                break;
            case 7:
                //入学方式
                value["inType"] = inputInType();
                break;
            case 8:
                //培养层次
                value["level"] = inputLevel();
                break;
            case 9:
                //年级
                value["grade"] = getInput("年级", "形如：2017",
                                          [this](const string& s) { return checkGrade(s); });
                break;
            case 10:
                //班级
                value["class"] = getInput("班级", "范围：1～10",
                                          [this](const string& s) { return checkClass(s); });
            default:
                break;
        }
    }

    if (dbHelper.update(index, value)) {
        isUpdate = true;
        cout << "编辑成功!!" << endl;
    } else {
        cout << "编辑失败!!" << endl;
    }
}

/**
* 排序
*/
void Student::sortData() {
    system("cls");
    Json::Value&& value = dbHelper.getValue();
    showListMenu(types, size);
    int isDesc;
    int by[size];
    cout << "请输入上面的条件前一个或多个序号作为排序条件,序号之间用空格隔开,越靠前的优先级越高" << endl;
    int i = 0, n;
    while (cin.peek() != '\n') {
        cin >> n;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "输入的内容不合法,请重新输入!" << endl;
        } else if (n >= size) {
            cout << "输入的内容有误,请重新输入!" << endl;
        } else {
            by[i++] = n;
        }
    }
    cin.ignore(1024, '\n');
    while (true) {
        cout << "是升序还是降序呢?(输入1为升序，输入-1为降序)" << endl;
        cin >> isDesc;
        cin.ignore(1024, '\n');
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "输入的内容不合法,请重新输入!" << endl;
        } else if (isDesc != 1 && isDesc != -1) {
            cout << "输入的内容有误,请重新输入!" << endl;
        } else {
            break;
        }
    }
    cout << "正在排序中,请稍后..." << endl;
    quickSort(value, 0, value.size() - 1,
              [isDesc, &by, i, this](const Json::Value& left, const Json::Value& right) {
                  int result = 0, j = 0;
                  //当条件相等时进行循环，直到条件不相等
                  while (j < i &&
                      (result = left[keys[by[j]]].asString().compare(right[keys[by[j]]].asString()) * isDesc) == 0) {
                      j++; //移到下一个条件
                  }
                  return result;
              });
    if (dbHelper.setValue(value)) {
        cout << "排序完成!" << endl;
    } else {
        cout << "排序失败!" << endl;
    }
}

/**
* 统计
*/
void Student::countData() {
    system("cls");
    int by[size];
    Json::Value&& value = dbHelper.getValue();
    showListMenu(types, size);
    cout << "请输入上面的一项或多项分类前的序号作为分类方式,条件之间用空格隔开" << endl;
    unsigned i = 0, n;
    while (cin.peek() != '\n') {
        cin >> n;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "输入的内容不合法,请重新输入!" << endl;
        } else if (n >= size) {
            cout << "输入的内容有误,请重新输入!" << endl;
        } else {
            by[i++] = n;
        }
    }
    cin.ignore(1024, '\n');
    vector<vector<string>> vecs; //用于存储所有条件和每种条件可能的值
    //遍历所有条件
    for (unsigned j = 0; j < i; j++) {
        vector<string> vec;
        //对每种条件先排序一次,方便统计所有可能出现的值
        quickSort(value, 0, value.size() - 1, [&by, j, this](const Json::Value& left, const Json::Value& right) {
            return left[keys[by[j]]].asString().compare(right[keys[by[j]]].asString());
        });
        for (auto& k : value) {
            const string str = k[keys[by[j]]].asString();
            if (vec.empty() || str != vec.back()) {
                //如果容器为空(防止调用back异常)或者当前值不是容器的最后一个值
                vec.push_back(str);
            }
        }
        vecs.push_back(vec);
    }
    drawLine('-', 30);
    cout.setf(ios_base::left, ios_base::adjustfield);
    for (unsigned j = 0; j < i; j++) {
        cout << setw(30) << types[by[j]];
    }
    cout << "数量" << endl;
    map<string, int> analyze; //存储要分析的数据
    showCountData(vecs, 0, value, by, analyze);
    drawLine('-', 30);
    if (!analyze.empty()) {
        analyzeData(analyze);
        drawLine('-', 30);
    }
}

/**
* 展示统计数据
* @param vecs 所有的类型的vector容器
* @param i 下标
* @param value json容器
* @param by 条件
* @param analyze 分析数据,回调
*/
void Student::showCountData(const vector<vector<string>>& vecs,
                            const unsigned i,
                            const Json::Value& value,
                            int by[],
                            map<string, int>& analyze) const {
    if (i < vecs.size()) {
        for (unsigned j = 0; j < vecs[i].size(); j++) {
            const Json::Value&& value1 = DbHelper::findAll(value, keys[by[i]], vecs[i][j]);
            if (!value1.isNull()) {
                showCountData(vecs, i + 1, value1, by, analyze); //递归查询符合条件的值
            }
        }
    } else {
        //递归完毕，开始展示数据
        stringstream s;
        for (unsigned j = 0; j < i; j++) {
            cout << setw(30) << value[0][keys[by[j]]].asString();
            if (j > 0)s << "，";
            s << types[by[j]] << "为" << value[0][keys[by[j]]].asString(); //构造分析文本
        }
        cout << value.size() << endl;
        analyze[s.str()] = value.size(); //保存数量
    }
}

/**
 * 数据分析
 * @param analyze 要分析的数据 
 */
void Student::analyzeData(const map<string, int>& analyze) {
    cout << "数据分析：" << endl;
    int sum = 0;
    pair<string, int> minPair{"", 0}, maxPair{"", 0};
    for (auto& pair : analyze) {
        if (minPair.second == 0 || pair.second < minPair.second) {
            minPair = pair;
        }else if (pair.second > maxPair.second) {
            maxPair = pair;
        }
        sum += pair.second;
    }
    cout << "数量之和为" << sum << endl
        << maxPair.first << "的数量最多,数量为" << maxPair.second
        << ",占比为" << (double(maxPair.second) / sum * 100) << "%" << endl
        << minPair.first << "的数量最少,数量为" << minPair.second
        << ",占比为" << (double(minPair.second) / sum * 100) << "%" << endl;
}

/**
* 校验学号
* @param id 学号
* @return 学号
*/
string Student::checkId(const string& id) {
    if (!isInt(id)) {
        throw CheckException("学号必须为数字!");
    }
    if (id.size() != 9) {
        throw CheckException("学号长度必须为9位!");
    }
    if (dbHelper.findById(id) >= 0) {
        throw CheckException("该学号已经被添加过!");
    }
    static DbHelper dbHelper2("data/college.json");
    const string college = id.substr(0, 2);
    const int index = dbHelper2.findById(college);
    if (index < 0) {
        throw CheckException("输入的学号的学院码有误!");
    }
    Json::Value&& value = dbHelper2.get(index);
    const int year = stoi(id.substr(2, 2)) + 2000;
    const int now = getTime()->tm_year + 1900;
    if (year > now) {
        throw CheckException("学号中的入学年份有误!");
    }
    if (getTime()->tm_year + 1900 != year) {
        cout << "学号中的入学年份与当前年份不一致!" << endl; //只发出警告
    }
    const string major = id.substr(4, 2);
    const int index2 = DbHelper::findById(value["majors"], major);
    if (index2 < 0) {
        throw CheckException("输入的学号的专业码有误!");
    }
    //int cls = stoi(id.substr(6, 1));
    //因为在整理数据的过程中发现这一位(第7位)并不只是表示班级,有很多学院用这一位来区分专业
    //所以检测班级非常不便,故注释掉
    this->id = id;
    collegeId = college;
    majorId = major;
    inYear = year;
    return id;
}

/**
* 校验性别
* @param sex 性别
* @return 男/女
*/
string Student::checkSex(const string& sex) {
    if (sex == "1") {
        this->sex = 1;
        return "男";
    }
    if (sex == "2") {
        this->sex = 0;
        return "女";
    }
    throw CheckException("性别只能是男或女!");
}

/**
* 校验出生日期
* @param birthDate 出生日期
* @return 处理后的出生日期
*/
string Student::checkBirthDate(const string& birthDate) {
    int year, month, day;
    char ch;
    stringstream in(birthDate);
    in >> year >> ch >> month >> ch >> day;
    if (!checkDate(year, month, day)) {
        throw CheckException("出生日期不合法!");
    }
    const int years = getTime()->tm_year + 1900 - year;
    if (years > 100 || years < 10) {
        throw CheckException("入学年龄必须在10-100之间");
    }
    stringstream out;
    //把日期格式化一下方便检验身份证
    out << setfill('0') << setw(4) << year
        << setfill('0') << setw(2) << month
        << setfill('0') << setw(2) << day;
    birthDateFormat = out.str();
    stringstream out2;
    //日期补零,方便之后的排序操作
    out2 << setfill('0') << setw(4) << year << '.'
        << setfill('0') << setw(2) << month << '.'
        << setfill('0') << setw(2) << day;
    return out2.str();
}

/**
* 校验身份证号码
* @param personId 身份证号码
* @return 身份证号码
*/
string Student::checkPersonId(const string& personId) const {
    if (!isChinese && !isInt(personId))return ""; //不是中国人可能没身份证
    if (!isInt(personId)) {
        throw CheckException("身份证号码必须为数字!");
    }
    if (personId.size() != 18) {
        throw CheckException("身份证号码必须为18位!");
    }
    if (dbHelper.find("personId", personId) >= 0) {
        throw CheckException("该身份证已经被添加过!");
    }
    const string locate = personId.substr(0, 6);
    static DbHelper dbHelper1("data/locate.json");
    if (dbHelper1[locate].isNull()) {
        throw CheckException("行政区划码错误!");
    }
    const string birthDate = personId.substr(6, 8);
    if (birthDateFormat != birthDate) {
        throw CheckException("身份证上的出生日期与之前输入的出生日期不一致!");
    }
    if (stoi(personId.substr(16, 1)) % 2 != sex) {
        throw CheckException("身份证上的性别与之前输入的性别不一致!");
    }
    if (personId.at(17) != getPersonId18(personId)) {
        throw CheckException("身份证校验码错误!");
    }
    return personId;
}

/**
* 校验姓名
* @param name 姓名
* @return 姓名
*/
string Student::checkName(const string& name) const {
    if (isChinese) {
        if (name.size() < 4 || name.size() > 40 || !isAllChinese(name)) {
            throw CheckException("姓名必须为二到二十个汉字!");
        }
    } else {
        if (name.size() > 40 || name.empty()) {
            throw CheckException("姓名必须小于40个字母且不能为空!");
        }
    }
    return name;
}

/**
* 校验年级
* @param grade 年级
* @return 年级
*/
string Student::checkGrade(const string& grade) const {
    if (!isInt(grade)) {
        throw CheckException("年级必须为数字!");
    }
    if (grade < to_string(inYear)) {
        throw CheckException("输入的年级必须大于等于入学年份!");
    }
    if (grade != to_string(inYear)) {
        cout << "输入的年级与学号上的年级不一致!" << endl; //只是发出警告
    }
    return grade;
}

/**
* 校验入学时间
* @param inDate 入学时间
* @return 处理后的入学日期
*/
string Student::checkInDate(const string& inDate) const {
    int year, month, day;
    stringstream s(inDate);
    char ch;
    s >> year >> ch >> month >> ch >> day;
    if (!checkDate(year, month, day)) {
        throw CheckException("入学日期不合法!");
    }
    if (month < 8 || month > 10) {
        throw CheckException("入学月份必须在8月-10月之间");
    }
    if (year != inYear) {
        throw CheckException("入学年份必须与学号的入学年份一致!");
    }
    stringstream out;
    //日期补零,方便之后的排序操作
    out << setfill('0') << setw(4) << year << '.'
        << setfill('0') << setw(2) << month << '.'
        << setfill('0') << setw(2) << day;
    return out.str();
}

/**
* 校验班级
* @param cls 班级
* @return 班级信息
*/
string Student::checkClass(const string& cls) const {
	if (!isInt(cls)) {
        throw CheckException("班级必须为数字!");
    }
    const int c = stoi(cls);
    if (c < 1 || c > 10) {
        throw CheckException("班级号必须在1-10之间!");
    }
    return to_string(c);
}

/**
* 校验辅导员
* @param instructor 辅导员名字
* @return 辅导员
*/
string Student::checkInstructor(const string& instructor) const {
    static DbHelper dbHelper("data/instructor.json");
    const string key = id.substr(0, 7);
    Json::Value&& value = dbHelper[key];
    if (value.isNull()) {
        dbHelper.add(key, instructor);
    } else {
        if (value.asString() != instructor) {
            throw CheckException("输入的辅导员信息与存储的该班级辅导员信息不一致!");
        }
    }
    return instructor;
}
