#include "../include/FileHandler.h"

#include <sys/stat.h>

#include <fstream>

#ifdef _WIN32
#include <direct.h>
#define mkdir _mkdir
#else
#include <sys/types.h>
#endif

FileHandler::FileHandler(const std::string& filename) : filename(filename) {
    ensureDataDirectory();
}

void FileHandler::ensureDataDirectory() {
    struct stat info;
    if (stat("data", &info) != 0) {
#ifdef _WIN32
        mkdir("data");
#else
        mkdir("data", 0755);
#endif
    }
}

bool FileHandler::saveTasks(TaskManager& manager) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    file << manager.getNextId() << std::endl;

    for (Task* task : manager.getAllTasks()) {
        file << task->serialize() << std::endl;
    }

    file.close();
    return true;
}

bool FileHandler::loadTasks(TaskManager& manager) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    std::string line;
    if (std::getline(file, line)) {
        try {
            manager.setNextId(std::stoi(line));
        } catch (...) {
            manager.setNextId(1);
        }
    }

    while (std::getline(file, line)) {
        try {
            Task task = Task::deserialize(line);
            manager.addTask(task.getTitle(), task.getDescription(), task.getCategory(),
                            task.getDueDate(), task.getPriority());

            Task* loadedTask = manager.getTask(task.getId());
            if (loadedTask && task.isCompleted()) {
                loadedTask->markAsCompleted();
            }
        } catch (...) {
            continue;
        }
    }

    file.close();
    return true;
}

bool FileHandler::clearFile() {
    std::ofstream file(filename, std::ofstream::trunc);
    if (!file.is_open()) {
        return false;
    }
    file.close();
    return true;
}
