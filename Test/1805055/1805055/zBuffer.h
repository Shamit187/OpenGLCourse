#pragma once
#include "header.h"
#include "bitmap.h"
#define DEBUG

#define A 0
#define B 1
#define C 2

#define X 0
#define Y 1
#define Z 2

#define AB 0
#define BC 1
#define CA 2

#define FAR_PLANE -1
#define NEAR_PLANE 1

struct triangle
{
    std::vector<std::vector<double>> vertices;
    std::vector<int> color;
};

bool isBetween(double row, double vertex_1_x, double vertex_2_x)
{
    return (row >= vertex_1_x && row <= vertex_2_x) || (row >= vertex_2_x && row <= vertex_1_x);
}

static unsigned long int g_seed = 1;
static inline int random()
{
 g_seed = (214013 * g_seed + 2531011);
 return (g_seed >> 16) & 0x7FFF;
}

void zBuffer(std::vector<std::string> lines, int screen_Width, int screen_Height, std::string z_buffer_file_output, std::string output_image)
{
    std::vector<triangle> triangles;

    // read data
    for (int i = 0; i < lines.size(); i += 4)
    {
        std::vector<int> color(3);
        std::vector<std::vector<double>> vertices(0, std::vector<double>(3));

        for (int j = 0; j < 3; j++)
        {
            std::vector<double> vertex(3);
            std::stringstream ss(lines[i + j]);
            ss >> vertex[0] >> vertex[1] >> vertex[2];
            vertices.push_back(vertex);
        }

        color[0] = random() % 256;
        color[1] = random() % 256;
        color[2] = random() % 256;

        triangle t;
        t.vertices = vertices;
        t.color = color;

        triangles.push_back(t);
    }


    std::vector<std::vector<double>> z_buffer(screen_Height, std::vector<double>(screen_Width, FAR_PLANE));
    std::vector<std::vector<std::vector<int>>> color_buffer(screen_Height, std::vector<std::vector<int>>(screen_Width, std::vector<int>(3, 0)));

    // for each triangle
    for (int ct = 0; ct < triangles.size(); ct++)
    {
        std::cout << "Triangle " << ct << std::endl;
        double top_scanline = -1e10;
        double bottom_scanline = 1e10;
        for (int j = 0; j < 3; j++)
        {
            top_scanline = std::max(top_scanline, triangles[ct].vertices[j][1]);
            bottom_scanline = std::min(bottom_scanline, triangles[ct].vertices[j][1]);
        }

        double dx = 2.0 / (screen_Width);
        double dy = 2.0 / (screen_Height);

        // File Reading Debugging
        /*
        std::cout << "Vertices: " << std::endl;
        for (int i = 0; i < 3; i++)
        {
            std::cout << std::fixed << std::setprecision (7) << triangles[ct].vertices[i][0] << " " << triangles[ct].vertices[i][1] << " " << triangles[ct].vertices[i][2] << std::endl;
        }
        std::cout << std::fixed << std::setprecision (7) << "Top scanline: " << top_scanline << std::endl;
        std::cout << std::fixed << std::setprecision (7) << "Bottom scanline: " << bottom_scanline << std::endl;
        */


        // for each scanline
        
        for (double row = top_scanline; row >= bottom_scanline; row -= dy)
        {

            if(row < FAR_PLANE || row > NEAR_PLANE)
                continue;

            std::vector<double> leftIntersection(3, 0);
            std::vector<double> rightIntersection(3, 0);
            std::vector<std::vector<double>> vertices(3, std::vector<double>(3, 0));
            std::vector<std::vector<double>> intersections(3, std::vector<double>(3, 0));

            for (int i = 0; i < 3; i++)
            {
                leftIntersection[X] = row;
                rightIntersection[X] = row;
            }

            
            for (int i = 0; i < 3; i++)
            {
                vertices[i][X] = triangles[ct].vertices[i][X];
                vertices[i][Y] = triangles[ct].vertices[i][Y];
                vertices[i][Z] = triangles[ct].vertices[i][Z];
            }
            
            for (int i = 0; i < 3; i++)
                intersections[i][Y] = vertices[i][Y];
            double lambda = 0;

            // AB
            if (vertices[A][Y] == vertices[B][Y] && vertices[A][Y] == row)
                continue;
            lambda = (vertices[B][Y] == vertices[A][Y]) ? 0 : (row - vertices[A][Y]) / (vertices[B][Y] - vertices[A][Y]);
            intersections[AB][X] = (vertices[A][X] + lambda * (vertices[B][X] - vertices[A][X]));
            intersections[AB][Z] = (vertices[A][Z] + lambda * (vertices[B][Z] - vertices[A][Z]));

            // BC
            if (vertices[C][Y] == vertices[B][Y] && vertices[C][Y] == row)
                continue;
            lambda = (vertices[B][Y] == vertices[C][Y]) ? 0 : (row - vertices[B][Y]) / (vertices[C][Y] - vertices[B][Y]);
            intersections[BC][X] = (vertices[B][X] + lambda * (vertices[C][X] - vertices[B][X]));
            intersections[BC][Z] = (vertices[B][Z] + lambda * (vertices[C][Z] - vertices[B][Z]));

            // CA
            if (vertices[C][Y] == vertices[A][Y] && vertices[C][Y] == row)
                continue;
            lambda = (vertices[C][Y] == vertices[A][Y]) ? 0 : (row - vertices[C][Y]) / (vertices[A][Y] - vertices[C][Y]);
            intersections[CA][X] = (vertices[C][X] + lambda * (vertices[A][X] - vertices[C][X]));
            intersections[CA][Z] = (vertices[C][Z] + lambda * (vertices[A][Z] - vertices[C][Z]));

            if (isBetween(row, vertices[A][Y], vertices[B][Y]))
            {
                if (isBetween(row, vertices[A][Y], vertices[C][Y]))
                {
                    // std::cout << "AB and CA ";
                    leftIntersection = intersections[AB][X] < intersections[CA][X] ? intersections[AB] : intersections[CA];
                    rightIntersection = intersections[AB][X] < intersections[CA][X] ? intersections[CA] : intersections[AB];
                }
                else
                {
                    // std::cout << "AB and BC ";
                    leftIntersection = intersections[AB][X] < intersections[BC][X] ? intersections[AB] : intersections[BC];
                    rightIntersection = intersections[AB][X] < intersections[BC][X] ? intersections[BC] : intersections[AB];
                }
            }
            else
            {
                // std::cout << "BC and CA ";
                leftIntersection = intersections[BC][X] < intersections[CA][X] ? intersections[BC] : intersections[CA];
                rightIntersection = intersections[BC][X] < intersections[CA][X] ? intersections[CA] : intersections[BC];
            }

            // Intersection Debuggin
            /*
            std::cout << std::fixed << std::setprecision(7) << row << ": " << leftIntersection[X] << " to " << rightIntersection[X] << std::endl;
            */


            // for each pixel
            for (double col = leftIntersection[X]; col <= rightIntersection[X]; col += dx)
            {
                if (col < FAR_PLANE || col > NEAR_PLANE)
                    continue;

                int pixel_x = (int)((col + 1) * screen_Width / 2);
                int pixel_y = (int)(((-row) + 1) * screen_Height / 2);

                //Pixel debuggin
                // std::cout << std::fixed << std::setprecision(7) << "Pixel: " << pixel_x << ", " << pixel_y << std::endl;

                double lambda = (rightIntersection[X] == leftIntersection[X]) ? 0 : (col - leftIntersection[X]) / (rightIntersection[X] - leftIntersection[X]);
                double z = (leftIntersection[Z] + lambda * (rightIntersection[Z] - leftIntersection[Z]));
                z = -z;

                if(z < FAR_PLANE || z > NEAR_PLANE)
                    continue;

                if(z_buffer[pixel_y][pixel_x] > z)
                    continue;    
                

                z_buffer[pixel_y][pixel_x] = z;
                color_buffer[pixel_y][pixel_x][0] = triangles[ct].color[0];
                color_buffer[pixel_y][pixel_x][1] = triangles[ct].color[1];
                color_buffer[pixel_y][pixel_x][2] = triangles[ct].color[2];

            }
        }
        
    }

    
    bitmap_image image(screen_Width, screen_Height);
    for (int row = 0; row < screen_Height; row++)
    {
        for (int col = 0; col < screen_Width; col++)
        {
            image.set_pixel(col, row, color_buffer[row][col][0], color_buffer[row][col][1], color_buffer[row][col][2]);
        }
    }
    image.save_image(output_image);

    std::ofstream output(z_buffer_file_output);
    for(int row = 0; row < screen_Height; row++)
    {
        for(int col = 0; col < screen_Width; col++)
        {
            if(z_buffer[row][col] > FAR_PLANE)
                output << std::fixed << std::setprecision (6) << z_buffer[row][col] << "\t";
        }
        output << std::endl;
    }
    
}
