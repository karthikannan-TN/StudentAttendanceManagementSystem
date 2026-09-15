#include "FileManager.h"
#include <fstream>

bool FileManager::loadStudents(const std::string& fileName, LinkedList& students) {
    std::ifstream input(fileName);
    if (!input.is_open()) return false;
    students.clear();
    std::string line;
    while (std::getline(input, line)) {
        Student student;
        if (Student::deserialize(line, student)) students.addStudent(student);
    }
    return true;
}

bool FileManager::saveStudents(const std::string& fileName, const LinkedList& students) {
    std::ofstream output(fileName, std::ios::trunc);
    if (!output.is_open()) return false;
    for (const Student& student : students.displayStudents()) output << student.serialize() << '\n';
    return true;
}
