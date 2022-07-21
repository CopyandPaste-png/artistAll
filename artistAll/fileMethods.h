#pragma once
#include <fstream>
#include <filesystem>
#include <string>
#include "logging.h"

/*
Files are formated as follows:
    <key>:<value>\n
*/


static std::string _readTokenFile(std::string fileName,std::string entry) {
    std::ifstream file(fileName);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            if (line.find(entry) != std::string::npos) {
                return line.substr(line.find(":") + 1, line.length() - line.find(":"));
            }
        }
    }

    return "NONE";
}

/*
    Checks if value is in file
    @param fileName file to check
    @param key <key> to check
    @return true if <key> is found, else false
*/
static bool _isValueInFile(std::string fileName, std::string key) {
    std::ifstream file(fileName);
    if (file)
    {
        std::string line;
        while (std::getline(file, line))
        {
            if (line.find(key) != std::string::npos) {
                //<key> is found
                return true;
            }
        }
    }
    return false;
}

/*
    Edits a <key>'s <value> in a file. Creates a temp file which the editted entry is written into.
    If the <key> is in the file, then token.txt is deleted and temp.txt is renamed to token.txt,
    else temp.txt is deleted.
    @param fileName file to check
    @param key <key> to check
    @param newValue <key>'s new <value>
*/
static void _editValueInFile(std::string fileName, std::string key, std::string newValue) {
    std::ifstream file(fileName);
    std::ofstream temp("temp.txt");

    //Tracks if file is edited
    bool valueChanged = false;

    if (file)
    {
        std::string line;
        while (std::getline(file, line))
        {
            if (line.find(key) != std::string::npos) {
                //Writes the editted <key>:<value> pair to temp.txt
                temp << line.substr(0, line.find(":")) << ":" << newValue << "\n";
                //File has been changed. we switch the flag
                valueChanged = true;
            }
            else {
                //If <key> is not in line, write the file to temp
                temp << line << "\n";
            }
        }
    }

    //Close files before deleting and renaming
    temp.close();
    file.close();

    if (valueChanged) {
        //If file has been changed, then we delete token.txt and rename temp.txt to token.txt
        try { 
            std::filesystem::remove(fileName);
            std::filesystem::rename("temp.txt", fileName);
        }
        catch (std::filesystem::filesystem_error e) {
            logToFile(e.what());
        }
    }
    else {
        //If file is not changed, then we removed temp.txt
        std::filesystem::remove("temp.txt");
    }
}

/*
    Appends a <key>:<value> to a file
    @param fileName file to write to
    @param key <key>'s value
    @param value <value>'s value

*/
static void _writeToFile(std::string fileName,std::string key,std::string value) {
    std::ofstream file(fileName,std::ios_base::app);

    if (file)
    {
        file << key << ":" << value << "\n";
        file.close();
    }
}

static void _appendToFileDirectory(std::string directory, std::string fileName, std::string data) {

    if (std::filesystem::is_directory(directory) == false) {
        std::filesystem::create_directory(directory);
    }

    std::ofstream file(directory + "/" + fileName);

    if (file.is_open()) {
        file << data;
    }

    file.close();
}