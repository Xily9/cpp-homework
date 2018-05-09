#include "file.h"
#include <utility>
#include <fstream>
#include "utils.h"
#include <sstream>
#include <iostream>
using namespace std;

File& File::operator=(const int& i) {
    str = to_string(i);
    return *this;
}

File& File::operator=(const string& stri) {
    str = stri;
    return *this;
}

File& File::operator=(const File& file) {
    str = file.str;
    data = file.data;
    down(file.level - level);
    return *this;
}

File& File::operator=(const bool& boolean) {
    if (boolean) {
        str = "true";
    } else {
        str = "false";
    }
    return *this;
}

File& File::operator=(const double& db) {
    str = to_string(db);
    return *this;
}

File::File(const string& str, int level): str(str), level(level) {
    string temp;
    stringstream stream;
    switch (level) {
        case 1:
            stream << str;
            while (getline(stream, temp)) {
                data.emplace_back(temp, level + 1);
            }
            break;
        case 2:
            if (int(str.find(' ')) != -1) {
                stream << str;
                while (stream >> temp) {
                    data.emplace_back(temp, level + 1);
                }
            }
            break;
        case 3:
            if (int(str.find(',')) != -1) {
                vector<string> strs = split(str, ",");
                for (string& stra : strs) {
                    data.emplace_back(stra, level + 1);
                }
            }
            break;
        case 4:
            break;
        default:
            throw exception("error!");
    }
}

File::File(const string& str) : str(str), level(1) {
    data.emplace_back(str, level + 1);
}

File::File() : level(1) {
}

File File::reader(const string& fileName) {
    ifstream in(fileName);
    if (in.is_open()) {
        const string str((std::istreambuf_iterator<char>(in)),
                         std::istreambuf_iterator<char>());
        return File(str, 1);
    } else {
        throw exception("文件打开失败!");
    }
}

bool File::writer(const string& fileName, File& file) {
    file.toString();
    ofstream out(fileName);
    const auto result = bool(out << file.str);
    out.close();
    return result;
}

File& File::get(const unsigned index) {
    return data.at(index);
}

File File::get(const unsigned index) const {
    return data.at(index);
}

File&& File::get(const string& key) {
    for (File& file : data) {
        if (file[0].asString() == key) {
            return move(file[1]);
        }
    }
    return move(File());
}

File File::get(const string& key) const {
    for (File file : data) {
        if (file[0].asString() == key) {
            return file[1];
        }
    }
    return File();
}

void File::pop_back() {
    data.pop_back();
}

void File::append(File file) {
    file.down(file.level - level - 1);
    file.level -= file.level - level - 1;
    data.push_back(file);
}

vector<File>::iterator File::begin() {
    return data.begin();
}

vector<File>::iterator File::end() {
    return data.end();
}

vector<File>::const_iterator File::begin() const {
    return data.begin();
}

vector<File>::const_iterator File::end() const {
    return data.end();
}

void File::removeIndex(const unsigned index) {
    const std::vector<File>::iterator it = data.begin() + index;
    data.erase(it);
}


size_t File::size() const {
    return data.size();
}

bool File::empty() const {
    return data.empty();
}

string File::asString() const {
    return str;
}

bool File::asBool() const {
    if (str == "true") {
        return true;
    } else if (str == "false") {
        return false;
    } else {
        throw exception("解析bool类型时发生错误!");
    }
}

int File::asInt() const {
    return strToInt(str);
}

double File::asDouble() const {
    return strToDouble(str);
}

bool File::isNull() const {
    return data.empty() && str.empty();
}

File& File::operator[](unsigned index) {
    if (data.size() <= index) {
        for (unsigned i = data.size(); i <= index; i++) {
            data.emplace_back();
        }
    }
    return data.at(index);
}

File File::operator[](unsigned index) const {
    return data.at(index);
}

File&& File::operator[](const string& key) {
    return get(key);
}

File File::operator[](const string& key) const {
    return get(key);
}

bool File::operator==(File file) const {
    return str == file.str;
}

void File::toString() {
    switch (level) {
        case 1:
            str = join("\n");
            break;
        case 2:
            str = join(" ");
            break;
        case 3:
            str = join(",");
        case 4:
            break;
        default:
            throw exception("error!");
    }
}

string File::join(const string& pattern) {
    string result;
    bool ishead = true;
    for (File& file : data) {
        if (file.size() > 1) {
            file.toString();
        }
        if (!ishead) {
            result += pattern + file.str;
        } else {
            result += file.str;
            ishead = false;
        }
    }
    return result;
}

void File::down(int level) {
    for (File& file : data) {
        if (file.size() > 1) {
            file.down(level);
        }
        file.level -= level;
    }
}
