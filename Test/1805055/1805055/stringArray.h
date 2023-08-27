#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::string> splitLines(std::ifstream& inputFile){
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(inputFile, line)) {
        lines.push_back(line);
    }

    inputFile.close();
    return lines;
}