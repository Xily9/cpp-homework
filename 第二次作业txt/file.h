#pragma once
#include <string>
#include <vector>
using namespace std;
class File {
public:
    explicit File(const string& str, int level);
    File(const string & str);
    File();
    static File reader(const string& fileName);
    static bool writer(const string& fileName,File& file);
    File& get(const unsigned index);
    File get(const unsigned index) const;
    File&& get(const string& key);
    File get(const string& key) const;
    void pop_back();
    void append(File file);
    vector<File>::iterator begin();
    vector<File>::iterator end();
    vector<File>::const_iterator begin() const;
    vector<File>::const_iterator end() const;
    void removeIndex(unsigned index);
    size_t size() const;
    bool empty() const;
    string asString() const;
    bool asBool() const;
    int asInt() const;
    double asDouble() const;
    bool isNull() const;
    File& operator[](unsigned index);
    File operator[](unsigned index) const;
    File&& operator[](const string& key);
    File operator[](const string& key) const;
    bool operator==(File file) const;
    File& operator=(const int& i);
    File& operator=(const string& stri);
    File& operator=(const File& file);
    File& operator=(const bool& boolean);
    File& operator=(const double& db);
private:
    vector<File> data;
    string str;
    int level;
    void toString();
    string join(const string& pattern);
    void down(int level);
};