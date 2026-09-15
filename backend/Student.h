#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
private:
    std::string registrationNumber;
    std::string password;
    std::string name;
    std::string department;
    int semester;
    std::string section;
    double attendancePercentage;
    double cgpa;
    std::string phone;
    std::string email;
    std::string photo;

public:
    Student();
    Student(const std::string& registrationNumber, const std::string& password, const std::string& name,
            const std::string& department, int semester, const std::string& section,
            double attendancePercentage, double cgpa, const std::string& phone,
            const std::string& email, const std::string& photo);

    const std::string& getRegistrationNumber() const;
    const std::string& getPassword() const;
    const std::string& getName() const;
    const std::string& getDepartment() const;
    int getSemester() const;
    const std::string& getSection() const;
    double getAttendancePercentage() const;
    double getCgpa() const;
    const std::string& getPhone() const;
    const std::string& getEmail() const;
    const std::string& getPhoto() const;

    void setName(const std::string& value);
    void setDepartment(const std::string& value);
    void setSemester(int value);
    void setSection(const std::string& value);
    void setAttendancePercentage(double value);
    void setCgpa(double value);
    void setPhone(const std::string& value);
    void setEmail(const std::string& value);

    std::string serialize() const;
    static bool deserialize(const std::string& line, Student& student);
};

#endif
