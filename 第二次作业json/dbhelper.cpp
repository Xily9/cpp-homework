/**
* 数据帮助类实现文件<br/>
* 实现了对json集合增删改查操作<br/>
* Copyright (c) 2018 Xily.All Rights Reserved.
* @author 曾宏健 221701423 572089608@qq.com
* @date 2018.4.22
*/

#include "function.h"
#include "dbhelper.h"
#include <fstream>
using namespace std;

/**
 * 构造函数
 * @param fileName 文件名
 */
DbHelper::DbHelper(const string& fileName) {
    ifstream ifstream;
    this->fileName = fileName;
    ifstream.open(fileName);
    if (ifstream.is_open()) {
        ifstream >> value;
        ifstream.close();
    }
}

/**
 * 根据id字段查找数据
 * @param id id字段的值
 * @return 查找到的第一条数据的下标,查找不到返回-1
 */
int DbHelper::findById(const int id) const {
    return findById(value, id);
}

/**
* 根据id字段查找数据
* @param id id字段的值
* @return 查找到的第一条数据的下标,查找不到返回-1
*/
int DbHelper::findById(const string& id) const {
    return findById(value, id);
}

/**
* 根据id字段查找数据
* @param value json数据集合
* @param id id字段的值
* @return 查找到的第一条数据的下标,查找不到返回-1
*/
int DbHelper::findById(const Json::Value& value, int id) {
    for (unsigned int i = 0; i < value.size(); i++) {
        if (value[i]["id"].asInt() == id) {
            return i;
        }
    }
    return -1;
}

/**
* 根据id字段查找数据
* @param value json数据集合
* @param id id字段的值
* @return 查找到的第一条数据的下标,查找不到返回-1
*/
int DbHelper::findById(const Json::Value& value, const string& id) {
    for (unsigned int i = 0; i < value.size(); i++) {
        if (value[i]["id"].asString() == id) {
            return i;
        }
    }
    return -1;
}

/**
 * 根据指定字段查找数据
 * @param key 字段名
 * @param val 值
 * @return 查找到的第一条数据的下标,查找不到返回-1
 */
int DbHelper::find(const string& key, const int val) const {
    return find(value, key, val);
}

/**
* 根据指定字段查找数据
* @param key 字段名
* @param val 值
* @return 查找到的第一条数据的下标,查找不到返回-1
*/
int DbHelper::find(const string& key, const string& val) const {
    return find(value, key, val);
}

/**
* 根据指定字段查找数据
* @param value json数据集合
* @param key 字段名
* @param val 值
* @return 查找到的第一条数据的下标,查找不到返回-1
*/
int DbHelper::find(const Json::Value& value, const string& key, int val) {
    for (unsigned int i = 0; i < value.size(); i++) {
        if (value[i][key].asInt() == val) {
            return i;
        }
    }
    return -1;
}

/**
* 根据指定字段查找数据
* @param value json数据集合
* @param key 字段名
* @param val 值
* @return 查找到的第一条数据的下标,查找不到返回-1
*/
int DbHelper::find(const Json::Value& value, const string& key, const string& val) {
    for (unsigned int i = 0; i < value.size(); i++) {
        if (value[i][key].asString() == val) {
            return i;
        }
    }
    return -1;
}

/**
* 根据指定字段查找数据
* @param key 字段名
* @param val 值
* @return 查找到的json数据集合
*/
Json::Value DbHelper::findAll(const string& key, const int val) const {
    return findAll(value, key, val);
}

/**
* 根据指定字段查找数据
* @param key 字段名
* @param val 值
* @return 查找到的json数据集合
*/
Json::Value DbHelper::findAll(const string& key, const string& val) const {
    return findAll(value, key, val);
}

/**
 * 根据一组字段查找数据
 * @param map map容器,key=>value
 * @return 查找到的json数据集合
 */
Json::Value DbHelper::findAll(const map<string, string>& map) const {
    return findAll(value, map);
}

/**
 * 根据一组字段查找数据
 * @param value json数据集合
 * @param map map容器,key=>value
 * @return 查找到的json数据集合
 */
Json::Value DbHelper::findAll(const Json::Value& value, const map<string, string>& map) {
    Json::Value values;
    for (auto& i : value) {
        bool check = true;
        for (auto& j : map) {
            if (int(i[j.first].asString().find(j.second)) == -1) {
                check = false;
                break;
            }
        }
        if (check) {
            values.append(i);
        }
    }
    return values;
}

/**
 * 根据指定字段查找数据
 * @param value json数据集合
 * @param key 字段名
 * @param val 值
 * @return 查找到的json数据集合
 */
Json::Value DbHelper::findAll(const Json::Value& value, const string& key, const int val) {
    Json::Value values;
    for (auto& i : value) {
        if (findInInt(i[key].asInt(), val) != -1) {
            values.append(i);
        }
    }
    return values;
}

/**
* 根据指定字段查找数据
* @param value json数据集合
* @param key 字段名
* @param val 值
* @return 查找到的json数据集合
*/
Json::Value DbHelper::findAll(const Json::Value& value, const string& key, const string& val) {
    Json::Value values;
    for (auto& i : value) {
        if (int(i[key].asString().find(val)) != -1) {
            values.append(i);
        }
    }
    return values;
}

/**
 * 添加一条数据
 * @param val json数据集合
 * @return 状态
 */
bool DbHelper::add(const Json::Value& val) {
    value.append(val);
    return apply();
}

/**
 * 添加一个字段
 * @param key 字段名
 * @param val 值
 * @return 状态
 */
bool DbHelper::add(const string& key,const Json::Value& val) {
    value[key] = val;
    return apply();
}

/**
 * 删除一条数据
 * @param index 数据下标
 * @return 状态
 */
bool DbHelper::del(const int index) {
    Json::Value removed;
    bool status = value.removeIndex(index, &removed);
    if (status) {
        status &= apply();
    }
    return status;
}

/**
 * 更新一条数据
 * @param index 数据下标 
 * @param val json数据集合
 * @return 状态
 */
bool DbHelper::update(const int index, const Json::Value& val) {
    value[index] = val;
    return apply();
}

/**
 * 交换两个数据
 * @param index1 第一个数据下标
 * @param index2 第二个数据下标
 * @return 状态
 */
bool DbHelper::swap(const int index1, const int index2) {
    value[index1].swap(value[index2]);
    return apply();
}

/**
 * 获取整个json集合
 * @return json集合
 */
Json::Value DbHelper::getValue() const {
    return value;
}

/**
* 获取下标的json数据集合
* @param index 下标
* @return json数据集合
*/
Json::Value DbHelper::get(const int index) const {
    return value[index];
}

/**
* 获取字段的json数据集合
* @param key 字段名
* @return
*/
Json::Value DbHelper::get(const string& key) const {
    return value[key];
}

/**
 * 将json数据集合设置为另一个集合
 * @param val json数据集合
 * @return 状态
 */
bool DbHelper::setValue(Json::Value& val) {
    value = val;
    return apply();
}

/**
 * 获取下标的json数据集合
 * @param index 下标
 * @return json数据集合
 */
Json::Value DbHelper::operator[](const int index) const {
    return get(index);
}

/**
 * 获取字段的json数据集合
 * @param key 字段名
 * @return 
 */
Json::Value DbHelper::operator[](const string& key) const {
    return get(key);
}

/**
 * 将json数据集合写入文件
 * @return 状态
 */
bool DbHelper::apply() const {
    ofstream ofstream;
    ofstream.open(fileName);
    if (ofstream.is_open()) {
        ofstream << value;
        ofstream.close();
        return true;
    }
    return false;
}
