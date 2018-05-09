/**
* ���ݰ�����ʵ���ļ�<br/>
* ʵ���˶�json������ɾ�Ĳ����<br/>
* Copyright (c) 2018 Xily.All Rights Reserved.
* @author ���꽡 221701423 572089608@qq.com
* @date 2018.4.22
*/

#include "function.h"
#include "dbhelper.h"
#include <fstream>
using namespace std;

/**
 * ���캯��
 * @param fileName �ļ���
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
 * ����id�ֶβ�������
 * @param id id�ֶε�ֵ
 * @return ���ҵ��ĵ�һ�����ݵ��±�,���Ҳ�������-1
 */
int DbHelper::findById(const int id) const {
    return findById(value, id);
}

/**
* ����id�ֶβ�������
* @param id id�ֶε�ֵ
* @return ���ҵ��ĵ�һ�����ݵ��±�,���Ҳ�������-1
*/
int DbHelper::findById(const string& id) const {
    return findById(value, id);
}

/**
* ����id�ֶβ�������
* @param value json���ݼ���
* @param id id�ֶε�ֵ
* @return ���ҵ��ĵ�һ�����ݵ��±�,���Ҳ�������-1
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
* ����id�ֶβ�������
* @param value json���ݼ���
* @param id id�ֶε�ֵ
* @return ���ҵ��ĵ�һ�����ݵ��±�,���Ҳ�������-1
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
 * ����ָ���ֶβ�������
 * @param key �ֶ���
 * @param val ֵ
 * @return ���ҵ��ĵ�һ�����ݵ��±�,���Ҳ�������-1
 */
int DbHelper::find(const string& key, const int val) const {
    return find(value, key, val);
}

/**
* ����ָ���ֶβ�������
* @param key �ֶ���
* @param val ֵ
* @return ���ҵ��ĵ�һ�����ݵ��±�,���Ҳ�������-1
*/
int DbHelper::find(const string& key, const string& val) const {
    return find(value, key, val);
}

/**
* ����ָ���ֶβ�������
* @param value json���ݼ���
* @param key �ֶ���
* @param val ֵ
* @return ���ҵ��ĵ�һ�����ݵ��±�,���Ҳ�������-1
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
* ����ָ���ֶβ�������
* @param value json���ݼ���
* @param key �ֶ���
* @param val ֵ
* @return ���ҵ��ĵ�һ�����ݵ��±�,���Ҳ�������-1
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
* ����ָ���ֶβ�������
* @param key �ֶ���
* @param val ֵ
* @return ���ҵ���json���ݼ���
*/
Json::Value DbHelper::findAll(const string& key, const int val) const {
    return findAll(value, key, val);
}

/**
* ����ָ���ֶβ�������
* @param key �ֶ���
* @param val ֵ
* @return ���ҵ���json���ݼ���
*/
Json::Value DbHelper::findAll(const string& key, const string& val) const {
    return findAll(value, key, val);
}

/**
 * ����һ���ֶβ�������
 * @param map map����,key=>value
 * @return ���ҵ���json���ݼ���
 */
Json::Value DbHelper::findAll(const map<string, string>& map) const {
    return findAll(value, map);
}

/**
 * ����һ���ֶβ�������
 * @param value json���ݼ���
 * @param map map����,key=>value
 * @return ���ҵ���json���ݼ���
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
 * ����ָ���ֶβ�������
 * @param value json���ݼ���
 * @param key �ֶ���
 * @param val ֵ
 * @return ���ҵ���json���ݼ���
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
* ����ָ���ֶβ�������
* @param value json���ݼ���
* @param key �ֶ���
* @param val ֵ
* @return ���ҵ���json���ݼ���
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
 * ���һ������
 * @param val json���ݼ���
 * @return ״̬
 */
bool DbHelper::add(const Json::Value& val) {
    value.append(val);
    return apply();
}

/**
 * ���һ���ֶ�
 * @param key �ֶ���
 * @param val ֵ
 * @return ״̬
 */
bool DbHelper::add(const string& key,const Json::Value& val) {
    value[key] = val;
    return apply();
}

/**
 * ɾ��һ������
 * @param index �����±�
 * @return ״̬
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
 * ����һ������
 * @param index �����±� 
 * @param val json���ݼ���
 * @return ״̬
 */
bool DbHelper::update(const int index, const Json::Value& val) {
    value[index] = val;
    return apply();
}

/**
 * ������������
 * @param index1 ��һ�������±�
 * @param index2 �ڶ��������±�
 * @return ״̬
 */
bool DbHelper::swap(const int index1, const int index2) {
    value[index1].swap(value[index2]);
    return apply();
}

/**
 * ��ȡ����json����
 * @return json����
 */
Json::Value DbHelper::getValue() const {
    return value;
}

/**
* ��ȡ�±��json���ݼ���
* @param index �±�
* @return json���ݼ���
*/
Json::Value DbHelper::get(const int index) const {
    return value[index];
}

/**
* ��ȡ�ֶε�json���ݼ���
* @param key �ֶ���
* @return
*/
Json::Value DbHelper::get(const string& key) const {
    return value[key];
}

/**
 * ��json���ݼ�������Ϊ��һ������
 * @param val json���ݼ���
 * @return ״̬
 */
bool DbHelper::setValue(Json::Value& val) {
    value = val;
    return apply();
}

/**
 * ��ȡ�±��json���ݼ���
 * @param index �±�
 * @return json���ݼ���
 */
Json::Value DbHelper::operator[](const int index) const {
    return get(index);
}

/**
 * ��ȡ�ֶε�json���ݼ���
 * @param key �ֶ���
 * @return 
 */
Json::Value DbHelper::operator[](const string& key) const {
    return get(key);
}

/**
 * ��json���ݼ���д���ļ�
 * @return ״̬
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
