#include "utils.h"
#include "function.h"
#include "dbhelper.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>

using namespace std;
const string types[] = {
    "ѧ��", "����", "�Ա�", "����", "��������", "����", "����״��",
    "������ò", "���֤��", "ѧ�����", "��ѧ����", "��ѧ��ʽ", "ѧԺ", "רҵ", "ѧ��",
    "�������", "�꼶", "�༶��", "����Ա"
};

/**
 * ��ʾ���˵�
 */
void showMainMenu() {
    cout << "Copyright (C) 2018 ���꽡(221701423).All Rights Reserved." << endl << endl;
    showTime();
    cout << "*************************************************************" << endl
        << "*    A�����ѧ������                                        *" << endl
        << "*    B����ʾѧ������                                        *" << endl
        << "*    C������ѧ������                                        *" << endl
        << "*    D������ѧ������                                        *" << endl
        << "*    E��ͳ�Ʒ���ѧ������                                    *" << endl
        << "*    Q���˳�ϵͳ                                            *" << endl
        << "*************************************************************" << endl
        << "��ѡ��A,B,C,D,E,Q����";
}

/**
* ��ʾϵͳ��ǰʱ��
*/
void showTime() {
    const char* weekday[7] = {"��", "һ", "��", "��", "��", "��", "��"};
    tm* timeInfo = getTime(); //��õ�ǰʱ��
    printf("��ǰ���ڡ�ʱ�䣺%04d.%02d.%02d(����%s)  %02d:%02d:%02d\n",
           timeInfo->tm_year + 1900,
           timeInfo->tm_mon + 1,
           timeInfo->tm_mday,
           weekday[timeInfo->tm_wday],
           timeInfo->tm_hour,
           timeInfo->tm_min,
           timeInfo->tm_sec);
}

/**
 * ���һ��������
 * @param dbHelper db������ 
 */
void addData(DbHelper& dbHelper) {
    File value;
    inputData(dbHelper, value, false);
    dbHelper.add(value);
    cout << "���һ����ѧ�����ݳɹ�!" << endl;
}

/**
 * ¼������
 * @param dbHelper db������ 
 * @param value txt���� 
 * @param isEdit �Ƿ��Ǳ༭״̬
 * @return �����txt����
 */
File& inputData(DbHelper& dbHelper, File& value, const bool isEdit) {
    int collegeId, inYear;
    if (!isEdit) {
        value[0] = getInput("ѧ��", "ѧ�ű���Ϊ9λ",
                               [&dbHelper, &collegeId, &inYear](const string& id) {
                                   return checkId(dbHelper, id, collegeId, inYear);
                               });
    } else {
        collegeId = strToInt(value[0].asString().substr(0, 2));
        inYear = strToInt(value[0].asString().substr(2, 2)) + 2000;
    }
    value[3] = inputCountry();
    bool isChinese = value[3].asString() == "�й�";
    value[1] = getInput("����", isChinese ? "����Ϊ2-10������" : "����Ӧ������40���ַ�",
                             [isChinese](const string& name) { return checkName(name, isChinese); });
    value[2] = getInput("�Ա�", "ֻ��������/Ů", [](const string& sex) { return checkSex(sex); });
    string birthDateFormat;
    value[4] = getInput("��������", "��ʽ��������1998.11.4",
                                  [&birthDateFormat](const string& birthDate) {
                                      return checkBirthDate(birthDate, birthDateFormat);
                                  });
    value[8] = getInput("���֤����", "",
                                 [&dbHelper, &value, &birthDateFormat](const string& personId) {
                                     return checkPersonId(dbHelper, personId,
                                                          value[2].asString() == "��" ? 1 : 2,
                                                          birthDateFormat);
                                 });
    value[5] = inputNation();
    value[7] = inputPolitics();
    value[6] = inputMarry();
    value[9] = inputStudentType();
    value[11] = inputInType();
    value[10] = getInput("��ѧ����", "����2017.09.14", [inYear](const string& inDate) {
        return checkInDate(inDate, inYear);
    });
    int index;
    value[12] = inputCollege(index, collegeId);
    value[13] = inputMajor(index);
    value[16] = getInput("�꼶", "����2015", [inYear](const string& grade) {
        return checkGrade(grade, inYear);
    }, true, to_string(inYear));
    value[14] = getInput("ѧ��", "", [](const string& length) { return ""; }, true, "4");
    value[15] = inputLevel();
    value[17] = getInput("�༶", "", [](const string& cls) {
        return checkClass(cls);
    });
    value[18] = getInput("����Ա", "", [&value](const string& instructor) {
        return checkInstructor(instructor, value[0].asString());
    });
    return value;
}

