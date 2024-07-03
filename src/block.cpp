#include "Renderer.h"
#include "block.h"

block::block(GLfloat s, glm::vec3 pos, GLboolean solid){
    side = s;
    position = pos;
    is_solid = solid;
    verticies.assign(24, {});
}

block::~block(){}

void block::GenerateVerticies(){
    GLfloat hside = side / 2.0;
    GLuint x = position.x, y = position.y, z = position.z;
    // Vertex Position
    // 24 verticies per block

    // Back Face 0123
    verticies[0] = {x - hside, y - hside, z - hside, 0.86}; // 0
    verticies[1] = {x - hside, y + hside, z - hside, 0.86}; // 1
    verticies[2] = {x + hside, y + hside, z - hside, 0.86}; // 2
    verticies[3] = {x + hside, y - hside, z - hside, 0.86}; // 3

    // Front Face 4567
    verticies[4] = {x - hside, y - hside, z + hside, 0.86}; // 4
    verticies[5] = {x - hside, y + hside, z + hside, 0.86}; // 5
    verticies[6] = {x + hside, y + hside, z + hside, 0.86}; // 6
    verticies[7] = {x + hside, y - hside, z + hside, 0.86}; // 7

    // Left Face 0154
    verticies[8] = {x - hside, y - hside, z - hside, 0.71}; // 0
    verticies[9] = {x - hside, y + hside, z - hside, 0.71}; // 1
    verticies[10] = {x - hside, y + hside, z + hside, 0.71}; // 5
    verticies[11] = {x - hside, y - hside, z + hside, 0.71}; // 4

    // Right Face 7623
    verticies[12] = {x + hside, y - hside, z + hside, 0.71}; // 7
    verticies[13] = {x + hside, y + hside, z + hside, 0.71}; // 6
    verticies[14] = {x + hside, y + hside, z - hside, 0.71}; // 2
    verticies[15] = {x + hside, y - hside, z - hside, 0.71}; // 3

    // Top Face 5126
    verticies[16] = {x - hside, y + hside, z + hside, 0.30}; // 5
    verticies[17] = {x - hside, y + hside, z - hside, 0.30}; // 1
    verticies[18] = {x + hside, y + hside, z - hside, 0.30}; // 2
    verticies[19] = {x + hside, y + hside, z + hside, 0.30}; // 6

    // Bottom Face 0473
    verticies[20] = {x - hside, y - hside, z - hside, 0.30}; // 0
    verticies[21] = {x - hside, y - hside, z + hside, 0.30}; // 4
    verticies[22] = {x + hside, y - hside, z + hside, 0.30}; // 7
    verticies[23] = {x + hside, y - hside, z - hside, 0.30}; // 3
    
}

void block::RenderFace(GLuint face){
    if(face == 0){
        // Need to draw back face
        for(int i = 0; i < 6; i++) indices.push_back(faceindices[0][i]);
    } else if(face == 1){
        // Need to draw front face
        for(int i = 0; i < 6; i++) indices.push_back(faceindices[1][i]);
    } else if(face == 2){
        // Need to draw left face
        for(int i = 0; i < 6; i++) indices.push_back(faceindices[2][i]);
    } else if(face == 3){
        // Need to draw right face
        for(int i = 0; i < 6; i++) indices.push_back(faceindices[3][i]);
    } else if(face == 4){
        // Need to draw top face
        for(int i = 0; i < 6; i++) indices.push_back(faceindices[4][i]);
    } else{
        // Need to draw bottom face
        for(int i = 0; i < 6; i++) indices.push_back(faceindices[5][i]);
    }
}

void block::Render(GLuint mask){
    if(!is_solid) return;
    GenerateVerticies();
    for(int i = 0; i < 24; i++){
        // Texture-Center-Position
        for(int j = 0; j < 4; j++){
            rendervert.push_back(verticies[i][j]);
        }
    }

    GLuint idx = 0;
    while(mask != 0){
        if(mask&1) block::RenderFace(idx);
        mask /= 2, idx++;
    }
}