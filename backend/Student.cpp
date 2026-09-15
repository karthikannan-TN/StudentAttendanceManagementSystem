#include "Student.h"
#include <iomanip>
#include <sstream>
#include <vector>

Student::Student() : semester(1), attendancePercentage(0.0), cgpa(0.0) {}

Student::Student(const std::string& registrationNumber, const std::string& password, const std::string& name,
                 const std::string& department, int semester, const std::string& section,
                 double attendancePercentage, double cgpa, const std::string& phone,
                 const std::string& email, const std::string& photo)
    : registrationNumber(registrationNumber), password(password), name(name), department(department),
      semester(semester), section(section), attendancePercentage(attendancePercentage), cgpa(cgpa),
      phone(phone), email(email), photo(photo) {}

const std::string& Student::getRegistrationNumber() const { return registrationNumber; }
const std::string& Student::getPassword() const { return password; }
const std::string& Student::getName() const { return name; }
const std::string& Student::getDepartment() const { return department; }
int Student::getSemester() const { return semester; }
const std::string& Student::getSection() const { return section; }
double Student::getAttendancePercentage() const { return attendancePercentage; }
double Student::getCgpa() const { return cgpa; }
const std::string& Student::getPhone() const { return phone; }
const std::string& Student::getEmail() const { return email; }
const std::string& Student::getPhoto() const { return photo; }

void Student::setName(const std::string& value) { name = value; }
void Student::setDepartment(const std::string& value) { department = value; }
void Student::setSemester(int value) { semester = value; }
void Student::setSection(const std::string& value) { section = value; }
void Student::setAttendancePercentage(double value) { attendancePercentage = value < 0 ? 0 : (value > 100 ? 100 : value); }
void Student::setCgpa(double value) { cgpa = value < 0 ? 0 : (value > 10 ? 10 : value); }
void Student::setPhone(const std::string& value) { phone = value; }
void Student::setEmail(const std::string& value) { email = value; }

std::string Student::serialize() const {
    std::ostringstream out;
    out << registrationNumber << '|' << password << '|' << name << '|' << department << '|'
        << semester << '|' << section << '|' << std::fixed << std::setprecision(1)
        << attendancePercentage << '|' << cgpa << '|' << phone << '|' << email << '|' << photo;
    return out.str();
}

bool Student::deserialize(const std::string& line, Student& student) {
    std::stringstream stream(line);
    std::string part;
    std::vector<std::string> values;
    while (std::getline(stream, part, '|')) values.push_back(part);
    if (values.size() != 11) return false;
    try {
        student = Student(values[0], values[1], values[2], values[3], std::stoi(values[4]), values[5],
                          std::stod(values[6]), std::stod(values[7]), values[8], values[9], values[10]);
    } catch (...) { return false; }
    return true;
}