/**
 * �Ӽ����ϻ�ȡ�ַ�������У��
 * @tparam T lambda
 * @param type ֵ����
 * @param message ��ʾ��Ϣ
 * @param check �ص�����
 * @param useDefault �Ƿ���Ĭ��ֵ,Ĭ��û��
 * @param defaultValue Ĭ��ֵ,Ĭ�Ͽ�
 * @return ��ȡ��������ͨ�����ַ���
 */
template <typename T>
string getInput(const string& type, const string& message, T check, const bool useDefault, const string& defaultValue) {
    string str;
    while (true) {
        cout << "������" << type;
        if (useDefault) {
            cout << "(Ĭ��Ϊ" << defaultValue << ")";
        }
        cout << endl;
        if (!message.empty()) {
            cout << message << endl;
        }
        if (useDefault && cin.peek() == '\n') {
            str = defaultValue;
        } else {
            cin >> str;
        }
        getchar();
        string errorMsg = check(str);
        if (errorMsg.empty()) {
            return str;
        } else {
            cout << errorMsg << endl;
        }
    }
}

/**
 * �������
 * @return ���� 
 */
string inputCountry() {
    static const DbHelper dbHelper("data/country.txt");
    return inputList(dbHelper, "����", 3);
}

/**
 * ��������
 * @return ���� 
 */
string inputNation() {
    static const DbHelper dbHelper("data/nation.txt");
    return inputList(dbHelper, "����");
}

/**
 * ����������ò
 * @return ������ò
 */
string inputPolitics() {
    static const DbHelper dbHelper("data/politics.txt");
    return inputList(dbHelper, "������ò");
}

/**
 * �������״��
 * @return ����״��
 */
string inputMarry() {
    static const DbHelper dbHelper("data/marry.txt");
    return inputList(dbHelper, "�������");
}

/**
 * ����ѧ�����
 * @return ѧ�����
 */
string inputStudentType() {
    static const DbHelper dbHelper("data/student_type.txt");
    return inputList(dbHelper, "ѧ�����");
}

/**
 * ������ѧ��ʽ
 * @return ��ѧ��ʽ
 */
string inputInType() {
    static const DbHelper dbHelper("data/in_type.txt");
    return inputList(dbHelper, "��ѧ��ʽ");
}

/**
 * �����������
 * @return �������
 */
string inputLevel() {
    static const DbHelper dbHelper("data/level.txt");
    return inputList(dbHelper, "�������");
}

/**
 * ����ѧԺ��Ϣ
 * @param index ���ڻص�ѧԺ���
 * @param collegeId ѧ���ϵ�ѧԺ��Ϣ
 * @return ѧԺ��Ϣ
 */
string inputCollege(int& index, const int collegeId) {
    static const DbHelper dbHelper("data/college.txt");
    unsigned n;
    const File value = dbHelper.getValue();
    static int width = getConsoleWidth();
    cout << endl << "----------------------------------" << endl;
    cout.setf(ios_base::left, ios_base::adjustfield);
    for (unsigned i = 0; i < value.size(); i++) {
        cout << setw(width / 4) << "[" + to_string(i) + "] " + value[i][1].asString();
        if (i % 4 == 3) {
            cout << endl;
        }
    }
    cout << endl << "----------------------------------" << endl;
    while (true) {
        cout << endl << "������ѧԺǰ�����ţ�";
        cin >> n;
        getchar();
        if (cin.fail()) {
            cin.clear();
            cin.sync();
            cout << "��������ݲ��Ϸ�,����������!" << endl;
        } else if (n >= value.size()) {
            cout << "�������������,����������!" << endl;
        } else if (value[n][0].asInt() != collegeId) {
            cout << "�����ѧԺ��Ϣ��֮ǰѧ�Ŷ�Ӧ��ѧԺ��Ϣ��һ��!" << endl;
        } else {
            break;
        }
    }
    index = n;
    return value[n][1].asString();
}

/**
 * ����רҵ��Ϣ
 * @param index ѧԱ���
 * @return רҵ��Ϣ
 */
