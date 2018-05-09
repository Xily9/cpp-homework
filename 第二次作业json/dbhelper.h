#pragma once

/**
* 数据帮助类头文件<br/>
* 实现了对json集合增删改查操作<br/>
* Copyright (c) 2018 Xily.All Rights Reserved.
* @author 曾宏健 221701423 572089608@qq.com
* @date 2018.4.22
*/

#include "json.h"
#include <string>

using std::string;
using std::map;

class DbHelper {
public:
    explicit DbHelper(const string& fileName);
    int findById(int id) const;
    int findById(const string& id) const;
    static int findById(const Json::Value& value,int id);
    static int findById(const Json::Value& value,const string& id);
    int find(const string& key, int val) const;
    int find(const string& key, const string& val) const;
    static int find(const Json::Value& value,const string& key, int val);
    static int find(const Json::Value& value,const string& key, const string& val);
    Json::Value findAll(const string& key, int val) const;
    Json::Value findAll(const string& key, const string& val) const;
    Json::Value findAll(const map<string, string>& map) const;
    static Json::Value findAll(const Json::Value& value, const map<string, string>& map);
    static Json::Value findAll(const Json::Value& value, const string& key, int val);
    static Json::Value findAll(const Json::Value& value, const string& key, const string& val);
    bool add(const Json::Value& val);
    bool add(const string& key, const Json::Value& val);
    bool del(int index);
    bool update(int index, const Json::Value& val);
    bool swap(int index1, int index2);
    Json::Value getValue() const;
    bool setValue(Json::Value& val);
    Json::Value get(int index) const;;
    Json::Value get(const string& key) const;
    Json::Value operator[](int index) const;
    Json::Value operator[](const string& key) const;
    bool apply() const;
private:
    string fileName;
    Json::Value value;
};
