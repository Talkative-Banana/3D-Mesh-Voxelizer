#include "utils.h"
#pragma once

class block {
private:
    void GenerateVerticies();
public:
    GLfloat side;
    glm::vec3 position;
    GLboolean is_solid;
    std::vector<std::vector<GLfloat>> verticies;
    std::vector<GLfloat> rendervert;
    std::vector<GLuint> indices;
    std::vector<std::vector<GLuint>> faceindices = {{2, 3, 0, 2, 0, 1}, // Back
                                                    {7, 6, 5, 7, 5, 4}, // Front
                                                    {11, 10, 9, 11, 9, 8}, // Left
                                                    {15, 14, 13, 15, 13, 12}, // Right
                                                    {19, 18, 17, 19, 17, 16}, // Top
                                                    {23, 22, 21, 23, 21, 20}};// Bottom


    block(GLfloat s, glm::vec3 pos, GLboolean solid);
    ~block();

    void Render(GLuint mask);
    void RenderFace(GLuint face);
};