#include <string>
#include <iostream>
#include "check.h"
using namespace std;

int main() {
    cout << "使用说明：输入两个文件的相对路径/绝对路径，即可判断文件相似性" << endl;
    string f1, f2;
    cout << "请输入第一个文件的路径:" << endl;
    cin >> f1;
    cout << "请输入第二个文件的路径:" << endl;
    cin >> f2;
    Check(f1, f2);
}
