#include "Qite.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

#include "Interpreter.hpp"

void Qite::execute(const std::string& code) {
  // Create maps for variables and arrays
  std::unordered_map<std::string, std::string> variables;
  std::unordered_map<std::string, std::vector<std::string>> arrays;

  // Pass the maps to the Interpreter constructor
  Interpreter interpreter(variables, arrays);
  interpreter.run(code);
}

void Qite::executeFromFile(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "\033[1;31mError: no filename provided\033[0m" << std::endl;
    return;
  }

  std::stringstream buffer;
  buffer << file.rdbuf();           // Read the entire file into a stringstream
  std::string code = buffer.str();  // Convert stringstream to string
  execute(code);                    // Pass the string to the execute method
}