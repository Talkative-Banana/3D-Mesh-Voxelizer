#include "utils.h"
#include "block.h"
#pragma once

class chunk{
private:
    GLuint side;
    GLboolean displaychunk;
    glm::vec3 chunkpos;
    block *blocks[256][256][256];
public:
    GLuint count;
    GLuint filled[256][256][256];
    std::vector<GLuint>  indices;
    std::vector<GLfloat> rendervert;

    chunk(GLuint s, glm::vec3 position, GLboolean display);
    ~chunk();

    void Render();
    GLuint RenderFace(std::vector<GLint> position);
    GLboolean isSolid(std::vector<GLint> postion);
};
