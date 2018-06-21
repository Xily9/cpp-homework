#pragma once
#include <vector>
#include <string>

class Check {
public:
    Check(const std::string& file1, const std::string& file2);
    class CheckException:std::runtime_error {
    public:
        explicit CheckException(const std::string& _Message)
            : runtime_error(_Message) {
        }
    };
private:
    std::vector<std::string> vec1;
    std::vector<std::string> vec2;
    void parse(std::ifstream& fin, std::vector<std::string>& vec2) const;
    void analyze();
};
