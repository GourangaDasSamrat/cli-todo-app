#ifndef UTILS_H
#define UTILS_H

#include <string>

#include "Task.h"

class Utils {
 public:
  static bool isValidInteger(const std::string& str);
  static int stringToInt(const std::string& str);
  static Priority stringToPriority(const std::string& str);
  static std::string trim(const std::string& str);
  static std::string toLowerCase(const std::string& str);
  static bool isValidDate(const std::string& date);
};

#endif