string inputMajor(const int index) {
    static DbHelper dbHelper("data/college.txt");
    unsigned n;
    const File value = dbHelper[index][2];
    showListMenu(value, 4);
    while (true) {
        cout << endl << "������רҵǰ�����ţ�";
        cin >> n;
        getchar();
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "��������ݲ��Ϸ�,����������!" << endl;
        } else if (n >= value.size()) {
            cout << "�������������,����������!" << endl;
        } else {
            break;
        }
    }
    return value[n].asString();
}

/**
 * ���б��л�ȡ����
 * @param dbHelper db������ 
 * @param type ֵ����
 * @param lineLength һ����ʾ���� 
 * @return ��ȡ�����ַ���
 */
string inputList(const DbHelper& dbHelper, const string& type, const unsigned lineLength) {
    unsigned n;
    const File value = dbHelper.getValue();
    showListMenu(value, lineLength);
    while (true) {
        cout << "������" << type << "ǰ������(Ĭ��Ϊ" << value[0].asString() << ")��";
        if (cin.peek() != '\n') {
            cin >> n;
            getchar();
            if (cin.fail()) {
                cin.clear();
                cin.sync();
                cout << "��������ݲ��Ϸ�,����������!" << endl;
            } else if (n >= value.size()) {
                cout << "�������������,����������!" << endl;
            } else {
                break;
            }
        } else {
            getchar();
            n = 0;
            break;
        }

    }
    return value[n].asString();
}

/**
 * չʾ����
 * @param dbHelper db������ 
 * @param value txt����,Ĭ��Ϊ��
 */
void showData(DbHelper& dbHelper, File value) {
    if (value.isNull()) {
        value = dbHelper.getValue();
    }
    int page = 1;
    const int pageNum = value.size() / 20 + 1;
    cin.clear();
    fflush(stdin);
    while (true) {
        system("cls");
        cout.setf(ios_base::left, ios_base::adjustfield);
        cout << setw(5) << "���" << setw(10) << "ѧ��" << setw(10) << "����" << endl;
        for (int i = 0; i < 20; i++) {
            const File& array = value[(page - 1) * 20 + i];
            if (array.isNull()) {
                break;
            }
            cout << setw(5) << (page - 1) * 20 + i + 1 << setw(10) << array[0].asString()
                << setw(10) << array[1].asString() << endl;
        }
        bool out = false;
        while (!out) {
            cout << "----------------------------------" << endl
                << "��ѡ���������һҳ(A)����һҳ(D)���鿴ѧ����Ϣ(S)��������һ��(Q)" << endl;
            switch (getKey()) {
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
                case 'S':
                    unsigned n;
                    while (true) {
                        cout << "���������:";
                        cin >> n;
                        if (n >= value.size()) {
                            cout << "������һ���Ϸ������!" << endl;
                            cin.clear();
                            cin.ignore(1024, '\n');
                        } else {
                            break;
                        }
                    }
                    showLine(dbHelper, value[n - 1][0].asString());
                    out = true;
                    break;
                default:
                    cout << endl << "\aѡ�����������ѡ��......" << endl << endl;
                    break;
            }
        }
    }
}

/**
 * չʾһ������
 * @param dbHelper db������ 
 * @param id ѧ��
 */
void showLine(DbHelper& dbHelper, const string& id) {
    system("cls");
    const int index = dbHelper.findById(id);
    if (index < 0) {
        cout << "��ȡѧ����Ϣ����!" << endl;
        system("pause");
    } else {
        File value = dbHelper[index];
        cout << "------------------------------" << endl;
        for (unsigned i = 0; i < 19; i++) {
            cout << types[i] << "��" << value[i].asString() << endl;
        }
        bool out = false;
        while (!out) {
            cout << "---------------------------------" << endl
                << "��ѡ�������ɾ����ǰ(D),ɾ�������꼶+רҵ(G),�޸�(E),�����ϼ�(Q)";
            switch (getKey()) {
                case 'D':
                    deleteByIndex(dbHelper, index);
                    system("pause");
                    out = true;
                    break;
                case 'G':
                    deleteData(dbHelper, value[13].asString(), value[16].asString());
                    system("pause");
                    out = true;
                    break;
                case 'E':
                    editByIndex(dbHelper, index);
                    system("pause");
                    out = true;
                    break;
                default:
                    cout << endl << "\aѡ�����������ѡ��......" << endl << endl;
                    break;
            }
        }
    }
}

