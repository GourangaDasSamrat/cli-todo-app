#ifndef TASK_H
#define TASK_H

#include <ctime>
#include <string>

enum class Priority { LOW, MEDIUM, HIGH };

class Task {
 private:
  int id;
  std::string title;
  std::string description;
  std::string category;
  std::string dueDate;
  Priority priority;
  bool completed;
  time_t createdAt;
  time_t completedAt;

 public:
  Task(
    int id,
    const std::string& title,
    const std::string& description = "",
    const std::string& category = "General",
    const std::string& dueDate = "",
    Priority priority = Priority::MEDIUM);

  // Getters
  int getId() const {
    return id;
  }
  std::string getTitle() const {
    return title;
  }
  std::string getDescription() const {
    return description;
  }
  std::string getCategory() const {
    return category;
  }
  std::string getDueDate() const {
    return dueDate;
  }
  Priority getPriority() const {
    return priority;
  }
  bool isCompleted() const {
    return completed;
  }
  time_t getCreatedAt() const {
    return createdAt;
  }
  time_t getCompletedAt() const {
    return completedAt;
  }

  // Setters
  void setTitle(const std::string& t) {
    title = t;
  }
  void setDescription(const std::string& d) {
    description = d;
  }
  void setCategory(const std::string& c) {
    category = c;
  }
  void setDueDate(const std::string& d) {
    dueDate = d;
  }
  void setPriority(Priority p) {
    priority = p;
  }
  void markAsCompleted();
  void markAsIncomplete();

  std::string priorityToString() const;
  std::string serialize() const;
  static Task deserialize(const std::string& data);
};

#endif
