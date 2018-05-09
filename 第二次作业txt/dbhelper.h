#pragma once

/**
* db������ͷ�ļ�
* ʵ���˶��ļ���ɾ�Ĳ����
* @author Xily 221701423
* @date 2018.4.22
*/

#include <string>
#include "file.h"
using namespace std;

class DbHelper {
public:
    explicit DbHelper(const string& fileName);
    //��Ҫ��������,Ҫ��ֵ�봫����
    DbHelper(const DbHelper&) = delete;
    DbHelper& operator=(const DbHelper&) = delete;
    DbHelper(const DbHelper&&) = delete;
    DbHelper& operator=(const DbHelper&&) = delete;
    ~DbHelper() = default;
    int findById(int id) const;
    int findById(const string& id) const;
    int findById(double id) const;
    int find(const string& key, int val) const;
    int find(const string& key, const string& val) const;
    int find(const string& key, double val) const;
    int find(const int key, int val) const;
    int find(const int key, const string& val) const;
    int find(const int key, double val) const;
    File findAll(const string& key, int val) const;
    File findAll(const string& key, const string& val) const;
    File findAll(const string& key, double val) const;
    File findAll(const int key, int val) const;
    File findAll(const int key, const string& val) const;
    File findAll(const int key, double val) const;
    static File findAll(const File& value, const string& key, int val);
    static File findAll(const File& value, const string& key, const string& val);
    static File findAll(const File& value, const string& key, double val);
    static File findAll(const File& value, const int key, int val);
    static File findAll(const File& value, const int key, const string& val);
    static File findAll(const File& value, const int key, double val);
    bool add(const File& val);
    bool add(const string& key, const File& val);
    bool del(int index);
    bool update(int index, const File& val);
    bool swap(int index1, int index2);

    File getValue() const {
        return value;
    }

    bool setValue(const File& val);

    File operator[](int index) const;
    File operator[](const string& key) const;
    bool apply();
private:
    string fileName;
    File value;
};
