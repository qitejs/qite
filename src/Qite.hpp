#ifndef QITE_HPP
#define QITE_HPP

#include <string>
#include <unordered_map>
#include <vector>

class Qite {
 public:
  void execute(const std::string& code);
  void executeFromFile(const std::string& filename);
};

#endif  // QITE_H
