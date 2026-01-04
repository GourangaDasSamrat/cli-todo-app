#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>

#include "TaskManager.h"

class FileHandler {
   private:
    std::string filename;

   public:
    FileHandler(const std::string& filename = "data/tasks.dat");

    bool saveTasks(TaskManager& manager);
    bool loadTasks(TaskManager& manager);
    bool clearFile();

   private:
    void ensureDataDirectory();
};

#endif
