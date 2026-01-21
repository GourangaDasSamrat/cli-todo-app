#include "../include/UIManager.h"

#include <ctime>
#include <iomanip>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define BOLD "\033[1m"

void UIManager::clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

int UIManager::getTerminalWidth() {
#ifdef _WIN32
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  return csbi.srWindow.Right - csbi.srWindow.Left + 1;
#else
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return w.ws_col;
#endif
}

void UIManager::printHeader(const std::string& title) {
  int width = getTerminalWidth();
  if (width < 20)
    width = 80;  // fallback

  std::string boxLine = "";
  for (int i = 0; i < width - 2; i++) {
    boxLine += "═";
  }

  std::string top = "╔" + boxLine + "╗";
  std::string bottom = "╚" + boxLine + "╝";

  int padding = (width - 4 - title.length()) / 2;
  std::string middle = "║ " + std::string(padding, ' ') + title +
                       std::string(width - 4 - padding - title.length(), ' ') +
                       " ║";

  std::cout << "\n" << BOLD << CYAN << top << "\n";
  std::cout << middle << "\n";
  std::cout << bottom << RESET << "\n\n";
}

std::string UIManager::getColorCode(Priority priority) {
  switch (priority) {
    case Priority::HIGH:
      return RED;
    case Priority::MEDIUM:
      return YELLOW;
    case Priority::LOW:
      return GREEN;
    default:
      return RESET;
  }
}

std::string UIManager::formatTimestamp(time_t timestamp) {
  if (timestamp == 0)
    return "N/A";

  char buffer[80];
  struct tm* timeinfo = localtime(&timestamp);
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
  return std::string(buffer);
}

void UIManager::printTask(const Task* task, int displayIndex) {
  std::string colorCode = getColorCode(task->getPriority());
  std::string statusMark = task->isCompleted() ? GREEN "[✓]" RESET : "[ ]";

  std::cout << displayIndex << ". " << statusMark << " " << colorCode << BOLD
            << task->getTitle() << RESET << "\n";

  if (!task->getDescription().empty()) {
    std::cout << "   Description: " << task->getDescription() << "\n";
  }

  std::cout << "   Category: " << MAGENTA << task->getCategory() << RESET
            << " | Priority: " << colorCode << task->priorityToString()
            << RESET;

  if (!task->getDueDate().empty()) {
    std::cout << " | Due: " << CYAN << task->getDueDate() << RESET;
  }

  std::cout << "\n   Created: " << formatTimestamp(task->getCreatedAt());

  if (task->isCompleted()) {
    std::cout << " | Completed: " << formatTimestamp(task->getCompletedAt());
  }

  std::cout << "\n\n";
}

void UIManager::printTaskList(const std::vector<Task*>& tasks) {
  if (tasks.empty()) {
    printInfo("No tasks found.");
    return;
  }

  for (size_t i = 0; i < tasks.size(); ++i) {
    printTask(tasks[i], i + 1);
  }
}

void UIManager::printMenu() {
  std::cout << BOLD << "╔══ MENU ══╗\n" << RESET;
  std::cout << " 1. Add Task\n";
  std::cout << " 2. View All Tasks\n";
  std::cout << " 3. View by Category\n";
  std::cout << " 4. Toggle Task Completion\n";
  std::cout << " 5. Delete Task\n";
  std::cout << " 6. Search Tasks\n";
  std::cout << " 7. Clear All Tasks\n";
  std::cout << " 0. Exit\n\n";
}

void UIManager::printSuccess(const std::string& message) {
  std::cout << GREEN << "✓ " << message << RESET << "\n";
}

void UIManager::printError(const std::string& message) {
  std::cout << RED << "✗ " << message << RESET << "\n";
}

void UIManager::printInfo(const std::string& message) {
  std::cout << BLUE << "ℹ " << message << RESET << "\n";
}

void UIManager::waitForEnter() {
  std::cout << "\nPress Enter to continue...";
  std::string dummy;
  std::getline(std::cin, dummy);
}