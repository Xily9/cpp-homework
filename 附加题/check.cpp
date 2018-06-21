#include "check.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include "function.h"
using namespace std;

/**
 * ���캯��
 * @param file1 ��һ���ļ�
 * @param file2 �ڶ����ļ�
 */
Check::Check(const string& file1, const string& file2) {
    cout << "���ڱ����һ���ļ�,���Ժ�..." << endl;
    system((string("gcc -S -o test.s ") + file1).c_str());
    cout << "���ڱ���ڶ����ļ�,���Ժ�..." << endl;
    system((string("gcc -S -o test2.s ") + file2).c_str());
    ifstream fin1("test.s");
    ifstream fin2("test2.s");
    if (!fin1.is_open() || !fin2.is_open()) {
        throw CheckException("����ʱ�����쳣,��ȷ������û�д���!");
    }
    cout << "���ڽ�����һ���ļ�,���Ժ�..." << endl;
    parse(fin1, vec1);
    cout << "���ڽ����ڶ����ļ�,���Ժ�..." << endl;
    parse(fin2, vec2);
    cout << "���ڱȶ������ļ�,���Ժ�..." << endl;
    analyze();
}

/**
 * ����������
 * @param fin �ļ�����
 * @param vec2 Ҫ������ַ�������
 */
void Check::parse(ifstream& fin, vector<string>& vec2) const {
    string line;
    vector<string> vec;
    vector<string> strs;
    string temp;
    while (getline(fin, line)) {
        vector<string> arr = split(line, "\t");
        if (arr.size() == 1) {
            //cout << arr.at(0) << endl;
            if (!temp.empty()) {
                //cout << temp << endl;
                vec.push_back(temp);
                temp.clear();
            }
        } else {
            string a = arr.at(1);
            const string::size_type pos = a.find(' ');
            if (pos < a.size()) {
                string name = a.substr(0, pos);
                string str = a.substr(pos + 1);
                if (a[0] == '.') {
                    //temp += name.substr(1, 2);
                } else {
                    temp += name.substr(0, 2);
                }
            } else {
                //cout << "����:"<<a<<endl;
                if (a[0] == '.') {
                    //temp += a.substr(1,2);
                } else {
                    temp += a.substr(0, 2);
                }
            }
        }
    }
    copy_if(vec.begin(), vec.end(), back_inserter(vec2), [](string& s) {
        return s.size() >= 10; //���˵��߼�����ٵĴ����,��������
    });
}

/**
 * ����������
 */
void Check::analyze() {
    vector<string> vec3, vec4, vec5;
    sort(vec1.begin(), vec1.end());
    sort(vec2.begin(), vec2.end());
    set_intersection(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), back_inserter(vec3));
    set_difference(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), back_inserter(vec4));
    set_difference(vec2.begin(), vec2.end(), vec1.begin(), vec1.end(), back_inserter(vec5));
    double percent = double(vec3.size()) / (vec1.size() + vec2.size()) * 2;
    if (percent < 0.8) {
        double size = 0;
        for (string& s : vec3) {
            size += s.size() / 30.;
            percent = double(size) / (vec1.size() + vec2.size()) * 2;
            if (percent > 0.9)break;
        }
    }
    if (percent < 0.9) {
        const double aaa = (1 - percent) / vec4.size();
        for (string& s1 : vec4) {
            if (s1.size() < 30)continue;
            int largest = 0;
            int size = 0;
            for (string& s2 : vec5) {
                if (s2.size() < 30)continue;
                const int temp = ldistance(s1, s2);
                if (temp > largest) {
                    largest = temp;
                    size = s2.size();
                }
            }
            percent += double(largest) / (s1.size() + size) * aaa;
            if(percent>0.9)break;
        }
    }
    cout <<"���ļ��������Դ�ԼΪ��"<< percent * 100 << "%" << endl;
    if(percent<0.3) {
        cout << "���ڳ��������,������<30%ʵ������,�������ɳ�Ϯ"<<endl;
    }else if(percent<0.5) {
        cout << "�����в��ִ�������,�����߼���,�����н��,���������ɳ�Ϯ" << endl;
    }else if(percent<0.9) {
        cout << "��������΢�е��,�����ֶ��������Ƿ�����" << endl;
    }else {
        cout << "��������ȷ���ǳ�Ϯ,����ֻ�޸���һ������,���߼���һ��" << endl;
    }
}
