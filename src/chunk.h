#include "utils.h"
#include "block.h"
#include <future>
#include <mutex>
#include <queue>

#pragma once

class chunk{
private:
    GLfloat side;
    GLboolean displaychunk;
    glm::vec3 chunkpos;
public:
    GLuint count;
    GLboolean filled[512][512][512];
    std::vector<int> BIndex;
    std::vector<GLuint>  indices;
    std::vector<GLfloat> rendervert;

    chunk(GLfloat s, glm::vec3 position, GLboolean display);
    ~chunk();

    void Render();
    void SetBindex();
};
