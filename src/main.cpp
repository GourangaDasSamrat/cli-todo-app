#include <iostream>
#include <limits>

#include "../include/FileHandler.h"
#include "../include/Task.h"
#include "../include/TaskManager.h"
#include "../include/UIManager.h"
#include "../include/Utils.h"

void addTaskFlow(TaskManager& manager) {
  std::string title, description, category, dueDate, priorityStr;

  std::cout << "Enter task title: ";
  std::getline(std::cin, title);
  title = Utils::trim(title);

  if (title.empty()) {
    UIManager::printError("Task title cannot be empty!");
    return;
  }

  std::cout << "Enter description (optional): ";
  std::getline(std::cin, description);
  description = Utils::trim(description);

  std::cout << "Enter category (default: General): ";
  std::getline(std::cin, category);
  category = Utils::trim(category);
  if (category.empty())
    category = "General";

  std::cout << "Enter due date (YYYY-MM-DD, optional): ";
  std::getline(std::cin, dueDate);
  dueDate = Utils::trim(dueDate);

  if (!dueDate.empty() && !Utils::isValidDate(dueDate)) {
    UIManager::printError("Invalid date format! Using empty date.");
    dueDate = "";
  }

  std::cout << "Enter priority (High/Medium/Low, default: Medium): ";
  std::getline(std::cin, priorityStr);
  Priority priority = Utils::stringToPriority(priorityStr);

  manager.addTask(title, description, category, dueDate, priority);
  UIManager::printSuccess("Task added successfully!");
}

void viewAllTasksFlow(TaskManager& manager) {
  UIManager::clearScreen();
  UIManager::printHeader("ALL TASKS");

  std::vector<Task*> tasks = manager.getAllTasks();
  UIManager::printTaskList(tasks);
}

void viewByCategoryFlow(TaskManager& manager) {
  std::string category;

  std::cout << "Enter category name: ";
  std::getline(std::cin, category);
  category = Utils::trim(category);

  if (category.empty()) {
    UIManager::printError("Category name cannot be empty!");
    return;
  }

  UIManager::clearScreen();
  UIManager::printHeader("TASKS IN CATEGORY: " + category);

  std::vector<Task*> tasks = manager.getTasksByCategory(category);
  UIManager::printTaskList(tasks);
}

void toggleTaskFlow(TaskManager& manager) {
  std::string idStr;

  std::cout << "Enter task number to toggle: ";
  std::getline(std::cin, idStr);

  if (!Utils::isValidInteger(idStr)) {
    UIManager::printError("Invalid task number!");
    return;
  }

  int taskId = Utils::stringToInt(idStr);

  if (manager.toggleTaskCompletion(taskId)) {
    UIManager::printSuccess("Task status toggled successfully!");
  } else {
    UIManager::printError("Task not found!");
  }
}

void deleteTaskFlow(TaskManager& manager) {
  std::string idStr;

  std::cout << "Enter task number to delete: ";
  std::getline(std::cin, idStr);

  if (!Utils::isValidInteger(idStr)) {
    UIManager::printError("Invalid task number!");
    return;
  }

  int taskId = Utils::stringToInt(idStr);

  if (manager.deleteTask(taskId)) {
    UIManager::printSuccess("Task deleted successfully!");
  } else {
    UIManager::printError("Task not found!");
  }
}

void searchTasksFlow(TaskManager& manager) {
  std::string keyword;

  std::cout << "Enter search keyword: ";
  std::getline(std::cin, keyword);
  keyword = Utils::trim(keyword);

  if (keyword.empty()) {
    UIManager::printError("Search keyword cannot be empty!");
    return;
  }

  UIManager::clearScreen();
  UIManager::printHeader("SEARCH RESULTS: " + keyword);

  std::vector<Task*> tasks = manager.searchTasks(keyword);
  UIManager::printTaskList(tasks);
}

void clearAllTasksFlow(TaskManager& manager, FileHandler& fileHandler) {
  std::string confirmation;

  std::cout << "Are you sure you want to clear ALL tasks? (yes/no): ";
  std::getline(std::cin, confirmation);

  if (Utils::toLowerCase(Utils::trim(confirmation)) == "yes") {
    manager.clearAllTasks();
    fileHandler.clearFile();
    UIManager::printSuccess("All tasks cleared!");
  } else {
    UIManager::printInfo("Operation cancelled.");
  }
}

int main() {
  TaskManager manager;
  FileHandler fileHandler;

  fileHandler.loadTasks(manager);

  std::string choice;
  bool running = true;

  while (running) {
    UIManager::clearScreen();
    UIManager::printHeader("TODO APPLICATION");
    UIManager::printMenu();

    std::cout << "Enter your choice: ";
    std::getline(std::cin, choice);

    if (!Utils::isValidInteger(choice)) {
      UIManager::printError("Invalid input! Please enter a number.");
      UIManager::waitForEnter();
      continue;
    }

    int option = Utils::stringToInt(choice);

    switch (option) {
      case 1:
        addTaskFlow(manager);
        fileHandler.saveTasks(manager);
        UIManager::waitForEnter();
        break;
      case 2:
        viewAllTasksFlow(manager);
        UIManager::waitForEnter();
        break;
      case 3:
        viewByCategoryFlow(manager);
        UIManager::waitForEnter();
        break;
      case 4:
        toggleTaskFlow(manager);
        fileHandler.saveTasks(manager);
        UIManager::waitForEnter();
        break;
      case 5:
        deleteTaskFlow(manager);
        fileHandler.saveTasks(manager);
        UIManager::waitForEnter();
        break;
      case 6:
        searchTasksFlow(manager);
        UIManager::waitForEnter();
        break;
      case 7:
        clearAllTasksFlow(manager, fileHandler);
        UIManager::waitForEnter();
        break;
      case 0:
        fileHandler.saveTasks(manager);
        UIManager::printSuccess("Tasks saved. Goodbye!");
        running = false;
        break;
      default:
        UIManager::printError("Invalid option! Please try again.");
        UIManager::waitForEnter();
    }
  }

  return 0;
}
