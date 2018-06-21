#include "check.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include "function.h"
using namespace std;

/**
 * 构造函数
 * @param file1 第一个文件
 * @param file2 第二个文件
 */
Check::Check(const string& file1, const string& file2) {
    cout << "正在编译第一个文件,请稍后..." << endl;
    system((string("gcc -S -o test.s ") + file1).c_str());
    cout << "正在编译第二个文件,请稍后..." << endl;
    system((string("gcc -S -o test2.s ") + file2).c_str());
    ifstream fin1("test.s");
    ifstream fin2("test2.s");
    if (!fin1.is_open() || !fin2.is_open()) {
        throw CheckException("编译时出现异常,请确保程序没有错误!");
    }
    cout << "正在解析第一个文件,请稍后..." << endl;
    parse(fin1, vec1);
    cout << "正在解析第二个文件,请稍后..." << endl;
    parse(fin2, vec2);
    cout << "正在比对两个文件,请稍后..." << endl;
    analyze();
}

/**
 * 解析汇编代码
 * @param fin 文件对象
 * @param vec2 要保存的字符串向量
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
                //cout << "命令:"<<a<<endl;
                if (a[0] == '.') {
                    //temp += a.substr(1,2);
                } else {
                    temp += a.substr(0, 2);
                }
            }
        }
    }
    copy_if(vec.begin(), vec.end(), back_inserter(vec2), [](string& s) {
        return s.size() >= 10; //过滤掉逻辑语句少的代码块,避免误判
    });
}

/**
 * 分析相似性
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
    cout <<"两文件的相似性大约为："<< percent * 100 << "%" << endl;
    if(percent<0.3) {
        cout << "由于程序的误判,相似率<30%实属正常,并不构成抄袭"<<endl;
    }else if(percent<0.5) {
        cout << "可能有部分代码相似,包括逻辑等,可能有借鉴,但并不构成抄袭" << endl;
    }else if(percent<0.9) {
        cout << "相似率稍微有点高,可以手动检查代码是否相似" << endl;
    }else {
        cout << "基本可以确定是抄袭,或者只修改了一点点代码,但逻辑上一样" << endl;
    }
}
