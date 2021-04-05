//
// Created by avram on 5.4.21..
//

#include <common.h>

std::string readFileContents(std::string path) {
    std::ifstream in(path);
    std::stringstream buffer;
    buffer << in.rdbuf();
    return buffer.str();
}


float frandom(float min, float max) {
    return min + (float)(rand()) / ((float)(RAND_MAX/(max - min)));
}