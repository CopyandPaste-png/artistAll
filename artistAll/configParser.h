#pragma once
#include <fstream>
#include <string>
#include <map>


/*
    Parses a .config file into a std::map
    @param fileName .config file to parse
    @return std::map<string,string>. Acts like a dictionary
*/
std::map<std::string, std::string>parseConfig(std::string fileName) {
    std::ifstream file(fileName);
    std::map<std::string, std::string> dict;

    if (file) {
        std::string line;
        while (std::getline(file, line)) {
            int firstIndex = line.find("=");
            std::string key = line.substr(0, firstIndex);
            std::string value = line.substr(firstIndex + 1, line.length() - firstIndex);
            dict.insert({ key,value });
        }
    }

    return dict;
}
