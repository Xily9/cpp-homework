#include "function.h"
#include <algorithm>
using namespace std;
/**
 * �ַ����ָ�
 * @param str ԭʼ�ַ���
 * @param pattern �ָ���
 * @return �ָ����ַ�������
 */
vector<string> split(string str, const string& pattern) {
    vector<string> result;
    str += pattern; //��չ�ַ����Է������  
    const string::size_type size = str.size();
    for (string::size_type i = 0; i < size; i++) {
        const string::size_type pos = str.find(pattern, i);
        if (pos < size) {
            const std::string s = str.substr(i, pos - i);
            result.push_back(s);
            i = pos + pattern.size() - 1;
        }
    }
    return result;
}
/**
 * �ַ������ƾ����㷨<br/>
 * ժ������
 * @param source ԭʼ�ַ���
 * @param target ��֮�Ƚϵ��ַ���
 * @return ���ƾ���
 */
int ldistance(const string& source, const string& target) {
    //step 1

    int n = source.length();
    int m = target.length();
    if (m == 0) return n;
    if (n == 0) return m;
    //Construct a matrix
    typedef vector< vector<int> >  Tmatrix;
    Tmatrix matrix(n + 1);
    for (int i = 0; i <= n; i++)  matrix[i].resize(m + 1);

    //step 2 Initialize

    for (int i = 1; i <= n; i++) matrix[i][0] = i;
    for (int i = 1; i <= m; i++) matrix[0][i] = i;

    //step 3
    for (int i = 1; i <= n; i++) {
        const char si = source[i - 1];
        //step 4
        for (int j = 1; j <= m; j++) {

            const char dj = target[j - 1];
            //step 5
            int cost;
            if (si == dj) {
                cost = 0;
            } else {
                cost = 1;
            }
            //step 6
            const int above = matrix[i - 1][j] + 1;
            const int left = matrix[i][j - 1] + 1;
            const int diag = matrix[i - 1][j - 1] + cost;
            matrix[i][j] = min(above, min(left, diag));

        }
    }//step7
    return matrix[n][m];
}