/**
 * ��������
 * @param dbHelper db������ 
 */
void findData(DbHelper& dbHelper) {
    string str;
    File value = dbHelper.getValue();
    showListMenu(types, 19);
    cout << "�����������һ����������ǰ�������Ϊ��������" << endl
        << "������ֵ֮���ö��Ÿ������������֮���û��и���������EOF����" << endl;
    while (cin >> str) {
        const int pos = str.find(',');
        const string val = str.substr(pos + 1);
        value = DbHelper::findAll(value,strToInt(str.substr(0, pos)) , val);
        if (value.isNull()) {
            cout << "���ҽ��Ϊ��!!" << endl;
            return;
        }
    }
    showData(dbHelper, value);
}

/**
 * ɾ������רҵ+�꼶����
 * @param dbHelper db������ 
 * @param major רҵ
 * @param grade �꼶
 */
void deleteData(DbHelper& dbHelper, const string& major, const string& grade) {
    if (getTime()->tm_year + 1904 - strToInt(grade) < 10) {
        cout << "����ɾ����ҵ10�����ϵ�ѧ��!" << endl;
    } else {
        cout << "ȷ��Ҫɾ����?????" << endl
            << "ɾ�������ݽ��޷����лָ�" << endl
            << "ȷ���밴Y,ȡ���밴���������" << endl;
        if (getKey() == 'Y') {
            File values = dbHelper.findAll(13, major);
            values = DbHelper::findAll(values, 16, grade);
            int i = 0;
            for (File value : values) {
                const int index = dbHelper.findById(value[0].asString());
                if (index >= 0) {
                    dbHelper.del(index);
                    i++;
                }
            }
            cout << "ִ�����,��ɾ��" << i << "������!" << endl;
        }
    }
}

/**
 * ɾ��һ������
 * @param dbHelper db������ 
 * @param index 
 */
void deleteByIndex(DbHelper& dbHelper, const int index) {
    cout << "ȷ��Ҫɾ����?????" << endl
        << "ȷ���밴Y,ȡ���밴���������" << endl;
    if (getKey() == 'Y') {
        if (dbHelper.del(index)) {
            cout << "ɾ���ɹ�!";
        } else {
            cout << "ɾ��ʧ��!";
        }
    }
}

/**
 * �༭һ������
 * @param dbHelper db������ 
 * @param index �����±�
 */
void editByIndex(DbHelper& dbHelper, int index) {
    File value = dbHelper[index];
    inputData(dbHelper, value, true);
    dbHelper.update(index, value);
    cout << "�༭�ɹ�!!" << endl;
}

/**
 * ����
 * @param dbHelper db������
 */
void sortData(DbHelper& dbHelper) {
    File value = dbHelper.getValue();
    showListMenu(types, 19);
    unsigned n;
    int isDesc;
    while (true) {
        cout << "���������������ǰ�������Ϊ��������" << endl;
        cin >> n;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "��������ݲ��Ϸ�,����������!" << endl;
        } else if (n >= 19) {
            cout << "�������������,����������!" << endl;
        } else {
            break;
        }
    }
    while (true) {
        cout << "�������ǽ�����?(1����2����)" << endl;
        cin >> isDesc;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "��������ݲ��Ϸ�,����������!" << endl;
        } else if (isDesc != 1 && isDesc != 2) {
            cout << "�������������,����������!" << endl;
        } else {
            break;
        }
    }
    cout << "����������,���Ժ�..." << endl;
    isDesc = isDesc == 1 ? 1 : -1;
    quickSort(value, 0, value.size()-1, [isDesc,n](const File& left,const File& right) {
        return left[n].asString().compare(right[n].asString())*isDesc;
    });
    dbHelper.setValue(value);
    cout << "�������!" << endl;
}

/**
 * ͳ��
 * @param dbHelper db������ 
 */
