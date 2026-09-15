#ifndef ATTENDANCE_MANAGER_H
#define ATTENDANCE_MANAGER_H

#include "LinkedList.h"
#include <string>

struct AttendanceAction {
    std::string registrationNumber;
    double oldAttendance;
    double newAttendance;
};

struct AttendanceTask {
    std::string registrationNumber;
    bool present;
    int totalClasses;
};

class AttendanceManager {
private:
    struct StackNode { AttendanceAction action; StackNode* next; explicit StackNode(const AttendanceAction& value) : action(value), next(nullptr) {} };
    struct QueueNode { AttendanceTask task; QueueNode* next; explicit QueueNode(const AttendanceTask& value) : task(value), next(nullptr) {} };
    StackNode* undoTop;
    QueueNode* queueFront;
    QueueNode* queueRear;

public:
    AttendanceManager();
    ~AttendanceManager();
    void queueAttendance(const AttendanceTask& task);
    int processDailyQueue(LinkedList& students);
    bool undoLastAttendance(LinkedList& students);
    int pendingTasks() const;
    void clear();
};

#endif
