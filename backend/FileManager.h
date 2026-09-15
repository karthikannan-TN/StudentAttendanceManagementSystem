#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "LinkedList.h"
#include <string>

class FileManager {
public:
    static bool loadStudents(const std::string& fileName, LinkedList& students);
    static bool saveStudents(const std::string& fileName, const LinkedList& students);
};

#endif
