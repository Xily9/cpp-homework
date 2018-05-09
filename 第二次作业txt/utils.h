#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <vector>
using namespace std;
char getPersonId18(const string& s);
tm* getTime();
bool isLeapYear(const int year);
bool checkDate(int year, int month, int day);
bool isInt(const string& str);
int strToInt(const string& str);
int strToDouble(const string& str);
int findInInt(int all, int in);
bool isAllChinese(const string& str);
int getConsoleWidth();
void setConsoleTitle(const char* title);
char getKey();
vector<string> split(string str, const string& pattern);
/**
* 快速排序
* @tparam T 任意类型
* @tparam U lambda
* @param array 待排序的集合
* @param left 左下标
* @param right 右下标
* @param complete 比较函数
*/
template <typename T, typename U>
void quickSort(T& array, int left, int right, U complete) {
    //快速排序之前先判断一下当前待排序数组元素个数是不是大于1 否则就没有必要排序
    if (left >= right) {
        //直接退出排序代码  没有必要进行排序了
        return;
    }
    //开始进行快排算法
    //首先我们先保存left索引对应的数据  当前数据作为切割数组的轴
    T piovt = array[left];
    //定义临时变量保存数组左端的索引
    int leftIndex = left;
    int rightIndex = right;
    while (leftIndex < rightIndex) {
        //现在我们通过循环从右边开始搜索一个比轴值小的数据
        while (leftIndex < rightIndex) {
            //如果右边的数大于当前的参数轴值
            if (complete(piovt, array[rightIndex]) <= 0) {
                //右端索引指示器左移
                rightIndex--;
            } else {
                //说明我们右端出现比轴值更大的数据
                //这个时候我们就可以把这个更大的数据填充到索引轴索引对应的地方
                array[leftIndex] = array[rightIndex];
                leftIndex++;
                //我们需要跳出循环了当前工作完毕
                break;
            }
        }
        //从左边开始搜索一个比轴值更大的数填写上次留下的坑
        while (leftIndex < rightIndex) {
            //如果左边的数据小于轴值 我们索引指示器就往右走
            if (complete(piovt, array[leftIndex]) >= 0) {
                leftIndex++;
            } else {
                //说明我们在左端找到了比轴值更大的数据
                array[rightIndex] = array[leftIndex];
                rightIndex--;
                break;
            }
        }
    }
    //此时leftIndex=rightIndex,可以把之前记录的值放在这个位置
    array[leftIndex] = piovt;
    //递归调用，把leftIndex前面的完成排序
    quickSort(array, left, leftIndex - 1, complete);
    //递归调用，把rightIndex后面的完成排序
    quickSort(array, rightIndex + 1, right, complete);
}
