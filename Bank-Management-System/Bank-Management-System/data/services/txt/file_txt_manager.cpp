#include "file_txt_manager.h"
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

// Opens the file in append mode (adds the record at the end).
void FileTxtManager::SaveLineInFile(const string& record,const string& fileName) {
	ofstream file;
	file.open(fileName, ios::app | ios::out);
	if (file.is_open())
	{
		file << record << endl;  // Write the record followed by a newline
		file.close();             // Close the file to save changes
	}
	else
	{
		throw std::runtime_error("Error : Unable to open file: " + fileName);
	}
}

// Saves multiple records (vector of strings) into the specified file.
// Each record is written on a new line.
// The file is opened in output mode, overwriting any existing content.
// If the file can't be opened, a warning is shown.
void FileTxtManager::SaveLinesInFile(const vector<string>& vRecords, const string& fileName) {
	ofstream  file;
	file.open(fileName, ios::out);
	if (file.is_open())
	{
		for (const string& record : vRecords)
		{
			file << record << endl;  // Write each record on a separate line
		}
		file.close();  // Close the file after writing all records
	}
	else
	{
		throw std::runtime_error("Error : Unable to open file: " + fileName);
	}
}



// Reads all lines (records) from the specified file and returns them as a vector of strings.
unique_ptr<vector<string>> FileTxtManager::GetLinesFromFile(const string& fileName) {
	ifstream file(fileName , ios::in);
	if (!file.is_open()) {
		throw runtime_error("Error : Unable to open file: " + fileName + "\n");
	}

	unique_ptr<vector<string>> vContentFile = make_unique<vector<string>>();
	string record;

	while (getline(file, record)) {
		if (!record.empty())
			vContentFile->push_back(record);
	}
	file.close();
	return vContentFile;
}