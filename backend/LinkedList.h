#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "Student.h"
#include <string>
#include <vector>

enum class SortField { RegistrationNumber, Name, AttendancePercentage };

class LinkedList {
private:
    struct Node {
        Student data;
        Node* next;
        explicit Node(const Student& student) : data(student), next(nullptr) {}
    };

    Node* head;
    int count;

    void mergeSort(std::vector<Student>& values, int left, int right, SortField field) const;
    void merge(std::vector<Student>& values, int left, int middle, int right, SortField field) const;
    bool comesBefore(const Student& first, const Student& second, SortField field) const;

public:
    LinkedList();
    ~LinkedList();
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    bool addStudent(const Student& student);
    bool deleteStudent(const std::string& registrationNumber);
    bool updateStudent(const std::string& registrationNumber, const Student& replacement);
    Student* searchStudent(const std::string& registrationNumber);
    const Student* searchStudent(const std::string& registrationNumber) const;
    Student* searchByName(const std::string& name);
    Student* binarySearchByRegistration(const std::string& registrationNumber) const;
    std::vector<Student> displayStudents() const;
    std::vector<Student> sortedStudents(SortField field) const;
    int size() const;
    void clear();
};

#endif
