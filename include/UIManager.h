#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <string>
#include <vector>

#include "Task.h"

class UIManager {
 public:
  static void clearScreen();
  static void printHeader(const std::string& title);
  static void printTask(const Task* task, int displayIndex);
  static void printTaskList(const std::vector<Task*>& tasks);
  static void printMenu();
  static void printSuccess(const std::string& message);
  static void printError(const std::string& message);
  static void printInfo(const std::string& message);
  static void waitForEnter();

 private:
  static std::string getColorCode(Priority priority);
  static std::string formatTimestamp(time_t timestamp);
  static int getTerminalWidth();
};

#endif
