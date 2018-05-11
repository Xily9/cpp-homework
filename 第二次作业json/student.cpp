/**
 * ѧ����ʵ���ļ�<br/>
 * ��ѧ��������ɾ�Ĳ�Ȳ���<br/>
 * Copyright (c) 2018 Xily.All Rights Reserved.<br/>
 * @author ���꽡 221701423 572089608@qq.com
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
* ���һ��������
*/
void Student::addData() {
    system("cls");
    const Json::Value&& value = inputData();
    if (dbHelper.add(value)) {
        cout << "���һ����ѧ�����ݳɹ�!" << endl;
    } else {
        cout << "���һ����ѧ������ʧ��!" << endl;
    }
}

/**
* ¼������
* @return �����json����
*/
Json::Value Student::inputData() {
    Json::Value value;
    //ѧ��
    value["id"] = getInput(
        "ѧ��", "9λ���֣�ѧԺ���루2λ��+��ѧ��ݣ�2λ��+���ֱ��루5λ����"
        "���磺221500555��\nѧ��ΪΨһ�룬���������ظ���Ҳ������Ϊ�գ������ѧ�Ų������޸ġ�",
        [this](const string& s) { return checkId(s); });
    //�˴���lambda���ʽ��װ��֤����,�������������ʹ�����Ա����������,����ͬ��
    //����
    value["country"] = inputCountry();
    isChinese = value["country"].asString() == "�й�"; //�ж��Ƿ�Ϊ�й���
    //����
    value["name"] = getInput("����", isChinese ? "���磺�����죬2��20������" : "����Ӧ������40���ַ�",
                             [this](const string& s) { return checkName(s); });
    //�Ա�
    value["sex"] = getInput("�Ա�", "����1Ϊ�У�����2ΪŮ",
                            [this](const string& s) { return checkSex(s); });
    //��������
    value["birthDate"] = getInput("��������", "��ʽ����1998.11.4��1998/11/4��1998-11-4\n"
                                  "��ѧʱ10<=����<=100�����ڱ����ǺϷ������ڡ�",
                                  [this](const string& s) { return checkBirthDate(s); });
    //���֤��
    value["personId"] = getInput(
        "���֤����", isChinese
                     ? "18λ��ǰ17λ�������֣����һλΪ0��9��X��\n"
                     "����������6λ��+�������ڣ�8λ��+˳���루3λ��+У���루1λ�������֤�Ų����ظ�"
                     : "��Ϊ����ˣ����֤�������գ�����������ĸ���ɣ�",
        [this](const string& s) { return checkPersonId(s); });
    //����
    value["nation"] = inputNation();
    //������ò
    value["politics"] = inputPolitics();
    //����״��
    value["marry"] = inputMarry();
    //ѧ������
    value["studentType"] = inputStudentType();
    //��ѧ��ʽ
    value["inType"] = inputInType();
    //��ѧ����
    value["inDate"] = getInput("��ѧ����", "��ʽ����2017.9.14��2017/9/14��2017-9-14\n"
                               "8=<�·�<=10�����ڱ����ǺϷ������ڡ�",
                               [this](const string& s) { return checkInDate(s); });
    //ѧԺ
    value["college"] = inputCollege();
    //רҵ
    value["major"] = inputMajor();
    //�꼶
    value["grade"] = getInput("�꼶", "���磺2017���꼶��ѧ�ŵ��꼶Ӧ��Ҫһ��",
                              [this](const string& s) { return checkGrade(s); }
                              , true, to_string(inYear));
    //ѧ��
    value["length"] = getInput("ѧ��", "", [](const string& length) { return length; }, true, "4");
    //�������
    value["level"] = inputLevel();
    //�༶
    value["class"] = getInput("�༶", "��Χ��1��10",
                              [this](const string& s) { return checkClass(s); });
    //����Ա
    value["instructor"] = getInput("����Ա", "����Ա������ð༶�ĸ���Ա��Ϣһ��\n"
                                   "���û�д洢�ð༶�ĸ���Ա��Ϣ\n"
                                   "�����ζ����¼����Ǹð༶�ĵ�һ����Ϣ,����ر�֤����ĸ���Ա����ȷ��",
                                   [this](const string& s) { return checkInstructor(s); });
    return value;
}

