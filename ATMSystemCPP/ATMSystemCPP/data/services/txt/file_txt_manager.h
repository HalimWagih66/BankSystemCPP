#pragma once
#include <string>
#include <vector>
#include <memory>

class FileTxtManager
{
public:
    // Saves a single line (record) to the specified file
    static void SaveLineInFile(const std::string& record, const std::string& fileName);

    // Saves multiple lines (records) to the specified file
    static void SaveLinesInFile(const std::vector<std::string>& vRecords, const std::string& fileName);

    // Reads all lines from the specified file and returns them as a vector of strings
    static std::unique_ptr<std::vector<std::string>> GetLinesFromFile(const std::string& fileName);

    // Default constructor
    FileTxtManager() = default;
};