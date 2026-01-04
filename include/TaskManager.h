#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <memory>
#include <vector>

#include "Task.h"

class TaskManager {
   private:
    std::vector<std::unique_ptr<Task>> tasks;
    int nextId;

   public:
    TaskManager();

    void addTask(const std::string& title, const std::string& description = "",
                 const std::string& category = "General", const std::string& dueDate = "",
                 Priority priority = Priority::MEDIUM);

    bool deleteTask(int id);
    bool toggleTaskCompletion(int id);
    Task* getTask(int id);
    std::vector<Task*> getAllTasks();
    std::vector<Task*> getTasksByCategory(const std::string& category);
    std::vector<Task*> searchTasks(const std::string& keyword);
    void clearAllTasks();

    int getNextId() const { return nextId; }
    void setNextId(int id) { nextId = id; }
};

#endif
