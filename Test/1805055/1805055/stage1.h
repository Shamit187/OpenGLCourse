#pragma once
#include "header.h"
#include "homogenousSystem.h"

int modelTransformation(std::vector<std::string>& lines, std::string filename) {
    std::ofstream outputFile(filename); 

    int commandIndex = 0;

    std::stack<TransformationMatrix> transformationStack;
    TransformationMatrix currentTransformation;
    
    //debug
    // std::cout << "Transformation starting" << std::endl;
    // currentTransformation.printMatrix();

    for (int i = 0; i < lines.size(); i++){
        std::istringstream iss(lines[i]);
        std::string command;
        iss >> command;

        if (command == "triangle") {
            for (int j = 0; j < 3; ++j) {
                std::istringstream iss(lines[++i]);
                double px, py, pz;
                iss >> px >> py >> pz;
                HomogeneousCoordinate vertex = HomogeneousCoordinate(px, py, pz);
                vertex = vertex.applyTransformation(currentTransformation);
                vertex.printCoordinateToFile(outputFile);
            }
            outputFile << std::endl;

            //debug
            // std::cout << commandIndex << ": Triangle output to file." << std::endl;
        } 
        else if (command == "translate") {
            std::istringstream iss(lines[++i]);
            double tx, ty, tz;
            iss >> tx >> ty >> tz;
            TransformationMatrix translation = TransformationMatrix::createTranslationMatrix(tx, ty, tz);
            currentTransformation = currentTransformation * translation;

            //debug
            // std::cout << commandIndex << ": translation" << std::endl;
            // currentTransformation.printMatrix();
        } 
        else if (command == "scale") {
            std::istringstream iss(lines[++i]);
            double sx, sy, sz;
            iss >> sx >> sy >> sz;
            TransformationMatrix scale = TransformationMatrix::createScalingMatrix(sx, sy, sz);
            currentTransformation = currentTransformation * scale ;

            //debug
            // std::cout << commandIndex << ": scale" << std::endl;
            // currentTransformation.printMatrix();
        } 
        else if (command == "rotate") {
            std::istringstream iss(lines[++i]);
            double angle, axis_x, axis_y, axis_z;
            iss >> angle >> axis_x >> axis_y >> axis_z;
            TransformationMatrix rotate = TransformationMatrix::createRotationMatrix(angle, axis_x, axis_y, axis_z);
            currentTransformation = currentTransformation * rotate;

            //debug
            // std::cout << commandIndex << ": rotate" << std::endl;
            // currentTransformation.printMatrix();
        } 
        else if (command == "push") {
            transformationStack.push(currentTransformation);
        } 
        else if (command == "pop") {
            if (!transformationStack.empty()) {
                currentTransformation = transformationStack.top();
                transformationStack.pop();
            } else {
                currentTransformation = TransformationMatrix();
            }

            //debug
            // std::cout << commandIndex << ": popped from stack" << std::endl;
            // currentTransformation.printMatrix();
        } 
        else if (command == "end") {
            break;
        } 
        else {
            std::cout << "Invalid command: " << command << ". Skipping...\n";
        }
        commandIndex++;
    }
    outputFile.close();
    return 0;
}
