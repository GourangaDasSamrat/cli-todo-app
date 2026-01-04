#include "../include/Task.h"

#include <iomanip>
#include <sstream>
#include <vector>

Task::Task(int id, const std::string& title, const std::string& description,
           const std::string& category, const std::string& dueDate, Priority priority)
    : id(id),
      title(title),
      description(description),
      category(category),
      dueDate(dueDate),
      priority(priority),
      completed(false),
      createdAt(time(nullptr)),
      completedAt(0) {}

void Task::markAsCompleted() {
    completed = true;
    completedAt = time(nullptr);
}

void Task::markAsIncomplete() {
    completed = false;
    completedAt = 0;
}

std::string Task::priorityToString() const {
    switch (priority) {
        case Priority::LOW:
            return "Low";
        case Priority::MEDIUM:
            return "Medium";
        case Priority::HIGH:
            return "High";
        default:
            return "Unknown";
    }
}

std::string Task::serialize() const {
    std::stringstream ss;
    ss << id << "|" << title << "|" << description << "|" << category << "|" << dueDate << "|"
       << static_cast<int>(priority) << "|" << completed << "|" << createdAt << "|" << completedAt;
    return ss.str();
}

Task Task::deserialize(const std::string& data) {
    std::stringstream ss(data);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(ss, token, '|')) {
        tokens.push_back(token);
    }

    if (tokens.size() < 9) {
        throw std::runtime_error("Invalid task data");
    }

    int id = std::stoi(tokens[0]);
    Priority priority = static_cast<Priority>(std::stoi(tokens[5]));

    Task task(id, tokens[1], tokens[2], tokens[3], tokens[4], priority);
    task.completed = (tokens[6] == "1");
    task.createdAt = std::stoll(tokens[7]);
    task.completedAt = std::stoll(tokens[8]);

    return task;
}
