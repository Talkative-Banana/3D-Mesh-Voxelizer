#include "Renderer.h"
#include "block.h"

block::block(GLuint s, glm::vec3 pos, GLboolean solid){
    side = s;
    position = pos;
    is_solid = solid;
}

block::~block(){}

void block::GenerateVerticies(){
    GLfloat hside = side / 2;
    GLuint x = position.x, y = position.y, z = position.z;
    // Vertex Position
    // 24 verticies per block

    // Back Face 0123
    verticies.push_back({x - hside, y - hside, z - hside, 0.86}); // 0
    // verticies.push_back({x - hside, y - hside, z - hside, x, y, z}); // 0 0
    verticies.push_back({x - hside, y + hside, z - hside, 0.86}); // 1
    // verticies.push_back({x - hside, y + hside, z - hside, x, y, z}); // 1 1
    verticies.push_back({x + hside, y + hside, z - hside, 0.86}); // 2
    // verticies.push_back({x + hside, y + hside, z - hside, x, y, z}); // 2 2
    verticies.push_back({x + hside, y - hside, z - hside, 0.86}); // 3
    // verticies.push_back({x + hside, y - hside, z - hside, x, y, z}); // 3 3

    // Front Face 4567
    verticies.push_back({x - hside, y - hside, z + hside, 0.86}); // 4
    // verticies.push_back({x - hside, y - hside, z + hside, x, y, z}); // 4 4
    verticies.push_back({x - hside, y + hside, z + hside, 0.86}); // 5
    // verticies.push_back({x - hside, y + hside, z + hside, x, y, z}); // 5 5
    verticies.push_back({x + hside, y + hside, z + hside, 0.86}); // 6
    // verticies.push_back({x + hside, y + hside, z + hside, x, y, z}); // 6 6
    verticies.push_back({x + hside, y - hside, z + hside, 0.86}); // 7
    // verticies.push_back({x + hside, y - hside, z + hside, x, y, z}); // 7 7

    // Left Face 0154
    verticies.push_back({x - hside, y - hside, z - hside, 0.71}); // 0
    // verticies.push_back({x - hside, y - hside, z - hside, x, y, z}); // 0 8
    verticies.push_back({x - hside, y + hside, z - hside, 0.71}); // 1
    // verticies.push_back({x - hside, y + hside, z - hside, x, y, z}); // 1 9
    verticies.push_back({x - hside, y + hside, z + hside, 0.71}); // 5
    // verticies.push_back({x - hside, y + hside, z + hside, x, y, z}); // 5 10
    verticies.push_back({x - hside, y - hside, z + hside, 0.71}); // 4
    // verticies.push_back({x - hside, y - hside, z + hside, x, y, z}); // 4 11

    // Right Face 7623
    verticies.push_back({x + hside, y - hside, z + hside, 0.71}); // 7
    // verticies.push_back({x + hside, y - hside, z + hside, x, y, z}); // 7 12
    verticies.push_back({x + hside, y + hside, z + hside, 0.71}); // 6
    // verticies.push_back({x + hside, y + hside, z + hside, x, y, z}); // 6 13
    verticies.push_back({x + hside, y + hside, z - hside, 0.71}); // 2
    // verticies.push_back({x + hside, y + hside, z - hside, x, y, z}); // 2 14
    verticies.push_back({x + hside, y - hside, z - hside, 0.71}); // 3
    // verticies.push_back({x + hside, y - hside, z - hside, x, y, z}); // 3 15

    // Top Face 5126
    verticies.push_back({x - hside, y + hside, z + hside, 0.30}); // 5
    // verticies.push_back({x - hside, y + hside, z + hside, x, y, z}); // 5 16
    verticies.push_back({x - hside, y + hside, z - hside, 0.30}); // 1
    // verticies.push_back({x - hside, y + hside, z - hside, x, y, z}); // 1 17
    verticies.push_back({x + hside, y + hside, z - hside, 0.30}); // 2
    // verticies.push_back({x + hside, y + hside, z - hside, x, y, z}); // 2 18
    verticies.push_back({x + hside, y + hside, z + hside, 0.30}); // 6
    // verticies.push_back({x + hside, y + hside, z + hside, x, y, z}); // 6 19

    // Bottom Face 0473
    verticies.push_back({x - hside, y - hside, z - hside, 0.30}); // 0
    // verticies.push_back({x - hside, y - hside, z - hside, x, y, z}); // 0 20
    verticies.push_back({x - hside, y - hside, z + hside, 0.30}); // 4
    // verticies.push_back({x - hside, y - hside, z + hside, x, y, z}); // 4 21
    verticies.push_back({x + hside, y - hside, z + hside, 0.30}); // 7
    // verticies.push_back({x + hside, y - hside, z + hside, x, y, z}); // 7 22
    verticies.push_back({x + hside, y - hside, z - hside, 0.30}); // 3
    // verticies.push_back({x + hside, y - hside, z - hside, x, y, z}); // 3 23
    
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