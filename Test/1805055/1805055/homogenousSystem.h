#pragma once
#include "header.h"

struct TransformationMatrix {
    double matrix[4][4];

    TransformationMatrix() {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (i == j)
                    matrix[i][j] = 1.0;
                else
                    matrix[i][j] = 0.0;
            }
        }
    }

    static TransformationMatrix createTranslationMatrix(double x, double y, double z) {
        TransformationMatrix translationMatrix;

        translationMatrix.matrix[0][3] = x;
        translationMatrix.matrix[1][3] = y;
        translationMatrix.matrix[2][3] = z;

        return translationMatrix;
    }

    static TransformationMatrix createScalingMatrix(double x, double y, double z) {
        TransformationMatrix scalingMatrix;

        scalingMatrix.matrix[0][0] = x;
        scalingMatrix.matrix[1][1] = y;
        scalingMatrix.matrix[2][2] = z;

        return scalingMatrix;
    }

    static TransformationMatrix createRotationMatrix(double angle, double axis_x, double axis_y, double axis_z) {
        TransformationMatrix rotationMatrix;

        double norm = sqrt(axis_x * axis_x + axis_y * axis_y + axis_z * axis_z);
        axis_x /= norm;
        axis_y /= norm;
        axis_z /= norm;

        double c = cos(angle * (M_PI / 180));
        double s = sin(angle * (M_PI / 180));
        double t = 1 - c;

        rotationMatrix.matrix[0][0] = t * axis_x * axis_x + c;
        rotationMatrix.matrix[0][1] = t * axis_x * axis_y - s * axis_z;
        rotationMatrix.matrix[0][2] = t * axis_x * axis_z + s * axis_y;

        rotationMatrix.matrix[1][0] = t * axis_x * axis_y + s * axis_z;
        rotationMatrix.matrix[1][1] = t * axis_y * axis_y + c;
        rotationMatrix.matrix[1][2] = t * axis_y * axis_z - s * axis_x;

        rotationMatrix.matrix[2][0] = t * axis_x * axis_z - s * axis_y;
        rotationMatrix.matrix[2][1] = t * axis_y * axis_z + s * axis_x;
        rotationMatrix.matrix[2][2] = t * axis_z * axis_z + c;

        return rotationMatrix;
    }

    TransformationMatrix operator*(const TransformationMatrix& other) const {
        TransformationMatrix result;

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                result.matrix[i][j] = 0.0;
                for (int k = 0; k < 4; ++k) {
                    result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
                }
            }
        }

        return result;
    }

    void printMatrix() {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                std::cout << matrix[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    }
};

struct HomogeneousCoordinate {
    double x;
    double y;
    double z;
    double w;

    HomogeneousCoordinate() : x(0), y(0), z(0), w(1.0) {}

    HomogeneousCoordinate(double x, double y, double z) : x(x), y(y), z(z), w(1.0) {}

    HomogeneousCoordinate applyTransformation(const TransformationMatrix& matrix) const {
        double resultX = matrix.matrix[0][0] * x + matrix.matrix[0][1] * y + matrix.matrix[0][2] * z + matrix.matrix[0][3] * w;
        double resultY = matrix.matrix[1][0] * x + matrix.matrix[1][1] * y + matrix.matrix[1][2] * z + matrix.matrix[1][3] * w;
        double resultZ = matrix.matrix[2][0] * x + matrix.matrix[2][1] * y + matrix.matrix[2][2] * z + matrix.matrix[2][3] * w;
        double resultW = matrix.matrix[3][0] * x + matrix.matrix[3][1] * y + matrix.matrix[3][2] * z + matrix.matrix[3][3] * w;

        if(resultW != 0){
            resultX /= resultW;
            resultY /= resultW;
            resultZ /= resultW;
        }

        return HomogeneousCoordinate(resultX, resultY, resultZ);
    }

    HomogeneousCoordinate operator-(const HomogeneousCoordinate& other) const{
        return HomogeneousCoordinate(x - other.x, y - other.y, z - other.z);
    }

    HomogeneousCoordinate cross(const HomogeneousCoordinate& other) const {
        return HomogeneousCoordinate(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
    }

    double length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    void normalizeVector() {
        double len = length();
        if (len != 0) {
            x /= len;
            y /= len;
            z /= len;
        }
    }

    void printCoordinate() const {
        std::cout << x << " " << y << " " << z << std::endl;
    }

    void printCoordinateToFile(std::ofstream& outputFile) const {
        if (outputFile.is_open()) {
            outputFile << std::fixed << std::setprecision (7) << x << " " << y << " " << z << std::endl;
        } else {
            std::cerr << "Error writing vertex to file" << std::endl;
        }
    }

};
