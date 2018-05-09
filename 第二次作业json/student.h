#pragma once

/**
* 学生类头文件<br/>
* 对学生进行增删改查等操作<br/>
* Copyright (c) 2018 Xily.All Rights Reserved.
* @author 曾宏健 221701423 572089608@qq.com
* @date 2018.5.5
*/

#include "json.h"
#include "dbhelper.h"
#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;
using std::cin;

class Student {
public:
    explicit Student(DbHelper&& dbHelper): dbHelper(dbHelper) {
    }

    void addData();
    void showData(Json::Value value = Json::Value());
    void findData();
    void sortData();
    void countData();
private:
    string id;                  //学号
    string collegeId;           //学号中的学院编码
    string majorId;             //学号中的专业编码
    int inYear = 0;             //学号中的入学年份
    bool isChinese = false;     //是否是中国人
    string birthDateFormat;     //八位格式化后的出生日期
    int sex = 0;                //性别
    int collegeIndex = 0;       //记录学院的数据下标用于判断专业
    bool isUpdate = false;      //记录有没有发生数据更新事件
    DbHelper& dbHelper;         //数据帮助类
    static const int size = 19; //字段总数
    const char* types[size] = {
        "学号", "姓名", "性别", "国别", "出生年月", "民族", "婚姻状况",
        "政治面貌", "身份证号", "学生类别", "入学年月", "入学方式", "学院", "专业", "学制",
        "培养层次", "年级", "班级号", "辅导员"
    }; //字段简介
    const char* keys[size] = {
        "id", "name", "sex", "country", "birthDate", "nation", "marry",
        "politics", "personId", "studentType", "inDate", "inType", "college", "major",
        "length", "level", "grade", "class", "instructor"
    }; //字段名
    Json::Value inputData();
    static string inputCountry();
    static string inputNation();
    static string inputPolitics();
    static string inputMarry();
    static string inputStudentType();
    static string inputInType();
    static string inputLevel();
    string inputCollege();
    string inputMajor() const;
    template <typename T>
    static string getInput(const string& type, const string& message, T check, bool useDefault = false,
        const string& defaultValue = "");
    void showLine(const string& id);
    void deleteData(const string& major, const string& grade);
    void deleteByIndex(int index);
    void editByIndex(int index);
    void showCountData(const vector<vector<string>>& vecs, unsigned i, const Json::Value& value, int by[]) const;
    string checkId(const string& id);
    string checkBirthDate(const string& birthDate);
    string checkSex(const string& sex);
    string checkPersonId(const string& personId) const;
    string checkName(const string& name) const;
    string checkGrade(const string& grade) const;
    string checkInDate(const string& inDate) const;
    string checkClass(const string& cls) const;
    string checkInstructor(const string& instructor) const;
    //检验失败异常
    class CheckException :public std::exception {
    public:
        explicit CheckException(const string& s) :exception(std::logic_error(s.c_str())) {}
    };
};

/**
* 从键盘上获取字符串并做校验
* @tparam T 函数对象
* @param type 值文字
* @param message 提示信息
* @param check 回调函数
* @param useDefault 是否有默认值,默认没有
* @param defaultValue 默认值,默认空
* @return 获取到并检验通过的字符串
*/
template <typename T>
string Student::getInput(const string& type, const string& message, T check,const bool useDefault,
    const string& defaultValue) {
    string str;
    while (true) {
        cout << "请输入" << type;
        if (useDefault) {
            cout << "(默认为" << defaultValue << ")";
        }
        cout << std::endl;
        if (!message.empty()) {
            cout << message << std::endl;
        }
        if (useDefault && cin.peek() == '\n') {
            str = defaultValue;
        } else {
            cin >> str;
        }
        cin.ignore(1024, '\n');
        try {
            return check(str);
        } catch (CheckException& e) {
            cout << e.what() << std::endl;
        }
    }
}