void countData(const DbHelper& dbHelper) {
    int by[17];
    File value = dbHelper.getValue();
    showListMenu(types, 19);
    cout << "�����������һ���������ǰ�������Ϊ���෽ʽ,����֮���ÿո����" << endl;
    int i = 0, n;
    while (cin.peek() != '\n') {
        cin >> n;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "��������ݲ��Ϸ�,����������!" << endl;
        } else if (n >= 17) {
            cout << "�������������,����������!" << endl;
        } else {
            by[i++] = n;
        }
    }
    getchar();
    vector<vector<string>> vecs;
    for (int j = 0; j < i; j++) {
        vector<string> vec;
        quickSort(value, 0, value.size()-1, [by,j](const File& left, const File& right) {
            return left[by[j]].asString().compare(right[by[j]].asString());
        });
        for (auto& k : value) {
            const string str = k[by[j]].asString();
            if (vec.empty() || str != vec.back()) {
                vec.push_back(str);
            }
        }
        vecs.push_back(vec);
    }
    cout << "---------------------------------" << endl;
    cout.setf(ios_base::left, ios_base::adjustfield);
    for (int j = 0; j < i;j++) {
        cout << setw(30) << types[by[j]];
    }
    cout << "����" << endl;
    showCountData(vecs, 0, value, by);
    cout << "---------------------------------" << endl;
}

/**
 * չʾͳ������
 * @param vecs ���е����͵�vector����
 * @param i �±�
 * @param value txt����
 * @param by ����
 */
void showCountData(const vector<vector<string>>& vecs, const unsigned i, const File& value, int by[]) {
    if (i < vecs.size()) {
        for (unsigned j = 0; j < vecs[i].size(); j++) {
            const File value1 = DbHelper::findAll(value, by[i],vecs[i][j]);
            if (!value1.isNull()) {
                showCountData(vecs, i + 1, value1, by);
            }
        }
    } else {
        for(unsigned j=0;j<i;j++) {
            cout << setw(30) << value[0][by[j]].asString();
        }
        cout << value.size() << endl;
    }
}

/**
 * չʾ�б�˵�
 * @param list string����
 * @param size �����С
 */
void showListMenu(const string list[], unsigned size) {
    cout << "---------------------------------" << endl;
    for (unsigned i = 0; i < size; i++) {
        cout << "[" << i << "] " << list[i] << "\t";
        if (i % 6 == 5) {
            cout << endl;
        }
    }
    cout << endl << "---------------------------------" << endl;
}

/**
 * չʾ�б�˵�
 * @param value txt����
 * @param lineLength һ����ʾ����
 */
void showListMenu(const File& value, const unsigned lineLength) {
    static int width = getConsoleWidth();
    cout << endl << "----------------------------------" << endl;
    cout.setf(ios_base::left, ios_base::adjustfield);
    for (unsigned i = 0; i < value.size(); i++) {
        cout << setw(width / lineLength) << "[" + to_string(i) + "] " + value[i].asString();
        if (i % lineLength == lineLength - 1) {
            cout << endl;
        }
    }
    cout << endl << "----------------------------------" << endl;
}

/**
 * У��ѧ��
 * @param dbHelper db������ 
 * @param id ѧ��
 * @param collegeId ѧ���ϵ�ѧԺ��Ϣ,���ڻص�
 * @param inYear ѧ���ϵ���ѧ���,���ڻص�
 * @return ������Ϣ
 */
string checkId(const DbHelper& dbHelper, const string& id, int& collegeId, int& inYear) {
    if (!isInt(id)) {
        return "ѧ�ű���Ϊ����!";
    }
    if (dbHelper.findById(id) >= 0) {
        return "��ѧ���Ѿ�����ӹ�!";
    }
    static DbHelper dbHelper2("data/college.txt");
    const int college = strToInt(id.substr(0, 2));
    const int index = dbHelper2.find(0, college);
    if (index < 0) {
        return "�����ѧ�ŵ�ѧԺ������!";
    }
    File value = dbHelper2[index];
    const int year = strToInt(id.substr(2, 2)) + 2000;
    if (getTime()->tm_year + 1900 != year) {
        cout << "ѧ���е���ѧ����뵱ǰ��ݲ�һ��!" << endl;
    }
    int major = strToInt(id.substr(4, 2));
    int cls = strToInt(id.substr(6, 1));
    collegeId = value[0].asInt();
    inYear = year;
    return "";
}

/**
 * У���Ա�
 * @param sex �Ա�
 * @return ������Ϣ
 */
string checkSex(const string& sex) {
    if (sex == "��" || sex == "Ů") {
        return "";
    } else {
        return "�Ա�ֻ�����л�Ů!";
    }
}

