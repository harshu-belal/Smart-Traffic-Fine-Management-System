#include "FileManager.h"
#include <fstream>
#include <iostream>

using namespace std;

bool FileManager::fileExists(string filename) {
    ifstream file(filename.c_str());
    return file.good();
}

vector<string> FileManager::readAllLines(string filename) {
    vector<string> lines;
    ifstream file(filename.c_str());

    if (!file) {
        // File does not exist yet, just return an empty list
        return lines;
    }

    string line;
    while (getline(file, line)) {
        if (line.length() > 0) {
            lines.push_back(line);
        }
    }
    file.close();
    return lines;
}

void FileManager::appendLine(string filename, string line) {
    // ios::app makes sure we ADD to the file, not overwrite it
    ofstream file(filename.c_str(), ios::app);
    file << line << endl;
    file.close();
}

void FileManager::writeAllLines(string filename, vector<string> lines) {
    // Opening without ios::app overwrites the whole file.
    // Used for update/delete operations where the file is rebuilt.
    ofstream file(filename.c_str());
    for (int i = 0; i < (int)lines.size(); i++) {
        file << lines[i] << endl;
    }
    file.close();
}

vector<string> FileManager::splitLine(string line, char delimiter) {
    vector<string> tokens;
    string token = "";

    for (int i = 0; i < (int)line.length(); i++) {
        if (line[i] == delimiter) {
            tokens.push_back(token);
            token = "";
        } else {
            token += line[i];
        }
    }
    tokens.push_back(token);  // push the last token
    return tokens;
}
