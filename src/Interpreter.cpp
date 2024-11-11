#include "Interpreter.hpp"

#include <algorithm>
#include <iostream>
#include <regex>
#include <sstream>

Interpreter::Interpreter(
    std::unordered_map<std::string, std::string>& vars,
    std::unordered_map<std::string, std::vector<std::string>>& arrs)
    : variables(vars), arrays(arrs) {}

void Interpreter::run(const std::string& code) {
  std::istringstream stream(code);
  std::string line;
  while (std::getline(stream, line)) {
    parseLine(line);
  }
}

void Interpreter::parseLine(const std::string& line) {
  std::regex consoleLogRegex(R"(console\.log\(\s*([^;]+)\s*\);?)");
  std::regex variableRegex(R"((var|const|let)\s+(\w+)\s*=\s*([^;]+);?)");
  std::regex arrayRegex(R"((\w+)\s*=\s*\[([^\]]+)\];?)");

  std::smatch match;

  // Check for console.log
  if (std::regex_search(line, match, consoleLogRegex)) {
    std::string arg = match[1];
    executeConsoleLog(arg);
  }
  // Check for variable declaration
  else if (std::regex_search(line, match, variableRegex)) {
    std::string name = match[2];
    std::string value = match[3];
    // Trim whitespace
    name.erase(std::remove_if(name.begin(), name.end(), ::isspace), name.end());
    value.erase(std::remove_if(value.begin(), value.end(), ::isspace),
                value.end());
    // Remove quotes if they exist
    if (value.front() == '"' && value.back() == '"') {
      value = value.substr(1, value.size() - 2);
    } else if (value.front() == '\'' && value.back() == '\'') {
      value = value.substr(1, value.size() - 2);
    } else if (value.front() == '`' && value.back() == '`') {
      value = value.substr(1, value.size() - 2);
    }
    declareVariable(name, value);
  }
  // Check for array declaration
  else if (std::regex_search(line, match, arrayRegex)) {
    std::string name = match[1];
    std::string values = match[2];
    std::vector<std::string> arrayValues;
    std::istringstream ss(values);
    std::string item;
    while (std::getline(ss, item, ',')) {
      item.erase(std::remove_if(item.begin(), item.end(), ::isspace),
                 item.end());  // Trim whitespace
      arrayValues.push_back(item);
    }
    declareArray(name, arrayValues);
  }
}

void Interpreter::executeConsoleLog(const std::string& arg) {
  std::string processedArg = arg;

  // Remove surrounding quotes if they exist
  if ((processedArg.front() == '"' && processedArg.back() == '"') ||
      (processedArg.front() == '\'' && processedArg.back() == '\'') ||
      (processedArg.front() == '`' && processedArg.back() == '`')) {
    processedArg = processedArg.substr(1, processedArg.size() - 2);
  }

  // Check if the argument is a variable
  if (variables.find(processedArg) != variables.end()) {
    std::cout << variables[processedArg] << std::endl;
  } else if (arrays.find(processedArg) != arrays.end()) {
    std::cout << "[";
    for (size_t i = 0; i < arrays[processedArg].size(); ++i) {
      std::cout << arrays[processedArg][i];
      if (i < arrays[processedArg].size() - 1) {
        std::cout << ", ";
      }
    }
    std::cout << "]" << std::endl;
  } else {
    std::cout << processedArg << std::endl;  // Print the argument directly if
                                             // it's not a variable or array
  }
}

void Interpreter::declareVariable(const std::string& name,
                                  const std::string& value) {
  variables[name] = value;
}

void Interpreter::declareArray(const std::string& name,
                               const std::vector<std::string>& values) {
  arrays[name] = values;
}