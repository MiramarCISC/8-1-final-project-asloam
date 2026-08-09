#include "project.hpp"
#include <iostream>
#include <fstream>

using namespace std;


double calculateTotalHours(TaskNode* head) {
    double total = 0.0;
    TaskNode* current = head;

    while (current != nullptr) {
        total += current->data.estimatedHours;
        current = current->next;
    }

    return total;
}

bool isValidPriority(int priority) {
    return priority >= MIN_PRIORITY && priority <= MAX_PRIORITY;
}

bool isValidHours(double hours) {
    return hours > 0.0;
}

int getTaskCount(TaskNode* head) {
    int count = 0;
    TaskNode* current = head;

    while (current != nullptr) {
        count++;
        current = current->next;
    }

    return count;
}

int getCompletedTaskCount(TaskNode* head) {
    int count = 0;
    TaskNode* current = head;

    while (current != nullptr) {
        if (current->data.completed) {
            count++;
        }
        current = current->next;
    }

    return count;
}

void sortPrioritiesAscending(int priorities[], int count) {
    if (priorities == nullptr || count <= 1) {
        return;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (priorities[j] > priorities[j + 1]) {
                int temp = priorities[j];
                priorities[j] = priorities[j + 1];
                priorities[j + 1] = temp;
            }
        }
    }
}

void insertTask(TaskNode*& head, Task task) {
    TaskNode* newNode = new TaskNode;
    newNode->data = task;
    newNode->next = head;
    head = newNode;
}

TaskNode* findTaskById(TaskNode* head, int id) {
    TaskNode* current = head;

    while (current != nullptr) {
        if (current->data.id == id) {
            return current;
        }
        current = current->next;
    }

    return nullptr;
}

bool removeTaskById(TaskNode*& head, int id) {
    if (head == nullptr) {
        return false;
    }

    if (head->data.id == id) {
        TaskNode* temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    TaskNode* current = head;
    while (current->next != nullptr && current->next->data.id != id) {
        current = current->next;
    }

    if (current->next != nullptr) {
        TaskNode* temp = current->next;
        current->next = temp->next;
        delete temp;
        return true;
    }

    return false;
}

void clearTasks(TaskNode*& head) {
    TaskNode* current = head;
    while (current != nullptr) {
        TaskNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
}

int loadTasksFromFile(const string& filename, TaskNode*& head) {
    ifstream input(filename);
    if (!input.is_open()) {
        return 0;
    }

    clearTasks(head);
    int count = 0;
    Task t;

    while (input >> t.id >> t.title >> t.category >> t.priority >> t.estimatedHours >> t.completed) {
        insertTask(head, t);
        count++;
    }

    input.close();
    return count;
}

bool saveTasksToFile(const string& filename, TaskNode* head) {
    ofstream output(filename);
    if (!output.is_open()) {
        return false;
    }

    TaskNode* current = head;
    while (current != nullptr) {
        output << current->data.id << " "
               << current->data.title << " "
               << current->data.category << " "
               << current->data.priority << " "
               << current->data.estimatedHours << " "
               << current->data.completed << "\n";
        current = current->next;
    }

    output.close();
    return true;
}