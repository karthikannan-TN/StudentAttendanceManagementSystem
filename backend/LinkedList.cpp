#include "LinkedList.h"
#include <algorithm>
#include <cctype>

LinkedList::LinkedList() : head(nullptr), count(0) {}
LinkedList::~LinkedList() { clear(); }

bool LinkedList::addStudent(const Student& student) {
    if (searchStudent(student.getRegistrationNumber()) != nullptr) return false;
    Node* newNode = new Node(student);
    if (head == nullptr) head = newNode;
    else { Node* current = head; while (current->next != nullptr) current = current->next; current->next = newNode; }
    ++count;
    return true;
}

bool LinkedList::deleteStudent(const std::string& registrationNumber) {
    Node* current = head;
    Node* previous = nullptr;
    while (current != nullptr && current->data.getRegistrationNumber() != registrationNumber) { previous = current; current = current->next; }
    if (current == nullptr) return false;
    if (previous == nullptr) head = current->next; else previous->next = current->next;
    delete current;
    --count;
    return true;
}

bool LinkedList::updateStudent(const std::string& registrationNumber, const Student& replacement) {
    Node* student = head;
    while (student != nullptr) {
        if (student->data.getRegistrationNumber() == registrationNumber) { student->data = replacement; return true; }
        student = student->next;
    }
    return false;
}

Student* LinkedList::searchStudent(const std::string& registrationNumber) {
    Node* current = head;
    while (current != nullptr) { if (current->data.getRegistrationNumber() == registrationNumber) return &current->data; current = current->next; }
    return nullptr;
}

const Student* LinkedList::searchStudent(const std::string& registrationNumber) const {
    Node* current = head;
    while (current != nullptr) { if (current->data.getRegistrationNumber() == registrationNumber) return &current->data; current = current->next; }
    return nullptr;
}

Student* LinkedList::searchByName(const std::string& name) {
    Node* current = head;
    while (current != nullptr) { if (current->data.getName() == name) return &current->data; current = current->next; }
    return nullptr;
}

std::vector<Student> LinkedList::displayStudents() const {
    std::vector<Student> values;
    values.reserve(count);
    Node* current = head;
    while (current != nullptr) { values.push_back(current->data); current = current->next; }
    return values;
}

bool LinkedList::comesBefore(const Student& first, const Student& second, SortField field) const {
    if (field == SortField::RegistrationNumber) return first.getRegistrationNumber() <= second.getRegistrationNumber();
    if (field == SortField::Name) return first.getName() <= second.getName();
    return first.getAttendancePercentage() >= second.getAttendancePercentage();
}

void LinkedList::merge(std::vector<Student>& values, int left, int middle, int right, SortField field) const {
    std::vector<Student> first(values.begin() + left, values.begin() + middle + 1);
    std::vector<Student> second(values.begin() + middle + 1, values.begin() + right + 1);
    int i = 0, j = 0, k = left;
    while (i < static_cast<int>(first.size()) && j < static_cast<int>(second.size())) values[k++] = comesBefore(first[i], second[j], field) ? first[i++] : second[j++];
    while (i < static_cast<int>(first.size())) values[k++] = first[i++];
    while (j < static_cast<int>(second.size())) values[k++] = second[j++];
}

void LinkedList::mergeSort(std::vector<Student>& values, int left, int right, SortField field) const {
    if (left >= right) return;
    int middle = left + (right - left) / 2;
    mergeSort(values, left, middle, field);
    mergeSort(values, middle + 1, right, field);
    merge(values, left, middle, right, field);
}

std::vector<Student> LinkedList::sortedStudents(SortField field) const {
    std::vector<Student> values = displayStudents();
    if (!values.empty()) mergeSort(values, 0, static_cast<int>(values.size()) - 1, field);
    return values;
}

Student* LinkedList::binarySearchByRegistration(const std::string& registrationNumber) const {
    std::vector<Student> values = sortedStudents(SortField::RegistrationNumber);
    int low = 0, high = static_cast<int>(values.size()) - 1;
    while (low <= high) {
        int middle = low + (high - low) / 2;
        if (values[middle].getRegistrationNumber() == registrationNumber) return const_cast<Student*>(searchStudent(registrationNumber));
        if (values[middle].getRegistrationNumber() < registrationNumber) low = middle + 1; else high = middle - 1;
    }
    return nullptr;
}

int LinkedList::size() const { return count; }
void LinkedList::clear() { while (head != nullptr) { Node* next = head->next; delete head; head = next; } count = 0; }
