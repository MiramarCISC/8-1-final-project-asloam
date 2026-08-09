#ifndef PROJECT_HPP
#define PROJECT_HPP

#include <string>

struct Task {
    int id;
    std::string title;
    std::string category;
    int priority; // 1 (High) to 5 (Low)
    double estimatedHours;
    bool completed;
};

// Linked List Node
struct TaskNode {
    Task data;
    TaskNode* next;
};

const int MIN_PRIORITY = 1;
const int MAX_PRIORITY = 5;

double calculateTotalHours(TaskNode* head);
bool isValidPriority(int priority);
bool isValidHours(double hours);
int getTaskCount(TaskNode* head);
int getCompletedTaskCount(TaskNode* head);
void sortPrioritiesAscending(int priorities[], int count);
void insertTask(TaskNode*& head, Task task);
TaskNode* findTaskById(TaskNode* head, int id);
bool removeTaskById(TaskNode*& head, int id);
void clearTasks(TaskNode*& head);
int loadTasksFromFile(const std::string& filename, TaskNode*& head);
bool saveTasksToFile(const std::string& filename, TaskNode* head);

#endif