#include "AttendanceManager.h"
#include "FileManager.h"
#include <iomanip>
#include <iostream>
#include <limits>

namespace {
const std::string DATA_FILE = "students.txt";

void line() { std::cout << "\n" << std::string(104, '=') << "\n"; }
void printStudent(const Student& student) {
    std::cout << std::left << std::setw(14) << student.getRegistrationNumber()
              << std::setw(25) << student.getName().substr(0, 24)
              << std::setw(28) << student.getDepartment().substr(0, 27)
              << std::setw(7) << student.getSemester()
              << std::setw(8) << student.getSection()
              << std::setw(12) << std::fixed << std::setprecision(1) << student.getAttendancePercentage()
              << std::setw(6) << student.getCgpa() << '\n';
}

void showStudents(const std::vector<Student>& students) {
    line();
    std::cout << std::left << std::setw(14) << "REG. NO." << std::setw(25) << "NAME" << std::setw(28)
              << "DEPARTMENT" << std::setw(7) << "SEM" << std::setw(8) << "SECTION" << std::setw(12)
              << "ATTENDANCE" << "CGPA\n";
    line();
    for (const Student& student : students) printStudent(student);
    std::cout << "\nTotal records: " << students.size() << '\n';
}

std::string readLine(const std::string& prompt) { std::cout << prompt; std::string value; std::getline(std::cin, value); return value; }
int readInt(const std::string& prompt) { while (true) { std::string value = readLine(prompt); try { return std::stoi(value); } catch (...) { std::cout << "Enter a valid whole number.\n"; } } }
double readDouble(const std::string& prompt) { while (true) { std::string value = readLine(prompt); try { return std::stod(value); } catch (...) { std::cout << "Enter a valid number.\n"; } } }

bool login() {
    line();
    std::cout << "             AURORA UNIVERSITY — STUDENT ATTENDANCE MANAGEMENT SYSTEM\n";
    line();
    std::cout << "Demo accounts: student [12345678/student123], faculty [faculty01/faculty123], admin [admin/admin123]\n\n";
    std::string username = readLine("Username: ");
    std::string password = readLine("Password: ");
    bool valid = (username == "12345678" && password == "student123") ||
                 (username == "faculty01" && password == "faculty123") ||
                 (username == "admin" && password == "admin123");
    if (!valid) std::cout << "Invalid credentials.\n";
    return valid;
}

Student createStudent() {
    std::string registration = readLine("Registration number: ");
    std::string password = readLine("Temporary password: ");
    std::string name = readLine("Full name: ");
    std::string department = readLine("Department: ");
    int semester = readInt("Semester: ");
    std::string section = readLine("Section: ");
    double attendance = readDouble("Attendance percentage: ");
    double cgpa = readDouble("CGPA: ");
    std::string phone = readLine("Phone: ");
    std::string email = readLine("Email: ");
    std::string photo = readLine("Photo filename / URL: ");
    return Student(registration, password, name, department, semester, section, attendance, cgpa, phone, email, photo);
}

void updateStudent(LinkedList& students) {
    std::string registration = readLine("Registration number to update: ");
    Student* current = students.searchStudent(registration);
    if (current == nullptr) { std::cout << "Student was not found.\n"; return; }
    Student replacement = *current;
    std::string value;
    value = readLine("Name [" + current->getName() + "]: "); if (!value.empty()) replacement.setName(value);
    value = readLine("Department [" + current->getDepartment() + "]: "); if (!value.empty()) replacement.setDepartment(value);
    value = readLine("Semester [" + std::to_string(current->getSemester()) + "]: "); if (!value.empty()) replacement.setSemester(std::stoi(value));
    value = readLine("Section [" + current->getSection() + "]: "); if (!value.empty()) replacement.setSection(value);
    value = readLine("Attendance % [" + std::to_string(current->getAttendancePercentage()) + "]: "); if (!value.empty()) replacement.setAttendancePercentage(std::stod(value));
    value = readLine("CGPA [" + std::to_string(current->getCgpa()) + "]: "); if (!value.empty()) replacement.setCgpa(std::stod(value));
    value = readLine("Phone [" + current->getPhone() + "]: "); if (!value.empty()) replacement.setPhone(value);
    value = readLine("Email [" + current->getEmail() + "]: "); if (!value.empty()) replacement.setEmail(value);
    students.updateStudent(registration, replacement);
    FileManager::saveStudents(DATA_FILE, students);
    std::cout << "Student record updated and saved.\n";
}
}

