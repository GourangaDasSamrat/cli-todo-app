#include "../include/TaskManager.h"

#include <algorithm>

#include "../include/Utils.h"

TaskManager::TaskManager() : nextId(1) {}

void TaskManager::addTask(const std::string& title, const std::string& description,
                          const std::string& category, const std::string& dueDate,
                          Priority priority) {
    tasks.push_back(
        std::make_unique<Task>(nextId++, title, description, category, dueDate, priority));
}

bool TaskManager::deleteTask(int id) {
    auto it = std::find_if(tasks.begin(), tasks.end(),
                           [id](const std::unique_ptr<Task>& task) { return task->getId() == id; });

    if (it != tasks.end()) {
        tasks.erase(it);
        return true;
    }
    return false;
}

bool TaskManager::toggleTaskCompletion(int id) {
    Task* task = getTask(id);
    if (task) {
        if (task->isCompleted()) {
            task->markAsIncomplete();
        } else {
            task->markAsCompleted();
        }
        return true;
    }
    return false;
}

Task* TaskManager::getTask(int id) {
    auto it = std::find_if(tasks.begin(), tasks.end(),
                           [id](const std::unique_ptr<Task>& task) { return task->getId() == id; });

    return (it != tasks.end()) ? it->get() : nullptr;
}

std::vector<Task*> TaskManager::getAllTasks() {
    std::vector<Task*> result;
    for (auto& task : tasks) {
        result.push_back(task.get());
    }
    return result;
}

std::vector<Task*> TaskManager::getTasksByCategory(const std::string& category) {
    std::vector<Task*> result;
    std::string lowerCategory = Utils::toLowerCase(category);

    for (auto& task : tasks) {
        if (Utils::toLowerCase(task->getCategory()) == lowerCategory) {
            result.push_back(task.get());
        }
    }
    return result;
}

std::vector<Task*> TaskManager::searchTasks(const std::string& keyword) {
    std::vector<Task*> result;
    std::string lowerKeyword = Utils::toLowerCase(keyword);

    for (auto& task : tasks) {
        std::string lowerTitle = Utils::toLowerCase(task->getTitle());
        std::string lowerDesc = Utils::toLowerCase(task->getDescription());

        if (lowerTitle.find(lowerKeyword) != std::string::npos ||
            lowerDesc.find(lowerKeyword) != std::string::npos) {
            result.push_back(task.get());
        }
    }
    return result;
}

void TaskManager::clearAllTasks() {
    tasks.clear();
    nextId = 1;
}
