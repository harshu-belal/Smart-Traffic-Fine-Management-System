#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>

using std::string;
using std::vector;

// FileManager provides generic, reusable file handling operations.
// Every other class (Vehicle, Driver, Fine) uses these functions
// instead of writing its own file handling code again and again.
class FileManager {
public:
    // Checks whether a file already exists on disk
    static bool fileExists(string filename);

    // Reads every line of a file into a vector of strings
    static vector<string> readAllLines(string filename);

    // Appends a single line/record at the end of a file
    static void appendLine(string filename, string line);

    // Overwrites the whole file with the given lines
    // (used when we update or delete a record)
    static void writeAllLines(string filename, vector<string> lines);

    // Splits a line into parts using a delimiter (we use '|')
    static vector<string> splitLine(string line, char delimiter);
};

#endif
