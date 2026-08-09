#include "project.hpp"
#include <iostream>

using namespace std;

int main() {
    TaskNode* head = nullptr;
    
    loadTasksFromFile("data/tasks.txt", head);

    int choice = 0;
    while (choice != 6) {
        cout << "\n=== TO-DO LIST TASK MANAGER ===\n";
        cout << "1. Display All Tasks\n";
        cout << "2. Add New Task\n";
        cout << "3. Remove Task by ID\n";
        cout << "4. Calculate Total Hours\n";
        cout << "5. Save Tasks to File\n";
        cout << "6. Exit\n";
        cout << "Enter choice (1-6): ";
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number between 1 and 6.\n";
            continue;
        }

        if (choice == 1) {
            TaskNode* current = head;
            if (current == nullptr) {
                cout << "No tasks found.\n";
            } else {
                int count = getTaskCount(head);

                TaskNode** taskArray = new TaskNode*[count];
                TaskNode* temp = head;
                for (int i = 0; i < count; i++) {
                    taskArray[i] = temp;
                    temp = temp->next;
                }

                for (int i = 0; i < count - 1; i++) {
                    for (int j = 0; j < count - i - 1; j++) {
                        if (taskArray[j]->data.priority > taskArray[j + 1]->data.priority) {
                            TaskNode* swapTemp = taskArray[j];
                            taskArray[j] = taskArray[j + 1];
                            taskArray[j + 1] = swapTemp;
                        }
                    }
                }

                int* priorityArray = new int[count];
                for (int i = 0; i < count; i++) {
                    priorityArray[i] = taskArray[i]->data.priority;
                }
                sortPrioritiesAscending(priorityArray, count);

                cout << "\nSorted Priorities Summary: ";
                for (int i = 0; i < count; i++) {
                    cout << priorityArray[i] << (i == count - 1 ? "" : ", ");
                }
                cout << "\n";

                cout << "\n--- Current Tasks (Ordered by Priority) ---\n";
                for (int i = 0; i < count; i++) {
                    cout << "ID: " << taskArray[i]->data.id
                         << " | Title: " << taskArray[i]->data.title
                         << " | Category: " << taskArray[i]->data.category
                         << " | Priority: " << taskArray[i]->data.priority
                         << " | Hours: " << taskArray[i]->data.estimatedHours
                         << " | Done: " << (taskArray[i]->data.completed ? "Yes" : "No") << "\n";
                }

                delete[] priorityArray;
                delete[] taskArray;
            }
            
        } else if (choice == 2) {
            Task newTask;

            cout << "Enter Task ID (integer): ";
            cin >> newTask.id;

            cout << "Enter Title (single word or use _): ";
            cin >> newTask.title;

            cout << "Enter Category: ";
            cin >> newTask.category;

            cout << "Enter Priority (1-5): ";
            cin >> newTask.priority;
            if (!isValidPriority(newTask.priority)) {
                cout << "Invalid priority. Setting to 3 (Default).\n";
                newTask.priority = 3;
            }

            cout << "Enter Estimated Hours: ";
            cin >> newTask.estimatedHours;
            if (!isValidHours(newTask.estimatedHours)) {
                cout << "Invalid hours. Setting to 1.0.\n";
                newTask.estimatedHours = 1.0;
            }

            newTask.completed = false;
            insertTask(head, newTask);
            cout << "Task added successfully.\n";

        } else if (choice == 3) {
            int removeId;
            cout << "Enter Task ID to remove: ";
            cin >> removeId;
            if (removeTaskById(head, removeId)) {
                cout << "Task " << removeId << " removed successfully.\n";
            } else {
                cout << "Task ID not found.\n";
            }

        } else if (choice == 4) {
            double totalHours = calculateTotalHours(head);
            cout << "Total Estimated Hours: " << totalHours << " hrs\n";

        } else if (choice == 5) {
            if (saveTasksToFile("data/tasks.txt", head)) {
                cout << "Tasks successfully saved to data/tasks.txt\n";
            } else {
                cout << "Failed to save tasks to file.\n";
            }

        } else if (choice == 6) {
            cout << "Exiting program. Cleaning up memory...\n";
        } else {
            cout << "Invalid option. Please choose between 1 and 6.\n";
        }
    }

    clearTasks(head);
}