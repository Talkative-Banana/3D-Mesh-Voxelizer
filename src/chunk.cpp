#include "Renderer.h"
#include "chunk.h"

chunk::chunk(GLuint s, glm::vec3 position, GLboolean display){
    side = s;
    count = 0;
    chunkpos = position;
    displaychunk = display;
    memset(filled, 0, sizeof filled);
}

chunk::~chunk(){}

 GLboolean isSolid(std::vector<GLint> position, GLboolean (&filled)[256][256][256]){
    if((position[0] >= 0) && (position[0] < 256) && (position[1] >= 0) && (position[1] < 256) && (position[2] >= 0) && (position[2] < 256)){
        return filled[position[0]][position[1]][position[2]];
    }
    return false;
}
// k blue i red j green
// ctrl x -> red facing me

GLuint RenderFace(std::vector<GLint> position, GLboolean (&filled)[256][256][256]){
    // 1 -> back face: 2 -> front face: 3 -> left face: 4 -> right face: 5 -> top face: 6 -> bottom face
    GLuint mask = 0;
    std::vector<GLint> tmp = position;
    for(GLuint face = 1; face <= 6; face++){
        if(face == 1){
            // No Need to draw back face if block behind is solid
            tmp[2] -= 1;
            if(!isSolid(tmp, filled)) mask |= (1 << (face - 1));
            tmp[2] += 1;
        } else if(face == 2){
            // No Need to draw front face if block in front is solid
            tmp[2] += 1;
            if(!isSolid(tmp, filled)) mask |= (1 << (face - 1));
            tmp[2] -= 1;
        } else if(face == 3){
            // No Need to draw left face if block in left is solid
            tmp[0] -= 1;
            if(!isSolid(tmp, filled)) mask |= (1 << (face - 1));
            tmp[0] += 1;
        } else if(face == 4){
            // No Need to draw right face if block in right is solid
            tmp[0] += 1;
            if(!isSolid(tmp, filled)) mask |= (1 << (face - 1));
            tmp[0] -= 1;
        } else if(face == 5){
            // No Need to draw top face if block on top is solid
            tmp[1] += 1;
            if(!isSolid(tmp, filled)) mask |= (1 << (face - 1));
            tmp[1] -= 1;
        } else if(face == 6){
            // No Need to draw bottom face if block on bottom is solid
            tmp[1] -= 1;
            if(!isSolid(tmp, filled)) mask |= (1 << (face - 1));
            tmp[1] += 1;
        }
    }
    return mask;
}

void RenderSlab(int j, int side, GLboolean (&filled)[256][256][256], std::vector<std::tuple<std::vector<GLfloat>, std::vector<GLuint>, GLuint, GLuint>>& Data){
    std::vector<GLfloat> slabrendervert;
    std::vector<GLuint> slabindices;
    GLuint idx = 0, cnt = 0;
    for(int i = 0; i < 256; i++){
        for(int k = 0; k < 256; k++){
            // filled[i][j][k] = 1;
            if(!filled[i][j][k]) continue;
            glm::vec3 ofs = {i * side, j * side, k * side};
            std::vector<GLint> Idx = {i, j, k};
            GLuint mask = RenderFace(Idx, filled);
            block* bl = new block(side, ofs, true); bl->Render(mask);
            std::vector<GLfloat> blockrendervert = bl->rendervert;
            std::vector<GLuint> blockindices = bl->indices;
            for(auto x : blockrendervert) slabrendervert.push_back(x);
            for(auto x : blockindices) slabindices.push_back(idx + x);
            delete bl;
            idx += 24, cnt++;
        }
    }
    Data[j] = {slabrendervert, slabindices, cnt, idx};
}


void chunk::Render(){
    if(!displaychunk) return;

    std::vector<std::thread> Threads;
    std::vector<std::tuple<std::vector<GLfloat>, std::vector<GLuint>, GLuint, GLuint>> Data(256);


    for(int j = 0; j < 256; j++){
        std::thread newthread(RenderSlab, j, side, std::ref(filled), std::ref(Data));
        Threads.push_back(std::move(newthread));
    }

    for(int i = 0; i < 256; i++) Threads[i].join();

    GLuint _I = 0;
    for(int i = 0; i < 256; i++){
        auto &[arr1, arr2, c, I] = Data[i];
        for(int j = 0; j < arr1.size(); j++) rendervert.push_back(arr1[j]);
        for(int j = 0; j < arr2.size(); j++) indices.push_back(arr2[j] + _I);
        count += c; _I += I;
    }
}