/**
* �������
* @return ����
*/
string Student::inputCountry() {
    static const DbHelper dbHelper("data/country.json");
    return inputList(dbHelper, "����", 3);
}

/**
* ��������
* @return ����
*/
string Student::inputNation() {
    static const DbHelper dbHelper("data/nation.json");
    return inputList(dbHelper, "����");
}

/**
* ����������ò
* @return ������ò
*/
string Student::inputPolitics() {
    static const DbHelper dbHelper("data/politics.json");
    return inputList(dbHelper, "������ò");
}

/**
* �������״��
* @return ����״��
*/
string Student::inputMarry() {
    static const DbHelper dbHelper("data/marry.json");
    return inputList(dbHelper, "�������");
}

/**
* ����ѧ�����
* @return ѧ�����
*/
string Student::inputStudentType() {
    static const DbHelper dbHelper("data/student_type.json");
    return inputList(dbHelper, "ѧ�����");
}

/**
* ������ѧ��ʽ
* @return ��ѧ��ʽ
*/
string Student::inputInType() {
    static const DbHelper dbHelper("data/in_type.json");
    return inputList(dbHelper, "��ѧ��ʽ");
}

/**
* �����������
* @return �������
*/
string Student::inputLevel() {
    static const DbHelper dbHelper("data/level.json");
    return inputList(dbHelper, "�������");
}

/**
* ����ѧԺ��Ϣ
* @return ѧԺ��Ϣ
*/
string Student::inputCollege() {
    static const DbHelper dbHelper("data/college.json");
    unsigned n;
    const Json::Value value = dbHelper.getValue();
    showListMenu(value, 3, "name");
    while (true) {
        cout << "������ѧԺǰ�����ţ�";
        cin >> n;
        cin.ignore(1024, '\n');
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "��������ݲ��Ϸ�,����������!" << endl;
        } else if (n >= value.size()) {
            cout << "�������������,����������!" << endl;
        } else if (value[n]["id"].asString() != collegeId) {
            cout << "�����ѧԺ��Ϣ��֮ǰѧ�Ŷ�Ӧ��ѧԺ��Ϣ��һ��!" << endl;
        } else {
            break;
        }
    }
    collegeIndex = n;
    cout << "��ѡ�����[" << n << "] " + value[n]["name"].asString() << endl;
    return value[n]["name"].asString();
}

/**
* ����רҵ��Ϣ
* @return רҵ��Ϣ
*/
string Student::inputMajor() const {
    static DbHelper dbHelper("data/college.json");
    unsigned n;
    const Json::Value value = dbHelper[collegeIndex]["majors"];
    showListMenu(value, 4, "name");
    while (true) {
        cout << "������רҵǰ�����ţ�";
        cin >> n;
        cin.ignore(1024, '\n');
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "��������ݲ��Ϸ�,����������!" << endl;
        } else if (n >= value.size()) {
            cout << "�������������,����������!" << endl;
        } else if (value[n]["id"].asString() != majorId) {
            cout << "�����רҵ��Ϣ��֮ǰѧ�Ŷ�Ӧ��רҵ��Ϣ��һ��!" << endl;
        } else {
            break;
        }
    }
    cout << "��ѡ�����[" << n << "] " + value[n]["name"].asString() << endl;
    return value[n]["name"].asString();
}