int main() {
    if (!login()) return 1;
    LinkedList students;
    AttendanceManager attendanceManager;
    if (!FileManager::loadStudents(DATA_FILE, students)) {
        std::cout << "Could not load " << DATA_FILE << ". Run this program from the backend directory.\n";
        return 1;
    }
    std::cout << "Loaded " << students.size() << " student records successfully.\n";

    while (true) {
        line();
        std::cout << "1. Display students                 2. Add student\n"
                  << "3. Delete student                   4. Update student\n"
                  << "5. Linear search by registration    6. Binary search by registration\n"
                  << "7. Search by exact name             8. Merge sort students\n"
                  << "9. Queue daily attendance           10. Process attendance queue\n"
                  << "11. Undo last attendance            12. Save records\n"
                  << "0. Exit\n";
        int choice = readInt("\nChoose an option: ");
        if (choice == 0) { FileManager::saveStudents(DATA_FILE, students); std::cout << "Records saved. Goodbye.\n"; break; }
        if (choice == 1) showStudents(students.displayStudents());
        else if (choice == 2) { Student student = createStudent(); if (students.addStudent(student)) { FileManager::saveStudents(DATA_FILE, students); std::cout << "Student added and saved.\n"; } else std::cout << "That registration number already exists.\n"; }
        else if (choice == 3) { std::string registration = readLine("Registration number to delete: "); if (students.deleteStudent(registration)) { FileManager::saveStudents(DATA_FILE, students); std::cout << "Student deleted and file updated.\n"; } else std::cout << "Student was not found.\n"; }
        else if (choice == 4) updateStudent(students);
        else if (choice == 5 || choice == 6) { std::string registration = readLine("Registration number: "); Student* student = choice == 5 ? students.searchStudent(registration) : students.binarySearchByRegistration(registration); if (student) { line(); printStudent(*student); } else std::cout << "Student was not found.\n"; }
        else if (choice == 7) { std::string name = readLine("Exact student name: "); Student* student = students.searchByName(name); if (student) { line(); printStudent(*student); } else std::cout << "Student was not found.\n"; }
        else if (choice == 8) { int field = readInt("Sort by [1] Registration [2] Name [3] Attendance: "); SortField sort = field == 2 ? SortField::Name : (field == 3 ? SortField::AttendancePercentage : SortField::RegistrationNumber); showStudents(students.sortedStudents(sort)); }
        else if (choice == 9) { AttendanceTask task; task.registrationNumber = readLine("Registration number: "); int present = readInt("Present? [1 yes / 0 no]: "); task.present = present == 1; task.totalClasses = readInt("Total classes after today: "); attendanceManager.queueAttendance(task); std::cout << "Attendance task queued. Pending: " << attendanceManager.pendingTasks() << '\n'; }
        else if (choice == 10) { int processed = attendanceManager.processDailyQueue(students); FileManager::saveStudents(DATA_FILE, students); std::cout << processed << " attendance task(s) processed, pushed to the undo stack, and saved.\n"; }
        else if (choice == 11) { if (attendanceManager.undoLastAttendance(students)) { FileManager::saveStudents(DATA_FILE, students); std::cout << "Last attendance update undone and saved.\n"; } else std::cout << "Nothing is available to undo.\n"; }
        else if (choice == 12) std::cout << (FileManager::saveStudents(DATA_FILE, students) ? "All records saved.\n" : "Could not save records.\n");
        else std::cout << "Choose a valid menu option.\n";
    }
    return 0;
}
