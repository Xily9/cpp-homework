#pragma once

#include "dbhelper.h"

void showMainMenu();
void showTime();
void addData(DbHelper& dbHelper);
File& inputData(DbHelper& dbHelper, File& value, const bool isEdit = false);
template <typename T>
string getInput(const string& type, const string& message, T check, bool useDefault = false, const string& defaultValue = "");
string inputCountry();
string inputNation();
string inputPolitics();
string inputMarry();
string inputStudentType();
string inputInType();
string inputCollege(int& index, int collegeId);
string inputMajor(int index);
string inputLevel();
string inputList(const DbHelper& dbHelper, const string& type, unsigned lineLength = 5);
void showData(DbHelper& dbHelper, File value = File());
void showLine(DbHelper& dbHelper, const string& id);
void findData(DbHelper& dbHelper);
void deleteData(DbHelper& dbHelper, const string& major, const string& grade);
void deleteByIndex(DbHelper& dbHelper, int index);
void editByIndex(DbHelper& dbHelper, int index);
void sortData(DbHelper& dbHelper);
void countData(const DbHelper& dbHelper);
void showCountData(const vector<vector<string>>& vecs, unsigned i, const File& value, int by[]);
void showListMenu(const string list[], unsigned size);
void showListMenu(const File& value, const unsigned lineLength);
string checkId(const DbHelper& dbHelper, const string& id, int& collegeId, int& inYear);
string checkBirthDate(const string& birthDate, string& birthDateFormat);
string checkSex(const string& sex);
string checkPersonId(const DbHelper& dbHelper, const string& personId, int sex, const string& birthDate);
string checkName(const string& name, bool isChinese);
string checkGrade(const string& grade, int inYear);
string checkInDate(const string& inDate, const int inYear);
string checkClass(const string& cls);
string checkInstructor(const string& instructor, const string& id);