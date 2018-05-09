/**
 * db帮助类实现文件
 * 实现了对json集合增删改查操作
 * @author Xily 221701423
 * @date 2018.4.22
 */
#include "utils.h"
#include "dbhelper.h"
#include <fstream>
#include <cmath>
#include <iostream>
using namespace std;

/**
 * 构造函数
 * @param fileName 文件名
 */
DbHelper::DbHelper(const string& fileName) :fileName(fileName),value(File::reader(fileName)){}

/**
 * 根据id字段查找数据
 * @param id id字段的值
 * @return 查找到的第一条数据的下标,查找不到返回-1
 */
int DbHelper::findById(const int id) const {
    for (unsigned int i = 0; i < value.size(); i++) {
        if (value[i][0].asInt() == id) {
            return i;
        }
    }
    return -1;
}

/**
* 根据id字段查找数据
* @param id id字段的值
* @return 查找到的第一条数据的下标,查找不到返回-1
*/
int DbHelper::findById(const string& id) const {
    for (unsigned int i = 0; i < value.size(); i++) {
        if (value[i][0].asString() == id) {
            return i;
        }
    }
    return -1;
}
/**
* 根据id字段查找数据
* @param id id字段的值
* @return 查找到的第一条数据的下标,查找不到返回-1
*/
int DbHelper::findById(double id) const {
    for (unsigned int i = 0; i < value.size(); i++) {
        if (fabs(value[i][0].asDouble() - id) < 1e-7) {
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
    for (unsigned int i = 0; i < value.size(); i++) {
        if (value[i][key].asInt() == val) {
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
int DbHelper::find(const string& key, const string& val) const {
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
* @return 查找到的第一条数据的下标,查找不到返回-1
*/
int DbHelper::find(const string& key, const double val) const {
    for (unsigned int i = 0; i < value.size(); i++) {
        if (fabs(value[i][key].asDouble() - val) < 1e-7) {
            return i;
        }
    }
    return -1;
}

int DbHelper::find(const int key, int val) const {
    for (unsigned int i = 0; i < value.size(); i++) {
        if (value[i][key].asInt() == val) {
            return i;
        }
    }
    return -1;
}

int DbHelper::find(const int key, const string& val) const {
    for (unsigned int i = 0; i < value.size(); i++) {
        if (value[i][key].asString() == val) {
            return i;
        }
    }
    return -1;
}

int DbHelper::find(const int key, double val) const {
    for (unsigned int i = 0; i < value.size(); i++) {
        if (value[i][key].asInt() == val) {
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
File DbHelper::findAll(const string& key, const int val) const {
    return findAll(value, key, val);
}

/**
* 根据指定字段查找数据
* @param key 字段名
* @param val 值
* @return 查找到的json数据集合
*/
File DbHelper::findAll(const string& key, const string& val) const {
    return findAll(value, key, val);
}

/**
* 根据指定字段查找数据
* @param key 字段名
* @param val 值
* @return 查找到的json数据集合
*/
File DbHelper::findAll(const string& key, const double val) const {
    return findAll(value, key, val);
}

File DbHelper::findAll(const int key, int val) const {
    return findAll(value, key, val);
}

File DbHelper::findAll(const int key, const string& val) const {
    return findAll(value, key, val);
}

File DbHelper::findAll(const int key, double val) const {
    return findAll(value, key, val);
}

/**
 * 根据指定字段查找数据
 * @param value json数据集合
 * @param key 字段名
 * @param val 值
 * @return 查找到的json数据集合
 */
File DbHelper::findAll(const File& value, const string& key, const int val) {
    File values;
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
File DbHelper::findAll(const File& value, const string& key, const string& val) {
    File values;
    for (auto& i : value) {
        if (int(i[key].asString().find(val)) !=-1) {
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
File DbHelper::findAll(const File& value, const string& key, const double val) {
    File values;
    for (auto& i : value) {
        if (fabs(i[key].asDouble() - val) < 1e-7) {
            values.append(i);
        }
    }
    return values;
}

File DbHelper::findAll(const File& value, const int key, int val) {
    File values;
    for (auto& i : value) {
        if (findInInt(i[key].asInt(), val) != -1) {
            values.append(i);
        }
    }
    return values;
}

File DbHelper::findAll(const File& value, const int key, const string& val) {
    File values;
    for (auto& i : value) {
        if (int(i[key].asString().find(val)) != -1) {
            values.append(i);
        }
    }
    return values;
}

File DbHelper::findAll(const File& value, const int key, double val) {
    File values;
    for (auto& i : value) {
        if (fabs(i[key].asDouble() - val) < 1e-7) {
            values.append(i);
        }
    }
    cout << value.asString();
    return values;
}

/**
 * 添加一条数据
 * @param val json数据集合
 * @return 状态
 */
bool DbHelper::add(const File& val) {
    value.append(val);
    return apply();
}

/**
 * 添加一个字段
 * @param key 字段名
 * @param val 值
 * @return 状态
 */
bool DbHelper::add(const string& key, const File& val) {
    File temp;
    temp[0] = key;
    temp[1] = val;
    add(temp);
    return apply();
}

/**
 * 删除一条数据
 * @param index 数据下标
 * @return 状态
 */
bool DbHelper::del(const int index) {
    value.removeIndex(index);
    return apply();
}

/**
 * 更新一条数据
 * @param index 数据下标 
 * @param val json数据集合
 * @return 状态
 */
bool DbHelper::update(const int index, const File& val) {
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
    const File temp = value[index1];
    value[index1] = value[index2];
    value[index2] = temp;
    return apply();
}

/**
 * 将json数据集合设置为另一个集合
 * @param val json数据集合
 * @return 状态
 */
bool DbHelper::setValue(const File& val){
    value = val;
    return apply();
}

/**
 * 获取下标的json数据集合
 * @param index 下标
 * @return json数据集合
 */
File DbHelper::operator[](const int index) const {
    return value[index];
}

/**
 * 获取字段的json数据集合
 * @param key 字段名
 * @return 
 */
File DbHelper::operator[](const string& key) const {
    return value[key];
}

/**
 * 将json数据集合写入文件
 * @return 状态
 */
bool DbHelper::apply(){
    return File::writer(fileName, value);
}