/**
* չʾ����
* @param value json����,Ĭ��Ϊ��
*/
void Student::showData(Json::Value value) {
    bool isFind = true; //�Ƿ�Ϊ����ģʽ
    if (value.isNull()) {
        isFind = false;
        value = dbHelper.getValue();
    }
    int page = 1;
    const int pageNum = value.size() / 20 + (value.size() % 20 > 0); //ҳ��
    while (true) {
        system("cls");
        cout << "��ǰ��" << page << "ҳ������" << pageNum << "ҳ" << endl;
        drawLine('-', 40);
        cout.setf(ios_base::left, ios_base::adjustfield);
        cout << setw(10) << "���" << setw(20) << "ѧ��" << setw(20) << "����" << endl;
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
            cout << "��ѡ��������鿴ѧ����Ϣ(����ǰ�������)����һҳ(A)����һҳ(D)��������һ��(Q)" << endl;
            char key = _getch(); //�����̻�ȡ�û����µ���Ϣ
            if (isdigit(key)) {
                //������µ�������,��ô��Ϊ�û�Ҫ��ѧ����Ϣ
                cout << key; //����
                //ע:�������һ��bug,���û��޷�ɾ����һ���ַ�,�����������
                ungetc(key, stdin); //�ѵ�һ�����ַŻػ�����
                unsigned n;
                cin >> n;
                cin.ignore(1024, '\n');
                if (cin.fail()) {
                    cout << "��������ݲ��Ϸ�,����������!" << endl;
                    cin.clear();
                    cin.ignore(1024, '\n');
                } else if (n > value.size()) {
                    cout << "�������������,����������!" << endl;
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
                        cout << endl << "\aѡ�����������ѡ��......" << endl << endl;
                        break;
                }
            }
        }
        if (isUpdate) {
            //�����ݷ�������
            isUpdate = false; //�����ѵ��¼�
            if (isFind) {
                //�ǲ���ģʽ��ֱ���˳�
                break;
            }
            showData(); //���ǵĻ���ֱ�ӵݹ�ˢ������
            break;
        }
    }
}

/**
* չʾһ������
* @param id ѧ��
*/
void Student::showLine(const string& id) {
    system("cls");
    const int index = dbHelper.findById(id); //���Ҹ�ѧ�Ŷ�Ӧ���±�
    if (index < 0) {
        cout << "��ȡѧ����Ϣ����!" << endl;
    } else {
        Json::Value&& value = dbHelper.get(index); //��ȡ��ѧ����Ϣ
        drawLine('-', 30);
        for (unsigned i = 0; i < size; i++) {
            cout << types[i] << "��" << value[keys[i]].asString() << endl;
        }
        drawLine('-', 30);
        bool out = false;
        while (!out) {
            cout << "��ѡ�������ɾ����ǰ(D),ɾ�������꼶+רҵ(G),�޸�(E),�����ϼ�(Q)";
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
                    cout << endl << "\aѡ�����������ѡ��......" << endl;
                    break;
            }
        }
    }
    system("pause");
}

/**
* ��������
*/
void Student::findData() {
    system("cls");
    string key, val;
    Json::Value&& value = dbHelper.getValue();
    showListMenu(types, size);
    cout << "�����������һ����������ǰ�������Ϊ��������" << endl
        << "������ֵ֮���ÿո�������������֮���û��и���������EOF����" << endl
        << "֧��ģ��ƥ��,������17014��������221701423����170140123�Ƚ��" << endl;
    while (cin >> key) {
        cin >> val;
        value = DbHelper::findAll(value, keys[stoi(key)], val); //���ݼ����ͼ�ֵ��������
        if (value.isNull()) {
            cout << "���ҽ��Ϊ��!!" << endl;
            return;
        }
    }
    cin.clear();
    showData(value);
}

/**
* ɾ������רҵ+�꼶����
* @param major רҵ
* @param grade �꼶
*/
void Student::deleteData(const string& major, const string& grade) {
    if (getTime()->tm_year + 1896 - stoi(grade) < 10) {
        cout << "����ɾ����ҵ10�����ϵ�ѧ��!" << endl;
    } else {
        cout << "ȷ��Ҫɾ����?????" << endl
            << "ɾ�������ݽ��޷����лָ�" << endl
            << "ȷ���밴Y,ȡ���밴���������" << endl;
        if (getKey() == 'Y') {
            map<string, string> map;
            map["major"] = major;
            map["grade"] = grade;
            Json::Value&& values = dbHelper.findAll(map); //����רҵ�꼶��������������ѧ��
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
            cout << "ִ�����,��ɾ��" << i << "������!" << endl;
        }
    }
}

