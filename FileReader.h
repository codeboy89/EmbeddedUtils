
#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
class FileReader
{
public:
    FileReader(std::string filePath);
    ~FileReader();
    std::vector<std::string>  getVector();
private:
    std::ifstream inFile;
    std::vector<std::string> filesLines;
};

FileReader::FileReader(std::string filePath)
{
    this->inFile.open(filePath);
    if (!this->inFile) {
        std::cout << "File not opened" << std::endl;
    }
    else {
        std::string x;
        while (inFile >> x) {
            filesLines.push_back(x);
            x = "";
        }
        inFile.close();
    }
}

FileReader::~FileReader()
{
}

inline std::vector<std::string> FileReader::getVector()
{
    return this->filesLines;
}


