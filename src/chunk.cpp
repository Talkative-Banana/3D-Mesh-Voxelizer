#include "Renderer.h"
#include "chunk.h"

chunk::chunk(GLfloat s, const glm::vec3 position, GLboolean display){
    side = s;
    count = 0;
    BIndex = {0, 511, 0, 511, 0, 511}; // minx maxx miny maxy minz maxz
    chunkpos = position;
    displaychunk = display;
    memset(filled, 0, sizeof filled);
}

chunk::~chunk(){}

static GLboolean isSolid(const std::vector<GLint> position, const GLboolean (&filled)[512][512][512]){
    if((position[0] >= 0) && (position[0] < 512) && (position[1] >= 0) && (position[1] < 512) && (position[2] >= 0) && (position[2] < 512)){
        return filled[position[0]][position[1]][position[2]];
    }
    return false;
}
// k blue i red j green
// ctrl x -> red facing me

static GLuint RenderFace(const std::vector<GLint> position, const GLboolean (&filled)[512][512][512]){
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

static std::mutex s_mutex;

static void RenderSlab(int j, GLfloat side, const GLboolean (&filled)[512][512][512], std::vector<int> BIndex, std::vector<GLfloat>* Rendervert, std::vector<GLuint>* Index, GLuint* count, GLuint* I){
    std::vector<GLfloat> slabrendervert;
    std::vector<GLuint> slabindices;
    GLuint idx = 0, cnt = 0;
    for(int i = BIndex[1]; i <= BIndex[0]; i++){
        for(int k = BIndex[5]; k <= BIndex[4]; k++){
            // filled[i][j][k] = 1;
            if(!filled[i][j][k]) continue;
            glm::vec3 ofs = {i * side, j * side, k * side};
            std::vector<GLint> Idx = {i, j, k};
            GLuint mask = RenderFace(Idx, filled);
            block bl = block(side, ofs, true); bl.Render(mask);
            std::vector<GLfloat> blockrendervert = bl.rendervert;
            std::vector<GLuint> blockindices = bl.indices;
            for(auto x : blockrendervert) slabrendervert.push_back(x);
            for(auto x : blockindices) slabindices.push_back(idx + x);
            idx += 24, cnt++;
        }
    }
    std::lock_guard<std::mutex> lock(s_mutex);
    for(int i = 0; i < slabrendervert.size(); i++) Rendervert->push_back(slabrendervert[i]);
    for(int i = 0; i < slabindices.size(); i++) Index->push_back(slabindices[i] + *I);
    *count += cnt; *I += idx;
}

void chunk::SetBindex(){
    for(int i = 0; i < 512; i++){
        for(int j = 0; j < 512; j++){
            for(int k = 0; k < 512; k++){
                if(!filled[i][j][k]) continue;
                BIndex[0] = max(BIndex[0], i); BIndex[2] = max(BIndex[2], j); BIndex[4] = max(BIndex[4], k);
                BIndex[1] = min(BIndex[1], i); BIndex[3] = min(BIndex[3], j); BIndex[5] = min(BIndex[5], k);
            }
        }
    }
}

void chunk::Render(){
    if(!displaychunk) return;
    std::vector<std::future<void>> m_Futures;
    GLuint I = 0;
    SetBindex();
    for(int j = BIndex[3]; j <= BIndex[2]; j++) m_Futures.push_back(std::async(std::launch::async, RenderSlab, j, side, std::cref(filled), BIndex, &rendervert, &indices, &count, &I));
}