/**
* ɾ��һ������
* @param index
*/
void Student::deleteByIndex(const int index) {
    cout << "ȷ��Ҫɾ����?????" << endl
        << "ȷ���밴Y,ȡ���밴���������" << endl;
    if (getKey() == 'Y') {
        if (dbHelper.del(index)) {
            isUpdate = true;
            cout << "ɾ���ɹ�!" << endl;
        } else {
            cout << "ɾ��ʧ��!" << endl;
        }
    }
}

/**
* �༭һ������
* @param index �����±�
*/
void Student::editByIndex(const int index) {
    const int size = 11;
    const char* types[size] = {
        "����", "����", "����", "����״��",
        "������ò", "ѧ�����", "��ѧ����", "��ѧ��ʽ",
        "�������", "�꼶", "�༶��"
    };
    int by[size];
    Json::Value&& value = dbHelper.get(index);
    cout << "ע���������ݹ����Ե�ԭ�򣬽����ṩ�����ֶε��޸�" << endl
        << "��������޸Ĳ����б��е����ݣ���ɾ���������ݺ�����ӣ�" << endl;
    showListMenu(types, size);
    cout << "�����������һ�������ֶ�ǰ�������Ϊ�����޸ĵ��ֶ�,���֮���ÿո����" << endl;
    unsigned i = 0, n;
    while (cin.peek() != '\n') {
        cin >> n;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "��������ݲ��Ϸ�,����������!" << endl;
        } else if (n >= size) {
            cout << "�������������,����������!" << endl;
        } else {
            by[i++] = n;
        }
    }
    inYear = stoi(value["id"].asString().substr(2, 2)) + 2000; //��ѧ���
    isChinese = value["country"].asString() == "�й�";           //�Ƿ����й���
    for (unsigned j = 0; j < i; j++) {
        switch (by[j]) {
            case 0:
                //����
                value["name"] = getInput("����", isChinese ? "����Ϊ2-10������" : "����Ӧ������40���ַ�",
                                         [this](const string& s) { return checkName(s); });
                break;
            case 1:
                //����
                value["country"] = inputCountry();
                isChinese = value["country"].asString() == "�й�";
                break;
            case 2:
                //����
                value["nation"] = inputNation();
                break;
            case 3:
                //����״��
                value["marry"] = inputMarry();
                break;
            case 4:
                //������ò
                value["politics"] = inputPolitics();
                break;
            case 5:
                //ѧ������
                value["studentType"] = inputStudentType();
                break;
            case 6:
                //��ѧ����
                value["inDate"] = getInput("��ѧ����", "����2017.09.14",
                                           [this](const string& s) { return checkInDate(s); });
                break;
            case 7:
                //��ѧ��ʽ
                value["inType"] = inputInType();
                break;
            case 8:
                //�������
                value["level"] = inputLevel();
                break;
            case 9:
                //�꼶
                value["grade"] = getInput("�꼶", "���磺2017",
                                          [this](const string& s) { return checkGrade(s); });
                break;
            case 10:
                //�༶
                value["class"] = getInput("�༶", "��Χ��1��10",
                                          [this](const string& s) { return checkClass(s); });
            default:
                break;
        }
    }

    if (dbHelper.update(index, value)) {
        isUpdate = true;
        cout << "�༭�ɹ�!!" << endl;
    } else {
        cout << "�༭ʧ��!!" << endl;
    }
}

