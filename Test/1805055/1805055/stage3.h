#pragma once
#include "header.h"
#include "homogenousSystem.h"

void projectionTransformation(std::string viewBox, std::vector<std::string> vertices, std::string filename){
    double fovX, fovY, aspectRatio, t, r, near, far;
    std::istringstream iss(viewBox);

    iss >> fovY >> aspectRatio >> near >> far;
    fovX = fovY * aspectRatio;
    t = near * tan ((fovY / 2) * (M_PI /180));
    r = near * tan ((fovX / 2) * (M_PI /180));

    TransformationMatrix projectionMatrix;
    projectionMatrix.matrix[0][0] = near/r;
    projectionMatrix.matrix[1][1] = near/t;
    projectionMatrix.matrix[2][2] = -(far + near) / (far - near);
    projectionMatrix.matrix[3][3] = 0;
    projectionMatrix.matrix[2][3] = -(2*far*near) / (far - near);
    projectionMatrix.matrix[3][2] = -1;

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
        vertex = vertex.applyTransformation(projectionMatrix);
        vertex.printCoordinateToFile(output);
    }

    output.close();
}