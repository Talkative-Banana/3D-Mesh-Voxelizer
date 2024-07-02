#include "utils.h"
#include "block.h"
#include <thread>
#include <queue>

#pragma once

class chunk{
private:
    GLuint side;
    GLboolean displaychunk;
    glm::vec3 chunkpos;
public:
    GLuint count;
    GLboolean filled[256][256][256];
    std::vector<GLuint>  indices;
    std::vector<GLfloat> rendervert;

    chunk(GLuint s, glm::vec3 position, GLboolean display);
    ~chunk();

    void Render();
};
