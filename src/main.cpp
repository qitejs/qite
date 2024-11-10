#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <cctype>
#include <cmath>

class Qite {
private:
    std::map<std::string, double> variables;

    bool isNumber(const std::string& str) {
        std::istringstream iss(str);
        double num;
        iss >> std::noskipws >> num;
        return iss.eof() && !iss.fail();
    }

    std::vector<std::string> tokenize(const std::string& input) {
        std::vector<std::string> tokens;
        std::string current;
        bool inString = false;
        bool inConsoleLog = false;

        for (size_t i = 0; i < input.length(); i++) {
            char c = input[i];

            // Handle strings
            if (c == '"' || c == '\'') {
                if (!inString) {
                    if (!current.empty()) {
                        tokens.push_back(current);
                        current.clear();
                    }
                    inString = true;
                    current += c;
                } else {
                    current += c;
                    tokens.push_back(current);
                    current.clear();
                    inString = false;
                }
                continue;
            }

            if (inString) {
                current += c;
                continue;
            }

            // Handle console.log
            if (input.substr(i, 11) == "console.log(" && !inConsoleLog) {
                if (!current.empty()) {
                    tokens.push_back(current);
                    current.clear();
                }
                tokens.push_back("console.log");
                i += 10;
                inConsoleLog = true;
                continue;
            }

            if (std::isspace(c)) {
                if (!current.empty()) {
                    tokens.push_back(current);
                    current.clear();
                }
            }
            else if (c == '=' || c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == ';') {
                if (!current.empty()) {
                    tokens.push_back(current);
                    current.clear();
                }
                if (c != ';') {  // Skip semicolons in tokens
                    tokens.push_back(std::string(1, c));
                }
            }
            else {
                current += c;
            }
        }

        if (!current.empty()) {
            tokens.push_back(current);
        }

        return tokens;
    }

    double evaluateExpression(const std::vector<std::string>& tokens, size_t& pos) {
        double result = 0;
        double currentNumber = 0;
        char operation = '+';

        while (pos < tokens.size() && tokens[pos] != ")") {
            std::string token = tokens[pos];

            if (token == "+" || token == "-" || token == "*" || token == "/") {
                operation = token[0];
            }
            else {
                double value;
                if (isNumber(token)) {
                    value = std::stod(token);
                }
                else if (variables.find(token) != variables.end()) {
                    value = variables[token];
                }
                else {
                    value = 0;  // Undefined variables are treated as 0
                }

                switch (operation) {
                    case '+': result += value; break;
                    case '-': result -= value; break;
                    case '*': result *= value; break;
                    case '/': result /= value; break;
                }
            }
            pos++;
        }

        return result;
    }

public:
    void executeFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            executeLine(line);
        }
    }

    void executeLine(const std::string& line) {
        std::vector<std::string> tokens = tokenize(line);

        for (size_t i = 0; i < tokens.size(); i++) {
            if (tokens[i] == "console.log") {
                i++;  // Skip the opening parenthesis
                std::string output;
                while (i < tokens.size() && tokens[i] != ")") {
                    if (tokens[i][0] == '"' || tokens[i][0] == '\'') {
                        // String literal
                        output += tokens[i].substr(1, tokens[i].length() - 2);
                    }
                    else if (variables.find(tokens[i]) != variables.end()) {
                        // Variable
                        output += std::to_string(variables[tokens[i]]);
                    }
                    else if (isNumber(tokens[i])) {
                        // Number
                        output += tokens[i];
                    }
                    i++;
                }
                std::cout << output << std::endl;
            }
            else if (i + 1 < tokens.size() && tokens[i + 1] == "=") {
                // Variable assignment
                std::string varName = tokens[i];
                i += 2;  // Skip the equals sign
                double value = evaluateExpression(tokens, i);
                variables[varName] = value;
            }
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input.js>" << std::endl;
        return 1;
    }

    Qite interpreter;
    interpreter.executeFile(argv[1]);
    return 0;
}