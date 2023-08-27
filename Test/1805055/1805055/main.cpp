#include "header.h"
#include "stringArray.h"
#include "stage1.h"
#include "stage2.h"
#include "stage3.h"
#include "zbuffer.h"

int main(){
    std::ifstream scene_file("scene.txt");
    std::ifstream config_file("config.txt");
    auto lines = splitLines(scene_file);
    scene_file.close();
    auto config_lines = splitLines(config_file);
    config_file.close();

    std::vector<std::string> cameraInformation;
    std::copy(lines.begin(), lines.begin() + 3, std::back_inserter(cameraInformation));

    std::string viewBox = lines[3];

    std::vector<std::string> modelTranformationCommand;
    std::copy(lines.begin() + 4, lines.end(), std::back_inserter(modelTranformationCommand));
    
    modelTransformation(modelTranformationCommand, "stage1.txt");

    scene_file = std::ifstream("stage1.txt");
    lines = splitLines(scene_file);
    scene_file.close();

    viewTransformation(cameraInformation, lines, "stage2.txt");

    scene_file = std::ifstream("stage2.txt");
    lines = splitLines(scene_file);
    scene_file.close();

    projectionTransformation(viewBox, lines, "stage3.txt");    

    scene_file = std::ifstream("stage3.txt");
    lines = splitLines(scene_file);
    scene_file.close();
    int screen_Width, screen_Height;
    std::stringstream ss(config_lines[0]);
    ss >> screen_Width >> screen_Height;

    zBuffer(lines, screen_Width, screen_Height, "z_buffer.txt", "out.bmp");
}