/**
 * У���������
 * @param birthDate ��������
 * @param birthDateFormat ��ʽ����ĳ�������,���ڻص�
 * @return ������Ϣ
 */
string checkBirthDate(const string& birthDate, string& birthDateFormat) {
    int year, month, day;
    char birthDateFormatChar[40];
    sscanf(birthDate.c_str(), "%d.%d.%d", &year, &month, &day);
    if (!checkDate(year, month, day)) {
        return "�������ڲ��Ϸ�!";
    }
    const int years = getTime()->tm_year + 1900 - year;
    if (years > 100 || years < 10) {
        return "��ѧ���������10-100֮��";
    }
    sprintf(birthDateFormatChar, "%04d%02d%02d", year, month, day);
    birthDateFormat = birthDateFormatChar;
    return "";
}

/**
 * У�����֤����
 * @param dbHelper db������ 
 * @param personId ���֤����
 * @param sex �Ա�
 * @param birthDate ��������
 * @return ������Ϣ
 */
string checkPersonId(const DbHelper& dbHelper, const string& personId, const int sex, const string& birthDate) {
    if (personId.size() != 18) {
        return "���֤�������Ϊ18λ!";
    }
    if (dbHelper.find(8, personId) >= 0) {
        return "�����֤�Ѿ�����ӹ�!";
    }
    const string locate = personId.substr(0, 6);
    static DbHelper dbHelper1("data/locate.txt");
    
    if (dbHelper1[locate].isNull()) {
        return "�������������!";
    }
    const string birthDate1 = personId.substr(6, 8);
    if (birthDate != birthDate1) {
        return "���֤�ϵĳ���������֮ǰ����ĳ������ڲ�һ��!";
    }
    if ((strToInt(personId.substr(16, 1)) + 1) % 2 + 1 != sex) {
        return "���֤�ϵ��Ա���֮ǰ������Ա�һ��!";
    }
    if (personId.at(17) != getPersonId18(personId)) {
        return "���֤У�������!";
    }
    return "";
}

/**
 * У������
 * @param name ����
 * @param isChinese �Ƿ����й���
 * @return ������Ϣ
 */
string checkName(const string& name, const bool isChinese) {
    if (isChinese) {
        if (name.size() < 4 || name.size() > 40 || !isAllChinese(name)) {
            return "��������Ϊ����ʮ������!";
        }
    } else {
        if (name.size() > 40) {
            return "��������С��40����ĸ!";
        }
    }
    return "";
}

/**
 * У���꼶
 * @param grade �꼶
 * @param inYear ѧ���ϵ���ѧ���
 * @return ������Ϣ
 */
string checkGrade(const string& grade, const int inYear) {
    if (grade != to_string(inYear)) {
        cout << "������꼶��ѧ�ŵ���ѧ���䲻һ��!";
    }
    return "";
}

/**
 * У����ѧʱ��
 * @param inDate ��ѧʱ��
 * @param inYear ѧ���ϵ���ѧ���
 * @return ������Ϣ
 */
string checkInDate(const string& inDate, const int inYear) {
    int year, month, day;
    sscanf(inDate.c_str(), "%d.%d.%d", &year, &month, &day);
    if (!checkDate(year, month, day)) {
        return "��ѧ���ڲ��Ϸ�!";
    }
    if (month < 8 || month > 10) {
        return "��ѧ�·ݱ�����8��-10��֮��";
    }
    if (year != inYear) {
        return "��ѧ��ݱ�����ѧ�ŵ���ѧ���һ��!";
    }
    return "";
}

/**
 * У��༶
 * @param cls �༶
 * @return ������Ϣ
 */
string checkClass(const string& cls) {
    if (cls < "01" || cls > "10") {
        return "�༶�ű�����01-10֮��!";
    }
    return "";
}

/**
 * У�鸨��Ա
 * @param instructor ����Ա����
 * @param id ѧ��
 * @return ������Ϣ
 */
string checkInstructor(const string& instructor, const string& id) {
    static DbHelper dbHelper("data/instructor.txt");
    const string key = id.substr(0, 7);
    File value = dbHelper[key];
    if (value.isNull()) {
        dbHelper.add(key, instructor);
    } else {
        if (value.asString() != instructor) {
            return "����ĸ���Ա��Ϣ��洢�ĸð༶����Ա��Ϣ��һ��!";
        }
    }
    return "";
}
