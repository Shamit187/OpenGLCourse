#pragma once
#include "header.h"
#include "homogenousSystem.h"

TransformationMatrix generateViewMatrix(HomogeneousCoordinate eye, HomogeneousCoordinate look, HomogeneousCoordinate up) {
    HomogeneousCoordinate l = look - eye;
    l.normalizeVector();

    HomogeneousCoordinate r = l.cross(up);
    r.normalizeVector();

    HomogeneousCoordinate u = r.cross(l);

    TransformationMatrix T = TransformationMatrix::createTranslationMatrix(-eye.x, -eye.y, -eye.z);

    TransformationMatrix R = TransformationMatrix();
    R.matrix[0][0] = r.x;
    R.matrix[0][1] = r.y;
    R.matrix[0][2] = r.z;
    R.matrix[1][0] = u.x;
    R.matrix[1][1] = u.y;
    R.matrix[1][2] = u.z;
    R.matrix[2][0] = -l.x;
    R.matrix[2][1] = -l.y;
    R.matrix[2][2] = -l.z;

    TransformationMatrix viewTransformation = R * T;
    return viewTransformation;
}


void viewTransformation(std::vector<std::string> cameraData, std::vector<std::string>vertices, std::string filename){
    HomogeneousCoordinate cameraPosition[3];
    for(int i = 0; i < 3; i++){
        std::istringstream iss(cameraData[i]);
        iss >> cameraPosition[i].x >> cameraPosition[i].y >> cameraPosition[i].z;
    }
    auto viewTransformation = generateViewMatrix(cameraPosition[0], cameraPosition[1], cameraPosition[2]);

    std::ofstream output(filename);

    for(int i = 0; i < vertices.size(); i++){
        if (vertices[i] == "") {
            output << std::endl;
            continue;
        }
        
        std::istringstream iss(vertices[i]);
        double x, y, z;
        iss >> x >> y >> z;

        HomogeneousCoordinate vertex(x, y, z);
        vertex = vertex.applyTransformation(viewTransformation);
        vertex.printCoordinateToFile(output);
    }

    output.close();
}