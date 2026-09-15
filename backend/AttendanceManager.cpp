#include "AttendanceManager.h"

AttendanceManager::AttendanceManager() : undoTop(nullptr), queueFront(nullptr), queueRear(nullptr) {}
AttendanceManager::~AttendanceManager() { clear(); }

void AttendanceManager::queueAttendance(const AttendanceTask& task) {
    QueueNode* node = new QueueNode(task);
    if (queueRear == nullptr) queueFront = queueRear = node;
    else { queueRear->next = node; queueRear = node; }
}

int AttendanceManager::processDailyQueue(LinkedList& students) {
    int processed = 0;
    while (queueFront != nullptr) {
        QueueNode* node = queueFront;
        queueFront = queueFront->next;
        if (queueFront == nullptr) queueRear = nullptr;
        Student* student = students.searchStudent(node->task.registrationNumber);
        if (student != nullptr && node->task.totalClasses > 0) {
            double oldValue = student->getAttendancePercentage();
            double estimatedPresent = oldValue * (node->task.totalClasses - 1) / 100.0 + (node->task.present ? 1 : 0);
            double newValue = (estimatedPresent / node->task.totalClasses) * 100.0;
            student->setAttendancePercentage(newValue);
            StackNode* action = new StackNode({node->task.registrationNumber, oldValue, newValue});
            action->next = undoTop;
            undoTop = action;
            ++processed;
        }
        delete node;
    }
    return processed;
}

bool AttendanceManager::undoLastAttendance(LinkedList& students) {
    if (undoTop == nullptr) return false;
    StackNode* action = undoTop;
    undoTop = undoTop->next;
    Student* student = students.searchStudent(action->action.registrationNumber);
    if (student != nullptr) student->setAttendancePercentage(action->action.oldAttendance);
    delete action;
    return student != nullptr;
}

int AttendanceManager::pendingTasks() const { int count = 0; for (QueueNode* node = queueFront; node != nullptr; node = node->next) ++count; return count; }
void AttendanceManager::clear() { while (undoTop != nullptr) { StackNode* next = undoTop->next; delete undoTop; undoTop = next; } while (queueFront != nullptr) { QueueNode* next = queueFront->next; delete queueFront; queueFront = next; } queueRear = nullptr; }
