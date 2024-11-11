#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <string>
#include <unordered_map>
#include <vector>

class Interpreter {
public:
    Interpreter(std::unordered_map<std::string, std::string>& vars,
                std::unordered_map<std::string, std::vector<std::string>>& arrs);
    void run(const std::string& code);

private:
    void parseLine(const std::string& line);
    void executeConsoleLog(const std::string& arg);
    void declareVariable(const std::string& name, const std::string& value);
    void declareArray(const std::string& name, const std::vector<std::string>& values);

    std::unordered_map<std::string, std::string>& variables;
    std::unordered_map<std::string, std::vector<std::string>>& arrays;
};

#endif // INTERPRETER_H
