/**
 * db������ʵ���ļ�
 * ʵ���˶�json������ɾ�Ĳ����
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
 * ���캯��
 * @param fileName �ļ���
 */
DbHelper::DbHelper(const string& fileName) :fileName(fileName),value(File::reader(fileName)){}

/**
 * ����id�ֶβ�������
 * @param id id�ֶε�ֵ
 * @return ���ҵ��ĵ�һ�����ݵ��±�,���Ҳ�������-1
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
* ����id�ֶβ�������
* @param id id�ֶε�ֵ
* @return ���ҵ��ĵ�һ�����ݵ��±�,���Ҳ�������-1
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
* ����id�ֶβ�������
* @param id id�ֶε�ֵ
* @return ���ҵ��ĵ�һ�����ݵ��±�,���Ҳ�������-1
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
 * ����ָ���ֶβ�������
 * @param key �ֶ���
 * @param val ֵ
 * @return ���ҵ��ĵ�һ�����ݵ��±�,���Ҳ�������-1
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
* ����ָ���ֶβ�������
* @param key �ֶ���
* @param val ֵ
* @return ���ҵ��ĵ�һ�����ݵ��±�,���Ҳ�������-1
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
* ����ָ���ֶβ�������
* @param key �ֶ���
* @param val ֵ
* @return ���ҵ��ĵ�һ�����ݵ��±�,���Ҳ�������-1
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
* ����ָ���ֶβ�������
* @param key �ֶ���
* @param val ֵ
* @return ���ҵ���json���ݼ���
*/
File DbHelper::findAll(const string& key, const int val) const {
    return findAll(value, key, val);
}

/**
* ����ָ���ֶβ�������
* @param key �ֶ���
* @param val ֵ
* @return ���ҵ���json���ݼ���
*/
File DbHelper::findAll(const string& key, const string& val) const {
    return findAll(value, key, val);
}

/**
* ����ָ���ֶβ�������
* @param key �ֶ���
* @param val ֵ
* @return ���ҵ���json���ݼ���
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
 * ����ָ���ֶβ�������
 * @param value json���ݼ���
 * @param key �ֶ���
 * @param val ֵ
 * @return ���ҵ���json���ݼ���
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
* ����ָ���ֶβ�������
* @param value json���ݼ���
* @param key �ֶ���
* @param val ֵ
* @return ���ҵ���json���ݼ���
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
* ����ָ���ֶβ�������
* @param value json���ݼ���
* @param key �ֶ���
* @param val ֵ
* @return ���ҵ���json���ݼ���
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
 * ���һ������
 * @param val json���ݼ���
 * @return ״̬
 */
bool DbHelper::add(const File& val) {
    value.append(val);
    return apply();
}

/**
 * ���һ���ֶ�
 * @param key �ֶ���
 * @param val ֵ
 * @return ״̬
 */
bool DbHelper::add(const string& key, const File& val) {
    File temp;
    temp[0] = key;
    temp[1] = val;
    add(temp);
    return apply();
}

/**
 * ɾ��һ������
 * @param index �����±�
 * @return ״̬
 */
bool DbHelper::del(const int index) {
    value.removeIndex(index);
    return apply();
}

/**
 * ����һ������
 * @param index �����±� 
 * @param val json���ݼ���
 * @return ״̬
 */
bool DbHelper::update(const int index, const File& val) {
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
    const File temp = value[index1];
    value[index1] = value[index2];
    value[index2] = temp;
    return apply();
}

/**
 * ��json���ݼ�������Ϊ��һ������
 * @param val json���ݼ���
 * @return ״̬
 */
bool DbHelper::setValue(const File& val){
    value = val;
    return apply();
}

/**
 * ��ȡ�±��json���ݼ���
 * @param index �±�
 * @return json���ݼ���
 */
File DbHelper::operator[](const int index) const {
    return value[index];
}

/**
 * ��ȡ�ֶε�json���ݼ���
 * @param key �ֶ���
 * @return 
 */
File DbHelper::operator[](const string& key) const {
    return value[key];
}

/**
 * ��json���ݼ���д���ļ�
 * @return ״̬
 */
bool DbHelper::apply(){
    return File::writer(fileName, value);
}
