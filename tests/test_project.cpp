#include "project.hpp"
#include <cassert>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// Helper function for floating-point comparisons
bool nearlyEqual(double actual, double expected, double tolerance = 0.0001) {
    return fabs(actual - expected) <= tolerance;
}

// Helper to create a temporary test data file
void createTestTasksFile(const string& filename) {
    ofstream out(filename);

    // Format: id title category priority estimatedHours completed
    out << "1 Homework School 1 2.5 0" << endl;
    out << "2 Grocery Personal 2 1.0 1" << endl;
    out << "3 Project Work 3 5.0 0" << endl;

    out.close();
}

// Week 1
void testWeek1() {
    // Test calculateTotalHours
    TaskNode* head = nullptr;
    assert(nearlyEqual(calculateTotalHours(head), 0.0));

    Task t1{1, "Task1", "School", 3, 2.5, false};
    Task t2{2, "Task2", "Work", 1, 4.0, false};

    insertTask(head, t1);
    insertTask(head, t2);

    assert(nearlyEqual(calculateTotalHours(head), 6.5));

    clearTasks(head);
}

// Week 2
void testWeek2() {
    // Priority validation
    assert(isValidPriority(MIN_PRIORITY));
    assert(isValidPriority(MAX_PRIORITY));
    assert(isValidPriority(3));
    assert(!isValidPriority(MIN_PRIORITY - 1));
    assert(!isValidPriority(MAX_PRIORITY + 1));

    // Hours validation
    assert(isValidHours(0.1));
    assert(isValidHours(100.0));
    assert(!isValidHours(0.0));
    assert(!isValidHours(-2.5));
}

// Week 3
void testWeek3() {
    TaskNode* head = nullptr;

    assert(getTaskCount(head) == 0);
    assert(getCompletedTaskCount(head) == 0);

    Task t1{1, "Math", "School", 1, 1.0, false};
    Task t2{2, "Physics", "School", 2, 2.0, true};
    Task t3{3, "CS", "School", 3, 3.0, true};

    insertTask(head, t1);
    insertTask(head, t2);
    insertTask(head, t3);

    assert(getTaskCount(head) == 3);
    assert(getCompletedTaskCount(head) == 2);

    clearTasks(head);
}

// Week 4
void testWeek4() {
    // Array sorting
    int priorities[] = {5, 2, 8, 1, 3};
    sortPrioritiesAscending(priorities, 5);

    assert(priorities[0] == 1);
    assert(priorities[1] == 2);
    assert(priorities[2] == 3);
    assert(priorities[3] == 5);
    assert(priorities[4] == 8);
}

// Week 5
void testWeek5() {
    Task t{1, "Homework", "School", 2, 3.0, false};

    // Verify struct fields and string properties
    assert(t.id == 1);
    assert(t.title == "Homework");
    assert(t.category == "School");
    assert(t.priority == 2);
    assert(nearlyEqual(t.estimatedHours, 3.0));
    assert(!t.completed);
}

// Week 6
void testWeek6() {
    // Linked List operations
    TaskNode* head = nullptr;

    Task t1{101, "Math_HW", "School", 1, 2.0, false};
    Task t2{102, "Physics_Lab", "School", 2, 4.0, false};

    insertTask(head, t1);
    insertTask(head, t2);

    TaskNode* found = findTaskById(head, 101);
    assert(found != nullptr);
    assert(found->data.title == "Math_HW");
    assert(findTaskById(head, 999) == nullptr);

    assert(removeTaskById(head, 102));
    assert(getTaskCount(head) == 1);
    assert(!removeTaskById(head, 999));

    clearTasks(head);
    assert(head == nullptr);
}

// Week 7
void testWeek7() {
    string filename = "test_tasks_temp.txt";
    createTestTasksFile(filename);

    TaskNode* head = nullptr;

    int loadedCount = loadTasksFromFile(filename, head);
    assert(loadedCount == 3);
    assert(getTaskCount(head) == 3);

    TaskNode* foundNode = findTaskById(head, 1);
    assert(foundNode != nullptr);
    assert(foundNode->data.title == "Homework");
    assert(nearlyEqual(foundNode->data.estimatedHours, 2.5));

    // Save to a new file and reload
    string outputFilename = "test_tasks_output_temp.txt";
    assert(saveTasksToFile(outputFilename, head));

    clearTasks(head);
    assert(head == nullptr);

    int reloadedCount = loadTasksFromFile(outputFilename, head);
    assert(reloadedCount == 3);

    clearTasks(head);

    // Clean up temporary test files
    remove(filename.c_str());
    remove(outputFilename.c_str());
}

int main() {
    testWeek1();
    testWeek2();
    testWeek3();
    testWeek4();
    testWeek5();
    testWeek6();
    testWeek7();

    cout << "All tests passed successfully!" << endl;
}