/**
* ����
*/
void Student::sortData() {
    system("cls");
    Json::Value&& value = dbHelper.getValue();
    showListMenu(types, size);
    int isDesc;
    int by[size];
    cout << "���������������ǰһ�����������Ϊ��������,���֮���ÿո����,Խ��ǰ�����ȼ�Խ��" << endl;
    int i = 0, n;
    while (cin.peek() != '\n') {
        cin >> n;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "��������ݲ��Ϸ�,����������!" << endl;
        } else if (n >= size) {
            cout << "�������������,����������!" << endl;
        } else {
            by[i++] = n;
        }
    }
    cin.ignore(1024, '\n');
    while (true) {
        cout << "�������ǽ�����?(����1Ϊ��������-1Ϊ����)" << endl;
        cin >> isDesc;
        cin.ignore(1024, '\n');
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "��������ݲ��Ϸ�,����������!" << endl;
        } else if (isDesc != 1 && isDesc != -1) {
            cout << "�������������,����������!" << endl;
        } else {
            break;
        }
    }
    cout << "����������,���Ժ�..." << endl;
    quickSort(value, 0, value.size() - 1,
              [isDesc, &by, i, this](const Json::Value& left, const Json::Value& right) {
                  int result = 0, j = 0;
                  //���������ʱ����ѭ����ֱ�����������
                  while (j < i &&
                      (result = left[keys[by[j]]].asString().compare(right[keys[by[j]]].asString()) * isDesc) == 0) {
                      j++; //�Ƶ���һ������
                  }
                  return result;
              });
    if (dbHelper.setValue(value)) {
        cout << "�������!" << endl;
    } else {
        cout << "����ʧ��!" << endl;
    }
}

/**
* ͳ��
*/
void Student::countData() {
    system("cls");
    int by[size];
    Json::Value&& value = dbHelper.getValue();
    showListMenu(types, size);
    cout << "�����������һ���������ǰ�������Ϊ���෽ʽ,����֮���ÿո����" << endl;
    unsigned i = 0, n;
    while (cin.peek() != '\n') {
        cin >> n;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "��������ݲ��Ϸ�,����������!" << endl;
        } else if (n >= size) {
            cout << "�������������,����������!" << endl;
        } else {
            by[i++] = n;
        }
    }
    cin.ignore(1024, '\n');
    vector<vector<string>> vecs; //���ڴ洢����������ÿ���������ܵ�ֵ
    //������������
    for (unsigned j = 0; j < i; j++) {
        vector<string> vec;
        //��ÿ������������һ��,����ͳ�����п��ܳ��ֵ�ֵ
        quickSort(value, 0, value.size() - 1, [&by, j, this](const Json::Value& left, const Json::Value& right) {
            return left[keys[by[j]]].asString().compare(right[keys[by[j]]].asString());
        });
        for (auto& k : value) {
            const string str = k[keys[by[j]]].asString();
            if (vec.empty() || str != vec.back()) {
                //�������Ϊ��(��ֹ����back�쳣)���ߵ�ǰֵ�������������һ��ֵ
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
    cout << "����" << endl;
    map<string, int> analyze; //�洢Ҫ����������
    showCountData(vecs, 0, value, by, analyze);
    drawLine('-', 30);
    if (!analyze.empty()) {
        analyzeData(analyze);
        drawLine('-', 30);
    }
}

/**
* չʾͳ������
* @param vecs ���е����͵�vector����
* @param i �±�
* @param value json����
* @param by ����
* @param analyze ��������,�ص�
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
                showCountData(vecs, i + 1, value1, by, analyze); //�ݹ��ѯ����������ֵ
            }
        }
    } else {
        //�ݹ���ϣ���ʼչʾ����
        stringstream s;
        for (unsigned j = 0; j < i; j++) {
            cout << setw(30) << value[0][keys[by[j]]].asString();
            if (j > 0)s << "��";
            s << types[by[j]] << "Ϊ" << value[0][keys[by[j]]].asString(); //��������ı�
        }
        cout << value.size() << endl;
        analyze[s.str()] = value.size(); //��������
    }
}

/**
 * ���ݷ���
 * @param analyze Ҫ���������� 
 */
void Student::analyzeData(const map<string, int>& analyze) {
    cout << "���ݷ�����" << endl;
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
    cout << "����֮��Ϊ" << sum << endl
        << maxPair.first << "���������,����Ϊ" << maxPair.second
        << ",ռ��Ϊ" << (double(maxPair.second) / sum * 100) << "%" << endl
        << minPair.first << "����������,����Ϊ" << minPair.second
        << ",ռ��Ϊ" << (double(minPair.second) / sum * 100) << "%" << endl;
}

/**
* У��ѧ��
* @param id ѧ��
* @return ѧ��
*/
string Student::checkId(const string& id) {
    if (!isInt(id)) {
        throw CheckException("ѧ�ű���Ϊ����!");
    }
    if (id.size() != 9) {
        throw CheckException("ѧ�ų��ȱ���Ϊ9λ!");
    }
    if (dbHelper.findById(id) >= 0) {
        throw CheckException("��ѧ���Ѿ�����ӹ�!");
    }
    static DbHelper dbHelper2("data/college.json");
    const string college = id.substr(0, 2);
    const int index = dbHelper2.findById(college);
    if (index < 0) {
        throw CheckException("�����ѧ�ŵ�ѧԺ������!");
    }
    Json::Value&& value = dbHelper2.get(index);
    const int year = stoi(id.substr(2, 2)) + 2000;
    const int now = getTime()->tm_year + 1900;
    if (year > now) {
        throw CheckException("ѧ���е���ѧ�������!");
    }
    if (getTime()->tm_year + 1900 != year) {
        cout << "ѧ���е���ѧ����뵱ǰ��ݲ�һ��!" << endl; //ֻ��������
    }
    const string major = id.substr(4, 2);
    const int index2 = DbHelper::findById(value["majors"], major);
    if (index2 < 0) {
        throw CheckException("�����ѧ�ŵ�רҵ������!");
    }
    //int cls = stoi(id.substr(6, 1));
    //��Ϊ���������ݵĹ����з�����һλ(��7λ)����ֻ�Ǳ�ʾ�༶,�кܶ�ѧԺ����һλ������רҵ
    //���Լ��༶�ǳ�����,��ע�͵�
    this->id = id;
    collegeId = college;
    majorId = major;
    inYear = year;
    return id;
}

/**
* У���Ա�
* @param sex �Ա�
* @return ��/Ů
*/
string Student::checkSex(const string& sex) {
    if (sex == "1") {
        this->sex = 1;
        return "��";
    }
    if (sex == "2") {
        this->sex = 0;
        return "Ů";
    }
    throw CheckException("�Ա�ֻ�����л�Ů!");
}

/**
* У���������
* @param birthDate ��������
* @return �����ĳ�������
*/
string Student::checkBirthDate(const string& birthDate) {
    int year, month, day;
    char ch;
    stringstream in(birthDate);
    in >> year >> ch >> month >> ch >> day;
    if (!checkDate(year, month, day)) {
        throw CheckException("�������ڲ��Ϸ�!");
    }
    const int years = getTime()->tm_year + 1900 - year;
    if (years > 100 || years < 10) {
        throw CheckException("��ѧ���������10-100֮��");
    }
    stringstream out;
    //�����ڸ�ʽ��һ�·���������֤
    out << setfill('0') << setw(4) << year
        << setfill('0') << setw(2) << month
        << setfill('0') << setw(2) << day;
    birthDateFormat = out.str();
    stringstream out2;
    //���ڲ���,����֮����������
    out2 << setfill('0') << setw(4) << year << '.'
        << setfill('0') << setw(2) << month << '.'
        << setfill('0') << setw(2) << day;
    return out2.str();
}

/**
* У�����֤����
* @param personId ���֤����
* @return ���֤����
*/
string Student::checkPersonId(const string& personId) const {
    if (!isChinese && !isInt(personId))return ""; //�����й��˿���û���֤
    if (!isInt(personId)) {
        throw CheckException("���֤�������Ϊ����!");
    }
    if (personId.size() != 18) {
        throw CheckException("���֤�������Ϊ18λ!");
    }
    if (dbHelper.find("personId", personId) >= 0) {
        throw CheckException("�����֤�Ѿ�����ӹ�!");
    }
    const string locate = personId.substr(0, 6);
    static DbHelper dbHelper1("data/locate.json");
    if (dbHelper1[locate].isNull()) {
        throw CheckException("�������������!");
    }
    const string birthDate = personId.substr(6, 8);
    if (birthDateFormat != birthDate) {
        throw CheckException("���֤�ϵĳ���������֮ǰ����ĳ������ڲ�һ��!");
    }
    if (stoi(personId.substr(16, 1)) % 2 != sex) {
        throw CheckException("���֤�ϵ��Ա���֮ǰ������Ա�һ��!");
    }
    if (personId.at(17) != getPersonId18(personId)) {
        throw CheckException("���֤У�������!");
    }
    return personId;
}

/**
* У������
* @param name ����
* @return ����
*/
string Student::checkName(const string& name) const {
    if (isChinese) {
        if (name.size() < 4 || name.size() > 40 || !isAllChinese(name)) {
            throw CheckException("��������Ϊ������ʮ������!");
        }
    } else {
        if (name.size() > 40 || name.empty()) {
            throw CheckException("��������С��40����ĸ�Ҳ���Ϊ��!");
        }
    }
    return name;
}

/**
* У���꼶
* @param grade �꼶
* @return �꼶
*/
string Student::checkGrade(const string& grade) const {
    if (!isInt(grade)) {
        throw CheckException("�꼶����Ϊ����!");
    }
    if (grade < to_string(inYear)) {
        throw CheckException("������꼶������ڵ�����ѧ���!");
    }
    if (grade != to_string(inYear)) {
        cout << "������꼶��ѧ���ϵ��꼶��һ��!" << endl; //ֻ�Ƿ�������
    }
    return grade;
}

/**
* У����ѧʱ��
* @param inDate ��ѧʱ��
* @return ��������ѧ����
*/
string Student::checkInDate(const string& inDate) const {
    int year, month, day;
    stringstream s(inDate);
    char ch;
    s >> year >> ch >> month >> ch >> day;
    if (!checkDate(year, month, day)) {
        throw CheckException("��ѧ���ڲ��Ϸ�!");
    }
    if (month < 8 || month > 10) {
        throw CheckException("��ѧ�·ݱ�����8��-10��֮��");
    }
    if (year != inYear) {
        throw CheckException("��ѧ��ݱ�����ѧ�ŵ���ѧ���һ��!");
    }
    stringstream out;
    //���ڲ���,����֮����������
    out << setfill('0') << setw(4) << year << '.'
        << setfill('0') << setw(2) << month << '.'
        << setfill('0') << setw(2) << day;
    return out.str();
}

/**
* У��༶
* @param cls �༶
* @return �༶��Ϣ
*/
string Student::checkClass(const string& cls) const {
	if (!isInt(cls)) {
        throw CheckException("�༶����Ϊ����!");
    }
    const int c = stoi(cls);
    if (c < 1 || c > 10) {
        throw CheckException("�༶�ű�����1-10֮��!");
    }
    return to_string(c);
}

/**
* У�鸨��Ա
* @param instructor ����Ա����
* @return ����Ա
*/
string Student::checkInstructor(const string& instructor) const {
    static DbHelper dbHelper("data/instructor.json");
    const string key = id.substr(0, 7);
    Json::Value&& value = dbHelper[key];
    if (value.isNull()) {
        dbHelper.add(key, instructor);
    } else {
        if (value.asString() != instructor) {
            throw CheckException("����ĸ���Ա��Ϣ��洢�ĸð༶����Ա��Ϣ��һ��!");
        }
    }
    return instructor;
}
